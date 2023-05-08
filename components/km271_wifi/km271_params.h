#pragma once

#include <string>
#include "esphome/core/component.h"
#include "esphome/components/sensor/sensor.h"
#include "esphome/components/binary_sensor/binary_sensor.h"
#include <unordered_map>
#include <functional>

namespace esphome {
namespace KM271 {

class CommunicationComponent;


/** a buderus R2017 parameter identfies a group of values sent from the control unit in one telegram */
enum Buderus_R2017_ParameterId {
    BW1HK1    = 0x8000, //: "Betriebswerte 1 HK1"
    BW2HK1    = 0x8001, //: "Betriebswerte 2 HK1"
    VSTHK1    = 0x8002, //: "Vorlaufsolltemperatur HK1"       (Grad)
    VITHK1    = 0x8003, //: "Vorlaufisttemperatur HK1"        (Grad)
    RSTHK1    = 0x8004, //: "Raumsolltemperatur HK1"          (Grad)
    RITHK1    = 0x8005, //: "Raumisttemperatur HK1"           (Grad)
    EOZHK1    = 0x8006, //: "Einschaltoptimierungszeit HK1"
    AOZHK1    = 0x8007, //: "Ausschaltoptimierungszeit HK1"
    PLHK1     = 0x8008, //: "Pumpenleistung HK1"              (Prozent)
    MSHK1     = 0x8009, //: "Mischerstellung HK1"             (Prozent)
    NB01      = 0x800a, //: "nicht belegt"
    NB02      = 0x800b, //: "nicht belegt"
    KLHK1_P10 = 0x800c, //: "Heizkennlinie HK1 bei + 10 Grad" (Grad)
    KLHK1_P00 = 0x800d, //: "Heizkennlinie HK1 bei 0 Grad"    (Grad)
    KLHK1_N10 = 0x800e, //: "Heizkennlinie HK1 bei - 10 Grad" (Grad)
    NB03      = 0x800f, //: "nicht belegt"
    NB04      = 0x8010, //: "nicht belegt"
    NB05      = 0x8011, //: "nicht belegt"

    BW1HK2    = 0x8112, //: "Betriebswerte 1 HK2"
    BW2HK2    = 0x8113, //: "Betriebswerte 2 HK2"
    VSTHK2    = 0x8114, //: "Vorlaufsolltemperatur HK2"       (Grad)
    VITHK2    = 0x8115, //: "Vorlaufisttemperatur HK2"        (Grad)
    RSTHK2    = 0x8116, //: "Raumsolltemperatur HK2"          (Grad)
    RITHK2    = 0x8117, //: "Raumisttemperatur HK2"           (Grad)
    EOZHK2    = 0x8118, //: "Einschaltoptimierungszeit HK2"
    AOZHK2    = 0x8119, //: "Ausschaltoptimierungszeit HK2"
    PLHK2     = 0x811a, //: "Pumpenleistung HK2"              (Prozent)
    MSHK2     = 0x811b, //: "Mischerstellung HK2"             (Prozent)
    NB06      = 0x811c, //: "nicht belegt"
    NB07      = 0x811d, //: "nicht belegt"
    KLHK2_P10 = 0x811e, //: "Heizkennlinie HK2 bei + 10 Grad" (Grad)
    KLHK2_P00 = 0x811f, //: "Heizkennlinie HK2 bei 0 Grad"    (Grad)
    KLHK2_N10 = 0x8120, //: "Heizkennlinie HK2 bei - 10 Grad" (Grad)
    NB08      = 0x8121, //: "nicht belegt"
    NB09      = 0x8122, //: "nicht belegt"
    NB10      = 0x8123, //: "nicht belegt"

    BW1WW     = 0x8424, //: "Betriebswerte 1 WW"
    BW2WW     = 0x8425, //: "Betriebswerte 2 WW"
    WWST      = 0x8426, //: "Warmwassersolltemperatur"        (Grad)
    WWIT      = 0x8427, //: "Warmwasseristtemperatur",        (Grad)
    OZWW      = 0x8428, //: "Warmwasseroptimierungszeit"
    LPWW      = 0x8429, //: "Ladepumpe"                       ["aus", "Ladepumpe", "Warmwasserpumpe", "beide"]

    KVST      = 0x882a, //: "Kesselvorlaufsolltemperatur"     (Grad)
    KVIT      = 0x882b, //: "Kesselvorlaufisttemperatur"      (Grad)
    BET       = 0x882c, //: "Brennereinschalttemperatur"      (Grad)
    BAT       = 0x882d, //: "Brennerausschalttemperatur"      (Grad)
    KINT1     = 0x882e, //: "Kesselintegral 1"
    KINT2     = 0x882f, //: "Kesselintegral 2"
    KFEHL     = 0x8830, //: "Kesselfehler"
    KBETR     = 0x8831, //: "Kesselbetrieb"
    BANST     = 0x8832, //: "Brenneransteuerung"              ["aus", "an"]
    ABTMP     = 0x8833, //: "Abgastemperatur"                 (Grad)
    MODBSTELL = 0x8834, //: "modulare Brenner Stellwert"
    NB11      = 0x8835, //: "nicht belegt"
    BLZ1S2    = 0x8836, //: "Brennerlaufzeit 1 Minuten 2"
    BLZ1S1    = 0x8837, //: "Brennerlaufzeit 1 Minuten 1"
    BLZ1S0    = 0x8838, //: "Brennerlaufzeit 1 Minuten 0"
    BLZ2S2    = 0x8839, //: "Brennerlaufzeit 2 Minuten 2"
    BLZ2S1    = 0x883a, //: "Brennerlaufzeit 2 Minuten 1"
    BLZ2S0    = 0x883b, //: "Brennerlaufzeit 2 Minuten 0"

