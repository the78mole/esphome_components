import esphome.codegen as cg
import esphome.config_validation as cv
from esphome.components import number
from esphome.const import (
    CONF_ID,
    CONF_MIN_VALUE,
    CONF_MAX_VALUE,
    CONF_STEP
)

from . import (
    CONF_KM271_ID,
    KM271
)

CODEOWNERS = ["@jensgraef"]

TYPES = [
    "ww_temperature",
    "hc1_design_temperature",
]

km271_ns = cg.esphome_ns.namespace("KM271")

BuderusParamNumber = km271_ns.class_("BuderusParamNumber", number.Number, cg.Component)


CONFIG_SCHEMA = (
    cv.Schema(
        {
            cv.GenerateID(CONF_KM271_ID): cv.use_id(KM271),
            cv.Optional("ww_temperature"): number.NUMBER_SCHEMA.extend({
                cv.GenerateID(): cv.declare_id(BuderusParamNumber),
                cv.Optional(CONF_MAX_VALUE, default=60): cv.float_,
                cv.Optional(CONF_MIN_VALUE, default=30): cv.float_,
                cv.Optional(CONF_STEP, default=1): cv.positive_float,
            }),
            cv.Optional("hc1_design_temperature"): number.NUMBER_SCHEMA.extend({
                cv.GenerateID(): cv.declare_id(BuderusParamNumber),
                cv.Optional(CONF_MAX_VALUE, default=90): cv.float_,
                cv.Optional(CONF_MIN_VALUE, default=30): cv.float_,
                cv.Optional(CONF_STEP, default=1): cv.positive_float,
            })
        }
    )
)


async def setup_conf(config, key, hub):
    if key in config:
        conf = config[key]

        sens = await number.new_number(conf, min_value=conf[CONF_MIN_VALUE], max_value=conf[CONF_MAX_VALUE], step=conf[CONF_STEP])
        cg.add(getattr(hub, f"set_{key}_number")(sens))


async def to_code(config):
    hub = await cg.get_variable(config[CONF_KM271_ID])
    for key in TYPES:
        await setup_conf(config, key, hub)
