#ifndef KM271_HELPERS_H
#define KM271_HELPERS_H

#include <stdint.h>
#include <stddef.h>

namespace esphome {
namespace KM271 {


size_t buffer_to_hex(char* outbuf, const uint8_t* inbuf, size_t len);
void log_hex_buffer(const char *name, const uint8_t* buf, size_t len);

}
}

#endif // KM271_HELPERS_H
