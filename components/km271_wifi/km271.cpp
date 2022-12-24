#include "km271.h"
#include "km271_helpers.h"
#include "esphome/core/log.h"
#include "esphome/core/util.h"
#include "esphome/components/sensor/sensor.h"
#include "esphome/components/binary_sensor/binary_sensor.h"

namespace esphome {
namespace KM271 {

static const char * TAG = "km271";
static const uint8_t SENSOR_LOOP_CALL_EVERY = 5;

#define lenof(X)   (sizeof(X) / sizeof(X[0]))

KM271Component::KM271Component()
{
}

void KM271Component::parse_buderus(uint8_t * buf, size_t len) {

    if(len < 2) {
        ESP_LOGE(TAG, "Invalid data length.");
        return;
    }

    const uint16_t parameterIdNumeric = (buf[0] << 8) | buf[1];
    auto parameterId = static_cast<Buderus_R2017_ParameterId>(parameterIdNumeric);
    // filter out irrelevant noisy values
    if (parameterId == 0x0400 || parameterId == 0x882E || parameterId == 0x882F ) {
        return;
    }

    char tmpBuf[4 * MAX_TELEGRAM_SIZE];
    buffer_to_hex(tmpBuf, &buf[2], len - 2);
    ESP_LOGD(TAG, "Parameter 0x%04X: (Data: %d, 0x%s)", parameterId, len-2, tmpBuf);

    auto result = valueHandlerMap.equal_range(parameterId);
    for (ValueHandlerMap::iterator i=result.first; i!=result.second; i++) {
        BuderusValueHandler * handler = i->second;
        i->second->parseAndTransmit(buf + 2, len-2);
    }
}

void KM271Component::send_ACK_DLE() {
    write_byte(DLE);
}

void KM271Component::send_NAK() {
    write_byte(NAK);
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
            writer.telegramFinished();
            ESP_LOGD(TAG, "ack received");
        } else if(c==NAK) {
            if(writer.retryCount < maxTelegramRetries) {
                writer.restartTelegram();
                ESP_LOGW(TAG, "nack received, retrying");
            } else {
                writer.telegramFinished();
                ESP_LOGE(TAG, "nack received and retry count exhausted, aborting");
            }
        } else {
            if(writer.retryCount < maxTelegramRetries) {
                writer.restartTelegram();
                ESP_LOGW(TAG, "ack for writer was invalid, retrying: %d", c);
            } else {
                writer.telegramFinished();
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

    sensorLoopCounter++;
    if (sensorLoopCounter > SENSOR_LOOP_CALL_EVERY) {
        sensorLoopCounter = 0;

        for(ValueHandlerMap::iterator i = valueHandlerMap.begin(); i!=valueHandlerMap.end(); i++) {
            i->second->loop();
        }
    }

}

void KM271Component::setup() {
    ESP_LOGCONFIG(TAG, "Setup was called");
    sensorLoopCounter = 0;
    uint8_t logCommand[] = {0xEE, 0x00, 0x00};
    writer.enqueueTelegram(logCommand, 3);
};

void KM271Component::update() {
    ESP_LOGI(TAG, "Update was called");
};

void KM271Component::dump_config() {
    ESP_LOGCONFIG(TAG, "Dump Config was called");

    for(ValueHandlerMap::iterator i = valueHandlerMap.begin(); i!=valueHandlerMap.end(); i++) {
        ESP_LOGCONFIG(TAG, "Sensor %s enabled", i->second->paramDesc->desc);
    }
}

void KM271Component::on_shutdown() {
    ESP_LOGI(TAG, "Shutdown was called");
}

const t_Buderus_R2017_ParamDesc * KM271Component::findParameterForNewSensor(TransmissionParameter transmissionParameter, bool writableRequired)
{
    for(int i = 0; i < lenof(buderusParamDesc); i++) {
        const t_Buderus_R2017_ParamDesc * pDesc = &buderusParamDesc[i];
        if(pDesc->transmissionParameter == transmissionParameter ) {
            if (writableRequired && !pDesc->writable) {
                ESP_LOGE(TAG, "Transmission value %d %s is not writable", transmissionParameter, pDesc->desc);
                return nullptr;
            }
            return pDesc;
        }
    }
    return nullptr;
}

void KM271Component::set_sensor(TransmissionParameter transmissionParameter, esphome::sensor::Sensor *sensor)
{
    const t_Buderus_R2017_ParamDesc* pDesc = findParameterForNewSensor(transmissionParameter, false);
    if (!pDesc) {
        ESP_LOGE(TAG, "set_sensor: No available slot for transmission parameter %d found", transmissionParameter);
        return;
    }

    if(pDesc->sensorType == MULTI_PARAMETER_UNSIGNED_INTEGER) {
        auto *assembler = new MultiParameterUnsignedIntegerAssembler(sensor);

        uint8_t groupId = pDesc->sensorTypeParam >> 8;
        // we need to add value handlers to all group members
        for(int i = 0; i < lenof(buderusParamDesc); i++) {
            const t_Buderus_R2017_ParamDesc * otherPDesc = &buderusParamDesc[i];
            if(otherPDesc->sensorType == MULTI_PARAMETER_UNSIGNED_INTEGER) {
                uint8_t groupIdOfDesc = otherPDesc->sensorTypeParam >> 8;
                if (groupIdOfDesc == groupId) {
                    ESP_LOGE(TAG, "Adding sensor with type param %d to parameter 0x%04X", pDesc->sensorTypeParam, otherPDesc->parameterId);
                    valueHandlerMap.insert(std::pair<Buderus_R2017_ParameterId, BuderusValueHandler *>(otherPDesc->parameterId, new BuderusValueHandler(otherPDesc, assembler)));
                }
            }
        }
    } else {
        valueHandlerMap.insert(std::pair<Buderus_R2017_ParameterId, BuderusValueHandler *>(pDesc->parameterId, new BuderusValueHandler(pDesc, sensor)));
    }
}

void KM271Component::set_binary_sensor(TransmissionParameter transmissionParameter, esphome::binary_sensor::BinarySensor *sensor)
{
    const t_Buderus_R2017_ParamDesc* pDesc = findParameterForNewSensor(transmissionParameter, false);
    if (!pDesc) {
        ESP_LOGE(TAG, "set_binary_sensor: No available slot for transmission parameter %d found", transmissionParameter);
        return;
    }

    valueHandlerMap.insert(std::pair<Buderus_R2017_ParameterId, BuderusValueHandler *>(pDesc->parameterId, new BuderusValueHandler(pDesc, sensor)));
}

void KM271Component::set_communication_component(TransmissionParameter transmissionParameter, CommunicationComponent *component)
{
    const t_Buderus_R2017_ParamDesc* pDesc = findParameterForNewSensor(transmissionParameter, true);
    if (!pDesc) {
        ESP_LOGE(TAG, "set_switch: No available slot for transmission parameter %d found", transmissionParameter);
        return;
    }

    component->setupWriting(&writer, transmissionParameter);

    valueHandlerMap.insert(std::pair<Buderus_R2017_ParameterId, BuderusValueHandler *>(pDesc->parameterId, new BuderusValueHandler(pDesc, component)));
}

float KM271Component::get_setup_priority() const {
    return setup_priority::DATA;
}

} // namespace KM271
} // namespace esphome