    AT        = 0x893c, //: "Aussentemperatur"                (Grad)
    ATD       = 0x893d, //: "gedaempfte Aussentemperatur"     (Grad)
    VVK       = 0x893e, //: "Versionsnummer VK"
    VNK       = 0x893f, //: "Versionsnummer NK"
    MODKENN   = 0x8940, //: "Modulkennung"
    NB12      = 0x8941, //: "nicht belegt"

    ALARM     = 0xaa42, //: "ERR_Alarmstatus"

    CFG000    = 0x0000, //: "#1 Sommer ab, #2 HK1 Nachttemp, #3 HK1 Tagtemp, #4 HK1 Betriebsart, #5 HK1 Urlaubstemp"
    CFG00E    = 0x000E, //: "#0 WW Betriebsart, #2 HK1 Max Temperatur, #4 HK1 Auslegungstemp"
    CFG015    = 0x0015, //: "#0 HK1 Aufschalttemp, #1 WW Vorrangschaltung, #2 HK1 Aussenhalt Umschalttemp"
    CFG01C    = 0x001c, //: "#1 HK1 Absenkungsart, #2 HK1 Heizsystem"
    CFG031    = 0x0031, //: "#3 HK1 Temperatur Offset, #4 HK1 Fernbedienung, #5 Frost ab"

    CFG038    = 0x0038, //: "#1 Sommer ab, #2 HK2 Nachttemp, #3 HK2 Tagtemp, #4 HK2 Betriebsart, #5 HK2 Urlaubstemp"
    CFG046    = 0x0046, //: "#0 WW Betriebsart, #2 HK2 Max Temperatur, #4 HK2 Auslegungstemp"
    CFG04D    = 0x004D, //: "#0 HK2 Aufschalttemp, #1 WW Vorrangschaltung, #2 HK2 Aussenhalt Umschalttemp"
    CFG054    = 0x0054, //: "#1 HK2 Absenkungsart, #2 HK2 Heizsystem"
    CFG069    = 0x0069, //: "#3 HK2 Temperatur Offset, #4 HK2 Fernbedienung, #5 Frost ab"

