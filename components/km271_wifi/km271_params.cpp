#include "km271_params.h"
#include "esphome/core/log.h"
#include "esphome/core/util.h"
#include <stdint.h>

namespace esphome {
namespace KM271 {

static const char *const TAG = "BPARM";

BuderusParamSensor::BuderusParamSensor(esphome::sensor::Sensor *sensor,  SensorType sensorType):
    sensor(sensor),
    binarySensor(nullptr),
    sensorType(sensorType)
{

}

BuderusParamSensor::BuderusParamSensor(esphome::binary_sensor::BinarySensor *sensor):
    sensor(nullptr),
    binarySensor(sensor)
{

}

void BuderusParamSensor::parseAndTransmit(uint8_t *data, size_t len)
{
    if (sensor) {
        if (sensorType == INT) {
            ESP_LOGD(TAG, "Found int with length %d", len);
            uint32_t value = 0;
            for (int i=0; i<len; i++) {
                value = (value << 8) + data[i];
            }
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
          ESP_LOGD(TAG, "Sensor type %d NYI", sensorType);
        }
    } else if(binarySensor) {
        binarySensor->publish_state(data[len-1] > 0);
    } else {
        ESP_LOGE(TAG, "No sensor or binary sensor defined");
    }
}


}
}





