#include "km271.h"
#include "esphome/core/log.h"
#include "esphome/core/util.h"
#include "esphome/components/sensor/sensor.h"

namespace esphome {
namespace KM271 {

static const char *const TAG = "km271";

static const uint8_t STX = 0x02;
static const uint8_t ETX = 0x03;
static const uint8_t DLE = 0x10;
static const uint8_t NAK = 0x15;

void KM271Component::loop() {
    static int cnt = 1000;
    if(0==cnt) {
        ESP_LOGD(TAG, "%s", "Test");
        cnt=1000;
    }
    cnt--;
}

void KM271Component::setup() {
    ESP_LOGD(TAG, "Setup was called");
};

void KM271Component::update() {
    ESP_LOGD(TAG, "Update was called");
};

void KM271Component::dump_config() {
    ESP_LOGD(TAG, "Dump Config was called");
};

void KM271Component::on_shutdown() {
    ESP_LOGD(TAG, "Shutdown was called");
};

float KM271Component::get_setup_priority() const {
    return setup_priority::DATA;
}

} // namespace KM271
} // namespace esphome
