#include "km271.h"
#include "esphome/core/log.h"

namespace esphome {
namespace KM271 {

static const char *const TAG = "km271";

void KM271::loop() {
    static int cnt = 1000;
    if(0==cnt) {
        ESP_LOGD(TAG, "%s", "Test");
        cnt=1000;
    }
    cnt--;
}

}
}