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
        load_pump_running:
          name: "Ladepumpenbetrieb"
        boiler_error:
          name: "Kesselfehler"
        boiler_running:
          name: "Kesselbetrieb"
        boiler_actuation:
          name: "Brenneransteuerung"

    sensor:
      - platform: km271_wifi
        heating_circuit_1_flow_target_temperature:
          name: "HK1 Vorlaufsolltemperatur"
        heating_circuit_1_flow_temperature:
          name: "HK1 Vorlaufisttemperatur"
        heating_circuit_1_room_target_temperature:
          name: "HK1 Raumsolltemperatur"
        heating_circuit_1_room_temperature:
          name: "HK1 Raumisttemperatur"
        heating_circuit_1_pump_power:
          name: "HK1 Pumpenleistung"
        heating_circuit_1_mixer_position:
          name: "HK1 Mischerstellung"
        heating_circuit_1_curve_p10:
          name: "HK1 Heizkurve +10 °C"
        heating_circuit_1_curve_0:
          name: "HK1 Heizkurve 0 °C"
        heating_circuit_1_curve_n10:
          name: "HK1 Heizkurve -10 °C"
        heating_circuit_2_flow_target_temperature:
          name: "HK2 Vorlaufsolltemperatur"
        heating_circuit_2_flow_temperature:
          name: "HK2 Vorlaufisttemperatur"
        heating_circuit_2_room_target_temperature:
          name: "HK2 Raumsolltemperatur"
        heating_circuit_2_room_temperature:
          name: "HK2 Raumisttemperatur"
        heating_circuit_2_pump_power:
          name: "HK2 Pumpenleistung"
        heating_circuit_2_mixer_position:
          name: "HK2 Mischerstellung"
        heating_circuit_2_curve_p10:
          name: "HK2 Heizkurve +10 °C"
        heating_circuit_2_curve_0:
          name: "HK2 Heizkurve 0 °C"
        heating_circuit_2_curve_n10:
          name: "HK2 Heizkurve -10 °C"
        hot_water_target_temperature:
          name: "Warmwassersolltemperatur"
        hot_water_temperature:
          name: "Warmwasseristtemperatur"
        boiler_target_temperature:
          name: "Kesselvorlaufsolltemperatur"
        boiler_temperature:
          name: "Kesselvorlaufisttemperatur"
        boiler_turn_on_temperature:
          name: "Brennereinschalttemperatur"
        boiler_turn_off_temperature:
          name: "Brennerausschalttemperatur"
        exhaust_gas_temperature:
          name: "Abgastemperatur"
        outdoor_temperature:
          name: "Außentemperatur"
        attenuated_outdoor_temperature:
          name: "Gedaempfte Aussentemperatur"

    switch:

    number:

## How do I?
This section explains how certain features of the software can be used.


### How do I set the time / day of week of the heater via Home Assistant?

This is currently a little clunky.
First, have a look at ./snippets/buderus-km271-set-date-and-time.yaml and
merge the three sections into your ESPhome yaml file. Compile and install.

Now Home Assistant should show new entities to input the hours, minutes and
so on.
After setting those entities to the desired values, push the button "Datum
und Zeit setzen". This writes the settings to the controller.

While it seems that we can write a full date time object, only the fields
for hour, minute and day of week seem to have any effect on the Logamatic
2107. These three values are also the only values changeable using the
physical control interface.

Reading of the current time is not supported at the moment. If somebody has
an idea on how to this, please come forward!