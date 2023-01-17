"""Constants used by km271 component"""

# Selects
CONF_HC1_OPMODE = "config_heating_circuit_1_operation_mode"
CONF_HC2_OPMODE = "config_heating_circuit_2_operation_mode"
CONF_WW_OPMODE  = "config_ww_operation_mode"

# Numbers
CONF_WW_TEMP_TARGET             = "config_ww_temperature"
CONF_HC1_DESIGN_TEMP            = "config_heating_circuit_1_design_temperature"
CONF_HC1_ROOMT_TARGET_DAY       = "config_heating_circuit_1_room_target_temperature_day"
CONF_HC1_ROOMT_OFFSET           = "config_heating_circuit_1_room_temperature_offset"
CONF_HC1_FT_MAX                 = "config_heating_circuit_1_flow_temperature_max"
CONF_HC2_DESIGN_TEMP            = "config_heating_circuit_2_design_temperature"
CONF_HC2_ROOMT_TARGET_DAY       = "config_heating_circuit_2_room_target_temperature_day"
CONF_HC2_ROOMT_OFFSET           = "config_heating_circuit_2_room_temperature_offset"
CONF_HC2_FT_MAX                 = "config_heating_circuit_2_flow_temperature_max"

# Sensors
HC1_FT_TARGET       = "heating_circuit_1_flow_target_temperature"
HC1_FT_CURRENT      = "heating_circuit_1_flow_temperature"
HC1_ROOMT_TARGET    = "heating_circuit_1_room_target_temperature"
HC1_ROOMT_CURRENT   = "heating_circuit_1_room_temperature"
HC1_PUMP_POWER      = "heating_circuit_1_pump_power"
HC1_MIX_POS         = "heating_circuit_1_mixer_position"
HC1_CURVE_P10       = "heating_circuit_1_curve_p10"
HC1_CURVE_0         = "heating_circuit_1_curve_0"
HC1_CURVE_N10       = "heating_circuit_1_curve_n10"
HC2_FT_TARGET       = "heating_circuit_2_flow_target_temperature"
HC2_FT_CURRENT      = "heating_circuit_2_flow_temperature"
HC2_ROOMT_TARGET    = "heating_circuit_2_room_target_temperature"
HC2_ROOMT_CURRENT   = "heating_circuit_2_room_temperature"
HC2_PUMP_POWER      = "heating_circuit_2_pump_power"
HC2_MIX_POS         = "heating_circuit_2_mixer_position"
HC2_CURVE_P10       = "heating_circuit_2_curve_p10"
HC2_CURVE_0         = "heating_circuit_2_curve_0"
HC2_CURVE_N10       = "heating_circuit_2_curve_n10"
WW_TEMP_TARGET      = "ww_target_temperature"
WW_TEMP_CURRENT     = "ww_temperature"
BOILER_TEMP_TARGET  = "boiler_target_temperature"
BOILER_TEMP_CURRENT = "boiler_temperature"
BOILER_TEMP_TON     = "boiler_turn_on_temperature"
BOILER_TEMP_TOFF    = "boiler_turn_off_temperature"
EXHAUST_GAS_TEMP    = "exhaust_gas_temperature"
OUTDOOR_TEMP        = "outdoor_temperature"
OUTDOOR_TEMP_ATT    = "attenuated_outdoor_temperature"
BOILER_RUNTIME_1    = "boiler_runtime_1"
BOILER_RUNTIME_2    = "boiler_runtime_2"

# Switches
WW_OPMODE_AUTO_OFF = "ww_heating_auto_off"

# Binary Sensors
HC1_IS_OPT_SWOFF       = "heating_circuit_1_switch_off_optimization"
HC1_IS_OPT_SWON        = "heating_circuit_1_switch_on_optimization"
HC1_IS_AUTO            = "heating_circuit_1_automatic"
HC1_IS_PRIO_WW         = "heating_circuit_1_ww_priority_processing"
HC1_IS_SCREED_DRY      = "heating_circuit_1_screed_drying"
HC1_IS_HOLIDAY         = "heating_circuit_1_holiday"
HC1_IS_NOFREEZE        = "heating_circuit_1_antifreeze"
HC1_IS_MANUALLY        = "heating_circuit_1_manually"
HC1_IS_SUMMER          = "heating_circuit_1_summer"
HC1_IS_DAY             = "heating_circuit_1_day"
HC1_IS_RC_NOCOMM       = "heating_circuit_1_no_comm_with_rc"
HC1_IS_RC_FAULTY       = "heating_circuit_1_rc_faulty"
HC1_IS_ERR_FLOW_SENSOR = "heating_circuit_1_flow_sensor_error"
HC1_IS_MAX_FLOW        = "heating_circuit_1_max_flow"
HC1_IS_EXT_FAULT       = "heating_circuit_1_external_fault_input"

