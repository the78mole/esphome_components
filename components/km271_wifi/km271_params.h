#pragma once

#include <string>
#include <vector>
#include "esphome/core/component.h"
#include "esphome/components/sensor/sensor.h"
#include "esphome/components/binary_sensor/binary_sensor.h"
#include "esphome/components/switch/switch.h"
#include "esphome/components/number/number.h"
#include <unordered_map>

namespace esphome {
namespace KM271 {


enum Buderus_R2017_ParameterId {
    CFG_WW_Temperatur = 0x007e,
    CFG_WW_Aufbereitung = 0x0085,
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
    BLZ1S2    = 0x8836, //: "Brennerlaufzeit 1 Stunden 2"
    BLZ1S1    = 0x8837, //: "Brennerlaufzeit 1 Stunden 1"
    BLZ1S0    = 0x8838, //: "Brennerlaufzeit 1 Stunden 0"
    BLZ2S2    = 0x8839, //: "Brennerlaufzeit 2 Stunden 2"
    BLZ2S1    = 0x883a, //: "Brennerlaufzeit 2 Stunden 1"
    BLZ2S0    = 0x883b, //: "Brennerlaufzeit 2 Stunden 0"

    AT        = 0x893c, //: "Aussentemperatur"                (Grad)
    ATD       = 0x893d, //: "gedaempfte Aussentemperatur"     (Grad)
    VVK       = 0x893e, //: "Versionsnummer VK"
    VNK       = 0x893f, //: "Versionsnummer NK"
    MODKENN   = 0x8940, //: "Modulkennung"
    NB12      = 0x8941, //: "nicht belegt"

    ALARM     = 0xaa42, //: "ERR_Alarmstatus"

    CFG1      = 0x0000, //: "Sommar ab, HK1 Nacht-/Tag-/Urlaubstemperatur, Betriebsart"
    CFG2      = 0x000E, //: "HK1 Max Temperatur, HK1 Auslegung"
    CFG3      = 0x0015, //: "HK1 Aufschalttemperatur, HK1 Aussenhalt_ab"
    CFG4      = 0x001c, //: "HK1 Absenkungsart, HK1 Heizsystem"
    CFG5      = 0x0031, //: "HK1 Temperatur Offset, HK1 Fernbedienung, Frost ab"
    CFG6      = 0x004d, //: "WW Vorgang"
    CFG7      = 0x0070, //: "Gebäudeart"
    CFG8      = 0x007e, //: "WW Temperatur"
    CFG9      = 0x0085, //: "WW Betriebsart, WW Aufbereitung, WW Zirkulation"
    CFG10     = 0x0093, //: "Sprache, Anzeige"
    CFG11     = 0x009a, //: "Brennerart, Max Kesseltemperatur"
    CFG12     = 0x00a1, //: "Pumplogik, Abgastemperaturschwelle"
    CFG13     = 0x00a8, //: "Brenner Min Modulation, Brenner Mod Laufzeit"
};

enum SensorType {
    NONE = 0,
    UNSIGNED_INT,
    SIGNED_INT,
    UNSIGNED_INT_DIVIDED_BY_2,
    STRING,
    BYTE_AT_OFFSET, // a single byte, with offset in bytes specified in sensor param
    BIT_AT_OFFSET, // a single bit, with offset in bits specified in sensor param
    TAG_NACHT_AUTO_SELECT, //   [ 0 => "Nacht", 1=> "Tag", 2=> "Automatik" ],
};

class Writer3964R;


class BuderusParamSwitch: public esphome::switch_::Switch {
public:
    BuderusParamSwitch();
    void setupWriting(Writer3964R * writer, Buderus_R2017_ParameterId parameterId, SensorType sensorType);
protected:
    void write_state(bool state) override;

private:
    Writer3964R * writer;
    Buderus_R2017_ParameterId parameterId;
    SensorType sensorType;
};

class BuderusParamNumber: public esphome::number::Number {
public:
    BuderusParamNumber();
    void setupWriting(Writer3964R * writer, Buderus_R2017_ParameterId parameterId, SensorType sensorType);
    void loop();

protected:
    void control(float value);

private:
    Writer3964R * writer;
    Buderus_R2017_ParameterId parameterId;
    SensorType sensorType;
    uint32_t lastWriteRequest;
    bool hasPendingWriteRequest;
    float pendingWriteValue;
};



struct t_Buderus_R2017_ParamDesc {
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
        BuderusValueHandler(const t_Buderus_R2017_ParamDesc* paramDesc, esphome::sensor::Sensor * sensor);
        BuderusValueHandler(const t_Buderus_R2017_ParamDesc* paramDesc, esphome::binary_sensor::BinarySensor * sensor);
        BuderusValueHandler(const t_Buderus_R2017_ParamDesc* paramDesc, BuderusParamSwitch * paramSwitch);
        BuderusValueHandler(const t_Buderus_R2017_ParamDesc* paramDesc, BuderusParamNumber* paramNumber);

