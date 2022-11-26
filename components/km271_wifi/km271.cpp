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

                ESP_LOGD(TAG, "Parameter 0x%04X: %s %s (Data: %d, 0x%s, %d)", parameterId, pDesc->desc, pDesc->unit, len-2, tmpBuf, *tmpBuf);
            }
            if(pDesc->sensor) {
                pDesc->sensor->parseAndTransmit(buf + 2, len-2);
            }
            break;
        }
    }

    // ESP_LOGD(TAG, "Received param 0x%04X", parameterId);
}

void KM271Component::send_ACK_DLE() {
    write_byte(DLE);
}

void KM271Component::send_NAK() {
    write_byte(NAK);
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
    // ESP_LOGD(TAG, "R%02X", c);

    if (writer.writerState == WaitingForDle) {
        if (c == DLE) {
            while(writer.hasByteToSend()) {
                uint8_t byte = writer.popNextByte();
                write_byte(byte);
            }
            return;
        } else {
            ESP_LOGW(TAG, "no dle received: %2X", c);
            writer.restartTelegram();
        }
    } else if(writer.writerState == WaitForAck) {
        if (c==DLE) {
            writer.reset();
            ESP_LOGD(TAG, "ack received");
        } else if(c==NAK) {
            if(writer.retryCount < maxTelegramRetries) {
                writer.restartTelegram();
                ESP_LOGW(TAG, "nack received, retrying");
            } else {
                writer.reset();
                ESP_LOGE(TAG, "nack received and retry count exhausted, aborting");
            }
        } else {
            if(writer.retryCount < maxTelegramRetries) {
                writer.restartTelegram();
                ESP_LOGW(TAG, "ack for writer was invalid, retrying: %d", c);
            } else {
                writer.reset();
                ESP_LOGE(TAG, "ack for writer was invalid and retry count exhausted, aborting: %d", c);
            }
        }
        return;
    }
    uint32_t timeSinceLA = now - last_received_byte_time;

    if(timeSinceLA > ZVZ && parser.parsingInProgress()) {
        // Reset transaction when QVZ is over
        ESP_LOGW(TAG, "ZVZ time-out, recv: %2X, state %d", c, parser.parserState);
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
      while(available()) {
        uint8_t c = read();

        // if we have a write, start our request on a stx from the km217. This seems more reliable.
        if (c == STX && parser.parserState == WaitingForStart && writer.writerState == RequestPending) {
                write_byte(STX);
                writer.setSTXSent();
         } else {
            process_incoming_byte(c);
        }
    };
}

void KM271Component::setup() {
    ESP_LOGCONFIG(TAG, "Setup was called");
    uint8_t logCommand[] = {0xEE, 0x00, 0x00};
    writer.enqueueTelegram(logCommand, 3);
};

void KM271Component::update() {
    ESP_LOGI(TAG, "Update was called");
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
