#include "km271.h"
#include "esphome/core/log.h"
#include "esphome/core/util.h"
#include "esphome/components/sensor/sensor.h"

namespace esphome {
namespace KM271 {

static const char *const TAG = "km271";

static const char STX = 0x02;
static const char ETX = 0x03;
static const char DLE = 0x10;
static const char NAK = 0x15;

static const uint32_t QVZ = 2000;   // Quittierungsverzugszeit: Time-out in milliseconds for achnoledge
static const uint32_t ZVZ = 220;    // Zeichenverzugszeit: Time-out between data of active transmission

#define RXBUFLEN      128

static const int ALIVE_RST = 20000; // Milliseconds

enum State3964R {
    WAIT_STX = 0,
    WAIT_DLE_ETX,
    WAIT_CSUM
};

void KM271Component::parse_3964R() {

}

void KM271Component::send_ACK_DLE() {
    write_byte(DLE);
}

void KM271Component::send_NAK() {
    write_byte(NAK);
}

void KM271Component::print_hex_buffer(char * buf, size_t len) {
    char tmpBuf[4 * RXBUFLEN];
    char * pTmpBuf = &tmpBuf[0];
    char * pBuf = &buf[0];

    memset(tmpBuf, 0, sizeof(tmpBuf));

    for(size_t i = 0; i < len; i++) {
        //ESP_LOGD(TAG, "BUF (%5d) PRINT %3d: 0x%02X", sizeof(tmpBuf), i, buf[i]);
        pTmpBuf += sprintf(pTmpBuf, "%02X ", buf[i]);
    }

    ESP_LOGD(TAG, "RxBuf [%d]: 0x%s", len, tmpBuf);

}

void KM271Component::process_state(char c) {
    static State3964R state = WAIT_STX;
    State3964R new_state = WAIT_STX;

    static uint32_t last_action;
    const uint32_t now = millis();
    static int rxLen = 0;

    static char lastChar = 0x00;
    static char csum, savedCsum;
    static char rxBuffer[RXBUFLEN];
    static char * pRxBuf;
    static bool toggleDLE;

    uint32_t timeSinceLA = now - last_action;

    if(timeSinceLA > QVZ) {
        // Reset transaction when QVZ is over
        ESP_LOGW(TAG, "QVZ time-out");
        state = WAIT_STX;
    }

    new_state = state;

    csum ^= c; // Sum up the checksum
    rxLen++;

    switch(state) {

        case WAIT_STX:
            pRxBuf = &rxBuffer[0];
            csum = 0x00;
            rxLen = 0;
            toggleDLE = false;
            if(STX == c) {
                //ESP_LOGD(TAG, "Start Request received, sending ACK = DLE");
                this->send_ACK_DLE();
                new_state = WAIT_DLE_ETX;
            }
            break;

        case WAIT_DLE_ETX:
            if(timeSinceLA > ZVZ) {
                ESP_LOGW(TAG, "ZVZ time-out");
                new_state = WAIT_STX;
                break;
            }
            *pRxBuf = c;


            if(pRxBuf < &rxBuffer[RXBUFLEN]) {
                // If a double DLE is received, it is DLE = 0x10 data 
                // and not initiating the end of transmission
                if(ETX == c && toggleDLE) {
                    //ESP_LOGD(TAG, "End of Transmission received -> next CSUM (0x%02X)", csum);
                    savedCsum = csum;
                    new_state = WAIT_CSUM;
                    pRxBuf++;
                } else if (DLE == c && toggleDLE) {
                    // We have a 0x10 byte of data (not control char)
                    // don't move the buffer pointer (we wrote 0x10 a cycle before)
                } else {
                    pRxBuf++;
                }
                
                // Recognition of two 0x10 as data or single 0x10 as control
                if(DLE == c) {
                    toggleDLE = !(toggleDLE);
                } else {
                    toggleDLE = false;
                }

            } else {
                ESP_LOGE(TAG, "RX Buffer overrun!");
                new_state = WAIT_STX;
            }

            break;
        
        case WAIT_CSUM:
            *pRxBuf = c;
            //ESP_LOGD(TAG, "CSUM: S:0x%02X, C:0x%02X, R:0x%02X", savedCsum, csum, c);
            this->print_hex_buffer(rxBuffer, rxLen);
            if(0x00 == csum && savedCsum == c) {
                //ESP_LOGI(TAG, "Checksum match, sending ACK = DLE");
                this->send_ACK_DLE();
                ESP_LOGD(TAG, "Received data -> Parsing TODO");
                // parse the data
            } else {
                ESP_LOGE(TAG, "Checksum mismatch, sending NAK");
                this->send_NAK();
            }
            new_state = WAIT_STX;
            break;

        default:
            state = WAIT_STX;
            new_state = WAIT_STX;
            break;
    }

    state = new_state;
    last_action = now;
    lastChar = c;
}

void KM271Component::loop() {
    static int cnt = 0;
    static uint32_t last_action;
    const uint32_t now = millis();

    if (now - last_action > ALIVE_RST) {
        ESP_LOGD(TAG, "Alive");
        last_action = now;
    }

    while(available()) {
        const char c = read();      
        //ESP_LOGD(TAG, "Recv: 0x%02X (%0.2f)", c, (now - last_action) / 1000.0);
        this->process_state(c);
        last_action = now;
    };

}

void KM271Component::setup() {
    ESP_LOGCONFIG(TAG, "Setup was called");
};

void KM271Component::update() {
    ESP_LOGI(TAG, "Update was called");
};

void KM271Component::dump_config() {
    ESP_LOGCONFIG(TAG, "Dump Config was called");
};

void KM271Component::on_shutdown() {
    ESP_LOGI(TAG, "Shutdown was called");
};

float KM271Component::get_setup_priority() const {
    return setup_priority::DATA;
}

} // namespace KM271
} // namespace esphome