        void parseAndTransmit(uint8_t *data, size_t len);
        void loop();

    public:
       const t_Buderus_R2017_ParamDesc * paramDesc;

    private:
        esphome::sensor::Sensor *sensor;
        esphome::binary_sensor::BinarySensor *binarySensor;
        BuderusParamSwitch *switch_;
        BuderusParamNumber *number;
};


typedef std::unordered_multimap<Buderus_R2017_ParameterId, BuderusValueHandler *, std::hash<int>> ValueHandlerMap;

static ValueHandlerMap valueHandlerMap;

static const t_Buderus_R2017_ParamDesc buderusParamDesc[] = {
        { CFG_WW_Temperatur, true, SensorType::BYTE_AT_OFFSET, 3, "CFG_WW_Temperatur", ""},
        { CFG_WW_Aufbereitung, true, SensorType::TAG_NACHT_AUTO_SELECT, 0, "CFG_WW_Aufbereitung", ""},
        { BW1HK1    , false, SensorType::UNSIGNED_INT, 0, "Betriebswerte 1 HK1", ""},
        { BW2HK1    , false, SensorType::UNSIGNED_INT, 0, "Betriebswerte 2 HK1", ""},
        { VSTHK1    , false, SensorType::UNSIGNED_INT, 0, "Vorlaufsolltemperatur HK1", "°C"},        // (Grad)
        { VITHK1    , false, SensorType::UNSIGNED_INT, 0, "Vorlaufisttemperatur HK1", "°C"},         // (Grad)
        { RSTHK1    , false, SensorType::UNSIGNED_INT_DIVIDED_BY_2, 0, "Raumsolltemperatur HK1", "°C"},           // (Grad)
        { RITHK1    , false, SensorType::UNSIGNED_INT_DIVIDED_BY_2, 0, "Raumisttemperatur HK1", "°C"},            // (Grad)
        { EOZHK1    , false, SensorType::UNSIGNED_INT, 0, "Einschaltoptimierungszeit HK1", ""},
        { AOZHK1    , false, SensorType::UNSIGNED_INT, 0, "Ausschaltoptimierungszeit HK1", ""},
        { PLHK1     , false, SensorType::UNSIGNED_INT, 0, "Pumpenleistung HK1", "%"},               // (Grad)
        { MSHK1     , false, SensorType::SIGNED_INT, 0, "Mischerstellung HK1", "%"},              // (Grad)
        { NB01      , false, SensorType::NONE, 0, "nicht belegt", ""},
        { NB02      , false, SensorType::NONE, 0, "nicht belegt", ""},
        { KLHK1_P10 , false, SensorType::UNSIGNED_INT, 0, "Heizkennlinie HK1 bei + 10 Grad", "°C"},  // (Grad)
        { KLHK1_P00 , false, SensorType::UNSIGNED_INT, 0, "Heizkennlinie HK1 bei 0 Grad", "°C"},     // (Grad)
        { KLHK1_N10 , false, SensorType::UNSIGNED_INT, 0, "Heizkennlinie HK1 bei - 10 Grad", "°C"},  // (Grad)
        { NB03      , false, SensorType::NONE, 0, "nicht belegt", ""},
        { NB04      , false, SensorType::NONE, 0, "nicht belegt", ""},
        { NB05      , false, SensorType::NONE, 0, "nicht belegt", ""},
    
        { BW1HK2    , false, SensorType::UNSIGNED_INT, 0, "Betriebswerte 1 HK2", ""},
        { BW2HK2    , false, SensorType::UNSIGNED_INT, 0, "Betriebswerte 2 HK2", ""},
        { VSTHK2    , false, SensorType::UNSIGNED_INT, 0, "Vorlaufsolltemperatur HK2", "°C"},        // (Grad)
        { VITHK2    , false, SensorType::UNSIGNED_INT, 0, "Vorlaufisttemperatur HK2", "°C"},         // (Grad)
        { RSTHK2    , false, SensorType::UNSIGNED_INT_DIVIDED_BY_2, 0, "Raumsolltemperatur HK2", "°C"},           // (Grad)
        { RITHK2    , false, SensorType::UNSIGNED_INT_DIVIDED_BY_2, 0, "Raumisttemperatur HK2", "°C"},            // (Grad)
        { EOZHK2    , false, SensorType::UNSIGNED_INT, 0, "Einschaltoptimierungszeit HK2", ""},
        { AOZHK2    , false, SensorType::UNSIGNED_INT, 0, "Ausschaltoptimierungszeit HK2", ""},
        { PLHK2     , false, SensorType::UNSIGNED_INT, 0, "Pumpenleistung HK2", "%"},
        { MSHK2     , false, SensorType::SIGNED_INT, 0, "Mischerstellung HK2", "%"},
        { NB06      , false, SensorType::NONE, 0, "nicht belegt", ""},
        { NB07      , false, SensorType::NONE, 0, "nicht belegt", ""},
        { KLHK2_P10 , false, SensorType::UNSIGNED_INT, 0, "Heizkennlinie HK2 bei + 10 Grad", "°C"},  // (Grad)
        { KLHK2_P00 , false, SensorType::UNSIGNED_INT, 0, "Heizkennlinie HK2 bei 0 Grad", "°C"},     // (Grad)
        { KLHK2_N10 , false, SensorType::UNSIGNED_INT, 0, "Heizkennlinie HK2 bei - 10 Grad", "°C"},  // (Grad)
        { NB08      , false, SensorType::NONE, 0, "nicht belegt", ""},
        { NB09      , false, SensorType::NONE, 0, "nicht belegt", ""},
        { NB10      , false, SensorType::NONE, 0, "nicht belegt", ""},
    
        { BW1WW     , false, SensorType::UNSIGNED_INT, 0, "Betriebswerte 1 WW", ""},
        { BW2WW     , false, SensorType::UNSIGNED_INT, 0, "Betriebswerte 2 WW", ""},
        { WWST      , false, SensorType::UNSIGNED_INT, 0, "Warmwassersolltemperatur", "°C"},         // (Grad)
        { WWIT      , false, SensorType::UNSIGNED_INT, 0, "Warmwasseristtemperatur", "°C"},          // (Grad)
        { OZWW      , false, SensorType::UNSIGNED_INT, 0, "Warmwasseroptimierungszeit", ""},
        { LPWW      , false, SensorType::BIT_AT_OFFSET, 0, "Ladepumpe", "" },
        { LPWW      , false, SensorType::BIT_AT_OFFSET, 1, "Zirkulationspumpe", "" },
        { KVST      , false, SensorType::UNSIGNED_INT, 0, "Kesselvorlaufsolltemperatur", "°C"},      // (Grad)
        { KVIT      , false, SensorType::UNSIGNED_INT, 0, "Kesselvorlaufisttemperatur", "°C"},       // (Grad)
        { BET       , false, SensorType::UNSIGNED_INT, 0, "Brennereinschalttemperatur", "°C"},       // (Grad)
        { BAT       , false, SensorType::UNSIGNED_INT, 0, "Brennerausschalttemperatur", "°C"},       // (Grad)
        { KINT1     , false, SensorType::UNSIGNED_INT, 0, "Kesselintegral 1", ""},
        { KINT2     , false, SensorType::UNSIGNED_INT, 0, "Kesselintegral 2", ""},
        { KFEHL     , false, SensorType::UNSIGNED_INT, 0, "Kesselfehler", ""},
        { KBETR     , false, SensorType::UNSIGNED_INT, 0, "Kesselbetrieb", ""},
        { BANST     , false, SensorType::UNSIGNED_INT, 0, "Brenneransteuerung", ""},                 // ["aus", "an"]
        { ABTMP     , false, SensorType::UNSIGNED_INT, 0, "Abgastemperatur", "°C"},                  // (Grad)
        { MODBSTELL , false, SensorType::UNSIGNED_INT, 0, "modulare Brenner Stellwert", ""},
        { NB11      , false, SensorType::NONE, 0, "nicht belegt", ""},
        { BLZ1S2    , false, SensorType::UNSIGNED_INT, 0, "Brennerlaufzeit 1 Stunden 2", "h"},
        { BLZ1S1    , false, SensorType::UNSIGNED_INT, 0, "Brennerlaufzeit 1 Stunden 1", "h"},
        { BLZ1S0    , false, SensorType::UNSIGNED_INT, 0, "Brennerlaufzeit 1 Stunden 0", "h"},
        { BLZ2S2    , false, SensorType::UNSIGNED_INT, 0, "Brennerlaufzeit 2 Stunden 2", "h"},
        { BLZ2S1    , false, SensorType::UNSIGNED_INT, 0, "Brennerlaufzeit 2 Stunden 1", "h"},
        { BLZ2S0    , false, SensorType::UNSIGNED_INT, 0, "Brennerlaufzeit 2 Stunden 0", "h"},
    
        { AT        , false, SensorType::SIGNED_INT, 0, "Aussentemperatur", "°C"},                 // (Grad)
        { ATD       , false, SensorType::SIGNED_INT, 0, "Gedaempfte Aussentemperatur", "°C"},      // (Grad)
        { VVK       , false, SensorType::UNSIGNED_INT, 0, "Versionsnummer VK", ""},
        { VNK       , false, SensorType::UNSIGNED_INT, 0, "Versionsnummer NK", ""},
        { MODKENN   , false, SensorType::UNSIGNED_INT, 0, "Modulkennung", ""},
        { NB12      , false, SensorType::NONE, 0, "nicht belegt", ""},
        { ALARM     , false, SensorType::UNSIGNED_INT, 0, "Alarmstatus", ""}
};


}
}
