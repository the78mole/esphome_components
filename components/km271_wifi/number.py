import esphome.codegen as cg
import esphome.config_validation as cv
from esphome.components import number
from esphome.const import (
    CONF_ID,
    CONF_MIN_VALUE,
    CONF_MAX_VALUE
)

from . import (
    CONF_KM271_ID,
    KM271
)

CODEOWNERS = ["@jensgraef"]

TYPES = [
    "warm_water_temperature"
]

km271_ns = cg.esphome_ns.namespace("KM271")

BuderusParamNumber = km271_ns.class_("BuderusParamNumber", number.Number, cg.Component)


CONFIG_SCHEMA = (
    cv.Schema(
        {
            cv.GenerateID(CONF_KM271_ID): cv.use_id(KM271),
            cv.Optional("warm_water_temperature"): number.NUMBER_SCHEMA.extend({
                cv.GenerateID(): cv.declare_id(BuderusParamNumber),
            })
        }
    )
)


async def setup_conf(config, key, hub):
    if key in config:
        conf = config[key]

        sens = await number.new_number(conf, min_value=30, max_value=60, step=1)
        cg.add(getattr(hub, f"set_{key}_number")(sens))


async def to_code(config):
    hub = await cg.get_variable(config[CONF_KM271_ID])
    for key in TYPES:
        await setup_conf(config, key, hub)
