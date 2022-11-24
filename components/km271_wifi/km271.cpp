#include "km271.h"
#include <stdint.h>
#include "esphome/core/log.h"
#include "esphome/core/util.h"
#include "esphome/components/sensor/sensor.h"
#include "esphome/components/binary_sensor/binary_sensor.h"


namespace esphome {
namespace KM271 {

static const char * TAG = "km271";

#define lenof(X)   (sizeof(X) / sizeof(X[0]))

static const int ALIVE_RST = 20000; // Milliseconds

KM271Component::KM271Component()
{
}

void KM271Component::parse_buderus(uint8_t * buf, size_t len) {

    if(len < 2) {
        ESP_LOGE(TAG, "Invalid data length.");
        return;
    }

    uint16_t parameterId = (buf[0] << 8) | buf[1];

    for(int i = 0; i < lenof(buderusParamDesc); i++) {
        const t_Buderus_R2017_ParamDesc * pDesc = &buderusParamDesc[i];
        if(pDesc->parameterId == parameterId) {
            if(pDesc->debugEn) {
                char tmpBuf[4 * MAX_TELEGRAM_SIZE];
                genDataString(tmpBuf, &buf[2], len - 2);

                ESP_LOGD(TAG, "Found parameter 0x%04X: %s %s (Data: %d, 0x%s)", parameterId, pDesc->desc, pDesc->unit, len-2, tmpBuf);
            }
            if(pDesc->sensor) {
                pDesc->sensor->parseAndTransmit(buf + 2, len-2);
            }
            break;
        }
    }

    ESP_LOGD(TAG, "Received param 0x%04X", parameterId);
}

void KM271Component::send_ACK_DLE() {
    write_byte(DLE);
}

void KM271Component::send_NAK() {
    write_byte(NAK);
}


void KM271Component::writeRequestValues()
{
    write_byte(0xee);
    write_byte(0x00);
    write_byte(0x00);
}

size_t KM271Component::genDataString(char* outbuf, uint8_t* inbuf, size_t len) {
    char * pBuf = outbuf;

    if(len < 1) {
        ESP_LOGD(TAG, "Invalid conversion len < 1 (%d)", len);
        return 0;
    }
    for(size_t i = 0; i < len; i++) {
        pBuf += sprintf(pBuf, "%02X ", inbuf[i]);
    }
    pBuf--;
    *pBuf = 0x00;
    pBuf++;
    return (pBuf - outbuf);
}

void KM271Component::print_hex_buffer(uint8_t* buf, size_t len) {
    char tmpBuf[4 * MAX_TELEGRAM_SIZE];
    char * pTmpBuf = &tmpBuf[0];
    uint8_t * pBuf = &buf[0];

    if(0x04 != buf[0]) {
        memset(tmpBuf, 0, sizeof(tmpBuf));

        for(size_t i = 0; i < len; i++) {
            //ESP_LOGD(TAG, "BUF (%5d) PRINT %3d: 0x%02X", sizeof(tmpBuf), i, buf[i]);
            pTmpBuf += sprintf(pTmpBuf, "%02X ", buf[i]);
        }

        ESP_LOGD(TAG, "RxBuf [%d]: 0x%s", len, tmpBuf);
    }

}

void KM271Component::process_incoming_byte(uint8_t c) {
    const uint32_t now = millis();

    uint32_t timeSinceLA = now - last_received_byte_time;

    if(timeSinceLA > ZVZ && parser.parsingInProgress()) {
        // Reset transaction when QVZ is over
        ESP_LOGW(TAG, "ZVZ time-out");
        parser.reset();
    }
    last_received_byte_time = now;

    if(parser.parsingInProgress()) {
        parser.consumeByte(c);

        if (parser.parserState == TelegramComplete) {
            this->send_ACK_DLE();
            parse_buderus(parser.decodedTelegram, parser.currentTelegramLength);
            parser.reset();
        }
    } else {
        if(c == STX) {
            // ESP_LOGD(TAG, "Start Request received, sending ACK = DLE");
            this->send_ACK_DLE();
            parser.startTelegram();
        }
    }
}

void KM271Component::loop() {
    static int cnt = 0;
    static uint32_t last_action;
    const uint32_t now = millis();

    if (now - last_action > ALIVE_RST) {
        ESP_LOGD(TAG, "Alive");
        // this->send_ACK_DLE();
        last_action = now;
    }

    while(available()) {
        uint8_t c = read();
        // ESP_LOGD(TAG, "Recv: 0x%02X (%0.2f)", c, (now - last_action) / 1000.0);
        process_incoming_byte(c);
        last_action = now;
    };

}

void KM271Component::setup() {
    ESP_LOGCONFIG(TAG, "Setup was called");
    const t_Buderus_R2017_ParamDesc * pDesc;
};

void KM271Component::update() {
    ESP_LOGI(TAG, "Update was called");
    //this->params.init();
};

void KM271Component::dump_config() {
    ESP_LOGCONFIG(TAG, "Dump Config was called");
    for(int i = 0; i < lenof(buderusParamDesc); i++) {
        const t_Buderus_R2017_ParamDesc * pDesc = &buderusParamDesc[i];
        if (pDesc->sensor) {
            ESP_LOGCONFIG(TAG, "Sensor %s enabled", pDesc->desc);
        }
    }
}

void KM271Component::on_shutdown() {
    ESP_LOGI(TAG, "Shutdown was called");
}

void KM271Component::set_sensor(Buderus_R2017_ParameterId parameterId, esphome::sensor::Sensor *sensor)
{
    for(int i = 0; i < lenof(buderusParamDesc); i++) {
        t_Buderus_R2017_ParamDesc * pDesc = &buderusParamDesc[i];
        if(pDesc->parameterId == parameterId) {
            if (pDesc->sensor) {
                ESP_LOGE(TAG, "Sensor for id %d already set", parameterId);
                return;
            }
            pDesc->sensor = new BuderusParamSensor(sensor, pDesc->sensorType);
            return;
        }
    }

    ESP_LOGE(TAG, "Parameter %d is not supported", parameterId);
}

void KM271Component::set_binary_sensor(Buderus_R2017_ParameterId parameterId, esphome::binary_sensor::BinarySensor *sensor)
{
    for(int i = 0; i < lenof(buderusParamDesc); i++) {
        t_Buderus_R2017_ParamDesc * pDesc = &buderusParamDesc[i];
        if(pDesc->parameterId == parameterId) {
            if (pDesc->sensor) {
                ESP_LOGE(TAG, "Sensor for id %d already set", parameterId);
                return;
            }
            pDesc->sensor = new BuderusParamSensor(sensor);
            return;
        }
    }

    ESP_LOGE(TAG, "Parameter ID %d is not supported", parameterId);

}



float KM271Component::get_setup_priority() const {
    return setup_priority::DATA;
}

} // namespace KM271
} // namespace esphome