    CFG070    = 0x0070, //: "#2 Gebäudeart"
    CFG07E    = 0x007e, //: "#3 WW Temperatur"
    CFG085    = 0x0085, //: "#0 WW Betriebsart, #3 WW Aufbereitung, #5 WW Zirkulation"
    CFG093    = 0x0093, //: "#0 Sprache, #1 Anzeige"
    CFG09A    = 0x009a, //: "#1 Brennerart, #3 Max Kesseltemperatur"
    CFG0A1    = 0x00a1, //: "#0 Pumplogik, #5 Abgastemperaturschwelle"
    CFG0A8    = 0x00a8, //: "#0 Brenner Minuten Modulation, #1 Brenner Modulation Laufzeit"
    CFG100    = 0x0100, //: "#0 HK1 HK1 Heizprogramm, #3 HK1 Urlaub(stage)"
    CFG169    = 0x0169, //: "#0 HK1 HK1 Heizprogramm, #3 HK1 Urlaub(stage)"
    CFG1E0    = 0x01E0, //: "#0 Uhrzeit offset"

//    CFG300    = 0x0300, //: "Fehlerspeicher1"
//    CFG307    = 0x0307, //: "Fehlerspeicher2"
//    CFG30E    = 0x030e, //: "Fehlerspeicher3"
//    CFG315    = 0x0315, //: "Fehlerspeicher4"
};

enum SensorType {
    NONE = 0,
    UNSIGNED_INT,
    SIGNED_INT,
    UNSIGNED_INT_DIVIDED_BY_2,
    STRING,
    BYTE_AT_OFFSET, // a single byte, with offset in bytes specified in sensor param
    BYTE_DIVIDED_BY_2_AT_OFFSET, // a single byte that needs to be divided by two after reading, with offset in bytes specified in sensor param
    BIT_AT_OFFSET, // a single bit, with offset in bits specified in sensor param
    MULTI_PARAMETER_UNSIGNED_INTEGER,  // a 24 bit unsigned integer that spans multiple parameters. sensor type determines the weight of the value: 0-2
    FIRMWARE_VERSION // two bytes that spans two parameters. sensor type param 0 => major version, sensors type param 1 => minor version
};


/** A transmission parameter identifies a single value to be transmitted to home assistant */
enum TransmissionParameter
{
    no_transmission,
    alarm_boiler_flow_sensor,
    alarm_burner,
    alarm_exhaust_gas_sensor,
    alarm_heating_circuit_2_flow_sensor,
    attenuated_outdoor_temperature,
    boiler_1st_stage_operation,
    boiler_2st_stage_operation,
    boiler_actuation,
    boiler_emission_test,
    boiler_error,
    boiler_performance_free,
    boiler_performance_high,
    boiler_protection,
    boiler_running,
    boiler_runtime_1,
    boiler_runtime_2,
    boiler_target_temperature,
    boiler_temperature,
    boiler_turn_off_temperature,
    boiler_turn_on_temperature,
    boiler_under_operation,
    circulation_pump_running,
    config_heating_circuit_1_summer_winter_switch_temperature,
    config_heating_circuit_1_room_target_temperature_night,
    config_heating_circuit_1_room_target_temperature_day,
    config_heating_circuit_1_operation_mode,
    config_heating_circuit_1_holiday_target_temperature,
    config_heating_circuit_1_flow_temperature_max,
    config_heating_circuit_1_design_temperature,
    config_heating_circuit_1_room_temperature_correction,
    //config_heating_circuit_1_outdoor_switch_temperature,
    config_heating_circuit_1_lowering_type,
    config_heating_circuit_1_heating_system_type,
    config_heating_circuit_1_room_temperature_offset,
    config_heating_circuit_1_remote_control,
    config_frost_switch_temperature,
    config_heating_circuit_2_summer_winter_switch_temperature,
    config_heating_circuit_2_room_target_temperature_night,
    config_heating_circuit_2_room_target_temperature_day,
    config_heating_circuit_2_operation_mode,
    config_heating_circuit_2_holiday_target_temperature,
    config_heating_circuit_2_flow_temperature_max,
    config_heating_circuit_2_design_temperature,
    config_heating_circuit_2_room_temperature_correction,
    //config_heating_circuit_2_outdoor_switch_temperature,
    config_heating_circuit_2_lowering_type,
    config_heating_circuit_2_heating_system_type,
    config_heating_circuit_2_room_temperature_offset,
    config_heating_circuit_2_remote_control,
    config_blr_building_type,
    config_ww_temperature,
    config_ww_operation_mode,
    config_ww_priority_mode,
    config_ww_circular_pump_interval,
    config_blr_burner_type,
    config_blr_temperature_max,
    config_blr_pump_turn_on_temperature,
    config_blr_exhaust_temperature_max,
    config_blr_burner_modulation_min,
    config_blr_burner_runtime_min,
    config_heating_circuit_1_heating_program,
    config_heating_circuit_1_holiday_days,
    config_heating_circuit_2_heating_program,
    config_heating_circuit_2_holiday_days,
    config_time_offset,
    error_additional_sensor,
    error_boiler_sensor,
    error_boiler_stays_cold,
    error_burner_malfunction,
    error_exhaust_gas_over_limit,
    error_exhaust_gas_sensor,
    error_external_disturbance,
    error_safety_chain_released,
    exhaust_gas_temperature,
    firmware_version,
    heating_circuit_1_antifreeze,
    heating_circuit_1_automatic,
    heating_circuit_1_curve_0,
    heating_circuit_1_curve_n10,
    heating_circuit_1_curve_p10,
    heating_circuit_1_day,
    heating_circuit_1_external_fault_input,
    heating_circuit_1_flow_sensor_error,
    heating_circuit_1_flow_target_temperature,
    heating_circuit_1_flow_temperature,
    heating_circuit_1_holiday,
    heating_circuit_1_manually,
    heating_circuit_1_max_flow,
    heating_circuit_1_mixer_position,
    heating_circuit_1_no_comm_with_rc,
    heating_circuit_1_pump_power,
    heating_circuit_1_rc_faulty,
    heating_circuit_1_room_target_temperature,
    heating_circuit_1_room_temperature,
    heating_circuit_1_screed_drying,
    heating_circuit_1_summer,
    heating_circuit_1_switch_off_optimization,
    heating_circuit_1_switch_on_optimization,
    heating_circuit_1_ww_priority_processing,
    heating_circuit_2_antifreeze,
    heating_circuit_2_automatic,
    heating_circuit_2_curve_0,
    heating_circuit_2_curve_n10,
    heating_circuit_2_curve_p10,
    heating_circuit_2_day,
    heating_circuit_2_external_fault_input,
    heating_circuit_2_flow_sensor_error,
    heating_circuit_2_flow_target_temperature,
    heating_circuit_2_flow_temperature,
    heating_circuit_2_holiday,
    heating_circuit_2_manually,
    heating_circuit_2_max_flow,
    heating_circuit_2_mixer_position,
    heating_circuit_2_no_comm_with_rc,
    heating_circuit_2_pump_power,
    heating_circuit_2_rc_faulty,
    heating_circuit_2_room_target_temperature,
    heating_circuit_2_room_temperature,
    heating_circuit_2_screed_drying,
    heating_circuit_2_summer,
    heating_circuit_2_switch_off_optimization,
    heating_circuit_2_switch_on_optimization,
    heating_circuit_2_ww_priority_processing,
    load_pump_running,
    module_identifier,
    outdoor_temperature,
    solar_pump_lowering,
    ww_automatic,
    ww_day_mode,
    ww_disinfection,
    ww_error_anode,
    ww_error_disinfection,
    ww_error_sensor,
    ww_error_stays_cold,
    ww_heating_auto_off,
    ww_holiday,
    ww_loading,
    ww_manually,
    ww_post_processing,
    ww_priority_processing,
    ww_reload,
    ww_reloading,
    ww_switch_off_optimization,
    ww_switch_on_optimization,
    ww_target_temperature,
    ww_temperature
};

class Writer3964R;


struct t_Buderus_R2017_ParamDesc {
    TransmissionParameter transmissionParameter;
    Buderus_R2017_ParameterId parameterId;
    bool writable;
    SensorType sensorType;
    uint16_t sensorTypeParam;
    const char* desc;
    const char* unit;
};

typedef struct t_Buderus_R2017_ParamDesc t_Buderus_R2017_ParamDesc;


/** A BuderusValueHandler handles a value that we received from the heater. It passes the data to the configured switches, sensors and so on. */
class BuderusValueHandler {
    public:
        BuderusValueHandler(const t_Buderus_R2017_ParamDesc* paramDesc, esphome::sensor::Sensor *sensor);
        BuderusValueHandler(const t_Buderus_R2017_ParamDesc* paramDesc, esphome::binary_sensor::BinarySensor *binarySensor);
        BuderusValueHandler(const t_Buderus_R2017_ParamDesc* paramDesc, CommunicationComponent * communicationComponent);

        void parseAndTransmit(uint8_t *data, size_t len);
        void loop();
    private:
        void handleReceivedSignedValue(uint16_t sensorTypeParam, int32_t value);
        void handleReceivedUnsignedValue(uint16_t sensorTypeParam, uint32_t value);
        void handleReceivedFloatValue(uint16_t sensorTypeParam, float value);

    public:
       const t_Buderus_R2017_ParamDesc * paramDesc;

