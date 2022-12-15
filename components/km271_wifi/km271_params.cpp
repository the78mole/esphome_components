#include "km271_params.h"
#include "esphome/core/log.h"
#include "esphome/core/util.h"
#include "esphome/core/hal.h"
#include <stdint.h>
#include "3964r.h"

namespace esphome {
namespace KM271 {

static const char *const TAG = "BPARM";

BuderusValueHandler::BuderusValueHandler(const t_Buderus_R2017_ParamDesc* paramDesc, esphome::sensor::Sensor *sensor):
    paramDesc(paramDesc),
    sensor(sensor),
    binarySensor(nullptr),
    switch_(nullptr),
    number(nullptr)
{

}

BuderusValueHandler::BuderusValueHandler(const t_Buderus_R2017_ParamDesc* paramDesc, esphome::binary_sensor::BinarySensor *sensor):
    paramDesc(paramDesc),
    sensor(nullptr),
    binarySensor(sensor),
    switch_(nullptr),
    number(nullptr)
{

}

BuderusValueHandler::BuderusValueHandler(const t_Buderus_R2017_ParamDesc* paramDesc, BuderusParamSwitch *switch_):
    paramDesc(paramDesc),
    sensor(nullptr),
    binarySensor(nullptr),
    switch_(switch_),
    number(nullptr)
{

}

BuderusValueHandler::BuderusValueHandler(const t_Buderus_R2017_ParamDesc* paramDesc, BuderusParamNumber *paramNumber):
   paramDesc(paramDesc),
    sensor(nullptr),
    binarySensor(nullptr),
    switch_(nullptr),
    number(paramNumber)
{

}


uint32_t parseUnsignedInteger(uint8_t *data, size_t len)
{
    uint32_t value = 0;
    for (int i=0; i<len; i++) {
        value = (value << 8) + data[i];
    }
    return value;
}

int32_t parseSignedInteger(uint8_t *data, size_t len)
{
    if (len == 1) {
        return (int8_t) data[0];
    } else if (len == 2) {
        uint16_t value = (data[0] << 8) + data[1];
        return (int16_t) value;
    } else if (len == 4) {
        uint32_t value = parseUnsignedInteger(data, len);
        return (int32_t) value;
    } else {
        ESP_LOGE(TAG, "Found unsupported signed integer with length %d", len);
        return parseUnsignedInteger(data, len);
    }
}

void BuderusValueHandler::parseAndTransmit(uint8_t *data, size_t len)
{
    if (sensor) {
        if (paramDesc->sensorType == UNSIGNED_INT) {
            uint32_t value = parseUnsignedInteger(data, len);
            sensor->publish_state(value);
        } else if (paramDesc->sensorType == SIGNED_INT) {
            int32_t value = parseSignedInteger(data, len);
            sensor->publish_state(value);
        } else if (paramDesc->sensorType == UNSIGNED_INT_DIVIDED_BY_2) {
            uint32_t value = parseUnsignedInteger(data, len);
            sensor->publish_state(((float)value) / 2.0f);
        } else {
            ESP_LOGW(TAG, "Sensor type %d NYI", paramDesc->sensorType);
        }
    } else if(binarySensor) {
        if (paramDesc->sensorType == UNSIGNED_INT) {
            binarySensor->publish_state(data[len-1] > 0);
        } else if(paramDesc->sensorType == BIT_AT_OFFSET) {
            uint16_t bitOffset = paramDesc->sensorTypeParam;
            uint16_t byteOffset = 0;
            while (bitOffset >= 8) {
                byteOffset += 1;
                bitOffset -= 8;
                if (byteOffset >= len) {
                    ESP_LOGW(TAG, "Parameter %d has bit offset %d but message only has %d bytes", paramDesc->parameterId, paramDesc->sensorType, len);
                    return;
                }
            }
            bool value = !!(data[byteOffset] & (1 << bitOffset));
            binarySensor->publish_state(value);
        } else {
            ESP_LOGW(TAG, "Sensor type %d NYI for binary sensor", paramDesc->sensorType);
        }

    } else if(switch_) {
        if (paramDesc->sensorType == TAG_NACHT_AUTO_SELECT) {
            ESP_LOGD(TAG, "Found tag/nacht/auto select length %d: 0x%02x (0:Nacht, 1:Tag, 2: Auto) 0x%02x", len, data[0], data[1] );
            if(data[0] == 0) { // nacht
                switch_->publish_state(false);
            } else if(data[0] == 1 || data[0] == 2) { // tag, auto
                switch_->publish_state(true);
            } else {
                ESP_LOGW(TAG, "Invalid value for tag/nacht/auto select: %d 0x%02x 0x%02x ...", len, data[0], data[1]);
            }
        } else {
            ESP_LOGW(TAG, "Sensor type %d NYI for switch", paramDesc->sensorType);
        }
    } else if(number) {
        if (paramDesc->sensorType == UNSIGNED_INT) {
            uint32_t value = parseUnsignedInteger(data, len);
            number->publish_state(value);
        } else if (paramDesc->sensorType == SIGNED_INT) {
            int32_t value = parseSignedInteger(data, len);
            number->publish_state(value);
        } else if(paramDesc->sensorType == BYTE_AT_OFFSET) {
            if (paramDesc->sensorTypeParam < len) {
                uint8_t value = data[paramDesc->sensorTypeParam];
                number->publish_state(value);
            } else {
                ESP_LOGE(TAG, "Offset for sensor type BYTE_AT_OFFSET %d > data len %d", paramDesc->sensorTypeParam, len);
            }
        } else {
            ESP_LOGE(TAG, "Sensor type %d NYI for number", paramDesc->sensorType);
        }

    } else {
        ESP_LOGE(TAG, "No sensor, binary sensor, switch or number defined");
    }
}

void BuderusValueHandler::loop()
{
  if(number) {
      number->loop();
  }
}

BuderusParamSwitch::BuderusParamSwitch():
    writer(nullptr)
{
}

void BuderusParamSwitch::setupWriting(Writer3964R *writer, Buderus_R2017_ParameterId parameterId, SensorType sensorType)
{
    this->writer = writer;
    this->parameterId = parameterId;
    this->sensorType = sensorType;
}

void BuderusParamSwitch::write_state(bool state)
{
    const uint8_t keep = 0x65;
    const uint8_t data_type_warm_water = 0x0c;

    if (parameterId == CFG_WW_Aufbereitung) {
        const uint8_t automatic = 2;
        const uint8_t day = 1;
        const uint8_t night = 0;

        const uint8_t value = state ? automatic : night;

        const uint8_t message[] = { data_type_warm_water, 0x0E, value, keep, keep, keep, keep, keep};
        writer->enqueueTelegram(message, 8);
        publish_state(state); // confirm for now without waiting for an ack from the heater

    } else {
        ESP_LOGE(TAG, "No write configuration for parameter %d found", parameterId);
    }
}

BuderusParamNumber::BuderusParamNumber():
    writer(nullptr),
    hasPendingWriteRequest(false)
{
}

void BuderusParamNumber::setupWriting(Writer3964R *writer, Buderus_R2017_ParameterId parameterId, SensorType sensorType)
{
    this->writer = writer;
    this->parameterId = parameterId;
    this->sensorType = sensorType;
}

void BuderusParamNumber::control(float value)
{
    if(parameterId == CFG_WW_Temperatur) {
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

    } else if(parameterId == CFG_HK1_Auslegungstemperatur) {
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
        ESP_LOGE(TAG, "No write configuration for number parameter %d found", parameterId);
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

            if (parameterId == CFG_WW_Temperatur) {
              const uint8_t message[] = { data_type_warm_water, 0x07, keep, keep, keep, (uint8_t)this->pendingWriteValue, keep, keep};
                if(writer->enqueueTelegram(message, 8)) {
                    this->hasPendingWriteRequest = false;
                    publish_state(this->pendingWriteValue);

                }
            } else if(parameterId == CFG_HK1_Auslegungstemperatur) {
                const uint8_t message[] = { data_type_heating_circuit_1, 0x0e, keep, keep, keep, keep, (uint8_t)this->pendingWriteValue, keep};
                  if(writer->enqueueTelegram(message, 8)) {
                      this->hasPendingWriteRequest = false;
                      publish_state(this->pendingWriteValue);

                  }
            } else {
                ESP_LOGE(TAG, "No support for writing parameter %d", parameterId);
                this->hasPendingWriteRequest = false;

            }
        }
    }
}


}
}





