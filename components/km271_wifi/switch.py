import esphome.codegen as cg
import esphome.config_validation as cv
from esphome.components import switch
from esphome.const import (
    CONF_ID
)

from . import (
    CONF_KM271_ID,
    KM271
)

CODEOWNERS = ["@the78mole", "@jensgraef"]

TYPES = [
    "warm_water_heating_auto_off"
]

km271_ns = cg.esphome_ns.namespace("KM271")

BuderusParamSwitch = km271_ns.class_("BuderusParamSwitch", switch.Switch, cg.Component)


CONFIG_SCHEMA = (
    cv.Schema(
        {
            cv.GenerateID(CONF_KM271_ID): cv.use_id(KM271),
            cv.Optional("warm_water_heating_auto_off"): switch.switch_schema(BuderusParamSwitch),
        }
    )
)


async def setup_conf(config, key, hub):
    if key in config:
        conf = config[key]

        sens = await switch.new_switch(conf)
        cg.add(getattr(hub, f"set_{key}_switch")(sens))


async def to_code(config):
    hub = await cg.get_variable(config[CONF_KM271_ID])
    for key in TYPES:
        await setup_conf(config, key, hub)
