#pragma once

#include <string>
#include <vector>
#include <chrono>
#include <iostream>
#include <sys/time.h>
#include <ctime>
#include "esphome/core/component.h"
#include "esphome/components/sensor/sensor.h"
#include "esphome/components/uart/uart.h"


namespace esphome {
namespace KM271 {

class KM271Component : public PollingComponent, public uart::UARTDevice {
 public:
  //void register_sml_listener(SmlListener *listener);

  void loop() override;
  //void dump_config() override;
  //std::vector<SmlListener *> sml_listeners_{};
  // KM271 (uint32_t updateInterval, uart::UARTComponent *parent) : 
  //   PollingComponent(updateInterval), uart::UARTDevice(parent)
  // {
  //   parentUC = parent;
  // }

  // KM271 () : PollingComponent(1000) {}

  void setup();
  void dump_config();
  float get_setup_priority() const override;
  void update();
  void on_shutdown();

 protected:
  //void process_km271_file_(const bytes &sml_data);
  //char check_start_end_bytes_(uint8_t byte);
  //void publish_value_(const ObisInfo &obis_info);

  // Serial parser
  bool record_ = false;
  uint16_t incoming_mask_ = 0;
  uint8_t km271_data_;
};

} // namespace KM271
} // namespace esphome