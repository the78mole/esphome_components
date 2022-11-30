#include "km271_params.h"
#include "esphome/core/log.h"
#include "esphome/core/util.h"
#include "esphome/core/hal.h"
#include <stdint.h>
#include "3964r.h"

namespace esphome {
namespace KM271 {

static const char *const TAG = "BPARM";

BuderusParamSensor::BuderusParamSensor(esphome::sensor::Sensor *sensor,  SensorType sensorType, uint8_t sensorTypeParam):
    sensor(sensor),
    binarySensor(nullptr),
    switch_(nullptr),
    number(nullptr),
    sensorType(sensorType),
    sensorTypeParam(sensorTypeParam)
{

}

BuderusParamSensor::BuderusParamSensor(esphome::binary_sensor::BinarySensor *sensor, SensorType sensorType, uint8_t sensorTypeParam):
    sensor(nullptr),
    binarySensor(sensor),
    switch_(nullptr),
    number(nullptr),
    sensorType(sensorType),
    sensorTypeParam(sensorTypeParam)
{

}

BuderusParamSensor::BuderusParamSensor(BuderusParamSwitch *switch_, SensorType sensorType, uint8_t sensorTypeParam):
    sensor(nullptr),
    binarySensor(nullptr),
    switch_(switch_),
    number(nullptr),
    sensorType(sensorType),
    sensorTypeParam(sensorTypeParam)
{

}

BuderusParamSensor::BuderusParamSensor(BuderusParamNumber *paramNumber, SensorType sensorType, uint8_t sensorTypeParam):
    sensor(nullptr),
    binarySensor(nullptr),
    switch_(nullptr),
    number(paramNumber),
    sensorType(sensorType),
    sensorTypeParam(sensorTypeParam)
{

}

uint32_t parseInt(uint8_t *data, size_t len)
{
    uint32_t value = 0;
    for (int i=0; i<len; i++) {
        value = (value << 8) + data[i];
    }
    return value;
}

void BuderusParamSensor::parseAndTransmit(uint8_t *data, size_t len)
{
    if (sensor) {
        if (sensorType == INT) {
            ESP_LOGD(TAG, "Found int with length %d", len);
            uint32_t value = parseInt(data, len);
            sensor->publish_state(value);
        } 
        else if (sensorType == INTDIVIDEDBY2) {
            ESP_LOGD(TAG, "Found int with length %d that needs to be devided by 2", len);
            uint32_t value = 0;
            for (int i=0; i<len; i++) {
                value = (value << 8) + data[i];
            }
            sensor->publish_state(((float)value) / 2.0f);
        }
        else {
            ESP_LOGW(TAG, "Sensor type %d NYI", sensorType);
        }
    } else if(binarySensor) {
        binarySensor->publish_state(data[len-1] > 0);
    } else if(switch_) {
        if (sensorType == TAG_NACHT_AUTO_SELECT) {
            ESP_LOGD(TAG, "Found tag/nacht/auto select length %d: %s", len, (char *)data);
            if(data[0] == 0) { // nacht
                switch_->publish_state(false);
            } else if(data[0] == 1 || data[0] == 2) { // tag, auto
                switch_->publish_state(true);
            } else {
                ESP_LOGW(TAG, "Invalid value for tag/nacht/auto select: %d %c %c ...", len, data[0], data[1]);
            }
        } else {
            ESP_LOGW(TAG, "Sensor type %d NYI for switch", sensorType);
        }
    } else if(number) {
        if (sensorType == INT) {
            uint32_t value = parseInt(data, len);
            number->publish_state(value);
        } else if(sensorType == BYTE_AT_OFFSET) {
            if (sensorTypeParam < len) {
                uint8_t value = data[sensorTypeParam];
                number->publish_state(value);
            } else {
                ESP_LOGE(TAG, "Offset for sensor type BYTE_AT_OFFSET %d > data len %d", sensorTypeParam, len);
            }
        } else {
            ESP_LOGE(TAG, "Sensor type %d NYI for number", sensorType);
        }

    } else {
        ESP_LOGE(TAG, "No sensor, binary sensor or switch defined");
    }
}

void BuderusParamSensor::loop()
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
    const uint8_t keep = 0x65;
    const uint8_t data_type_warm_water = 0x0c;

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

    } else {
        ESP_LOGE(TAG, "No write configuration for number parameter %d found", parameterId);
    }
}

void BuderusParamNumber::loop()
{
    uint32_t writeConsolidationPeriod = 1000;
    const uint8_t keep = 0x65;
    const uint8_t data_type_warm_water = 0x0c;

    if (this->hasPendingWriteRequest) {
        uint32_t now = millis();
        if (now - lastWriteRequest > writeConsolidationPeriod) {
            this->hasPendingWriteRequest = false;
            const uint8_t message[] = { data_type_warm_water, 0x07, keep, keep, keep, (uint8_t)this->pendingWriteValue, keep, keep};
            writer->enqueueTelegram(message, 8);
            publish_state(this->pendingWriteValue);
        }
    }
}


}
}





