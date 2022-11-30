#pragma once

#include <string>
#include <vector>
#include "esphome/core/component.h"
#include "esphome/components/sensor/sensor.h"
#include "esphome/components/binary_sensor/binary_sensor.h"


namespace esphome {
namespace KM271 {


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

enum Buderus_R2017_ErrorMsg {
    0 = "Kein Fehler",
    2 = "Aussenfühler defekt",
    3 = "HK1-Vorlauffühler defekt",
    4 = "HK2-Vorlauffühler defekt",
    8 = "Warmwasserfühler defekt",
    9 = "Warmwasser bleibt kalt",
   10 = "Störung thermische Desinfektion",
   11 = "HK1-Fernbedienung defekt",
   12 = "HK2-Fernbedienung defekt",
   15 = "Keine Kommunikation mit HK1-Fernbedienung",
   16 = "Keine Kommunikation mit HK2-Fernbedienung",
   20 = "Störung Brenner 1",
   24 = "Keine Verbindung mit Kessel 1",
   30 = "Interner Fehler Nr. 1",
   31 = "Interner Fehler Nr. 2",
   32 = "Interner Fehler Nr. 3",
   33 = "Interner Fehler Nr. 4",
   49 = "Kesselvorlauffühler defekt",
   50 = "Kesselzusatzfühler defekt",
   51 = "Kessel bleibt kalt",
   52 = "Störung Brenner",
   53 = "Störung Sicherheitskette",
   54 = "Externe Störung Kessel",
   55 = "Abgasfühler defekt",
   56 = "Abgasgrenze überschritten",
   87 = "Rücklauffühler defekt",
   92 = "RESET"

};

enum SensorType {
    NONE = 0,
    INT,
    INTDIVIDEDBY2,
    STRING,
};


class BuderusParamSensor {
    public:
        BuderusParamSensor(esphome::sensor::Sensor * sensor, SensorType sensorType);
        BuderusParamSensor(esphome::binary_sensor::BinarySensor * sensor);

        void parseAndTransmit(uint8_t *data, size_t len);

