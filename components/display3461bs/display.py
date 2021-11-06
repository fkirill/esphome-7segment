from voluptuous import schema_builder
import esphome.codegen as cg
import esphome.config_validation as cv
from esphome.components import display
from esphome import pins
from esphome.const import CONF_ID

display3461bs_ns = cg.esphome_ns.namespace("display3461bs")
Display3461BSComponent = display3461bs_ns.class_(
    "Display3461BSComponent", cg.PollingComponent
)
Display3461BSComponentRef = Display3461BSComponent.operator("ref")

CONFIG_SCHEMA = (
    cv.Schema(
        {
            cv.GenerateID(): cv.declare_id(Display3461BSComponent),
            cv.Required("pin_a"): pins.gpio_output_pin_schema,
            cv.Required("pin_b"): pins.gpio_output_pin_schema,
            cv.Required("pin_c"): pins.gpio_output_pin_schema,
            cv.Required("pin_d"): pins.gpio_output_pin_schema,
            cv.Required("pin_e"): pins.gpio_output_pin_schema,
            cv.Required("pin_f"): pins.gpio_output_pin_schema,
            cv.Required("pin_g"): pins.gpio_output_pin_schema,
            cv.Required("pin_dp"): pins.gpio_output_pin_schema,
            cv.Required("pin_d1"): pins.gpio_output_pin_schema,
            cv.Required("pin_d2"): pins.gpio_output_pin_schema,
            cv.Required("pin_d3"): pins.gpio_output_pin_schema,
            cv.Required("pin_d4"): pins.gpio_output_pin_schema,
            cv.Optional("common_anode", default = True): cv.boolean,
            cv.Optional("delay", default = "1ms"): cv.positive_time_period,
            cv.Optional("pattern1", default = False): cv.boolean,
            cv.Optional("pattern2", default = False): cv.boolean,
            cv.Optional("pattern3", default = False): cv.boolean,
            cv.Optional("pattern4", default = False): cv.boolean,
            cv.Optional("tick", default = "500ms"): cv.positive_time_period,
        }
    )
    .extend(cv.polling_component_schema("10ms"))
)

async def to_code(config):
    var = cg.new_Pvariable(config[CONF_ID])
    await cg.register_component(var, config)

    pin_a = await cg.gpio_pin_expression(config["pin_a"])
    cg.add(var.set_pin_a(pin_a))
    pin_b = await cg.gpio_pin_expression(config["pin_b"])
    cg.add(var.set_pin_b(pin_b))
    pin_c = await cg.gpio_pin_expression(config["pin_c"])
    cg.add(var.set_pin_c(pin_c))
    pin_d = await cg.gpio_pin_expression(config["pin_d"])
    cg.add(var.set_pin_d(pin_d))
    pin_e = await cg.gpio_pin_expression(config["pin_e"])
    cg.add(var.set_pin_e(pin_e))
    pin_f = await cg.gpio_pin_expression(config["pin_f"])
    cg.add(var.set_pin_f(pin_f))
    pin_g = await cg.gpio_pin_expression(config["pin_g"])
    cg.add(var.set_pin_g(pin_g))
    pin_dp = await cg.gpio_pin_expression(config["pin_dp"])
    cg.add(var.set_pin_dp(pin_dp))
    pin_d1 = await cg.gpio_pin_expression(config["pin_d1"])
    cg.add(var.set_pin_d1(pin_d1))
    pin_d2 = await cg.gpio_pin_expression(config["pin_d2"])
    cg.add(var.set_pin_d2(pin_d2))
    pin_d3 = await cg.gpio_pin_expression(config["pin_d3"])
    cg.add(var.set_pin_d3(pin_d3))
    pin_d4 = await cg.gpio_pin_expression(config["pin_d4"])
    cg.add(var.set_pin_d4(pin_d4))
    cg.add(var.set_common_anode(config["common_anode"]))
    delay = int(round(config["delay"].total_milliseconds))
    cg.add(var.set_delay(delay))
    cg.add(var.set_pattern1(config["pattern1"]))
    cg.add(var.set_pattern2(config["pattern2"]))
    cg.add(var.set_pattern3(config["pattern3"]))
    cg.add(var.set_pattern4(config["pattern4"]))
    tick = int(round(config["tick"].total_milliseconds))
    cg.add(var.set_tick(tick))
