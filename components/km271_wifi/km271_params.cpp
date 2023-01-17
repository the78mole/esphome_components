#include "km271_params.h"
#include "esphome/core/log.h"
#include "esphome/core/hal.h"
#include <stdint.h>
#include "3964r.h"
#include "km271_communication_components.h"

namespace esphome {
namespace KM271 {

static const char *const TAG = "BPARM";

BuderusValueHandler::BuderusValueHandler(const t_Buderus_R2017_ParamDesc *paramDesc, esphome::sensor::Sensor *sensor):
    paramDesc(paramDesc),
    communicationComponent(nullptr),
    sensor(sensor),
    binarySensor(nullptr)
{

}

BuderusValueHandler::BuderusValueHandler(const t_Buderus_R2017_ParamDesc *paramDesc, esphome::binary_sensor::BinarySensor *binarySensor):
    paramDesc(paramDesc),
    communicationComponent(nullptr),
    sensor(nullptr),
    binarySensor(binarySensor)
{

}

BuderusValueHandler::BuderusValueHandler(const t_Buderus_R2017_ParamDesc* paramDesc, CommunicationComponent * communicationComponent):
    paramDesc(paramDesc),
    communicationComponent(communicationComponent),
    sensor(nullptr),
    binarySensor(nullptr)
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
    if (paramDesc->sensorType == UNSIGNED_INT) {
        uint32_t value = parseUnsignedInteger(data, len);
        handleReceivedUnsignedValue(paramDesc->sensorTypeParam, value);
    } else if (paramDesc->sensorType == SIGNED_INT) {
        int32_t value = parseSignedInteger(data, len);
        handleReceivedSignedValue(paramDesc->sensorTypeParam, value);
    } else if (paramDesc->sensorType == UNSIGNED_INT_DIVIDED_BY_2) {
        uint32_t value = parseUnsignedInteger(data, len);
        handleReceivedFloatValue(paramDesc->sensorTypeParam, (float)value / 2.0f);
    } else if(paramDesc->sensorType == BIT_AT_OFFSET) {
        uint16_t bitOffset = paramDesc->sensorTypeParam;
        uint16_t byteOffset = 0;
        while (bitOffset >= 8) {
            byteOffset += 1;
            bitOffset -= 8;
            if (byteOffset >= len) {
                ESP_LOGW(TAG, "Parameter 0x%04x has bit offset %d but message only has %d bytes", paramDesc->parameterId, paramDesc->sensorType, len);
                return;
            }
        }
        bool value = !!(data[byteOffset] & (1 << bitOffset));
        handleReceivedUnsignedValue(paramDesc->sensorTypeParam, value);
    } else if(paramDesc->sensorType == BYTE_AT_OFFSET) {
        if (paramDesc->sensorTypeParam < len) {
            uint8_t value = data[paramDesc->sensorTypeParam];
            handleReceivedUnsignedValue(paramDesc->sensorTypeParam, value);
        } else {
            ESP_LOGE(TAG, "Offset for sensor type BYTE_AT_OFFSET %d > data len %d", paramDesc->sensorTypeParam, len);
        }
    } else if (paramDesc->sensorType == BYTE_DIVIDED_BY_2_AT_OFFSET) {
        if (paramDesc->sensorTypeParam < len) {
            uint8_t value = data[paramDesc->sensorTypeParam];
            handleReceivedFloatValue(paramDesc->sensorTypeParam, (float)value * 0.5);
        } else {
            ESP_LOGE(TAG, "Offset for sensor type BYTE_DIVIDED_BY_2_AT_OFFSET %d > data len %d", paramDesc->sensorTypeParam, len);
        }
    } else if (paramDesc->sensorType == MULTI_PARAMETER_UNSIGNED_INTEGER) {
        ESP_LOGD(TAG, "Parameter: 0x%04x type param %d Len %d, data: %d %d", paramDesc->parameterId, paramDesc->sensorTypeParam, len, data[0], data[1]);
        uint32_t value = parseUnsignedInteger(data, len);
        handleReceivedUnsignedValue(paramDesc->sensorTypeParam, value);
    } else if (paramDesc->sensorType == FIRMWARE_VERSION) {
        ESP_LOGD(TAG, "Parameter: 0x%04x type param %d Len %d, data: %d", paramDesc->parameterId, paramDesc->sensorTypeParam, len, data[0]);
        uint32_t value = parseUnsignedInteger(data, len);
        handleReceivedUnsignedValue(paramDesc->sensorTypeParam, value);
    } else {
        ESP_LOGW(TAG, "Sensor type %d NYI", paramDesc->sensorType);
    }
}

void BuderusValueHandler::loop()
{
    if(communicationComponent) {
        communicationComponent->loop();
    }
}

void BuderusValueHandler::handleReceivedSignedValue(uint16_t sensorTypeParam, int32_t value)
{
    if (sensor) {
        sensor->publish_state(value);
    } else if(binarySensor) {
        binarySensor->publish_state(value);
    } else if (communicationComponent) {
        communicationComponent->handleReceivedSignedValue(sensorTypeParam, value);
    } else {
        ESP_LOGW(TAG, "No handler for signed values found at %d", paramDesc->sensorType);
    }
}

void BuderusValueHandler::handleReceivedUnsignedValue(uint16_t sensorTypeParam, uint32_t value)
{
    if (sensor) {
        sensor->publish_state(value);
    } else if(binarySensor) {
        binarySensor->publish_state(value);
    } else if (communicationComponent) {
        communicationComponent->handleReceivedUnsignedValue(sensorTypeParam, value);
    } else {
        ESP_LOGW(TAG, "No handler for unsigned values found at %d", paramDesc->sensorType);
    }

}

void BuderusValueHandler::handleReceivedFloatValue(uint16_t sensorTypeParam, float value)
{
    if (sensor) {
        sensor->publish_state(value);
    } else if(binarySensor) {
        binarySensor->publish_state(value);
    } else if (communicationComponent) {
        communicationComponent->handleReceivedFloatValue(sensorTypeParam, value);
    } else {
        ESP_LOGW(TAG, "No handler for float values found at %d", paramDesc->sensorType);
    }
}


} // namespace
} // namespace



