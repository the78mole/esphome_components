#pragma once

#include <string>
#include <vector>
#include "esphome/core/component.h"
#include "esphome/components/sensor/sensor.h"

namespace esphome {
namespace KM271 {


enum Buderus_R2017_Params {
    BW1HK1    = 0x8000, //: "Betriebswerte 1 HK1"
    BW2HK1    = 0x8001, //: "Betriebswerte 2 HK1"
    VSTHK1    = 0x8002, //: "Vorlaufsolltemperatur HK1"       (Grad)
    VITHK1    = 0x8003, //: "Vorlaufisttemperatur HK1"        (Grad)
    RSTHK1    = 0x8004, //: "Raumsolltemperatur HK1"          (Grad)
    RITHK1    = 0x8005, //: "Raumisttemperatur HK1"           (Grad)   
    EOZHK1    = 0x8006, //: "Einschaltoptimierungszeit HK1"
    AOZHK1    = 0x8007, //: "Ausschaltoptimierungszeit HK1"
    PLHK1     = 0x8008, //: "Pumpenleistung HK1"              (Grad)
    MSHK1     = 0x8009, //: "Mischerstellung HK1"             (Grad)
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
    PLHK2     = 0x811a, //: "Pumpenleistung HK2"
    MSHK2     = 0x811b, //: "Mischerstellung HK2"
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
};

struct t_Buderus_R2017_ParamDesc {
    Buderus_R2017_Params param;
    bool debugEn;
    const char* desc;
    const char* unit;
};

typedef struct t_Buderus_R2017_ParamDesc t_Buderus_R2017_ParamDesc;

static const t_Buderus_R2017_ParamDesc buderusParamDesc[] = {
        { BW1HK1    , true, "Betriebswerte 1 HK1", "" },
    	{ BW2HK1    , true, "Betriebswerte 2 HK1", "" },
    	{ VSTHK1    , true, "Vorlaufsolltemperatur HK1", "°C" },        // (Grad)
    	{ VITHK1    , true, "Vorlaufisttemperatur HK1", "°C" },         // (Grad)
    	{ RSTHK1    , true, "Raumsolltemperatur HK1", "°C" },           // (Grad)
    	{ RITHK1    , true, "Raumisttemperatur HK1", "°C" },            // (Grad)   
    	{ EOZHK1    , true, "Einschaltoptimierungszeit HK1", "" },
    	{ AOZHK1    , true, "Ausschaltoptimierungszeit HK1", "" },
    	{ PLHK1     , true, "Pumpenleistung HK1", "°C" },               // (Grad)
    	{ MSHK1     , true, "Mischerstellung HK1", "°C" },              // (Grad)
    	{ NB01      , true, "nicht belegt", "" },
    	{ NB02      , true, "nicht belegt", "" },
    	{ KLHK1_P10 , true, "Heizkennlinie HK1 bei + 10 Grad", "°C" },  // (Grad)
    	{ KLHK1_P00 , true, "Heizkennlinie HK1 bei 0 Grad", "°C" },     // (Grad)
    	{ KLHK1_N10 , true, "Heizkennlinie HK1 bei - 10 Grad", "°C" },  // (Grad)
    	{ NB03      , false, "nicht belegt", "" },
    	{ NB04      , false, "nicht belegt", "" },
    	{ NB05      , false, "nicht belegt", "" },
    
    	{ BW1HK2    , true, "Betriebswerte 1 HK2", "" },
    	{ BW2HK1    , true, "Betriebswerte 2 HK2", "" },
    	{ VSTHK2    , true, "Vorlaufsolltemperatur HK2", "°C" },        // (Grad)
    	{ VITHK2    , true, "Vorlaufisttemperatur HK2", "°C" },         // (Grad)
    	{ RSTHK2    , true, "Raumsolltemperatur HK2", "°C" },           // (Grad)
    	{ RITHK2    , true, "Raumisttemperatur HK2", "°C" },            // (Grad)
    	{ EOZHK2    , true, "Einschaltoptimierungszeit HK2", "" },
    	{ AOZHK2    , true, "Ausschaltoptimierungszeit HK2", "" },
    	{ PLHK2     , true, "Pumpenleistung HK2", "" },
    	{ MSHK2     , true, "Mischerstellung HK2", "" },
    	{ NB06      , false, "nicht belegt", "" },
    	{ NB07      , false, "nicht belegt", "" },
    	{ KLHK2_P10 , true, "Heizkennlinie HK2 bei + 10 Grad", "°C" },  // (Grad)
    	{ KLHK2_P00 , true, "Heizkennlinie HK2 bei 0 Grad", "°C" },     // (Grad)
    	{ KLHK2_N10 , true, "Heizkennlinie HK2 bei - 10 Grad", "°C" },  // (Grad)
    	{ NB08      , false, "nicht belegt", "" },
    	{ NB09      , false, "nicht belegt", "" },
    	{ NB10      , false, "nicht belegt", "" },
    
    	{ BW1WW     , true, "Betriebswerte 1 WW", "" },
    	{ BW2WW     , true, "Betriebswerte 2 WW", "" },
    	{ WWST      , true, "Warmwassersolltemperatur", "°C" },         // (Grad)
    	{ WWIT      , true, "Warmwasseristtemperatur", "°C" },          // (Grad)
    	{ OZWW      , true, "Warmwasseroptimierungszeit", "" },
    	{ LPWW      , true, "Ladepumpe", "" },                          // ["aus", "Ladepumpe", "Warmwasserpumpe", "beide"]
    
    	{ KVST      , true, "Kesselvorlaufsolltemperatur", "°C" },      // (Grad)
    	{ KVIT      , true, "Kesselvorlaufisttemperatur", "°C" },       // (Grad)
    	{ BET       , true, "Brennereinschalttemperatur", "°C" },       // (Grad)
    	{ BAT       , true, "Brennerausschalttemperatur", "°C" },       // (Grad)
    	{ KINT1     , false, "Kesselintegral 1", "" },
    	{ KINT2     , false, "Kesselintegral 2", "" },
    	{ KFEHL     , true, "Kesselfehler", "" },
    	{ KBETR     , true, "Kesselbetrieb", "" },
    	{ BANST     , true, "Brenneransteuerung", "" },                 // ["aus", "an"]
    	{ ABTMP     , true, "Abgastemperatur", "°C" },                  // (Grad)
    	{ MODBSTELL , true, "modulare Brenner Stellwert", "" },
    	{ NB11      , false, "nicht belegt", "" },
    	{ BLZ1S2    , true, "Brennerlaufzeit 1 Stunden 2", "h" },
    	{ BLZ1S1    , true, "Brennerlaufzeit 1 Stunden 1", "h" },
    	{ BLZ1S0    , true, "Brennerlaufzeit 1 Stunden 0", "h" },
    	{ BLZ2S2    , true, "Brennerlaufzeit 2 Stunden 2", "h" },
    	{ BLZ2S1    , true, "Brennerlaufzeit 2 Stunden 1", "h" },
    	{ BLZ2S0    , true, "Brennerlaufzeit 2 Stunden 0", "h" },
    
    	{ AT        , true, "Aussentemperatur", "°C" },                 // (Grad)
    	{ ATD       , true, "Gedaempfte Aussentemperatur", "°C" },      // (Grad)
    	{ VVK       , true, "Versionsnummer VK", "" },
    	{ VNK       , true, "Versionsnummer NK", "" },
    	{ MODKENN   , true, "Modulkennung", "" },
    	{ NB12      , false, "nicht belegt", "" },
};

enum SensorType {
    NONE = 0,
    INT,
    STRING,
};


class BuderusParamSensor {
    public:
        BuderusParamSensor();
        
    protected:
        
};
// class BuderusParams {
//     public:
//         bool parseData(const * buf, size_t len);

//         bool canHandle(uint16_t param);
//         int getInteger();
//         void getPChar(const char * cchar, size_t len);
//         string getString();
//         float getFloat();

// }

}
}