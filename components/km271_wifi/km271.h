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


#define GENERATE_SENSOR_SETTER(key, parameterId, sensorTypeParam) void set_##key##_sensor(esphome::sensor::Sensor *sensor) \
  { set_sensor(parameterId, sensorTypeParam, sensor); }
#define GENERATE_BINARY_SENSOR_SETTER(key, parameterId, sensorTypeParam) void set_##key##_binary_sensor(esphome::binary_sensor::BinarySensor *sensor) \
  { set_binary_sensor(parameterId, sensorTypeParam, sensor); }
#define GENERATE_SWITCH_SETTER(key, parameterId, sensorTypeParam) void set_##key##_switch(BuderusParamSwitch *switch_) \
  { set_switch(parameterId, sensorTypeParam, switch_); }
#define GENERATE_NUMBER_SETTER(key, parameterId, sensorTypeParam) void set_##key##_number(BuderusParamNumber *number) \
  { set_number(parameterId, sensorTypeParam, number); }


namespace esphome {
namespace KM271 {

class KM271Component : public Component, public uart::UARTDevice {
 public:
  KM271Component();

  void loop() override;
  void dump_config() override;

  // Betriebswerte 1 HK1
  GENERATE_BINARY_SENSOR_SETTER(heating_circuit_1_switch_off_optimization, BW1HK1, 0);
  GENERATE_BINARY_SENSOR_SETTER(heating_circuit_1_switch_on_optimization, BW1HK1, 1);
  GENERATE_BINARY_SENSOR_SETTER(heating_circuit_1_automatic, BW1HK1, 2);
  GENERATE_BINARY_SENSOR_SETTER(heating_circuit_1_ww_priority_processing, BW1HK1, 3);
  GENERATE_BINARY_SENSOR_SETTER(heating_circuit_1_screed_drying, BW1HK1, 4);
  GENERATE_BINARY_SENSOR_SETTER(heating_circuit_1_holiday, BW1HK1, 5);
  GENERATE_BINARY_SENSOR_SETTER(heating_circuit_1_antifreeze, BW1HK1, 6);
  GENERATE_BINARY_SENSOR_SETTER(heating_circuit_1_manually, BW1HK1, 7);
  // Betriebswerte 2 HK1
  GENERATE_BINARY_SENSOR_SETTER(heating_circuit_1_summer, BW2HK1, 0);
  GENERATE_BINARY_SENSOR_SETTER(heating_circuit_1_day, BW2HK1, 1);
  GENERATE_BINARY_SENSOR_SETTER(heating_circuit_1_no_comm_with_rc, BW2HK1, 2);
  GENERATE_BINARY_SENSOR_SETTER(heating_circuit_1_rc_faulty, BW2HK1, 3);
  GENERATE_BINARY_SENSOR_SETTER(heating_circuit_1_flow_sensor_error, BW2HK1, 4);
  GENERATE_BINARY_SENSOR_SETTER(heating_circuit_1_max_flow, BW2HK1, 5);
  GENERATE_BINARY_SENSOR_SETTER(heating_circuit_1_external_fault_input, BW2HK1, 6);
  // GENERATE_BINARY_SENSOR_SETTER(heating_circuit_1_party_pause, BW2HK1, 7);

  GENERATE_SENSOR_SETTER(heating_circuit_1_flow_target_temperature, VSTHK1, 0);
  GENERATE_SENSOR_SETTER(heating_circuit_1_flow_temperature, VITHK1, 0);
  GENERATE_SENSOR_SETTER(heating_circuit_1_room_target_temperature, RSTHK1, 0);
  GENERATE_SENSOR_SETTER(heating_circuit_1_room_temperature, RITHK1, 0);
  GENERATE_SENSOR_SETTER(heating_circuit_1_pump_power, PLHK1, 0);
  GENERATE_SENSOR_SETTER(heating_circuit_1_mixer_position, MSHK1, 0);
  GENERATE_SENSOR_SETTER(heating_circuit_1_curve_p10, KLHK1_P10, 0);
  GENERATE_SENSOR_SETTER(heating_circuit_1_curve_0, KLHK1_P00, 0);
  GENERATE_SENSOR_SETTER(heating_circuit_1_curve_n10, KLHK1_N10, 0);

