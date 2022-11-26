# KM271 WiFi Component

This component is the counterpart of the KM271 WiFi extension from the78mole

## How to install

Simply add the external component lines to your device's YAML file in ESPhome and configure the sensors and other stuff you need. 
An example yaml could be also found in this GIT repo.

    external_components:
      - source: github://the78mole/esphome_components@main
      components: [ km271_wifi ]

    km271_wifi:
    - id: budoil
      uart_id: uart_bus

    binary_sensor:
      - platform: km271_wifi
        boiler_error:
          name: "Kesselfehler"
        boiler_running:
          name: "Kesselbetrieb"
        load_pump_running:
          name: "Ladepumpenbetrieb"

    sensor:
      - platform: km271_wifi
        heating_circuit_1_flow_target_temperature:
          name: "Vorlaufsolltemperatur"
        heating_circuit_1_flow_temperature:
          name: "Vorlauftemperatur"
        hot_water_target_temperature:
          name: "Warmwassersolltemperatur"
        hot_water_temperature:
          name: "Warmwassertemperatur"
        boiler_target_temperature:
          name: "Kesselvorlaufsolltemperatur"
        boiler_temperature:
          name: "Kesselvorlauftemperatur"
        outdoor_temperature:
          name: "Außentemperatur"

The Sensors shall look like this:

TODO