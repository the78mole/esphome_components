#include "km271_communication_components.h"
#include "3964r.h"
#include "esphome/core/hal.h"


namespace esphome {
namespace KM271 {

static const char * TAG = "km271";


CommunicationComponent::CommunicationComponent():
    writer(nullptr)
{

}

void CommunicationComponent::setupWriting(Writer3964R *writer, TransmissionParameter transmissionParameter)
{
    this->writer = writer;
    this->transmissionParameter = transmissionParameter;
}


void CommunicationComponent::handleReceivedSignedValue(uint16_t sensorTypeParam, int32_t value)
{
    ESP_LOGW(TAG, "handleReceivedSignedValue NI for transmission parameter %d", transmissionParameter);
}

void CommunicationComponent::handleReceivedUnsignedValue(uint16_t sensorTypeParam, uint32_t value)
{
    ESP_LOGW(TAG, "handleReceivedUnsignedValue NI for transmission parameter %d", transmissionParameter);
}

void CommunicationComponent::handleReceivedFloatValue(uint16_t sensorTypeParam, float value)
{
    ESP_LOGW(TAG, "handleReceivedFloatValue NI for for transmission parameter %d", transmissionParameter);
}


void BuderusParamSwitch::handleReceivedUnsignedValue(uint16_t sensorTypeParam, uint32_t value)
{
    publish_state(value);
}

void BuderusParamSwitch::write_state(bool state)
{
    ESP_LOGE(TAG, "No write configuration for transmission %d found", transmissionParameter);
}

BuderusParamNumber::BuderusParamNumber():
    hasPendingWriteRequest(false)
{
}


void BuderusParamNumber::control(float value)
{
    if(transmissionParameter == config_ww_temperature) {
        float target_temperature = value;
        if (target_temperature < 30) {
            target_temperature = 30;
        } else if (target_temperature > 60) {
            target_temperature = 60;
        }

        // do not write directly, but instead wait until the value does not change for some time and write then
        // this is to avoid writing to the heater each time the user clicks on the up arrow
        this->hasPendingWriteRequest = true;
        this->pendingWriteValue = target_temperature;
        this->lastWriteRequest = millis();

    } else if(transmissionParameter == config_heating_circuit_1_design_temperature) {
        float target_temperature = value;
        if (target_temperature < 30) {
            target_temperature = 30;
        } else if (target_temperature > 90) {
            target_temperature = 90;
        }

        // do not write directly, but instead wait until the value does not change for some time and write then
        // this is to avoid writing to the heater each time the user clicks on the up arrow
        this->hasPendingWriteRequest = true;
        this->pendingWriteValue = target_temperature;
        this->lastWriteRequest = millis();
    } else {
        ESP_LOGE(TAG, "No write configuration for number transmission parameter %d found", transmissionParameter);
    }
}

void BuderusParamNumber::loop()
{
    uint32_t writeConsolidationPeriod = 1000;
    const uint8_t keep = 0x65;
    const uint8_t data_type_warm_water = 0x0c;
    const uint8_t data_type_heating_circuit_1 = 0x07;

    if (this->hasPendingWriteRequest) {
        uint32_t now = millis();
        if (now - lastWriteRequest > writeConsolidationPeriod) {

            if (transmissionParameter == config_ww_temperature) {
              const uint8_t message[] = { data_type_warm_water, 0x07, keep, keep, keep, (uint8_t)this->pendingWriteValue, keep, keep};
                if(writer->enqueueTelegram(message, 8)) {
                    this->hasPendingWriteRequest = false;
                    publish_state(this->pendingWriteValue);

                }
            } else if(transmissionParameter == config_heating_circuit_1_design_temperature) {
                const uint8_t message[] = { data_type_heating_circuit_1, 0x0e, keep, keep, keep, keep, (uint8_t)this->pendingWriteValue, keep};
                  if(writer->enqueueTelegram(message, 8)) {
                      this->hasPendingWriteRequest = false;
                      publish_state(this->pendingWriteValue);

                  }
            } else {
                ESP_LOGE(TAG, "No support for writing transmission parameter %d", transmissionParameter);
                this->hasPendingWriteRequest = false;
            }
        }
    }
}

void BuderusParamNumber::handleReceivedUnsignedValue(uint16_t sensorTypeParam, uint32_t value)
{
    publish_state(value);
}

void BuderusParamNumber::handleReceivedSignedValue(uint16_t sensorTypeParam, int32_t value)
{
    publish_state(value);
}


void BuderusParamNumber::handleReceivedFloatValue(uint16_t sensorTypeParam, float value)
{
    publish_state(value);
}


MultiParameterUnsignedIntegerAssembler::MultiParameterUnsignedIntegerAssembler(esphome::sensor::Sensor *targetSensor):
    sensor(targetSensor),
    component_known{false, false, false}
{

}

void MultiParameterUnsignedIntegerAssembler::handleReceivedUnsignedValue(uint16_t sensorTypeParam, uint32_t value)
{
    ESP_LOGD(TAG, "Received value for st param %d: %d", sensorTypeParam, value);

    int valueIndex = sensorTypeParam & 0x0f;
    if (valueIndex > 2) {
        ESP_LOGE(TAG, "Invalid sensor type param: %d", sensorTypeParam);
        return;
    }
    components[valueIndex] = value;
    component_known[valueIndex] = true;
    if (valueIndex != 0) { // only update the sensor value on lsb updates to avoid jumps
       return;
    }


    bool all_components_known = component_known[0] && component_known[1] && component_known[2];
    if (all_components_known) {
       uint32_t result = (((components[2] << 8) + components[1]) << 8 )  + components[0];
       ESP_LOGD(TAG, "Assembling %d %d %d to %d", components[0], components[1], components[2], result);
       sensor->publish_state(result);
    }
}

void BuderusParamSelect::setSelectMappings(std::vector<uint8_t> mappings)
{
    this->mappings = std::move(mappings);
}

void BuderusParamSelect::handleReceivedUnsignedValue(uint16_t sensorTypeParam, uint32_t value)
{
    auto it = std::find(mappings.cbegin(), mappings.cend(), value);
    if (it == mappings.end()) {
        ESP_LOGE(TAG, "Invalid value %u received for select of transmission parameter %d", value, transmissionParameter);
        return;
    }
    size_t mapping_idx = std::distance(mappings.cbegin(), it);
    auto selectValue = this->at(mapping_idx);
    this->publish_state(selectValue.value());
}

void BuderusParamSelect::control(const std::string &value) {

    const uint8_t keep = 0x65;
    const uint8_t data_type_warm_water = 0x0c;
    const uint8_t data_type_heating_circuit_1 = 0x07;

    auto idx = this->index_of(value);

    if (idx.has_value()) {
        uint8_t numericValue= this->mappings.at(idx.value());
        if (transmissionParameter == config_heating_circuit_1_operation_mode) {
            if (numericValue > 2) {
                ESP_LOGE(TAG, "Invalid select value for transmission parameter %d received: %d", transmissionParameter, numericValue);
                return;
            }

            const uint8_t message[] = { data_type_heating_circuit_1, 0x00, keep, keep, keep, keep, (uint8_t )numericValue, keep};
            writer->enqueueTelegram(message, 8);
            publish_state(value); // confirm for now without waiting for an ack from the heater
        } else if (transmissionParameter == config_ww_operation_mode) {
            if (numericValue > 2) {
                ESP_LOGE(TAG, "Invalid select value for transmission parameter %d received: %d", transmissionParameter, numericValue);
                return;
            }

            const uint8_t message[] = { data_type_warm_water, 0x0e, (uint8_t)numericValue, keep, keep, keep, keep, keep};
            writer->enqueueTelegram(message, 8);
            publish_state(value); // confirm for now without waiting for an ack from the heater
        } else {
            ESP_LOGE(TAG, "No write configuration for tranmssion id %d found", transmissionParameter);
        }
    } else {
        ESP_LOGE(TAG, "No mapping for select value %s found", value.c_str());
    }
}

}

}