  // Betriebswerte 1 HK2
  GENERATE_BINARY_SENSOR_SETTER(heating_circuit_2_switch_off_optimization, BW1HK2, 0);
  GENERATE_BINARY_SENSOR_SETTER(heating_circuit_2_switch_on_optimization, BW1HK2, 1);
  GENERATE_BINARY_SENSOR_SETTER(heating_circuit_2_automatic, BW1HK2, 2);
  GENERATE_BINARY_SENSOR_SETTER(heating_circuit_2_ww_priority_processing, BW1HK2, 3);
  GENERATE_BINARY_SENSOR_SETTER(heating_circuit_2_screed_drying, BW1HK2, 4);
  GENERATE_BINARY_SENSOR_SETTER(heating_circuit_2_holiday, BW1HK2, 5);
  GENERATE_BINARY_SENSOR_SETTER(heating_circuit_2_antifreeze, BW1HK2, 6);
  GENERATE_BINARY_SENSOR_SETTER(heating_circuit_2_manually, BW1HK2, 7);
  // Betriebswerte 2 HK2
  GENERATE_BINARY_SENSOR_SETTER(heating_circuit_2_summer, BW2HK2, 0);
  GENERATE_BINARY_SENSOR_SETTER(heating_circuit_2_day, BW2HK2, 1);
  GENERATE_BINARY_SENSOR_SETTER(heating_circuit_2_no_comm_with_rc, BW2HK2, 2);
  GENERATE_BINARY_SENSOR_SETTER(heating_circuit_2_rc_faulty, BW2HK2, 3);
  GENERATE_BINARY_SENSOR_SETTER(heating_circuit_2_flow_sensor_error, BW2HK2, 4);
  GENERATE_BINARY_SENSOR_SETTER(heating_circuit_2_max_flow, BW2HK2, 5);
  GENERATE_BINARY_SENSOR_SETTER(heating_circuit_2_external_fault_input, BW2HK2, 6);
  //GENERATE_BINARY_SENSOR_SETTER(heating_circuit_2_party_pause, BW2HK2, 7);

  GENERATE_SENSOR_SETTER(heating_circuit_2_flow_target_temperature, VSTHK2, 0);
  GENERATE_SENSOR_SETTER(heating_circuit_2_flow_temperature, VITHK2, 0);
  GENERATE_SENSOR_SETTER(heating_circuit_2_room_target_temperature, RSTHK2, 0);
  GENERATE_SENSOR_SETTER(heating_circuit_2_room_temperature, RITHK2, 0);
  GENERATE_SENSOR_SETTER(heating_circuit_2_pump_power, PLHK2, 0);
  GENERATE_SENSOR_SETTER(heating_circuit_2_mixer_position, MSHK2, 0);
  GENERATE_SENSOR_SETTER(heating_circuit_2_curve_p10, KLHK2_P10, 0);
  GENERATE_SENSOR_SETTER(heating_circuit_2_curve_0, KLHK2_P00, 0);
  GENERATE_SENSOR_SETTER(heating_circuit_2_curve_n10, KLHK2_N10, 0);

  // Betriebswerte 1 WW
  GENERATE_BINARY_SENSOR_SETTER(ww_automatic, BW1WW, 0);
  GENERATE_BINARY_SENSOR_SETTER(ww_disinfection, BW1WW, 1);
  GENERATE_BINARY_SENSOR_SETTER(ww_reload, BW1WW, 2);
  GENERATE_BINARY_SENSOR_SETTER(ww_holiday, BW1WW, 3);
  GENERATE_BINARY_SENSOR_SETTER(ww_error_disinfection, BW1WW, 4);
  GENERATE_BINARY_SENSOR_SETTER(ww_error_sensor, BW1WW, 5);
  GENERATE_BINARY_SENSOR_SETTER(ww_error_stays_cold, BW1WW, 6);
  GENERATE_BINARY_SENSOR_SETTER(ww_error_anode, BW1WW, 7);
  // Betriebswerte 2 WW
  GENERATE_BINARY_SENSOR_SETTER(ww_loading, BW2WW, 0);
  GENERATE_BINARY_SENSOR_SETTER(ww_manually, BW2WW, 1);
  GENERATE_BINARY_SENSOR_SETTER(ww_reloading, BW2WW, 2);
  GENERATE_BINARY_SENSOR_SETTER(ww_switch_off_optimization, BW2WW, 3);
  GENERATE_BINARY_SENSOR_SETTER(ww_switch_on_optimization, BW2WW, 4);
  GENERATE_BINARY_SENSOR_SETTER(ww_day_mode, BW2WW, 5);
  GENERATE_BINARY_SENSOR_SETTER(ww_post_processing, BW2WW, 6);
  GENERATE_BINARY_SENSOR_SETTER(ww_priority_processing, BW2WW, 7);

  GENERATE_SENSOR_SETTER(ww_target_temperature, WWST, 0);
  GENERATE_SENSOR_SETTER(ww_temperature, WWIT, 0);

  GENERATE_SENSOR_SETTER(boiler_target_temperature, KVST, 0);
  GENERATE_SENSOR_SETTER(boiler_temperature, KVIT, 0);
  GENERATE_SENSOR_SETTER(boiler_turn_on_temperature, BET, 0);
  GENERATE_SENSOR_SETTER(boiler_turn_off_temperature, BAT, 0);
  GENERATE_SENSOR_SETTER(exhaust_gas_temperature, ABTMP, 0);

