#pragma once

#include <string>
#include <vector>
#include "esphome/core/component.h"
#include "esphome/components/sensor/sensor.h"
#include "esphome/components/binary_sensor/binary_sensor.h"
#include "esphome/components/switch/switch.h"
#include "esphome/components/number/number.h"

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
    INT,
    INTDIVIDEDBY2,
    STRING,
    BYTE_AT_OFFSET, // a single byte, with ofset in byte specified in sensor param
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


class BuderusParamSensor {
    public:
        BuderusParamSensor(esphome::sensor::Sensor * sensor, SensorType sensorType, uint8_t senorTypeParam);
        BuderusParamSensor(esphome::binary_sensor::BinarySensor * sensor, SensorType sensorType, uint8_t senorTypeParam);
        BuderusParamSensor(BuderusParamSwitch * paramSwitch, SensorType sensorType, uint8_t senorTypeParam);
        BuderusParamSensor(BuderusParamNumber* paramNumber, SensorType sensorType, uint8_t senorTypeParam);


        void parseAndTransmit(uint8_t *data, size_t len);
        void loop();

    private:
        esphome::sensor::Sensor *sensor;
        esphome::binary_sensor::BinarySensor *binarySensor;
        BuderusParamSwitch *switch_;
        BuderusParamNumber *number;
        SensorType sensorType;
        uint8_t sensorTypeParam;
};



struct t_Buderus_R2017_ParamDesc {
    Buderus_R2017_ParameterId parameterId;
    bool debugEn;
    bool writable;
    SensorType sensorType;
    uint16_t sensorTypeParam;
    const char* desc;
    const char* unit;
    BuderusParamSensor* sensor;
};

typedef struct t_Buderus_R2017_ParamDesc t_Buderus_R2017_ParamDesc;

