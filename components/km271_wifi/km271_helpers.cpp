#include "km271_helpers.h"

#include <string.h>
#include <stdio.h>
#include "esphome/core/log.h"


namespace esphome {
namespace KM271 {

static const char *const TAG = "KM271";

/** @todo respect output buffer size */
size_t buffer_to_hex(char* outbuf, const uint8_t* inbuf, size_t len)
{
    char* pBuf = outbuf;

    for(size_t i = 0; i < len; i++) {
        pBuf += sprintf(pBuf, "%02X ", inbuf[i]);
    }
    return (pBuf - outbuf);
}

void log_hex_buffer(const char* name, const uint8_t* buf, size_t len)
{
    uint16_t bufSize = 256;
    char tmpBuf[bufSize];
    buffer_to_hex(tmpBuf, buf, len);
    ESP_LOGD(TAG, "%s [%d]: 0x%s", name, len, tmpBuf);
}

}
}