HC2_IS_OPT_SWOFF       = "heating_circuit_2_switch_off_optimization"
HC2_IS_OPT_SWON        = "heating_circuit_2_switch_on_optimization"
HC2_IS_AUTO            = "heating_circuit_2_automatic"
HC2_IS_PRIO_WW         = "heating_circuit_2_ww_priority_processing"
HC2_IS_SCREED_DRY      = "heating_circuit_2_screed_drying"
HC2_IS_HOLIDAY         = "heating_circuit_2_holiday"
HC2_IS_NOFREEZE        = "heating_circuit_2_antifreeze"
HC2_IS_MANUALLY        = "heating_circuit_2_manually"
HC2_IS_SUMMER          = "heating_circuit_2_summer"
HC2_IS_DAY             = "heating_circuit_2_day"
HC2_IS_RC_NOCOMM       = "heating_circuit_2_no_comm_with_rc"
HC2_IS_RC_FAULTY       = "heating_circuit_2_rc_faulty"
HC2_IS_ERR_FLOW_SENSOR = "heating_circuit_2_flow_sensor_error"
HC2_IS_MAX_FLOW        = "heating_circuit_2_max_flow"
HC2_IS_EXT_FAULT       = "heating_circuit_2_external_fault_input"

WW_IS_AUTO          = "ww_automatic"
WW_IS_DESINFECT     = "ww_disinfection"
WW_IS_RELOAD        = "ww_reload"
WW_IS_HOLIDAY       = "ww_holiday"
WW_IS_ERR_DESINFECT = "ww_error_disinfection"
WW_IS_ERR_SENSOR    = "ww_error_sensor"
WW_IS_ERR_STAY_COLD = "ww_error_stays_cold"
WW_IS_ERR_ANODE     = "ww_error_anode"
WW_IS_LOADING       = "ww_loading"
WW_IS_MANUALLY      = "ww_manually"
WW_IS_RELOADING     = "ww_reloading"
WW_IS_OPT_SWOFF     = "ww_switch_off_optimization"
WW_IS_OPT_SWON      = "ww_switch_on_optimization"
WW_IS_DAY           = "ww_day_mode"
WW_IS_POST_PROC     = "ww_post_processing"
WW_IS_PRIO_PROC     = "ww_priority_processing"

PUMP_LOAD_RUN  = "load_pump_running"
PUMP_CIRC_RUN  = "circulation_pump_running"
PUMP_SOLAR_LOW = "solar_pump_lowering"

ERR_BURNER_MALFUNCTION  = "error_burner_malfunction"
ERR_BOIL_SENS           = "error_boiler_sensor"
ERR_ADD_SENS            = "error_additional_sensor"
ERR_BOILD_STAY_COLD     = "error_boiler_stays_cold"
ERR_EXHAUST_GAS_SENSOR  = "error_exhaust_gas_sensor"
ERR_EXHAUST_GAS_OVLIMIT = "error_exhaust_gas_over_limit"
ERR_SAFETY_CHAIN        = "error_safety_chain_released"
ERR_EXT_DISTURBANCE     = "error_external_disturbance"

BOIL_IS_TEST_EMMISSION = "boiler_emission_test"
BOIL_IS_OP_STAGE1      = "boiler_1st_stage_operation"
BOIL_IS_PROTECTION     = "boiler_protection"
BOIL_IS_UNDER_OP       = "boiler_under_operation"
BOIL_IS_PERF_FREE      = "boiler_performance_free"
BOIL_IS_PERF_HIGH      = "boiler_performance_high"
BOIL_IS_OP_STAGE2      = "boiler_2st_stage_operation"

BOIL_IS_ACT = "boiler_actuation"

ALARM_EXHAUST_GAS_SENSOR = "alarm_exhaust_gas_sensor"
ALARM_BOILER_FLOW_SENSOR = "alarm_boiler_flow_sensor"
ALARM_BURNER             = "alarm_burner"
ALARM_HC2_FLOW_SENSOR    = "alarm_heating_circuit_2_flow_sensor"

# Text Sensors
FIRMWARE_VERSION = "firmware_version"
