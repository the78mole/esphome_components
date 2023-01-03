import esphome.codegen as cg
import esphome.config_validation as cv
from esphome.components import binary_sensor
from esphome.core import EnumValue

from esphome.const import (
    CONF_ID,
    DEVICE_CLASS_PROBLEM,
    DEVICE_CLASS_RUNNING,
    DEVICE_CLASS_POWER,
    ENTITY_CATEGORY_DIAGNOSTIC
)

from . import (
    CONF_KM271_ID,
    KM271
)

from .const import *

CODEOWNERS = ["@the78mole", "@jensgraef"]

TYPES = [
    HC1_IS_OPT_SWOFF,
    HC1_IS_OPT_SWON,
    HC1_IS_AUTO,
    HC1_IS_PRIO_WW,
    HC1_IS_SCREED_DRY,
    HC1_IS_HOLIDAY,
    HC1_IS_NOFREEZE,
    HC1_IS_MANUALLY,
    HC1_IS_SUMMER,
    HC1_IS_DAY,
    HC1_IS_RC_NOCOMM,
    HC1_IS_RC_FAULTY,
    HC1_IS_ERR_FLOWSENS,
    HC1_IS_MAX_FLOW,
    HC1_IS_EXT_FAULT,

    HC2_IS_OPT_SWOFF,
    HC2_IS_OPT_SWON,
    HC2_IS_AUTO,
    HC2_IS_PRIO_WW,
    HC2_IS_SCREED_DRY,
    HC2_IS_HOLIDAY,
    HC2_IS_NOFREEZE,
    HC2_IS_MANUALLY,
    HC2_IS_SUMMER,
    HC2_IS_DAY,
    HC2_IS_RC_NOCOMM,
    HC2_IS_RC_FAULTY,
    HC2_IS_ERR_FLOWSENS,
    HC2_IS_MAX_FLOW,
    HC2_IS_EXT_FAULT,

    WW_IS_AUTO,
    WW_IS_DESINFECT,
    WW_IS_RELOAD,
    WW_IS_HOLIDAY,
    WW_IS_ERR_DESINFECT,
    WW_IS_ERR_SENSOR,
    WW_IS_ERR_STAY_COLD,
    WW_IS_ERR_ANODE,
    WW_IS_LOADING,
    WW_IS_MANUALLY,
    WW_IS_RELOADING,
    WW_IS_OPT_SWOFF,
    WW_IS_OPT_SWON,
    WW_IS_DAY,
    WW_IS_POST_PROC,
    WW_IS_PRIO_PROC,

    PUMP_LOAD_RUN,
    PUMP_CIRC_RUN,
    PUMP_SOLAR_LOW,

    ERR_BURN_MALF,
    ERR_BOIL_SENS,
    ERR_ADD_SENS,
    ERR_BOILD_STAY_COLD,
    ERR_EXHAUST_GAS_SENS,
    ERR_EXHAUST_GAS_OVL,
    ERR_SAFETY_CHAIN,
    ERR_EXT_DISTURBANCE,

    BOIL_IS_TEST_EMMISSION,
    BOIL_IS_OP_STAGE1,
    BOIL_IS_PROTECTION,
    BOIL_IS_UNDER_OP,
    BOIL_IS_PERF_FREE,
    BOIL_IS_PERF_HIGH,
    BOIL_IS_OP_STAGE2,

    BOIL_IS_ACT,

    ALARM_EXHAUST_GASSENS,
    ALARM_BOILER_FLOWSENS,
    ALARM_BURNER,
    ALARM_HC2_FLOWSENS
]

