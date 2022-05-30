#include "km271_params.h"
#include "esphome/core/log.h"
#include "esphome/core/util.h"

namespace esphome {
namespace KM271 {

static const char *const TAG = "BPARM";

template <class T> uint16_t TBuderusParam<T>::getParamId() { return _paramId; };

template <class T> TBuderusParam<T>::TBuderusParam(uint16_t paramId, const char * desc, Units unit) 
    : _paramId(paramId), _desc(desc), _unit(unit) 
{};

template <class T> void TBuderusParam<T>::parseData(const char * buf) {

}

template <class T> T TBuderusParam<T>::parseGetValue(const char * buf) {
    parseData(buf);
    return getValue();
}

// Specialized classes
template <> int TBuderusParam<int>::getValue() { 
    return 0;
}




BuderusParams::BuderusParams() {
    ESP_LOGD(TAG, "Test");
}

void BuderusParams::init() {
    ESP_LOGD(TAG, "Init called.")
}

}
}