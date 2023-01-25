#include "km271_communication_components.h"
#include "3964r.h"
#include "km271_helpers.h"
#include "esphome/core/hal.h"


namespace esphome {
namespace KM271 {

static const char * TAG = "km271";

const uint8_t data_type_date_time = 0x01;
const uint8_t data_type_heating_circuit_1 = 0x07;
const uint8_t data_type_heating_circuit_2 = 0x08;
const uint8_t data_type_warm_water = 0x0c;
const uint8_t data_type_boiler = 0x10;
const uint8_t data_type_hc1_program = 0x11;
const uint8_t data_type_hc2_program = 0x12;
const uint8_t keep = 0x65;

uint8_t convertFloatToByte(float value)
{
    return (uint8_t)(value + 0.5);
}

CommunicationComponent::CommunicationComponent(bool writable):
    writable(writable),
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

bool CommunicationComponent::isWritable() const
{
    return writable;
}


BuderusParamSwitch::BuderusParamSwitch(): CommunicationComponent(true)
{

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
    CommunicationComponent(true),
    hasPendingWriteRequest(false)
{
}

float limitValueToRange(float value, float minimum, float maximum)
{
    if(value < minimum) {
        return minimum;
    }
    if (value > maximum) {
        return maximum;
    }
    return value;
}


void BuderusParamNumber::control(float value)
{
    // Do not write directly, but instead wait until the value does not change for some time and write then.
    // This is to avoid writing to the storage of the control unit each time the user clicks on the up arrow
    this->pendingWriteValue = value;
    this->hasPendingWriteRequest = true;
    this->lastWriteRequest = millis();
}

void BuderusParamNumber::sendAndConfirm(const uint8_t * message, uint8_t messageLength, float valueToConfirm)
{
    if(writer->enqueueTelegram(message, messageLength)) {
        this->hasPendingWriteRequest = false;
        publish_state(valueToConfirm);
    }
}

void BuderusParamNumber::buildTelegramSendAndConfirm(uint8_t telegramDataType, uint8_t telegramOffset, uint8_t telegramValuePosition, uint8_t telegramValue, float valueToConfirm)
{
    uint8_t message[] = { telegramDataType, telegramOffset, keep, keep, keep, keep, keep, keep};
    message[telegramValuePosition+2] = telegramValue;
    sendAndConfirm(message, sizeof(message), valueToConfirm);
}

enum TelegramBuilderRule
{
    UseSpecialBuilder, // use hard-coded behavior
    UseSelectValue, // use the select builder
    UseFloatValue,  // use the write value directly as byte
    UseFloatValueTimesTwo, // use the write value times two as byte
};

struct TelegramBuilderConfiguration
{
    TransmissionParameter transmissionParameter;
    TelegramBuilderRule builderRule;
    float minValue;
    float maxValue;
    uint8_t maxSelectIndex;
    uint8_t telegramDataType;
    uint8_t telegramOffset;
    uint8_t telegramValuePosition;
};

static const struct TelegramBuilderConfiguration telegramBuilderConfiguration[] = {
    {config_heating_circuit_1_room_target_temperature_night,    UseFloatValueTimesTwo,  10, 30, 0, data_type_heating_circuit_1,     0x00, 2},
    {config_heating_circuit_1_room_target_temperature_day,      UseFloatValueTimesTwo,  10, 30, 0, data_type_heating_circuit_1,     0x00, 3},
    {config_heating_circuit_1_holiday_target_temperature,       UseFloatValueTimesTwo,  10, 30, 0, data_type_heating_circuit_1,     0x00, 5},
    {config_heating_circuit_1_flow_temperature_max,             UseFloatValue,          20, 90, 0, data_type_heating_circuit_1,     0x0e, 2},
    {config_heating_circuit_1_design_temperature,               UseFloatValue,          30, 90, 0, data_type_heating_circuit_1,     0x0e, 4},
//    {config_heating_circuit_1_outdoor_switch_temperature,       UseFloatValue,          -20, 10, 0, data_type_heating_circuit_1,    0x15, 2}, // handled by config_frost_switch_temperature
    {config_heating_circuit_1_room_temperature_offset,          UseFloatValueTimesTwo,  -5, 5, 0, data_type_heating_circuit_1,      0x31, 3},
    {config_heating_circuit_1_holiday_days,                     UseFloatValue,          0, 99, 0, data_type_hc1_program,            0x00, 3},

    {config_heating_circuit_2_room_target_temperature_night,    UseFloatValueTimesTwo,  10, 30, 0, data_type_heating_circuit_2,     0x00, 2},
    {config_heating_circuit_2_room_target_temperature_day,      UseFloatValueTimesTwo,  10, 30, 0, data_type_heating_circuit_2,     0x00, 3},
    {config_heating_circuit_2_holiday_target_temperature,       UseFloatValueTimesTwo,  10, 30, 0, data_type_heating_circuit_2,     0x00, 5},
    {config_heating_circuit_2_flow_temperature_max,             UseFloatValue,          20, 90, 0, data_type_heating_circuit_2,     0x0e, 2},
    {config_heating_circuit_2_design_temperature,               UseFloatValue,          30, 90, 0, data_type_heating_circuit_2,     0x0e, 4},
//    {config_heating_circuit_2_outdoor_switch_temperature,       UseFloatValue,          -20, 10, 0, data_type_heating_circuit_2,    0x15, 2}, // handled by config_frost_switch_temperature
    {config_heating_circuit_2_room_temperature_offset,          UseFloatValueTimesTwo,  -5, 5, 0, data_type_heating_circuit_2,      0x31, 3},
    {config_heating_circuit_2_holiday_days,                     UseFloatValue,          0, 99, 0, data_type_hc2_program,            0x00, 3},

    {config_ww_temperature,                                     UseFloatValue,          30, 60, 0, data_type_warm_water,            0x07, 3},
    {config_frost_switch_temperature,                           UseFloatValue,          -20, 10, 0, data_type_heating_circuit_1,    0x31, 5},
//    {config_blr_temperature_max,                                UseFloatValue,          70, 99, 0, data_type_boiler,                0x00, 0}, //qs fake telegramOffset and telegramValuePosition
//    {config_blr_pump_turn_on_temperature,                       UseFloatValue,          15, 60, 0, data_type_boiler,                0x00, 0}, //qs fake telegramOffset and telegramValuePosition
//    {config_time_offset,                                        UseFloatValueTimesTwo,  -5, 5, 0,  data_type_boiler,                0x00, 0}, //qs fake telegramOffset and telegramValuePosition

    {config_heating_circuit_1_operation_mode,                   UseSelectValue,           0,  0,  2, data_type_heating_circuit_1, 0x00, 4},
    {config_heating_circuit_1_lowering_type,                    UseSelectValue,           0,  0,  3, data_type_heating_circuit_1, 0x1c, 1},
    {config_heating_circuit_1_heating_system_type,              UseSelectValue,           0,  0,  1, data_type_heating_circuit_1, 0x1c, 2},
    {config_heating_circuit_1_heating_program,                  UseSelectValue,           0,  0,  8, data_type_hc1_program,       0x00, 0},

    {config_heating_circuit_2_operation_mode,                   UseSelectValue,           0,  0,  2, data_type_heating_circuit_2, 0x00, 4},
    {config_heating_circuit_2_lowering_type,                    UseSelectValue,           0,  0,  3, data_type_heating_circuit_2, 0x1c, 1},
    {config_heating_circuit_2_heating_system_type,              UseSelectValue,           0,  0,  3, data_type_heating_circuit_2, 0x1c, 2},
    {config_heating_circuit_2_heating_program,                  UseSelectValue,           0,  0,  8, data_type_hc2_program,       0x00, 0},

    {config_ww_operation_mode,                                  UseSelectValue,           0,  0,  2, data_type_warm_water,        0x0e, 0},
    {config_ww_circular_pump_interval,                          UseSelectValue,           0,  0,  7, data_type_warm_water,        0x0e, 5},
    {config_summer_winter_switch_temperature,                   UseSelectValue,           0,  0, 31, data_type_heating_circuit_1, 0x00, 1},
//    {config_blr_building_type,                                  UseSelectValue,           0,  0, 2,  data_type_boiler,            0x00, 0}, //qs fake telegramOffset and telegramValuePosition
};


const struct TelegramBuilderConfiguration * findTelegramBuilderConfiguration(TransmissionParameter transmissionParameter)
{
    for(int i = 0; i < lenof(telegramBuilderConfiguration); i++) {
        const TelegramBuilderConfiguration * conf = &telegramBuilderConfiguration[i];
        if(conf->transmissionParameter == transmissionParameter ) {
            return conf;
        }
    }
    return nullptr;
}


void BuderusParamNumber::loop()
{
    uint32_t writeConsolidationPeriod = 1000;

    if (this->hasPendingWriteRequest) {
        uint32_t now = millis();
        if (now - lastWriteRequest > writeConsolidationPeriod) {
            /** @todo use a map */
            /** @todo perform lookup only once on startup */
            /** @todo convert remaineder */
            const struct TelegramBuilderConfiguration * bc = findTelegramBuilderConfiguration(transmissionParameter);
            if(bc && bc->builderRule == UseFloatValue) {
                const float limitedValue = limitValueToRange(this->pendingWriteValue, bc->minValue, bc->maxValue);
                buildTelegramSendAndConfirm(bc->telegramDataType, bc->telegramOffset, bc->telegramValuePosition,
                                            convertFloatToByte(limitedValue), limitedValue);
            }  else if(bc && bc->builderRule == UseFloatValueTimesTwo) {
                const float limitedValue = limitValueToRange(this->pendingWriteValue, bc->minValue, bc->maxValue);
                buildTelegramSendAndConfirm(bc->telegramDataType, bc->telegramOffset, bc->telegramValuePosition,
                                            convertFloatToByte(limitedValue * 2), limitedValue);
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
    CommunicationComponent(false),
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

BuderusParamSelect::BuderusParamSelect(): CommunicationComponent(true)
{

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
    const size_t mapping_idx = std::distance(mappings.cbegin(), it);
    const auto selectValue = this->at(mapping_idx);
    this->publish_state(selectValue.value());
}

void BuderusParamSelect::sendAndConfirm(const uint8_t * message, uint8_t messageLength, const std::string & value)
{
    if(writer->enqueueTelegram(message, messageLength)) {
        publish_state(value);
    }
}

void BuderusParamSelect::buildTelegramSendAndConfirm(uint8_t telegramDataType, uint8_t telegramOffset, uint8_t telegramValuePosition,
                                                     uint8_t selectIndex, const std::string &value)
{
    uint8_t message[] = { telegramDataType, telegramOffset, keep, keep, keep, keep, keep, keep};
    message[telegramValuePosition+2] = selectIndex;
    sendAndConfirm(message, sizeof(message), value);
}



void BuderusParamSelect::control(const std::string &value) {
    const auto idx = this->index_of(value);

    if (idx.has_value()) {
        uint8_t numericValue= this->mappings.at(idx.value());

        const struct TelegramBuilderConfiguration * bc = findTelegramBuilderConfiguration(transmissionParameter);
        if(bc && bc->builderRule == UseSelectValue) {
            if (numericValue > bc->maxSelectIndex) {
                ESP_LOGE(TAG, "Invalid select value for transmission parameter %d received: %d", transmissionParameter, numericValue);
                return;
            }
            buildTelegramSendAndConfirm(bc->telegramDataType, bc->telegramOffset, bc->telegramValuePosition, numericValue, value);
        } else {
            ESP_LOGE(TAG, "No write configuration for tranmssion id %d found", transmissionParameter);
        }
    } else {
        ESP_LOGE(TAG, "No mapping for select value %s found", value.c_str());
    }
}

FirmwareVersionSensor::FirmwareVersionSensor(): CommunicationComponent(false), major_known(false), minor_known(false)
{

}


void FirmwareVersionSensor::handleReceivedUnsignedValue(uint16_t sensorTypeParam, uint32_t value)
{
    ESP_LOGD(TAG, "Received value for st param %d: %d", sensorTypeParam, value);

    const int valueIndex = sensorTypeParam & 0x0f;

    if (valueIndex == 0) {
        major = value;
        major_known = true;
    } else if (valueIndex == 1) {
        minor = value;
        minor_known = true;
    } else {
        ESP_LOGE(TAG, "Invalid sensor type param: %d", sensorTypeParam);
        return;
    }

    if(major_known && minor_known) {
        char result[20];
        snprintf(result, sizeof(result), "%d.%d", major, minor);
        publish_state(result);
    }
}


}
}
