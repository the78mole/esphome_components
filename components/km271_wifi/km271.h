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
  GENERATE_SENSOR_SETTER(heating_circuit_1_room_target_temperature, RSTHK1);
  GENERATE_SENSOR_SETTER(heating_circuit_1_room_temperature, RITHK1);
  GENERATE_SENSOR_SETTER(heating_circuit_1_pump_power, PLHK1);
  GENERATE_SENSOR_SETTER(heating_circuit_1_mixer_position, MSHK1);
  GENERATE_SENSOR_SETTER(heating_circuit_1_curve_p10, KLHK1_P10);
  GENERATE_SENSOR_SETTER(heating_circuit_1_curve_0, KLHK1_P00);
  GENERATE_SENSOR_SETTER(heating_circuit_1_curve_n10, KLHK1_N10);
  GENERATE_SENSOR_SETTER(heating_circuit_2_flow_target_temperature, VSTHK2);
  GENERATE_SENSOR_SETTER(heating_circuit_2_flow_temperature, VITHK2);
  GENERATE_SENSOR_SETTER(heating_circuit_2_room_target_temperature, RSTHK2);
  GENERATE_SENSOR_SETTER(heating_circuit_2_room_temperature, RITHK2);
  GENERATE_SENSOR_SETTER(heating_circuit_2_pump_power, PLHK2);
  GENERATE_SENSOR_SETTER(heating_circuit_2_mixer_position, MSHK2);
  GENERATE_SENSOR_SETTER(heating_circuit_2_curve_p10, KLHK2_P10);
  GENERATE_SENSOR_SETTER(heating_circuit_2_curve_0, KLHK2_P00);
  GENERATE_SENSOR_SETTER(heating_circuit_2_curve_n10, KLHK2_N10);
  GENERATE_SENSOR_SETTER(hot_water_target_temperature, WWST);
  GENERATE_SENSOR_SETTER(hot_water_temperature, WWIT);
  GENERATE_SENSOR_SETTER(boiler_target_temperature, KVST);
  GENERATE_SENSOR_SETTER(boiler_temperature, KVIT);
  GENERATE_SENSOR_SETTER(boiler_turn_on_temperature, BET);
  GENERATE_SENSOR_SETTER(boiler_turn_off_temperature, BAT);
  GENERATE_SENSOR_SETTER(exhaust_gas_temperature, ABTMP);
  GENERATE_SENSOR_SETTER(outdoor_temperature, AT);
  GENERATE_SENSOR_SETTER(attenuated_outdoor_temperature, ATD);

  GENERATE_BINARY_SENSOR_SETTER(load_pump_running, LPWW);
  GENERATE_BINARY_SENSOR_SETTER(boiler_error, KFEHL);
  GENERATE_BINARY_SENSOR_SETTER(boiler_running, KBETR);
  GENERATE_BINARY_SENSOR_SETTER(boiler_actuation, BANST);

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
