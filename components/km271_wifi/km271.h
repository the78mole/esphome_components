#pragma once

#include <string>
#include <vector>
#include <chrono>
#include <iostream>
#include <sys/time.h>
#include <ctime>
#include "3964r.h"
#include "esphome/core/component.h"
#include "esphome/components/sensor/sensor.h"
#include "esphome/components/uart/uart.h"
#include "km271_params.h"


#define GENERATE_SENSOR_SETTER(key, parameterId) void set_##key##_sensor(esphome::sensor::Sensor *sensor) { set_sensor(parameterId, sensor); }
#define GENERATE_BINARY_SENSOR_SETTER(key, parameterId) void set_##key##_binary_sensor(esphome::binary_sensor::BinarySensor *sensor) { set_binary_sensor(parameterId, sensor); }


namespace esphome {
namespace KM271 {

class KM271Component : public Component, public uart::UARTDevice {
 public:
  KM271Component();

  void loop() override;
  void dump_config() override;

  GENERATE_SENSOR_SETTER(heating_circuit_1_flow_target_temperature, VSTHK1);
  GENERATE_SENSOR_SETTER(heating_circuit_1_flow_temperature, VITHK1);
  GENERATE_SENSOR_SETTER(hot_water_target_temperature, WWST);
  GENERATE_SENSOR_SETTER(hot_water_temperature, WWIT);
  GENERATE_SENSOR_SETTER(boiler_target_temperature, KVST);
  GENERATE_SENSOR_SETTER(boiler_temperature, KVIT);
  GENERATE_SENSOR_SETTER(outdoor_temperature, AT);
  GENERATE_BINARY_SENSOR_SETTER(boiler_error, KFEHL);
  GENERATE_BINARY_SENSOR_SETTER(boiler_running, KBETR);
  GENERATE_BINARY_SENSOR_SETTER(load_pump_running, LPWW);


  void setup();
  float get_setup_priority() const override;
  void update();
  void on_shutdown();


 protected:
  void set_sensor(Buderus_R2017_ParameterId parameterId, esphome::sensor::Sensor *sensor);
  void set_binary_sensor(Buderus_R2017_ParameterId parameterId, esphome::binary_sensor::BinarySensor *sensor);


  void process_incoming_byte(uint8_t c);
  void parse_buderus(uint8_t * buf, size_t len);


  // Helper function (for better readability of code)
  void send_ACK_DLE();
  void send_NAK();
  void writeRequestValues();
  size_t genDataString(char* outbuf, uint8_t* inbuf, size_t len);
  void print_hex_buffer(uint8_t* buf, size_t len);


  uint32_t last_received_byte_time;


  Parser3964R parser;
  Writer3964R writer;
};

} // namespace KM271
} // namespace esphome