  GENERATE_SENSOR_SETTER(outdoor_temperature, AT, 0);
  GENERATE_SENSOR_SETTER(attenuated_outdoor_temperature, ATD, 0);
  GENERATE_SENSOR_SETTER(boiler_runtime_1, BLZ1S0, 0x100);
  GENERATE_SENSOR_SETTER(boiler_runtime_2, BLZ2S0, 0x200);

  // Pumpenansteuerung
  GENERATE_BINARY_SENSOR_SETTER(load_pump_running, LPWW, 0);
  GENERATE_BINARY_SENSOR_SETTER(circulation_pump_running, LPWW, 1);
  GENERATE_BINARY_SENSOR_SETTER(solar_pump_lowering, LPWW, 2);
  // Kesselfehler
  GENERATE_BINARY_SENSOR_SETTER(error_burner_malfunction, KFEHL, 0);
  GENERATE_BINARY_SENSOR_SETTER(error_boiler_sensor, KFEHL, 1);
  GENERATE_BINARY_SENSOR_SETTER(error_additional_sensor, KFEHL, 2);
  GENERATE_BINARY_SENSOR_SETTER(error_boiler_stays_cold, KFEHL, 3);
  GENERATE_BINARY_SENSOR_SETTER(error_exhaust_gas_sensor, KFEHL, 4);
  GENERATE_BINARY_SENSOR_SETTER(error_exhaust_gas_over_limit, KFEHL, 5);
  GENERATE_BINARY_SENSOR_SETTER(error_safety_chain_released, KFEHL, 6);
  GENERATE_BINARY_SENSOR_SETTER(error_external_disturbance, KFEHL, 7);
  // Kesselbetrieb
  GENERATE_BINARY_SENSOR_SETTER(boiler_emission_test, KBETR, 0);
  GENERATE_BINARY_SENSOR_SETTER(boiler_1st_stage_operation, KBETR, 1);
  GENERATE_BINARY_SENSOR_SETTER(boiler_protection, KBETR, 2);
  GENERATE_BINARY_SENSOR_SETTER(boiler_under_operation, KBETR, 3);
  GENERATE_BINARY_SENSOR_SETTER(boiler_performance_free, KBETR, 4);
  GENERATE_BINARY_SENSOR_SETTER(boiler_performance_high, KBETR, 5);
  GENERATE_BINARY_SENSOR_SETTER(boiler_2st_stage_operation, KBETR, 6);

  GENERATE_BINARY_SENSOR_SETTER(boiler_actuation, BANST, 0);
  // Alarmstatus
  GENERATE_BINARY_SENSOR_SETTER(alarm_exhaust_gas_sensor, ALARM, 0);
  //GENERATE_BINARY_SENSOR_SETTER(alarm_02, ALARM, 1);
  GENERATE_BINARY_SENSOR_SETTER(alarm_boiler_flow_sensor, ALARM, 2);
  //GENERATE_BINARY_SENSOR_SETTER(alarm_08, ALARM, 3);
  GENERATE_BINARY_SENSOR_SETTER(alarm_burner, ALARM, 4);
  //GENERATE_BINARY_SENSOR_SETTER(alarm_20, ALARM, 5);
  GENERATE_BINARY_SENSOR_SETTER(alarm_heating_circuit_2_flow_sensor, ALARM, 6);
  //GENERATE_BINARY_SENSOR_SETTER(alarm_80, ALARM, 7);

  GENERATE_SWITCH_SETTER(ww_heating_auto_off, CFG_WW_Aufbereitung, 0);
  GENERATE_NUMBER_SETTER(ww_temperature, CFG_WW_Temperatur, 3);
  GENERATE_NUMBER_SETTER(hc1_design_temperature, CFG_HK1_Auslegungstemperatur, 4);

  void setup();
  float get_setup_priority() const override;
  void update();
  void on_shutdown();
  Writer3964R writer;

 protected:
  const t_Buderus_R2017_ParamDesc *findParameterForNewSensor(Buderus_R2017_ParameterId parameterId, uint16_t sensorTypeParam, bool writableRequired);

  void set_sensor(Buderus_R2017_ParameterId parameterId, uint16_t sensorTypeParam, esphome::sensor::Sensor *sensor);
  void set_binary_sensor(Buderus_R2017_ParameterId parameterId, uint16_t sensorTypeParam, esphome::binary_sensor::BinarySensor *sensor);
  void set_switch(Buderus_R2017_ParameterId parameterId, uint16_t sensorTypeParam, BuderusParamSwitch *switch_);
  void set_number(Buderus_R2017_ParameterId parameterId, uint16_t sensorTypeParam, BuderusParamNumber *number);

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
  /** used to call the loop function of the sensors every x calls to the loop function of the component */
  uint8_t sensorLoopCounter;
};

} // namespace KM271
} // namespace esphome
