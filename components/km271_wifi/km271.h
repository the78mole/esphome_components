#pragma once

#include <string>
#include "esphome/core/component.h"
#include "esphome/components/sensor/sensor.h"
#include "esphome/components/binary_sensor/binary_sensor.h"
#include "esphome/components/uart/uart.h"

#include "3964r.h"
#include "km271_communication_components.h"
#include "km271_params.h"


namespace esphome {
namespace KM271 {

class KM271Component : public Component, public uart::UARTDevice {
 public:
  KM271Component();

  void loop() override;
  void dump_config() override;

  void setup();
  float get_setup_priority() const override;
  void update();
  void on_shutdown();
  Writer3964R writer;

  void set_sensor(TransmissionParameter transmissionParameter, esphome::sensor::Sensor *sensor);
  void set_binary_sensor(TransmissionParameter transmissionParameter, esphome::binary_sensor::BinarySensor *sensor);
  void set_communication_component(TransmissionParameter transmissionParameter, CommunicationComponent *component);


 protected:
  const t_Buderus_R2017_ParamDesc *findParameterForNewSensor(TransmissionParameter transmissionParameter);

  void process_incoming_byte(uint8_t c);
  void parse_buderus(uint8_t * buf, size_t len);

  // Helper function (for better readability of code)
  void send_ACK_DLE();
  void send_NAK();
  void writeRequestValues();

  uint32_t last_received_byte_time;
  Parser3964R parser;
  /** used to call the loop function of the sensors every x calls to the loop function of the component */
  uint8_t sensorLoopCounter;
};

} // namespace KM271
} // namespace esphome