    private:
        esphome::sensor::Sensor *sensor;
        esphome::binary_sensor::BinarySensor *binarySensor;
        SensorType sensorType;
};


struct t_Buderus_R2017_ParamDesc {
    Buderus_R2017_ParameterId parameterId;
    bool debugEn;
    SensorType sensorType;
    const char* desc;
    const char* unit;
    BuderusParamSensor* sensor;
};

typedef struct t_Buderus_R2017_ParamDesc t_Buderus_R2017_ParamDesc;

static t_Buderus_R2017_ParamDesc buderusParamDesc[] = {
        { BW1HK1    , true, SensorType::INT, "Betriebswerte 1 HK1", "", NULL },
        { BW2HK1    , true, SensorType::INT, "Betriebswerte 2 HK1", "", NULL },
        { VSTHK1    , true, SensorType::INT, "Vorlaufsolltemperatur HK1", "°C", NULL },        // (Grad)
        { VITHK1    , true, SensorType::INT, "Vorlaufisttemperatur HK1", "°C", NULL },         // (Grad)
        { RSTHK1    , true, SensorType::INTDIVIDEDBY2, "Raumsolltemperatur HK1", "°C", NULL },           // (Grad)
        { RITHK1    , true, SensorType::INTDIVIDEDBY2, "Raumisttemperatur HK1", "°C", NULL },            // (Grad)
        { EOZHK1    , true, SensorType::INT, "Einschaltoptimierungszeit HK1", "", NULL },
        { AOZHK1    , true, SensorType::INT, "Ausschaltoptimierungszeit HK1", "", NULL },
        { PLHK1     , true, SensorType::INT, "Pumpenleistung HK1", "%", NULL },               // (Grad)
        { MSHK1     , true, SensorType::INT, "Mischerstellung HK1", "%", NULL },              // (Grad)
        { NB01      , false, SensorType::NONE, "nicht belegt", "", NULL },
        { NB02      , false, SensorType::NONE, "nicht belegt", "", NULL },
        { KLHK1_P10 , true, SensorType::INT, "Heizkennlinie HK1 bei + 10 Grad", "°C", NULL },  // (Grad)
        { KLHK1_P00 , true, SensorType::INT, "Heizkennlinie HK1 bei 0 Grad", "°C", NULL },     // (Grad)
        { KLHK1_N10 , true, SensorType::INT, "Heizkennlinie HK1 bei - 10 Grad", "°C", NULL },  // (Grad)
        { NB03      , false, SensorType::NONE, "nicht belegt", "", NULL },
        { NB04      , false, SensorType::NONE, "nicht belegt", "", NULL },
        { NB05      , false, SensorType::NONE, "nicht belegt", "", NULL },
    
        { BW1HK2    , true, SensorType::INT, "Betriebswerte 1 HK2", "", NULL },
        { BW2HK2    , true, SensorType::INT, "Betriebswerte 2 HK2", "", NULL },
        { VSTHK2    , true, SensorType::INT, "Vorlaufsolltemperatur HK2", "°C", NULL },        // (Grad)
        { VITHK2    , true, SensorType::INT, "Vorlaufisttemperatur HK2", "°C", NULL },         // (Grad)
        { RSTHK2    , true, SensorType::INTDIVIDEDBY2, "Raumsolltemperatur HK2", "°C", NULL },           // (Grad)
        { RITHK2    , true, SensorType::INTDIVIDEDBY2, "Raumisttemperatur HK2", "°C", NULL },            // (Grad)
        { EOZHK2    , true, SensorType::INT, "Einschaltoptimierungszeit HK2", "", NULL },
        { AOZHK2    , true, SensorType::INT, "Ausschaltoptimierungszeit HK2", "", NULL },
        { PLHK2     , true, SensorType::INT, "Pumpenleistung HK2", "%", NULL },
        { MSHK2     , true, SensorType::INT, "Mischerstellung HK2", "%", NULL },
        { NB06      , false, SensorType::NONE, "nicht belegt", "", NULL },
        { NB07      , false, SensorType::NONE, "nicht belegt", "", NULL },
        { KLHK2_P10 , true, SensorType::INT, "Heizkennlinie HK2 bei + 10 Grad", "°C", NULL },  // (Grad)
        { KLHK2_P00 , true, SensorType::INT, "Heizkennlinie HK2 bei 0 Grad", "°C", NULL },     // (Grad)
        { KLHK2_N10 , true, SensorType::INT, "Heizkennlinie HK2 bei - 10 Grad", "°C", NULL },  // (Grad)
        { NB08      , false, SensorType::NONE, "nicht belegt", "", NULL },
        { NB09      , false, SensorType::NONE, "nicht belegt", "", NULL },
        { NB10      , false, SensorType::NONE, "nicht belegt", "", NULL },
    
        { BW1WW     , true, SensorType::INT, "Betriebswerte 1 WW", "", NULL },
        { BW2WW     , true, SensorType::INT, "Betriebswerte 2 WW", "", NULL },
        { WWST      , true, SensorType::INT, "Warmwassersolltemperatur", "°C", NULL },         // (Grad)
        { WWIT      , true, SensorType::INT, "Warmwasseristtemperatur", "°C", NULL },          // (Grad)
        { OZWW      , true, SensorType::INT, "Warmwasseroptimierungszeit", "", NULL },
        { LPWW      , true, SensorType::INT, "Ladepumpe", "", NULL },                          // ["aus", "Ladepumpe", "Warmwasserpumpe", "beide"]

        { KVST      , true, SensorType::INT, "Kesselvorlaufsolltemperatur", "°C", NULL },      // (Grad)
        { KVIT      , true, SensorType::INT, "Kesselvorlaufisttemperatur", "°C", NULL },       // (Grad)
        { BET       , true, SensorType::INT, "Brennereinschalttemperatur", "°C", NULL },       // (Grad)
        { BAT       , true, SensorType::INT, "Brennerausschalttemperatur", "°C", NULL },       // (Grad)
        { KINT1     , true, SensorType::INT, "Kesselintegral 1", "", NULL },
        { KINT2     , true, SensorType::INT, "Kesselintegral 2", "", NULL },
        { KFEHL     , true, SensorType::INT, "Kesselfehler", "", NULL },
        { KBETR     , true, SensorType::INT, "Kesselbetrieb", "", NULL },
        { BANST     , true, SensorType::INT, "Brenneransteuerung", "", NULL },                 // ["aus", "an"]
        { ABTMP     , true, SensorType::INT, "Abgastemperatur", "°C", NULL },                  // (Grad)
        { MODBSTELL , true, SensorType::INT, "modulare Brenner Stellwert", "", NULL },
        { NB11      , false, SensorType::NONE, "nicht belegt", "", NULL },
        { BLZ1S2    , true, SensorType::INT, "Brennerlaufzeit 1 Stunden 2", "h", NULL },
        { BLZ1S1    , true, SensorType::INT, "Brennerlaufzeit 1 Stunden 1", "h", NULL },
        { BLZ1S0    , true, SensorType::INT, "Brennerlaufzeit 1 Stunden 0", "h", NULL },
        { BLZ2S2    , true, SensorType::INT, "Brennerlaufzeit 2 Stunden 2", "h", NULL },
        { BLZ2S1    , true, SensorType::INT, "Brennerlaufzeit 2 Stunden 1", "h", NULL },
        { BLZ2S0    , true, SensorType::INT, "Brennerlaufzeit 2 Stunden 0", "h", NULL },
    
        { AT        , true, SensorType::INT, "Aussentemperatur", "°C", NULL },                 // (Grad)
        { ATD       , true, SensorType::INT, "Gedaempfte Aussentemperatur", "°C", NULL },      // (Grad)
        { VVK       , true, SensorType::INT, "Versionsnummer VK", "", NULL },
        { VNK       , true, SensorType::INT, "Versionsnummer NK", "", NULL },
        { MODKENN   , true, SensorType::INT, "Modulkennung", "", NULL },
        { NB12      , false, SensorType::NONE, "nicht belegt", "", NULL },

        { ALARM     , true, SensorType::INT, "Alarmstatus", "", NULL }

};


}
}
