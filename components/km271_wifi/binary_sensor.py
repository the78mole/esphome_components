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

CODEOWNERS = ["@the78mole", "@jensgraef"]

TYPES = [
    "heating_circuit_1_switch_off_optimization",
    "heating_circuit_1_switch_on_optimization",
    "heating_circuit_1_automatic",
    "heating_circuit_1_ww_priority_processing",
    "heating_circuit_1_screed_drying",
    "heating_circuit_1_holiday",
    "heating_circuit_1_antifreeze",
    "heating_circuit_1_manually",
    "heating_circuit_1_summer",
    "heating_circuit_1_day",
    "heating_circuit_1_no_comm_with_rc",
    "heating_circuit_1_rc_faulty",
    "heating_circuit_1_flow_sensor_error",
    "heating_circuit_1_max_flow",
    "heating_circuit_1_external_fault_input",

    "heating_circuit_2_switch_off_optimization",
    "heating_circuit_2_switch_on_optimization",
    "heating_circuit_2_automatic",
    "heating_circuit_2_ww_priority_processing",
    "heating_circuit_2_screed_drying",
    "heating_circuit_2_holiday",
    "heating_circuit_2_antifreeze",
    "heating_circuit_2_manually",
    "heating_circuit_2_summer",
    "heating_circuit_2_day",
    "heating_circuit_2_no_comm_with_rc",
    "heating_circuit_2_rc_faulty",
    "heating_circuit_2_flow_sensor_error",
    "heating_circuit_2_max_flow",
    "heating_circuit_2_external_fault_input",

    "ww_automatic",
    "ww_disinfection",
    "ww_reload",
    "ww_holiday",
    "ww_error_disinfection",
    "ww_error_sensor",
    "ww_error_stays_cold",
    "ww_error_anode",
    "ww_loading",
    "ww_manually",
    "ww_reloading",
    "ww_switch_off_optimization",
    "ww_switch_on_optimization",
    "ww_day_mode",
    "ww_post_processing",
    "ww_priority_processing",

    "load_pump_running",
    "circulation_pump_running",
    "solar_pump_lowering",

    "error_burner_malfunction",
    "error_boiler_sensor",
    "error_additional_sensor",
    "error_boiler_stays_cold",
    "error_exhaust_gas_sensor",
    "error_exhaust_gas_over_limit",
    "error_safety_chain_released",
    "error_external_disturbance",
 
    "boiler_emission_test",
    "boiler_1st_stage_operation",
    "boiler_protection",
    "boiler_under_operation",
    "boiler_performance_free",
    "boiler_performance_high",
    "boiler_2st_stage_operation",

    "boiler_actuation",

    "alarm_exhaust_gas_sensor",
    "alarm_boiler_flow_sensor",
    "alarm_burner",
    "alarm_heating_circuit_2_flow_sensor"

]