    private:
        CommunicationComponent *communicationComponent;
        esphome::sensor::Sensor *sensor;
        esphome::binary_sensor::BinarySensor *binarySensor;

};

typedef std::unordered_multimap<Buderus_R2017_ParameterId, BuderusValueHandler *, std::hash<int>> ValueHandlerMap;

static ValueHandlerMap valueHandlerMap;

static const t_Buderus_R2017_ParamDesc buderusParamDesc[] = {
    // Konfiguration HK1
    {config_heating_circuit_1_summer_winter_switch_temperature, CFG000, true, SensorType::BYTE_AT_OFFSET, 1, "CFG_HK1_Sommer_Winter Umschalttemperatur", "°C"},
    {config_heating_circuit_1_room_target_temperature_night, CFG000, true, SensorType::BYTE_DIVIDED_BY_2_AT_OFFSET, 2, "CFG_HK1_Raumsolltemperatur Nacht", "°C"},
    {config_heating_circuit_1_room_target_temperature_day, CFG000, true, SensorType::BYTE_DIVIDED_BY_2_AT_OFFSET, 3, "CFG_HK1_Raumsolltemperatur Tag", "°C"},
    {config_heating_circuit_1_operation_mode, CFG000, true, SensorType::BYTE_AT_OFFSET, 4, "CFG_HK1_Betriebsart", ""},
    {config_heating_circuit_1_holiday_target_temperature, CFG000, true, SensorType::BYTE_DIVIDED_BY_2_AT_OFFSET, 5, "CFG_HK1_Urlaubstemperatur", "°C"},
    {config_heating_circuit_1_flow_temperature_max, CFG00E, true, SensorType::BYTE_AT_OFFSET, 2, "CFG_HK1_Heizkreistemperatur Maximal", "°C"},
    {config_heating_circuit_1_design_temperature, CFG00E, true, SensorType::BYTE_AT_OFFSET, 4, "CFG_HK1_Auslegungstemperatur", "°C"},
    {config_heating_circuit_1_room_temperature_correction, CFG015, true, SensorType::BYTE_DIVIDED_BY_2_AT_OFFSET, 0, "CFG_HK1_Raumtemperaturkorrektur Maximal", "°C"},
    // {config_ww_priority_mode, CFG015, true, SensorType::, 1, "CFG_WW_Vorrangschaltung", ""},
    //{config_heating_circuit_1_outdoor_switch_temperature, CFG015, true, SensorType::BYTE_AT_OFFSET, 2, "CFG_HK1_Aussenhalt Umschalttemperatur", "°C"},
    {config_heating_circuit_1_lowering_type, CFG01C, true, SensorType::BYTE_AT_OFFSET, 1, "CFG_HK1_Absenkungsart", ""},
    {config_heating_circuit_1_heating_system_type, CFG01C, true, SensorType::BYTE_AT_OFFSET, 2, "CFG_HK1_Heizsystem", ""},
    {config_heating_circuit_1_room_temperature_offset, CFG031, true, SensorType::BYTE_DIVIDED_BY_2_AT_OFFSET, 3, "CFG_HK1_Raumtemperatur Offset", "°C"},
    {config_heating_circuit_1_remote_control, CFG031, true, SensorType::BYTE_AT_OFFSET, 4, "CFG_HK1_Fernbedienung", ""},
    {config_frost_switch_temperature, CFG031, true, SensorType::BYTE_AT_OFFSET, 5, "CFG_Frost Umschalttemperatur", "°C"},
    {config_heating_circuit_1_heating_program, CFG100, true, SensorType::BYTE_AT_OFFSET, 0, "CFG_HK1_Heizprogramm", ""},
    {config_heating_circuit_1_holiday_days, CFG100, true, SensorType::BYTE_AT_OFFSET, 3, "CFG_HK1_Urlaubstage", ""},
    // Konfiguration HK2
    {config_heating_circuit_2_summer_winter_switch_temperature, CFG038, true, SensorType::BYTE_AT_OFFSET, 1, "CFG_HK2_Sommer_Winter Umschalttemperatur", "°C"},
    {config_heating_circuit_2_room_target_temperature_night, CFG038, true, SensorType::BYTE_DIVIDED_BY_2_AT_OFFSET, 2, "CFG_HK2_Raumsolltemperatur Nacht", "°C"},
    {config_heating_circuit_2_room_target_temperature_day, CFG038, true, SensorType::BYTE_DIVIDED_BY_2_AT_OFFSET, 3, "CFG_HK2_Raumsolltemperatur Tag", "°C"},
    {config_heating_circuit_2_operation_mode, CFG038, true, SensorType::BYTE_AT_OFFSET, 4, "CFG_HK2_Betriebsart", ""},
    {config_heating_circuit_2_holiday_target_temperature, CFG038, true, SensorType::BYTE_DIVIDED_BY_2_AT_OFFSET, 5, "CFG_HK2_Urlaubstemperatur", "°C"},
    {config_heating_circuit_2_flow_temperature_max, CFG046, true, SensorType::BYTE_AT_OFFSET, 2, "CFG_HK2_Heizkreistemperatur Maximal", "°C"},
    {config_heating_circuit_2_design_temperature, CFG046, true, SensorType::BYTE_AT_OFFSET, 4, "CFG_HK2_Auslegungstemperatur", "°C"},
    {config_heating_circuit_2_room_temperature_correction, CFG04D, true, SensorType::BYTE_DIVIDED_BY_2_AT_OFFSET, 0, "CFG_HK2_Raumtemperaturkorrektur Maximal", "°C"},
    //{config_heating_circuit_2_outdoor_switch_temperature, CFG04D, true, SensorType::BYTE_AT_OFFSET, 2, "CFG_HK2_Aussenhalt Umschalttemperatur", "°C"},
    {config_heating_circuit_2_lowering_type, CFG054, true, SensorType::BYTE_AT_OFFSET, 1, "CFG_HK2_Absenkungsart", ""},
    {config_heating_circuit_2_heating_system_type, CFG054, true, SensorType::BYTE_AT_OFFSET, 2, "CFG_HK2_Heizsystem", ""},
    {config_heating_circuit_2_room_temperature_offset, CFG069, true, SensorType::BYTE_DIVIDED_BY_2_AT_OFFSET, 3, "CFG_HK2_Raumtemperatur Offset", "°C"},
    {config_heating_circuit_2_remote_control, CFG069, true, SensorType::BYTE_AT_OFFSET, 4, "CFG_HK2_Fernbedienung", ""},
    {config_heating_circuit_2_heating_program, CFG169, true, SensorType::BYTE_AT_OFFSET, 0, "CFG_HK1_Heizprogramm", ""},
    {config_heating_circuit_2_holiday_days, CFG169, true, SensorType::BYTE_AT_OFFSET, 3, "CFG_HK1_Urlaubstage", ""},
    // Konfiguration WW
    {config_ww_temperature, CFG07E, true, SensorType::BYTE_AT_OFFSET, 3, "CFG_WW_Temperatur", "°C"},
    {config_ww_operation_mode, CFG085, true, SensorType::BYTE_AT_OFFSET, 0, "CFG_WW_Betriebsmodus", ""},
    {config_ww_priority_mode, CFG085, true, SensorType::BYTE_AT_OFFSET, 3, "CFG_WW_Vorrangschaltung", ""},
    {config_ww_circular_pump_interval, CFG085, true, SensorType::BYTE_AT_OFFSET, 5, "CFG_WW_Zirkulationspumpenintervall", ""},
    // Konfiguration Brenner
    // {config_blr_burner_type, CFG09A, true, SensorType::BYTE_AT_OFFSET, 1, "CFG_BLR_Brennerart", ""},
    //{config_blr_temperature_max, CFG09A, true, SensorType::BYTE_AT_OFFSET, 3, "CFG_BLR_Temperatur Maximal", "°C"},
    //{config_blr_pump_turn_on_temperature, CFG0A1, true, SensorType::BYTE_AT_OFFSET, 0, "CFG_BLR_Pumpe Anschalttemperatur", "°C"},
    //{config_blr_exhaust_temperature_max, CFG0A1, true, SensorType::BYTE_AT_OFFSET, 5, "CFG_BLR_Abgastemperatur Maximal", "°C"},
    // {config_blr_burner_modulation_min, CFG0A8, true, SensorType::BYTE_AT_OFFSET, 0, "CFG_BLR_Brennermodulationsleistung Minimal", ""},
    // {config_blr_burner_runtime_min, CFG0A8, true, SensorType::BYTE_AT_OFFSET, 1, "CFG_BLR_Brennerlaufzeit Minimal", ""},
    // Konfiguration Sonstiges
    //{config_blr_building_type, CFG070, true, SensorType::BYTE_AT_OFFSET, 2, "CFG_BLR_Gebaeudeart", ""},
    //{config_time_offset, CFG1E0, true, SensorType::BYTE_AT_OFFSET, 1, "CFG_Uhrzeit offset", ""},
    // Betriebswerte 1 HK1
    {heating_circuit_1_switch_off_optimization, BW1HK1, false, SensorType::BIT_AT_OFFSET, 0, "HK1 Ausschaltoptimierung", ""},
    {heating_circuit_1_switch_on_optimization, BW1HK1, false, SensorType::BIT_AT_OFFSET, 1, "HK1 Einschaltoptimierung", ""},
    {heating_circuit_1_automatic, BW1HK1, false, SensorType::BIT_AT_OFFSET, 2, "HK1 Automatik", ""},
    {heating_circuit_1_ww_priority_processing, BW1HK1, false, SensorType::BIT_AT_OFFSET, 3, "HK1 Warmwasservorrang", ""},
    {heating_circuit_1_screed_drying, BW1HK1, false, SensorType::BIT_AT_OFFSET, 4, "HK1 Estrichtrocknung", ""},
    {heating_circuit_1_holiday, BW1HK1, false, SensorType::BIT_AT_OFFSET, 5, "HK1 Ferien", ""},
    {heating_circuit_1_antifreeze, BW1HK1, false, SensorType::BIT_AT_OFFSET, 6, "HK1 Frostschutz", ""},
    {heating_circuit_1_manually, BW1HK1, false, SensorType::BIT_AT_OFFSET, 7, "HK1 Manuell", ""},
    // Betriebswerte 2 HK1
    {heating_circuit_1_summer, BW2HK1, false, SensorType::BIT_AT_OFFSET, 0, "HK1 Sommer-Modus", ""},
    {heating_circuit_1_day, BW2HK1, false, SensorType::BIT_AT_OFFSET, 1, "HK1 Tag-Modus", ""},
    {heating_circuit_1_no_comm_with_rc, BW2HK1, false, SensorType::BIT_AT_OFFSET, 2, "HK1 Keine Kommunikation mit FB", ""},
    {heating_circuit_1_rc_faulty, BW2HK1, false, SensorType::BIT_AT_OFFSET, 3, "HK1 FB fehlerhaft", ""},
    {heating_circuit_1_flow_sensor_error, BW2HK1, false, SensorType::BIT_AT_OFFSET, 4, "HK1 Fehler Vorlauffuehler", ""},
    {heating_circuit_1_max_flow, BW2HK1, false, SensorType::BIT_AT_OFFSET, 5, "HK1 Maximaler Vorlauf", ""},
    {heating_circuit_1_external_fault_input, BW2HK1, false, SensorType::BIT_AT_OFFSET, 6, "HK1 Externer Stoereingang", ""},
    //{BW2HK1, false, SensorType::BIT_AT_OFFSET, 7, "HK1 Frei - Party/Pause", ""}, // unklar was hier gemeint ist
    {heating_circuit_1_flow_target_temperature, VSTHK1, false, SensorType::UNSIGNED_INT, 0, "Vorlaufsolltemperatur HK1", "°C"},           // (Grad)
    {heating_circuit_1_flow_temperature, VITHK1, false, SensorType::UNSIGNED_INT, 0, "Vorlaufisttemperatur HK1", "°C"},            // (Grad)
    {heating_circuit_1_room_target_temperature, RSTHK1, false, SensorType::UNSIGNED_INT_DIVIDED_BY_2, 0, "Raumsolltemperatur HK1", "°C"}, // (Grad)
    {heating_circuit_1_room_temperature, RITHK1, false, SensorType::UNSIGNED_INT_DIVIDED_BY_2, 0, "Raumisttemperatur HK1", "°C"},  // (Grad)
    {no_transmission, EOZHK1, false, SensorType::UNSIGNED_INT, 0, "Einschaltoptimierungszeit HK1", ""},
    {no_transmission, AOZHK1, false, SensorType::UNSIGNED_INT, 0, "Ausschaltoptimierungszeit HK1", ""},
    {heating_circuit_1_pump_power, PLHK1, false, SensorType::UNSIGNED_INT, 0, "Pumpenleistung HK1", "%"}, // (Grad)
    {heating_circuit_1_mixer_position, MSHK1, false, SensorType::SIGNED_INT, 0, "Mischerstellung HK1", "%"},  // (Grad)
    {no_transmission, NB01, false, SensorType::NONE, 0, "nicht belegt", ""},
    {no_transmission, NB02, false, SensorType::NONE, 0, "nicht belegt", ""},
    {heating_circuit_1_curve_p10, KLHK1_P10, false, SensorType::UNSIGNED_INT, 0, "Heizkennlinie HK1 bei + 10 Grad", "°C"}, // (Grad)
    {heating_circuit_1_curve_0, KLHK1_P00, false, SensorType::UNSIGNED_INT, 0, "Heizkennlinie HK1 bei 0 Grad", "°C"},    // (Grad)
    {heating_circuit_1_curve_n10, KLHK1_N10, false, SensorType::UNSIGNED_INT, 0, "Heizkennlinie HK1 bei - 10 Grad", "°C"}, // (Grad)
    {no_transmission, NB03, false, SensorType::NONE, 0, "nicht belegt", ""},
    {no_transmission, NB04, false, SensorType::NONE, 0, "nicht belegt", ""},
    {no_transmission, NB05, false, SensorType::NONE, 0, "nicht belegt", ""},
    // Betriebswerte 1 HK2
    {heating_circuit_2_switch_off_optimization, BW1HK2, false, SensorType::BIT_AT_OFFSET, 0, "HK2 Ausschaltoptimierung", ""},
    {heating_circuit_2_switch_on_optimization, BW1HK2, false, SensorType::BIT_AT_OFFSET, 1, "HK2 Einschaltoptimierung", ""},
    {heating_circuit_2_automatic, BW1HK2, false, SensorType::BIT_AT_OFFSET, 2, "HK2 Automatik", ""},
    {heating_circuit_2_ww_priority_processing, BW1HK2, false, SensorType::BIT_AT_OFFSET, 3, "HK2 Warmwasservorrang", ""},
    {heating_circuit_2_screed_drying, BW1HK2, false, SensorType::BIT_AT_OFFSET, 4, "HK2 Estrichtrocknung", ""},
    {heating_circuit_2_holiday, BW1HK2, false, SensorType::BIT_AT_OFFSET, 5, "HK2 Ferien", ""},
    {heating_circuit_2_antifreeze, BW1HK2, false, SensorType::BIT_AT_OFFSET, 6, "HK2 Frostschutz", ""},
    {heating_circuit_2_manually, BW1HK2, false, SensorType::BIT_AT_OFFSET, 7, "HK2 Manuell", ""},
    // Betriebswerte 2 HK2
    {heating_circuit_2_summer, BW2HK2, false, SensorType::BIT_AT_OFFSET, 0, "HK2 Sommer-Modus", ""},
    {heating_circuit_2_day, BW2HK2, false, SensorType::BIT_AT_OFFSET, 1, "HK2 Tag-Modus", ""},
    {heating_circuit_2_no_comm_with_rc, BW2HK2, false, SensorType::BIT_AT_OFFSET, 2, "HK2 Keine Kommunikation mit FB", ""},
    {heating_circuit_2_rc_faulty, BW2HK2, false, SensorType::BIT_AT_OFFSET, 3, "HK2 FB fehlerhaft", ""},
    {heating_circuit_2_flow_sensor_error, BW2HK2, false, SensorType::BIT_AT_OFFSET, 4, "HK2 Fehler Vorlauffuehler", ""},
    {heating_circuit_2_max_flow, BW2HK2, false, SensorType::BIT_AT_OFFSET, 5, "HK2 Maximaler Vorlauf", ""},
    {heating_circuit_2_external_fault_input, BW2HK2, false, SensorType::BIT_AT_OFFSET, 6, "HK2 Externer Stoereingang", ""},
    {heating_circuit_2_flow_target_temperature, VSTHK2, false, SensorType::UNSIGNED_INT, 0, "Vorlaufsolltemperatur HK2", "°C"},           // (Grad)
    {heating_circuit_2_flow_temperature, VITHK2, false, SensorType::UNSIGNED_INT, 0, "Vorlaufisttemperatur HK2", "°C"},            // (Grad)
    {heating_circuit_2_room_target_temperature, RSTHK2, false, SensorType::UNSIGNED_INT_DIVIDED_BY_2, 0, "Raumsolltemperatur HK2", "°C"}, // (Grad)
    {heating_circuit_2_room_temperature, RITHK2, false, SensorType::UNSIGNED_INT_DIVIDED_BY_2, 0, "Raumisttemperatur HK2", "°C"},  // (Grad)
    {no_transmission, EOZHK2, false, SensorType::UNSIGNED_INT, 0, "Einschaltoptimierungszeit HK2", ""},
    {no_transmission, AOZHK2, false, SensorType::UNSIGNED_INT, 0, "Ausschaltoptimierungszeit HK2", ""},
    {heating_circuit_2_pump_power, PLHK2, false, SensorType::UNSIGNED_INT, 0, "Pumpenleistung HK2", "%"},
    {heating_circuit_2_mixer_position, MSHK2, false, SensorType::SIGNED_INT, 0, "Mischerstellung HK2", "%"},
    {no_transmission, NB06, false, SensorType::NONE, 0, "nicht belegt", ""},
    {no_transmission, NB07, false, SensorType::NONE, 0, "nicht belegt", ""},
    {heating_circuit_2_curve_p10, KLHK2_P10, false, SensorType::UNSIGNED_INT, 0, "Heizkennlinie HK2 bei + 10 Grad", "°C"}, // (Grad)
    {heating_circuit_2_curve_0, KLHK2_P00, false, SensorType::UNSIGNED_INT, 0, "Heizkennlinie HK2 bei 0 Grad", "°C"},    // (Grad)
    {heating_circuit_2_curve_n10, KLHK2_N10, false, SensorType::UNSIGNED_INT, 0, "Heizkennlinie HK2 bei - 10 Grad", "°C"}, // (Grad)
    {no_transmission, NB08, false, SensorType::NONE, 0, "nicht belegt", ""},
    {no_transmission, NB09, false, SensorType::NONE, 0, "nicht belegt", ""},
    {no_transmission, NB10, false, SensorType::NONE, 0, "nicht belegt", ""},
    // Betriebswerte 1 WW
    {ww_automatic, BW1WW, false, SensorType::BIT_AT_OFFSET, 0, "WW Automatik", ""},
    {ww_disinfection, BW1WW, false, SensorType::BIT_AT_OFFSET, 1, "WW Desinfektion", ""},
    {ww_reload, BW1WW, false, SensorType::BIT_AT_OFFSET, 2, "WW Nachladung", ""},
    {ww_holiday, BW1WW, false, SensorType::BIT_AT_OFFSET, 3, "WW Ferien", ""},
    {ww_error_disinfection, BW1WW, false, SensorType::BIT_AT_OFFSET, 4, "WW Fehler Desinfektion", ""},
    {ww_error_sensor, BW1WW, false, SensorType::BIT_AT_OFFSET, 5, "WW Fehler Fuehler", ""},
    {ww_error_stays_cold, BW1WW, false, SensorType::BIT_AT_OFFSET, 6, "WW Fehler WW bleibt kalt", ""},
    {ww_error_anode, BW1WW, false, SensorType::BIT_AT_OFFSET, 7, "WW Fehler Anode", ""},
    // Betriebswerte 2 WW
    {ww_loading, BW2WW, false, SensorType::BIT_AT_OFFSET, 0, "WW Laden", ""},
    {ww_manually, BW2WW, false, SensorType::BIT_AT_OFFSET, 1, "WW Manuell", ""},
    {ww_reloading, BW2WW, false, SensorType::BIT_AT_OFFSET, 2, "WW Nachladen", ""}, // ist 1 bei Lade-/Nachlade-Aktivität der Warmwasser - Ladepumpe, jedoch nicht über die komplette Zeit.
    {ww_switch_off_optimization, BW2WW, false, SensorType::BIT_AT_OFFSET, 3, "WW Ausschaltoptimierung", ""},
    {ww_switch_on_optimization, BW2WW, false, SensorType::BIT_AT_OFFSET, 4, "WW Einschaltoptimierung", ""},
    {ww_day_mode, BW2WW, false, SensorType::BIT_AT_OFFSET, 5, "WW Tag Modus", ""},
    {ww_post_processing, BW2WW, false, SensorType::BIT_AT_OFFSET, 6, "WW Nachbereitung", ""},    // wird gleichzeitig mit dem 6. Bit 1, aber mit zeitlicher Verzögerung 0. Möglicherweise das Zeitfenster, in dem bei Bedarf noch Warmwasserbereitung, auch über den Tag - Heiz - Modus hinaus, stattfindet.
    {ww_priority_processing, BW2WW, false, SensorType::BIT_AT_OFFSET, 7, "WW Vorrangschaltung", ""}, // ist 1, solange Warmwasserbereitung mit Vorrang stattfindet.
    {ww_target_temperature, WWST, false, SensorType::UNSIGNED_INT, 0, "WW Solltemperatur", "°C"}, // (Grad)
    {ww_temperature, WWIT, false, SensorType::UNSIGNED_INT, 0, "WW Isttemperatur", "°C"},  // (Grad)
    {no_transmission, OZWW, false, SensorType::UNSIGNED_INT, 0, "WW Optimierungszeit", ""},
    // Pumpenansteuerung
    {load_pump_running, LPWW, false, SensorType::BIT_AT_OFFSET, 0, "Ladepumpe", ""},
    {circulation_pump_running, LPWW, false, SensorType::BIT_AT_OFFSET, 1, "Zirkulationspumpe", ""},
    {solar_pump_lowering, LPWW, false, SensorType::BIT_AT_OFFSET, 2, "Solarpumpe Absenkung", ""},
    {boiler_target_temperature, KVST, false, SensorType::UNSIGNED_INT, 0, "Kesselvorlaufsolltemperatur", "°C"}, // (Grad)
    {boiler_temperature, KVIT, false, SensorType::UNSIGNED_INT, 0, "Kesselvorlaufisttemperatur", "°C"},  // (Grad)
    {boiler_turn_on_temperature, BET, false, SensorType::UNSIGNED_INT, 0, "Brennereinschalttemperatur", "°C"},   // (Grad)
    {boiler_turn_off_temperature, BAT, false, SensorType::UNSIGNED_INT, 0, "Brennerausschalttemperatur", "°C"},   // (Grad)
    {no_transmission, KINT1, false, SensorType::UNSIGNED_INT, 0, "Kesselintegral 1", ""},
    {no_transmission, KINT2, false, SensorType::UNSIGNED_INT, 0, "Kesselintegral 2", ""},
    // Kesselfehler
    {error_burner_malfunction, KFEHL, false, SensorType::BIT_AT_OFFSET, 0, "Fehler Brennerstoerung", ""},
    {error_boiler_sensor, KFEHL, false, SensorType::BIT_AT_OFFSET, 1, "Fehler Kesselfuehler", ""},
    {error_additional_sensor, KFEHL, false, SensorType::BIT_AT_OFFSET, 2, "Fehler Zusatzfuehler", ""},
    {error_boiler_stays_cold, KFEHL, false, SensorType::BIT_AT_OFFSET, 3, "Fehler Kessel bleibt kalt", ""},
    {error_exhaust_gas_sensor, KFEHL, false, SensorType::BIT_AT_OFFSET, 4, "Fehler Abgasfuehler", ""},
    {error_exhaust_gas_over_limit, KFEHL, false, SensorType::BIT_AT_OFFSET, 5, "Fehler Abgas ueber Grenzwert", ""},
    {error_safety_chain_released, KFEHL, false, SensorType::BIT_AT_OFFSET, 6, "Fehler Sicherungskette ausgeloest", ""},
    {error_external_disturbance, KFEHL, false, SensorType::BIT_AT_OFFSET, 7, "Fehler Externe Stoerung", ""},
    // Kesselbetrieb
    {boiler_emission_test, KBETR, false, SensorType::BIT_AT_OFFSET, 0, "Kessel Abgastest", ""},
    {boiler_1st_stage_operation, KBETR, false, SensorType::BIT_AT_OFFSET, 1, "Kessel Betrieb 1.Stufe", ""},
    {boiler_protection, KBETR, false, SensorType::BIT_AT_OFFSET, 2, "Kessel Schutz", ""},
    {boiler_under_operation, KBETR, false, SensorType::BIT_AT_OFFSET, 3, "Kessel unter Betrieb", ""},
    {boiler_performance_free, KBETR, false, SensorType::BIT_AT_OFFSET, 4, "Kessel Leistung frei", ""},
    {boiler_performance_high, KBETR, false, SensorType::BIT_AT_OFFSET, 5, "Kessel Leistung hoch", ""},
    {boiler_2st_stage_operation, KBETR, false, SensorType::BIT_AT_OFFSET, 6, "Kessel Betrieb 2.Stufe", ""},
    {boiler_actuation, BANST, false, SensorType::UNSIGNED_INT, 0, "Brenneransteuerung", ""}, // 0: Brenner aus, 1 : Brenner an in Stufe 1, 2 : Brenner an in Stufe 2(laut Buderus - ungeprüft)
    {exhaust_gas_temperature, ABTMP, false, SensorType::UNSIGNED_INT, 0, "Abgastemperatur", "°C"},  // (Grad)
    {no_transmission, MODBSTELL, false, SensorType::UNSIGNED_INT, 0, "modulare Brenner Stellwert", ""},
    {no_transmission, NB11, false, SensorType::NONE, 0, "nicht belegt", ""},
    {boiler_runtime_1, BLZ1S2, false, SensorType::MULTI_PARAMETER_UNSIGNED_INTEGER, 2, "Brennerlaufzeit 1 Minuten 2", "m"},
    {boiler_runtime_1, BLZ1S1, false, SensorType::MULTI_PARAMETER_UNSIGNED_INTEGER, 1, "Brennerlaufzeit 1 Minuten 1", "m"},
    {boiler_runtime_1, BLZ1S0, false, SensorType::MULTI_PARAMETER_UNSIGNED_INTEGER, 0, "Brennerlaufzeit 1 Minuten 0", "m"},
    {boiler_runtime_2, BLZ2S2, false, SensorType::MULTI_PARAMETER_UNSIGNED_INTEGER, 2, "Brennerlaufzeit 2 Minuten 2", "m"},
    {boiler_runtime_2, BLZ2S1, false, SensorType::MULTI_PARAMETER_UNSIGNED_INTEGER, 1, "Brennerlaufzeit 2 Minuten 1", "m"},
    {boiler_runtime_2, BLZ2S0, false, SensorType::MULTI_PARAMETER_UNSIGNED_INTEGER, 0, "Brennerlaufzeit 2 Minuten 0", "m"},
    {outdoor_temperature, AT, false, SensorType::SIGNED_INT, 0, "Aussentemperatur", "°C"},             // (Grad)
    {attenuated_outdoor_temperature, ATD, false, SensorType::SIGNED_INT, 0, "Gedaempfte Aussentemperatur", "°C"}, // (Grad)
    {firmware_version, VVK, false, SensorType::FIRMWARE_VERSION, 0, "Versionsnummer VK", ""},
    {firmware_version, VNK, false, SensorType::FIRMWARE_VERSION, 1, "Versionsnummer NK", ""},
    {module_identifier, MODKENN, false, SensorType::UNSIGNED_INT, 0, "Modulkennung", ""},
    {no_transmission, NB12, false, SensorType::NONE, 0, "nicht belegt", ""},
    // Alarmstatus
    {alarm_exhaust_gas_sensor, ALARM, false, SensorType::BIT_AT_OFFSET, 0, "Alarm Abgasfuehler", ""},
    {no_transmission, ALARM, false, SensorType::BIT_AT_OFFSET, 1, "Alarm 02", ""},
    {alarm_boiler_flow_sensor, ALARM, false, SensorType::BIT_AT_OFFSET, 2, "Alarm Kesselvorlauffuehler", ""},
    {no_transmission, ALARM, false, SensorType::BIT_AT_OFFSET, 3, "Alarm 08", ""},
    {alarm_burner, ALARM, false, SensorType::BIT_AT_OFFSET, 4, "Alarm Brenner", ""},
    {no_transmission, ALARM, false, SensorType::BIT_AT_OFFSET, 5, "Alarm 20", ""},
    {alarm_heating_circuit_2_flow_sensor, ALARM, false, SensorType::BIT_AT_OFFSET, 6, "Alarm HK2 Vorlauffuehler", ""},
    {no_transmission, ALARM, false, SensorType::BIT_AT_OFFSET, 7, "Alarm 80", ""},
};
}
}
