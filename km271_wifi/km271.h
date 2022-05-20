#pragma once

#include <string>
#include <vector>
#include "esphome/core/component.h"
#include "esphome/components/uart/uart.h"


namespace esphome {
namespace KM271 {

class KM271 : public Component, public uart::UARTDevice {
 public:
  //void register_sml_listener(SmlListener *listener);
  void loop() override;
  //void dump_config() override;
  //std::vector<SmlListener *> sml_listeners_{};

 protected:
  //void process_km271_file_(const bytes &sml_data);
  //char check_start_end_bytes_(uint8_t byte);
  //void publish_value_(const ObisInfo &obis_info);

  // Serial parser
  bool record_ = false;
  uint16_t incoming_mask_ = 0;
  uint8_t km271_data_;
};

}
}