CONFIG_SCHEMA = (
    cv.Schema(
        {
            cv.GenerateID(CONF_KM271_ID): cv.use_id(KM271),
            cv.Optional("heating_circuit_1_switch_off_optimization"): binary_sensor.binary_sensor_schema(
#                device_class=DEVICE_CLASS_NONE,
                entity_category=ENTITY_CATEGORY_DIAGNOSTIC,
            ),
            cv.Optional("heating_circuit_1_switch_on_optimization"): binary_sensor.binary_sensor_schema(
#                device_class=DEVICE_CLASS_NONE,
                entity_category=ENTITY_CATEGORY_DIAGNOSTIC,
            ),
            cv.Optional("heating_circuit_1_automatic"): binary_sensor.binary_sensor_schema(
#                device_class=DEVICE_CLASS_NONE,
                entity_category=ENTITY_CATEGORY_DIAGNOSTIC,
            ),
            cv.Optional("heating_circuit_1_ww_priority_processing"): binary_sensor.binary_sensor_schema(
#                device_class=DEVICE_CLASS_NONE,
                entity_category=ENTITY_CATEGORY_DIAGNOSTIC,
            ),
            cv.Optional("heating_circuit_1_screed_drying"): binary_sensor.binary_sensor_schema(
#                device_class=DEVICE_CLASS_NONE,
                entity_category=ENTITY_CATEGORY_DIAGNOSTIC,
            ),
            cv.Optional("heating_circuit_1_holiday"): binary_sensor.binary_sensor_schema(
#                device_class=DEVICE_CLASS_NONE,
                entity_category=ENTITY_CATEGORY_DIAGNOSTIC,
            ),
            cv.Optional("heating_circuit_1_antifreeze"): binary_sensor.binary_sensor_schema(
#                device_class=DEVICE_CLASS_NONE,
                entity_category=ENTITY_CATEGORY_DIAGNOSTIC,
            ),
            cv.Optional("heating_circuit_1_manually"): binary_sensor.binary_sensor_schema(
#                device_class=DEVICE_CLASS_NONE,
                entity_category=ENTITY_CATEGORY_DIAGNOSTIC,
            ),
            cv.Optional("heating_circuit_1_summer"): binary_sensor.binary_sensor_schema(
#                device_class=DEVICE_CLASS_NONE,
                entity_category=ENTITY_CATEGORY_DIAGNOSTIC,
            ),
            cv.Optional("heating_circuit_1_day"): binary_sensor.binary_sensor_schema(
#                device_class=DEVICE_CLASS_NONE,
                entity_category=ENTITY_CATEGORY_DIAGNOSTIC,
            ),
            cv.Optional("heating_circuit_1_no_comm_with_rc"): binary_sensor.binary_sensor_schema(
#                device_class=DEVICE_CLASS_NONE,
                entity_category=ENTITY_CATEGORY_DIAGNOSTIC,
            ),
            cv.Optional("heating_circuit_1_rc_faulty"): binary_sensor.binary_sensor_schema(
#                device_class=DEVICE_CLASS_NONE,
                entity_category=ENTITY_CATEGORY_DIAGNOSTIC,
            ),
            cv.Optional("heating_circuit_1_flow_sensor_error"): binary_sensor.binary_sensor_schema(
#                device_class=DEVICE_CLASS_NONE,
                entity_category=ENTITY_CATEGORY_DIAGNOSTIC,
            ),
            cv.Optional("heating_circuit_1_max_flow"): binary_sensor.binary_sensor_schema(
#                device_class=DEVICE_CLASS_NONE,
                entity_category=ENTITY_CATEGORY_DIAGNOSTIC,
            ),
            cv.Optional("heating_circuit_1_external_fault_input"): binary_sensor.binary_sensor_schema(
#                device_class=DEVICE_CLASS_NONE,
                entity_category=ENTITY_CATEGORY_DIAGNOSTIC,
            ),
            cv.Optional("heating_circuit_2_switch_off_optimization"): binary_sensor.binary_sensor_schema(
#                device_class=DEVICE_CLASS_NONE,
                entity_category=ENTITY_CATEGORY_DIAGNOSTIC,
            ),
            cv.Optional("heating_circuit_2_switch_on_optimization"): binary_sensor.binary_sensor_schema(
#                device_class=DEVICE_CLASS_NONE,
                entity_category=ENTITY_CATEGORY_DIAGNOSTIC,
            ),
            cv.Optional("heating_circuit_2_automatic"): binary_sensor.binary_sensor_schema(
#                device_class=DEVICE_CLASS_NONE,
                entity_category=ENTITY_CATEGORY_DIAGNOSTIC,
            ),
            cv.Optional("heating_circuit_2_ww_priority_processing"): binary_sensor.binary_sensor_schema(
                device_class=DEVICE_CLASS_RUNNING,
                entity_category=ENTITY_CATEGORY_DIAGNOSTIC,
            ),
            cv.Optional("heating_circuit_2_screed_drying"): binary_sensor.binary_sensor_schema(
                device_class=DEVICE_CLASS_RUNNING,
                entity_category=ENTITY_CATEGORY_DIAGNOSTIC,
            ),
            cv.Optional("heating_circuit_2_holiday"): binary_sensor.binary_sensor_schema(
#                device_class=DEVICE_CLASS_NONE,
                entity_category=ENTITY_CATEGORY_DIAGNOSTIC,
            ),
            cv.Optional("heating_circuit_2_antifreeze"): binary_sensor.binary_sensor_schema(
#                device_class=DEVICE_CLASS_NONE,
                entity_category=ENTITY_CATEGORY_DIAGNOSTIC,
            ),
            cv.Optional("heating_circuit_2_manually"): binary_sensor.binary_sensor_schema(
#                device_class=DEVICE_CLASS_NONE,
                entity_category=ENTITY_CATEGORY_DIAGNOSTIC,
            ),
            cv.Optional("heating_circuit_2_summer"): binary_sensor.binary_sensor_schema(
#                device_class=DEVICE_CLASS_NONE,
                entity_category=ENTITY_CATEGORY_DIAGNOSTIC,
            ),
            cv.Optional("heating_circuit_2_day"): binary_sensor.binary_sensor_schema(
#                device_class=DEVICE_CLASS_NONE,
                entity_category=ENTITY_CATEGORY_DIAGNOSTIC,
            ),
            cv.Optional("heating_circuit_2_no_comm_with_rc"): binary_sensor.binary_sensor_schema(
#                device_class=DEVICE_CLASS_NONE,
                entity_category=ENTITY_CATEGORY_DIAGNOSTIC,
            ),
            cv.Optional("heating_circuit_2_rc_faulty"): binary_sensor.binary_sensor_schema(
#                device_class=DEVICE_CLASS_NONE,
                entity_category=ENTITY_CATEGORY_DIAGNOSTIC,
            ),
            cv.Optional("heating_circuit_2_flow_sensor_error"): binary_sensor.binary_sensor_schema(
#                device_class=DEVICE_CLASS_NONE,
                entity_category=ENTITY_CATEGORY_DIAGNOSTIC,
            ),
            cv.Optional("heating_circuit_2_max_flow"): binary_sensor.binary_sensor_schema(
#                device_class=DEVICE_CLASS_NONE,
                entity_category=ENTITY_CATEGORY_DIAGNOSTIC,
            ),
            cv.Optional("heating_circuit_2_external_fault_input"): binary_sensor.binary_sensor_schema(
#                device_class=DEVICE_CLASS_NONE,
                entity_category=ENTITY_CATEGORY_DIAGNOSTIC,
            ),

            cv.Optional("ww_automatic"): binary_sensor.binary_sensor_schema(
#                device_class=DEVICE_CLASS_NONE,
                entity_category=ENTITY_CATEGORY_DIAGNOSTIC,
            ),
            cv.Optional("ww_disinfection"): binary_sensor.binary_sensor_schema(
#                device_class=DEVICE_CLASS_NONE,
                entity_category=ENTITY_CATEGORY_DIAGNOSTIC,
            ),
            cv.Optional("ww_reload"): binary_sensor.binary_sensor_schema(
#                device_class=DEVICE_CLASS_NONE,
                entity_category=ENTITY_CATEGORY_DIAGNOSTIC,
            ),
            cv.Optional("ww_holiday"): binary_sensor.binary_sensor_schema(
                device_class=DEVICE_CLASS_RUNNING,
                entity_category=ENTITY_CATEGORY_DIAGNOSTIC,
            ),
            cv.Optional("ww_error_disinfection"): binary_sensor.binary_sensor_schema(
                device_class=DEVICE_CLASS_RUNNING,
                entity_category=ENTITY_CATEGORY_DIAGNOSTIC,
            ),
            cv.Optional("ww_error_sensor"): binary_sensor.binary_sensor_schema(
                device_class=DEVICE_CLASS_PROBLEM,
                entity_category=ENTITY_CATEGORY_DIAGNOSTIC,
            ),
            cv.Optional("ww_error_stays_cold"): binary_sensor.binary_sensor_schema(
                device_class=DEVICE_CLASS_PROBLEM,
                entity_category=ENTITY_CATEGORY_DIAGNOSTIC,
            ),
            cv.Optional("ww_error_anode"): binary_sensor.binary_sensor_schema(
                device_class=DEVICE_CLASS_PROBLEM,
                entity_category=ENTITY_CATEGORY_DIAGNOSTIC,
            ),
            cv.Optional("ww_loading"): binary_sensor.binary_sensor_schema(
#                device_class=DEVICE_CLASS_NONE,
                entity_category=ENTITY_CATEGORY_DIAGNOSTIC,
            ),
            cv.Optional("ww_manually"): binary_sensor.binary_sensor_schema(
#                device_class=DEVICE_CLASS_NONE,
                entity_category=ENTITY_CATEGORY_DIAGNOSTIC,
            ),
            cv.Optional("ww_reloading"): binary_sensor.binary_sensor_schema(
#                device_class=DEVICE_CLASS_NONE,
                entity_category=ENTITY_CATEGORY_DIAGNOSTIC,
            ),
            cv.Optional("ww_switch_off_optimization"): binary_sensor.binary_sensor_schema(
#                device_class=DEVICE_CLASS_NONE,
                entity_category=ENTITY_CATEGORY_DIAGNOSTIC,
            ),
            cv.Optional("ww_switch_on_optimization"): binary_sensor.binary_sensor_schema(
#                device_class=DEVICE_CLASS_NONE,
                entity_category=ENTITY_CATEGORY_DIAGNOSTIC,
            ),
            cv.Optional("ww_day_mode"): binary_sensor.binary_sensor_schema(
#                device_class=DEVICE_CLASS_NONE,
                entity_category=ENTITY_CATEGORY_DIAGNOSTIC,
            ),
            cv.Optional("ww_post_processing"): binary_sensor.binary_sensor_schema(
#                device_class=DEVICE_CLASS_NONE,
                entity_category=ENTITY_CATEGORY_DIAGNOSTIC,
            ),
            cv.Optional("ww_priority_processing"): binary_sensor.binary_sensor_schema(
#                device_class=DEVICE_CLASS_NONE,
                entity_category=ENTITY_CATEGORY_DIAGNOSTIC,
            ),


            cv.Optional("load_pump_running"): binary_sensor.binary_sensor_schema(
                device_class=DEVICE_CLASS_RUNNING,
                entity_category=ENTITY_CATEGORY_DIAGNOSTIC,
            ),
            cv.Optional("circulation_pump_running"): binary_sensor.binary_sensor_schema(
                device_class=DEVICE_CLASS_RUNNING,
                entity_category=ENTITY_CATEGORY_DIAGNOSTIC,
            ),
            cv.Optional("solar_pump_lowering"): binary_sensor.binary_sensor_schema(
                device_class=DEVICE_CLASS_RUNNING,
                entity_category=ENTITY_CATEGORY_DIAGNOSTIC,
            ),

            #            cv.Optional("boiler_error"): binary_sensor.binary_sensor_schema(
            #                device_class=DEVICE_CLASS_PROBLEM,
            #                entity_category=ENTITY_CATEGORY_DIAGNOSTIC,
            #            ),
            cv.Optional("error_burner_malfunction"): binary_sensor.binary_sensor_schema(
                device_class=DEVICE_CLASS_PROBLEM,
                entity_category=ENTITY_CATEGORY_DIAGNOSTIC,
            ),
            cv.Optional("error_boiler_sensor"): binary_sensor.binary_sensor_schema(
                device_class=DEVICE_CLASS_PROBLEM,
                entity_category=ENTITY_CATEGORY_DIAGNOSTIC,
            ),
            cv.Optional("error_additional_sensor"): binary_sensor.binary_sensor_schema(
                device_class=DEVICE_CLASS_PROBLEM,
                entity_category=ENTITY_CATEGORY_DIAGNOSTIC,
            ),
            cv.Optional("error_boiler_stays_cold"): binary_sensor.binary_sensor_schema(
                device_class=DEVICE_CLASS_PROBLEM,
                entity_category=ENTITY_CATEGORY_DIAGNOSTIC,
            ),
            cv.Optional("error_exhaust_gas_sensor"): binary_sensor.binary_sensor_schema(
                device_class=DEVICE_CLASS_PROBLEM,
                entity_category=ENTITY_CATEGORY_DIAGNOSTIC,
            ),
            cv.Optional("error_exhaust_gas_over_limit"): binary_sensor.binary_sensor_schema(
                device_class=DEVICE_CLASS_PROBLEM,
                entity_category=ENTITY_CATEGORY_DIAGNOSTIC,
            ),
            cv.Optional("error_safety_chain_released"): binary_sensor.binary_sensor_schema(
                device_class=DEVICE_CLASS_PROBLEM,
                entity_category=ENTITY_CATEGORY_DIAGNOSTIC,
            ),
            cv.Optional("error_external_disturbance"): binary_sensor.binary_sensor_schema(
                device_class=DEVICE_CLASS_PROBLEM,
                entity_category=ENTITY_CATEGORY_DIAGNOSTIC,
            ),

            #            cv.Optional("boiler_running"): binary_sensor.binary_sensor_schema(
            #                device_class=DEVICE_CLASS_RUNNING,
            #                entity_category=ENTITY_CATEGORY_DIAGNOSTIC,
            #            ),
            cv.Optional("boiler_emission_test"): binary_sensor.binary_sensor_schema(
#                device_class=DEVICE_CLASS_NONE,
                entity_category=ENTITY_CATEGORY_DIAGNOSTIC,
            ),
            cv.Optional("boiler_1st_stage_operation"): binary_sensor.binary_sensor_schema(
#                device_class=DEVICE_CLASS_NONE,
                entity_category=ENTITY_CATEGORY_DIAGNOSTIC,
            ),
            cv.Optional("boiler_protection"): binary_sensor.binary_sensor_schema(
#                device_class=DEVICE_CLASS_NONE,
                entity_category=ENTITY_CATEGORY_DIAGNOSTIC,
            ),
            cv.Optional("boiler_under_operation"): binary_sensor.binary_sensor_schema(
#                device_class=DEVICE_CLASS_NONE,
                entity_category=ENTITY_CATEGORY_DIAGNOSTIC,
            ),
            cv.Optional("boiler_performance_free"): binary_sensor.binary_sensor_schema(
#                device_class=DEVICE_CLASS_NONE,
                entity_category=ENTITY_CATEGORY_DIAGNOSTIC,
            ),
            cv.Optional("aa"): binary_sensor.binary_sensor_schema(
#                device_class=DEVICE_CLASS_NONE,
                entity_category=ENTITY_CATEGORY_DIAGNOSTIC,
            ),
            cv.Optional("boiler_performance_high"): binary_sensor.binary_sensor_schema(
#                device_class=DEVICE_CLASS_NONE,
                entity_category=ENTITY_CATEGORY_DIAGNOSTIC,
            ),
            cv.Optional("boiler_2st_stage_operation"): binary_sensor.binary_sensor_schema(
#                device_class=DEVICE_CLASS_NONE,
                entity_category=ENTITY_CATEGORY_DIAGNOSTIC,
            ),


            cv.Optional("boiler_actuation"): binary_sensor.binary_sensor_schema(
                device_class=DEVICE_CLASS_POWER,
                entity_category=ENTITY_CATEGORY_DIAGNOSTIC,
            ),

            cv.Optional("alarm_exhaust_gas_sensor"): binary_sensor.binary_sensor_schema(
                device_class=DEVICE_CLASS_PROBLEM,
                entity_category=ENTITY_CATEGORY_DIAGNOSTIC,
            ),
            cv.Optional("alarm_boiler_flow_sensor"): binary_sensor.binary_sensor_schema(
                device_class=DEVICE_CLASS_PROBLEM,
                entity_category=ENTITY_CATEGORY_DIAGNOSTIC,
            ),
            cv.Optional("alarm_burner"): binary_sensor.binary_sensor_schema(
                device_class=DEVICE_CLASS_PROBLEM,
                entity_category=ENTITY_CATEGORY_DIAGNOSTIC,
            ),
            cv.Optional("alarm_heating_circuit_2_flow_sensor"): binary_sensor.binary_sensor_schema(
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