static t_Buderus_R2017_ParamDesc buderusParamDesc[] = {
        { CFG_WW_Temperatur, true, true, SensorType::BYTE_AT_OFFSET, 3, "CFG_WW_Temperatur", "", NULL},
        { CFG_WW_Aufbereitung, true, true, SensorType::TAG_NACHT_AUTO_SELECT, 0, "CFG_WW_Aufbereitung", "", NULL},
        { BW1HK1    , true, false, SensorType::INT, 0, "Betriebswerte 1 HK1", "", NULL },
        { BW2HK1    , true, false, SensorType::INT, 0, "Betriebswerte 2 HK1", "", NULL },
        { VSTHK1    , true, false, SensorType::INT, 0, "Vorlaufsolltemperatur HK1", "°C", NULL },        // (Grad)
        { VITHK1    , true, false, SensorType::INT, 0, "Vorlaufisttemperatur HK1", "°C", NULL },         // (Grad)
        { RSTHK1    , true, false, SensorType::INTDIVIDEDBY2, 0, "Raumsolltemperatur HK1", "°C", NULL },           // (Grad)
        { RITHK1    , true, false, SensorType::INTDIVIDEDBY2, 0, "Raumisttemperatur HK1", "°C", NULL },            // (Grad)
        { EOZHK1    , true, false, SensorType::INT, 0, "Einschaltoptimierungszeit HK1", "", NULL },
        { AOZHK1    , true, false, SensorType::INT, 0, "Ausschaltoptimierungszeit HK1", "", NULL },
        { PLHK1     , true, false, SensorType::INT, 0, "Pumpenleistung HK1", "%", NULL },               // (Grad)
        { MSHK1     , true, false, SensorType::INT, 0, "Mischerstellung HK1", "%", NULL },              // (Grad)
        { NB01      , false, false, SensorType::NONE, 0, "nicht belegt", "", NULL },
        { NB02      , false, false, SensorType::NONE, 0, "nicht belegt", "", NULL },
        { KLHK1_P10 , true, false, SensorType::INT, 0, "Heizkennlinie HK1 bei + 10 Grad", "°C", NULL },  // (Grad)
        { KLHK1_P00 , true, false, SensorType::INT, 0, "Heizkennlinie HK1 bei 0 Grad", "°C", NULL },     // (Grad)
        { KLHK1_N10 , true, false, SensorType::INT, 0, "Heizkennlinie HK1 bei - 10 Grad", "°C", NULL },  // (Grad)
        { NB03      , false, false, SensorType::NONE, 0, "nicht belegt", "", NULL },
        { NB04      , false, false, SensorType::NONE, 0, "nicht belegt", "", NULL },
        { NB05      , false, false, SensorType::NONE, 0, "nicht belegt", "", NULL },
    
        { BW1HK2    , true, false, SensorType::INT, 0, "Betriebswerte 1 HK2", "", NULL },
        { BW2HK2    , true, false, SensorType::INT, 0, "Betriebswerte 2 HK2", "", NULL },
        { VSTHK2    , true, false, SensorType::INT, 0, "Vorlaufsolltemperatur HK2", "°C", NULL },        // (Grad)
        { VITHK2    , true, false, SensorType::INT, 0, "Vorlaufisttemperatur HK2", "°C", NULL },         // (Grad)
        { RSTHK2    , true, false, SensorType::INTDIVIDEDBY2, 0, "Raumsolltemperatur HK2", "°C", NULL },           // (Grad)
        { RITHK2    , true, false, SensorType::INTDIVIDEDBY2, 0, "Raumisttemperatur HK2", "°C", NULL },            // (Grad)
        { EOZHK2    , true, false, SensorType::INT, 0, "Einschaltoptimierungszeit HK2", "", NULL },
        { AOZHK2    , true, false, SensorType::INT, 0, "Ausschaltoptimierungszeit HK2", "", NULL },
        { PLHK2     , true, false, SensorType::INT, 0, "Pumpenleistung HK2", "%", NULL },
        { MSHK2     , true, false, SensorType::INT, 0, "Mischerstellung HK2", "%", NULL },
        { NB06      , false, false, SensorType::NONE, 0, "nicht belegt", "", NULL },
        { NB07      , false, false, SensorType::NONE, 0, "nicht belegt", "", NULL },
        { KLHK2_P10 , true, false, SensorType::INT, 0, "Heizkennlinie HK2 bei + 10 Grad", "°C", NULL },  // (Grad)
        { KLHK2_P00 , true, false, SensorType::INT, 0, "Heizkennlinie HK2 bei 0 Grad", "°C", NULL },     // (Grad)
        { KLHK2_N10 , true, false, SensorType::INT, 0, "Heizkennlinie HK2 bei - 10 Grad", "°C", NULL },  // (Grad)
        { NB08      , false, false, SensorType::NONE, 0, "nicht belegt", "", NULL },
        { NB09      , false, false, SensorType::NONE, 0, "nicht belegt", "", NULL },
        { NB10      , false, false, SensorType::NONE, 0, "nicht belegt", "", NULL },
    
        { BW1WW     , true, false, SensorType::INT, 0, "Betriebswerte 1 WW", "", NULL },
        { BW2WW     , true, false, SensorType::INT, 0, "Betriebswerte 2 WW", "", NULL },
        { WWST      , true, false, SensorType::INT, 0, "Warmwassersolltemperatur", "°C", NULL },         // (Grad)
        { WWIT      , true, false, SensorType::INT, 0, "Warmwasseristtemperatur", "°C", NULL },          // (Grad)
        { OZWW      , true, false, SensorType::INT, 0, "Warmwasseroptimierungszeit", "", NULL },
        { LPWW      , true, false, SensorType::INT, 0, "Ladepumpe", "", NULL },                          // ["aus", "Ladepumpe", "Warmwasserpumpe", "beide"]

        { KVST      , true, false, SensorType::INT, 0, "Kesselvorlaufsolltemperatur", "°C", NULL },      // (Grad)
        { KVIT      , true, false, SensorType::INT, 0, "Kesselvorlaufisttemperatur", "°C", NULL },       // (Grad)
        { BET       , true, false, SensorType::INT, 0, "Brennereinschalttemperatur", "°C", NULL },       // (Grad)
        { BAT       , true, false, SensorType::INT, 0, "Brennerausschalttemperatur", "°C", NULL },       // (Grad)
        { KINT1     , true, false, SensorType::INT, 0, "Kesselintegral 1", "", NULL },
        { KINT2     , true, false, SensorType::INT, 0, "Kesselintegral 2", "", NULL },
        { KFEHL     , true, false, SensorType::INT, 0, "Kesselfehler", "", NULL },
        { KBETR     , true, false, SensorType::INT, 0, "Kesselbetrieb", "", NULL },
        { BANST     , true, false, SensorType::INT, 0, "Brenneransteuerung", "", NULL },                 // ["aus", "an"]
        { ABTMP     , true, false, SensorType::INT, 0, "Abgastemperatur", "°C", NULL },                  // (Grad)
        { MODBSTELL , true, false, SensorType::INT, 0, "modulare Brenner Stellwert", "", NULL },
        { NB11      , false, false, SensorType::NONE, 0, "nicht belegt", "", NULL },
        { BLZ1S2    , true, false, SensorType::INT, 0, "Brennerlaufzeit 1 Stunden 2", "h", NULL },
        { BLZ1S1    , true, false, SensorType::INT, 0, "Brennerlaufzeit 1 Stunden 1", "h", NULL },
        { BLZ1S0    , true, false, SensorType::INT, 0, "Brennerlaufzeit 1 Stunden 0", "h", NULL },
        { BLZ2S2    , true, false, SensorType::INT, 0, "Brennerlaufzeit 2 Stunden 2", "h", NULL },
        { BLZ2S1    , true, false, SensorType::INT, 0, "Brennerlaufzeit 2 Stunden 1", "h", NULL },
        { BLZ2S0    , true, false, SensorType::INT, 0, "Brennerlaufzeit 2 Stunden 0", "h", NULL },
    
        { AT        , true, false, SensorType::INT, 0, "Aussentemperatur", "°C", NULL },                 // (Grad)
        { ATD       , true, false, SensorType::INT, 0, "Gedaempfte Aussentemperatur", "°C", NULL },      // (Grad)
        { VVK       , true, false, SensorType::INT, 0, "Versionsnummer VK", "", NULL },
        { VNK       , true, false, SensorType::INT, 0, "Versionsnummer NK", "", NULL },
        { MODKENN   , true, false, SensorType::INT, 0, "Modulkennung", "", NULL },
        { NB12      , false, false, SensorType::NONE, 0, "nicht belegt", "", NULL },

        { ALARM     , true, false, SensorType::INT, 0, "Alarmstatus", "", NULL }
};


}
}