CONFIG_SCHEMA = (
    cv.Schema(
        {
            cv.GenerateID(CONF_KM271_ID): cv.use_id(KM271),
            cv.Optional(HC1_IS_OPT_SWOFF): binary_sensor.binary_sensor_schema(
#                device_class=DEVICE_CLASS_NONE,
                entity_category=ENTITY_CATEGORY_DIAGNOSTIC,
            ),
            cv.Optional(HC1_IS_OPT_SWON): binary_sensor.binary_sensor_schema(
#                device_class=DEVICE_CLASS_NONE,
                entity_category=ENTITY_CATEGORY_DIAGNOSTIC,
            ),
            cv.Optional(HC1_IS_AUTO): binary_sensor.binary_sensor_schema(
#                device_class=DEVICE_CLASS_NONE,
                entity_category=ENTITY_CATEGORY_DIAGNOSTIC,
            ),
            cv.Optional(HC1_IS_PRIO_WW): binary_sensor.binary_sensor_schema(
#                device_class=DEVICE_CLASS_NONE,
                entity_category=ENTITY_CATEGORY_DIAGNOSTIC,
            ),
            cv.Optional(HC1_IS_SCREED_DRY): binary_sensor.binary_sensor_schema(
#                device_class=DEVICE_CLASS_NONE,
                entity_category=ENTITY_CATEGORY_DIAGNOSTIC,
            ),
            cv.Optional(HC1_IS_HOLIDAY): binary_sensor.binary_sensor_schema(
#                device_class=DEVICE_CLASS_NONE,
                entity_category=ENTITY_CATEGORY_DIAGNOSTIC,
            ),
            cv.Optional(HC1_IS_NOFREEZE): binary_sensor.binary_sensor_schema(
#                device_class=DEVICE_CLASS_NONE,
                entity_category=ENTITY_CATEGORY_DIAGNOSTIC,
            ),
            cv.Optional(HC1_IS_MANUALLY): binary_sensor.binary_sensor_schema(
#                device_class=DEVICE_CLASS_NONE,
                entity_category=ENTITY_CATEGORY_DIAGNOSTIC,
            ),
            cv.Optional(HC1_IS_SUMMER): binary_sensor.binary_sensor_schema(
#                device_class=DEVICE_CLASS_NONE,
                entity_category=ENTITY_CATEGORY_DIAGNOSTIC,
            ),
            cv.Optional(HC1_IS_DAY): binary_sensor.binary_sensor_schema(
#                device_class=DEVICE_CLASS_NONE,
                entity_category=ENTITY_CATEGORY_DIAGNOSTIC,
            ),
            cv.Optional(HC1_IS_RC_NOCOMM): binary_sensor.binary_sensor_schema(
#                device_class=DEVICE_CLASS_NONE,
                entity_category=ENTITY_CATEGORY_DIAGNOSTIC,
            ),
            cv.Optional(HC1_IS_RC_FAULTY): binary_sensor.binary_sensor_schema(
#                device_class=DEVICE_CLASS_NONE,
                entity_category=ENTITY_CATEGORY_DIAGNOSTIC,
            ),
            cv.Optional(HC1_IS_ERR_FLOWSENS): binary_sensor.binary_sensor_schema(
#                device_class=DEVICE_CLASS_NONE,
                entity_category=ENTITY_CATEGORY_DIAGNOSTIC,
            ),
            cv.Optional(HC1_IS_MAX_FLOW): binary_sensor.binary_sensor_schema(
#                device_class=DEVICE_CLASS_NONE,
                entity_category=ENTITY_CATEGORY_DIAGNOSTIC,
            ),
            cv.Optional(HC1_IS_EXT_FAULT): binary_sensor.binary_sensor_schema(
#                device_class=DEVICE_CLASS_NONE,
                entity_category=ENTITY_CATEGORY_DIAGNOSTIC,
            ),
            cv.Optional(HC2_IS_OPT_SWOFF): binary_sensor.binary_sensor_schema(
#                device_class=DEVICE_CLASS_NONE,
                entity_category=ENTITY_CATEGORY_DIAGNOSTIC,
            ),
            cv.Optional(HC2_IS_OPT_SWON): binary_sensor.binary_sensor_schema(
#                device_class=DEVICE_CLASS_NONE,
                entity_category=ENTITY_CATEGORY_DIAGNOSTIC,
            ),
            cv.Optional(HC2_IS_AUTO): binary_sensor.binary_sensor_schema(
#                device_class=DEVICE_CLASS_NONE,
                entity_category=ENTITY_CATEGORY_DIAGNOSTIC,
            ),
            cv.Optional(HC2_IS_PRIO_WW): binary_sensor.binary_sensor_schema(
                device_class=DEVICE_CLASS_RUNNING,
                entity_category=ENTITY_CATEGORY_DIAGNOSTIC,
            ),
            cv.Optional(HC2_IS_SCREED_DRY): binary_sensor.binary_sensor_schema(
                device_class=DEVICE_CLASS_RUNNING,
                entity_category=ENTITY_CATEGORY_DIAGNOSTIC,
            ),
            cv.Optional(HC2_IS_HOLIDAY): binary_sensor.binary_sensor_schema(
#                device_class=DEVICE_CLASS_NONE,
                entity_category=ENTITY_CATEGORY_DIAGNOSTIC,
            ),
            cv.Optional(HC2_IS_NOFREEZE): binary_sensor.binary_sensor_schema(
#                device_class=DEVICE_CLASS_NONE,
                entity_category=ENTITY_CATEGORY_DIAGNOSTIC,
            ),
            cv.Optional(HC2_IS_MANUALLY): binary_sensor.binary_sensor_schema(
#                device_class=DEVICE_CLASS_NONE,
                entity_category=ENTITY_CATEGORY_DIAGNOSTIC,
            ),
            cv.Optional(HC2_IS_SUMMER): binary_sensor.binary_sensor_schema(
#                device_class=DEVICE_CLASS_NONE,
                entity_category=ENTITY_CATEGORY_DIAGNOSTIC,
            ),
            cv.Optional(HC2_IS_DAY): binary_sensor.binary_sensor_schema(
#                device_class=DEVICE_CLASS_NONE,
                entity_category=ENTITY_CATEGORY_DIAGNOSTIC,
            ),
            cv.Optional(HC2_IS_RC_NOCOMM): binary_sensor.binary_sensor_schema(
#                device_class=DEVICE_CLASS_NONE,
                entity_category=ENTITY_CATEGORY_DIAGNOSTIC,
            ),
            cv.Optional(HC2_IS_RC_FAULTY): binary_sensor.binary_sensor_schema(
#                device_class=DEVICE_CLASS_NONE,
                entity_category=ENTITY_CATEGORY_DIAGNOSTIC,
            ),
            cv.Optional(HC2_IS_ERR_FLOWSENS): binary_sensor.binary_sensor_schema(
#                device_class=DEVICE_CLASS_NONE,
                entity_category=ENTITY_CATEGORY_DIAGNOSTIC,
            ),
            cv.Optional(HC2_IS_MAX_FLOW): binary_sensor.binary_sensor_schema(
#                device_class=DEVICE_CLASS_NONE,
                entity_category=ENTITY_CATEGORY_DIAGNOSTIC,
            ),
            cv.Optional(HC2_IS_EXT_FAULT): binary_sensor.binary_sensor_schema(
#                device_class=DEVICE_CLASS_NONE,
                entity_category=ENTITY_CATEGORY_DIAGNOSTIC,
            ),

            cv.Optional(WW_IS_AUTO): binary_sensor.binary_sensor_schema(
#                device_class=DEVICE_CLASS_NONE,
                entity_category=ENTITY_CATEGORY_DIAGNOSTIC,
            ),
            cv.Optional(WW_IS_DESINFECT): binary_sensor.binary_sensor_schema(
#                device_class=DEVICE_CLASS_NONE,
                entity_category=ENTITY_CATEGORY_DIAGNOSTIC,
            ),
            cv.Optional(WW_IS_RELOAD): binary_sensor.binary_sensor_schema(
#                device_class=DEVICE_CLASS_NONE,
                entity_category=ENTITY_CATEGORY_DIAGNOSTIC,
            ),
            cv.Optional(WW_IS_HOLIDAY): binary_sensor.binary_sensor_schema(
                device_class=DEVICE_CLASS_RUNNING,
                entity_category=ENTITY_CATEGORY_DIAGNOSTIC,
            ),
            cv.Optional(WW_IS_ERR_DESINFECT): binary_sensor.binary_sensor_schema(
                device_class=DEVICE_CLASS_RUNNING,
                entity_category=ENTITY_CATEGORY_DIAGNOSTIC,
            ),
            cv.Optional(WW_IS_ERR_SENSOR): binary_sensor.binary_sensor_schema(
                device_class=DEVICE_CLASS_PROBLEM,
                entity_category=ENTITY_CATEGORY_DIAGNOSTIC,
            ),
            cv.Optional(WW_IS_ERR_STAY_COLD): binary_sensor.binary_sensor_schema(
                device_class=DEVICE_CLASS_PROBLEM,
                entity_category=ENTITY_CATEGORY_DIAGNOSTIC,
            ),
            cv.Optional(WW_IS_ERR_ANODE): binary_sensor.binary_sensor_schema(
                device_class=DEVICE_CLASS_PROBLEM,
                entity_category=ENTITY_CATEGORY_DIAGNOSTIC,
            ),
            cv.Optional(WW_IS_LOADING): binary_sensor.binary_sensor_schema(
#                device_class=DEVICE_CLASS_NONE,
                entity_category=ENTITY_CATEGORY_DIAGNOSTIC,
            ),
            cv.Optional(WW_IS_MANUALLY): binary_sensor.binary_sensor_schema(
#                device_class=DEVICE_CLASS_NONE,
                entity_category=ENTITY_CATEGORY_DIAGNOSTIC,
            ),
            cv.Optional(WW_IS_RELOADING): binary_sensor.binary_sensor_schema(
#                device_class=DEVICE_CLASS_NONE,
                entity_category=ENTITY_CATEGORY_DIAGNOSTIC,
            ),
            cv.Optional(WW_IS_OPT_SWOFF): binary_sensor.binary_sensor_schema(
#                device_class=DEVICE_CLASS_NONE,
                entity_category=ENTITY_CATEGORY_DIAGNOSTIC,
            ),
            cv.Optional(WW_IS_OPT_SWON): binary_sensor.binary_sensor_schema(
#                device_class=DEVICE_CLASS_NONE,
                entity_category=ENTITY_CATEGORY_DIAGNOSTIC,
            ),
            cv.Optional(WW_IS_DAY): binary_sensor.binary_sensor_schema(
#                device_class=DEVICE_CLASS_NONE,
                entity_category=ENTITY_CATEGORY_DIAGNOSTIC,
            ),
            cv.Optional(WW_IS_POST_PROC): binary_sensor.binary_sensor_schema(
#                device_class=DEVICE_CLASS_NONE,
                entity_category=ENTITY_CATEGORY_DIAGNOSTIC,
            ),
            cv.Optional(WW_IS_PRIO_PROC): binary_sensor.binary_sensor_schema(
#                device_class=DEVICE_CLASS_NONE,
                entity_category=ENTITY_CATEGORY_DIAGNOSTIC,
            ),


            cv.Optional(PUMP_LOAD_RUN): binary_sensor.binary_sensor_schema(
                device_class=DEVICE_CLASS_RUNNING,
                entity_category=ENTITY_CATEGORY_DIAGNOSTIC,
            ),
            cv.Optional(PUMP_CIRC_RUN): binary_sensor.binary_sensor_schema(
                device_class=DEVICE_CLASS_RUNNING,
                entity_category=ENTITY_CATEGORY_DIAGNOSTIC,
            ),
            cv.Optional(PUMP_SOLAR_LOW): binary_sensor.binary_sensor_schema(
                device_class=DEVICE_CLASS_RUNNING,
                entity_category=ENTITY_CATEGORY_DIAGNOSTIC,
            ),

            #            cv.Optional("boiler_error"): binary_sensor.binary_sensor_schema(
            #                device_class=DEVICE_CLASS_PROBLEM,
            #                entity_category=ENTITY_CATEGORY_DIAGNOSTIC,
            #            ),
            cv.Optional(ERR_BURN_MALF): binary_sensor.binary_sensor_schema(
                device_class=DEVICE_CLASS_PROBLEM,
                entity_category=ENTITY_CATEGORY_DIAGNOSTIC,
            ),
            cv.Optional(ERR_BOIL_SENS): binary_sensor.binary_sensor_schema(
                device_class=DEVICE_CLASS_PROBLEM,
                entity_category=ENTITY_CATEGORY_DIAGNOSTIC,
            ),
            cv.Optional(ERR_ADD_SENS): binary_sensor.binary_sensor_schema(
                device_class=DEVICE_CLASS_PROBLEM,
                entity_category=ENTITY_CATEGORY_DIAGNOSTIC,
            ),
            cv.Optional(ERR_BOILD_STAY_COLD): binary_sensor.binary_sensor_schema(
                device_class=DEVICE_CLASS_PROBLEM,
                entity_category=ENTITY_CATEGORY_DIAGNOSTIC,
            ),
            cv.Optional(ERR_EXHAUST_GAS_SENS): binary_sensor.binary_sensor_schema(
                device_class=DEVICE_CLASS_PROBLEM,
                entity_category=ENTITY_CATEGORY_DIAGNOSTIC,
            ),
            cv.Optional(ERR_EXHAUST_GAS_OVL): binary_sensor.binary_sensor_schema(
                device_class=DEVICE_CLASS_PROBLEM,
                entity_category=ENTITY_CATEGORY_DIAGNOSTIC,
            ),
            cv.Optional(ERR_SAFETY_CHAIN): binary_sensor.binary_sensor_schema(
                device_class=DEVICE_CLASS_PROBLEM,
                entity_category=ENTITY_CATEGORY_DIAGNOSTIC,
            ),
            cv.Optional(ERR_EXT_DISTURBANCE): binary_sensor.binary_sensor_schema(
                device_class=DEVICE_CLASS_PROBLEM,
                entity_category=ENTITY_CATEGORY_DIAGNOSTIC,
            ),

            #            cv.Optional("boiler_running"): binary_sensor.binary_sensor_schema(
            #                device_class=DEVICE_CLASS_RUNNING,
            #                entity_category=ENTITY_CATEGORY_DIAGNOSTIC,
            #            ),
            cv.Optional(BOIL_IS_TEST_EMMISSION): binary_sensor.binary_sensor_schema(
#                device_class=DEVICE_CLASS_NONE,
                entity_category=ENTITY_CATEGORY_DIAGNOSTIC,
            ),
            cv.Optional(BOIL_IS_OP_STAGE1): binary_sensor.binary_sensor_schema(
#                device_class=DEVICE_CLASS_NONE,
                entity_category=ENTITY_CATEGORY_DIAGNOSTIC,
            ),
            cv.Optional(BOIL_IS_PROTECTION): binary_sensor.binary_sensor_schema(
#                device_class=DEVICE_CLASS_NONE,
                entity_category=ENTITY_CATEGORY_DIAGNOSTIC,
            ),
            cv.Optional(BOIL_IS_UNDER_OP): binary_sensor.binary_sensor_schema(
#                device_class=DEVICE_CLASS_NONE,
                entity_category=ENTITY_CATEGORY_DIAGNOSTIC,
            ),
            cv.Optional(BOIL_IS_PERF_FREE): binary_sensor.binary_sensor_schema(
#                device_class=DEVICE_CLASS_NONE,
                entity_category=ENTITY_CATEGORY_DIAGNOSTIC,
            ),
            cv.Optional("aa"): binary_sensor.binary_sensor_schema(
#                device_class=DEVICE_CLASS_NONE,
                entity_category=ENTITY_CATEGORY_DIAGNOSTIC,
            ),
            cv.Optional(BOIL_IS_PERF_HIGH): binary_sensor.binary_sensor_schema(
#                device_class=DEVICE_CLASS_NONE,
                entity_category=ENTITY_CATEGORY_DIAGNOSTIC,
            ),
            cv.Optional(BOIL_IS_OP_STAGE2): binary_sensor.binary_sensor_schema(
#                device_class=DEVICE_CLASS_NONE,
                entity_category=ENTITY_CATEGORY_DIAGNOSTIC,
            ),


            cv.Optional(BOIL_IS_ACT): binary_sensor.binary_sensor_schema(
                device_class=DEVICE_CLASS_POWER,
                entity_category=ENTITY_CATEGORY_DIAGNOSTIC,
            ),

            cv.Optional(ALARM_EXHAUST_GASSENS): binary_sensor.binary_sensor_schema(
                device_class=DEVICE_CLASS_PROBLEM,
                entity_category=ENTITY_CATEGORY_DIAGNOSTIC,
            ),
            cv.Optional(ALARM_BOILER_FLOWSENS): binary_sensor.binary_sensor_schema(
                device_class=DEVICE_CLASS_PROBLEM,
                entity_category=ENTITY_CATEGORY_DIAGNOSTIC,
            ),
            cv.Optional(ALARM_BURNER): binary_sensor.binary_sensor_schema(
                device_class=DEVICE_CLASS_PROBLEM,
                entity_category=ENTITY_CATEGORY_DIAGNOSTIC,
            ),
            cv.Optional(ALARM_HC2_FLOWSENS): binary_sensor.binary_sensor_schema(
                device_class=DEVICE_CLASS_PROBLEM,
                entity_category=ENTITY_CATEGORY_DIAGNOSTIC,
            ),
        }
    )
)


async def setup_conf(config, key, hub):
    if key in config:
        conf = config[key]

        sens = await binary_sensor.new_binary_sensor(conf)
        cg.add(getattr(hub, f"set_binary_sensor")(cg.RawExpression("KM271:: " +key), sens))


async def to_code(config):
    hub = await cg.get_variable(config[CONF_KM271_ID])
    for key in TYPES:
        await setup_conf(config, key, hub)
