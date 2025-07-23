/*!
********************************************************************************************
* @file datacache.c
* @brief Data Cache C implementation generator
********************************************************************************************
* @version           interface data_cache v0.1
*
* @copyright         (C) Copyright EnduroSat
*
*                    Contents and presentations are protected world-wide.
*                    Any kind of using, copying etc. is prohibited without prior permission.
*                    All rights - incl. industrial property rights - are reserved.
*
*-------------------------------------------------------------------------------------------
* GENERATOR: org.endurosat.generators.macchiato.binders.Gen_DC v0.9
*-------------------------------------------------------------------------------------------
* !!! Please note that this code is fully GENERATED and shall not be manually modified as
* all changes will be overwritten !!!
********************************************************************************************
*/

#include <stdio.h>
#include <string.h>
#include <limits.h>
#include "datacache.h"
#include "datacache_cfg.h"

/**********************************************************************
 *
 *  Internal macros and defines
 *
 **********************************************************************/
#ifdef DC_DATA_ACCESS_SYNC_ENABLED
#define DC_DATA_LOCK(data_id)   do { dc_cfg_lock_acquire(dc_data_rt[data_id].data_lock) } while (0U);
#define DC_DATA_UNLOCK(data_id) do { dc_cfg_lock_release(dc_data_rt[data_id].data_lock) } while (0U);
#else
#define DC_DATA_LOCK(data_id)   while (0U);
#define DC_DATA_UNLOCK(data_id) while (0U);
#endif

// special bool values are used here in order to increase the Hamming distance between the discrete values
#define FALSE   (0x00U)
#define TRUE    (0xFFU)

/**********************************************************************
 *
 *  Internal data types
 *
 **********************************************************************/

/** \struct dc_cfg_entry_immut_t
 *  \brief DC shall keep a static configuration for each data entry in FLASH ROM represented by the following data type:
*/
typedef struct
{
    const uint16_t data_id;       /**< internal data attribute ID as specified in the FIDL file */
    void * const p_data_raw;      /**< a pointer to the entry data buffer */
    const uint32_t data_size;     /**< in bytes */
    const uint32_t data_timeout;  /**< time before data status gets set to DC_DATA_STATUS_TOUT if no updates received */
} dc_cfg_entry_immut_t;

/** \struct dc_data_rtctx_t
 *  \brief DC shall keep runtime data context for each data entry in RAM represented by the following data type:
*/
typedef struct
{
    dc_data_input_t last_input_type;      /**< last input type used for this data */
    dc_data_status_t last_data_status;    /**< last DC-calculated data status */
    uint32_t last_update_tstamp;          /**< timestamp of last data update  */
#if defined(DC_DATA_ACCESS_SYNC_ENABLED)
    dc_cfg_lock_t data_lock;              /**< mutex or other handle to support data access synchronization */
#endif
} dc_data_rtctx_t;

typedef struct
{
    DATA_CACHE_OBC_0_t obc_0_data;
    DATA_CACHE_ADCS_0_t adcs_0_data;
    DATA_CACHE_ADCS_1_t adcs_1_data;
    DATA_CACHE_ADCS_2_t adcs_2_data;
    DATA_CACHE_EPS_0_t eps_0_data;
    DATA_CACHE_SSP_0_Telemetry_t ssp_0_data;
    DATA_CACHE_SSP_1_Telemetry_t ssp_1_data;
    DATA_CACHE_SSP_2_Telemetry_t ssp_2_data;
    DATA_CACHE_SSP_3_Telemetry_t ssp_3_data;
    DATA_CACHE_AOCS_CNTRL_TLM_t aocs_cntrl_tlm_data;
    DATA_CACHE_AOCS_CNTRL_SYS_STATE_t aocs_cntrl_sys_state_data;
    DATA_CACHE_AOCS_CNTRL_REF_PARAMS_t aocs_cntrl_ref_params_data;
    DATA_CACHE_SENSOR_GYRO_SENSOR_FRAME_t sensor_gyro_sensor_frame_data;
    DATA_CACHE_SENSOR_GYRO_BODY_FRAME_t sensor_gyro_body_frame_data;
    DATA_CACHE_SENSOR_MAG_PRIMARY_SENSOR_FRAME_t sensor_mag_primary_sensor_frame_data;
    DATA_CACHE_SENSOR_MAG_PRIMARY_BODY_FRAME_t sensor_mag_primary_body_frame_data;
    DATA_CACHE_SENSOR_MAG_SECONDARY_SENSOR_FRAME_t sensor_mag_secondary_sensor_frame_data;
    DATA_CACHE_SENSOR_MAG_SECONDARY_BODY_FRAME_t sensor_mag_secondary_body_frame_data;
    DATA_CACHE_SENSOR_COARSE_SUN_SENSOR_FRAME_t sensor_coarse_sun_sensor_frame_data;
    DATA_CACHE_SENSOR_COARSE_SUN_BODY_FRAME_t sensor_coarse_sun_body_frame_data;
    DATA_CACHE_SENSOR_PANEL_TEMP_SENSOR_FRAME_t sensor_panel_temp_sensor_frame_data;
    DATA_CACHE_SENSOR_PANEL_TEMP_BODY_FRAME_t sensor_panel_temp_body_frame_data;
    DATA_CACHE_SENSOR_GYRO_TEMP_SENSOR_FRAME_t sensor_gyro_temp_sensor_frame_data;
    DATA_CACHE_SENSOR_GYRO_TEMP_BODY_FRAME_t sensor_gyro_temp_body_frame_data;
    DATA_CACHE_ACTUATOR_MTQ_VALUES_t actuator_mtq_values_data;
    DATA_CACHE_ACTUATOR_TORQUE_VALUES_t actuator_torque_values_data;
    DATA_CACHE_ADCS_3_t adcs_3_data;
    DATA_CACHE_ADCS_4_t adcs_4_data;
    DATA_CACHE_EPS_9_t eps_9_data;
    DATA_CACHE_EPS_10_t eps_10_data;
    DATA_CACHE_EPS_14_t eps_14_data;
    DATA_CACHE_CUBEADCS_GEN2_OP_STATUS_COMMON_t cubeadcs_gen2_op_status_common_data;
    DATA_CACHE_CUBEADCS_GEN2_OP_STATUS_APP_t cubeadcs_gen2_op_status_app_data;
    DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_166_t cubeadcs_gen2_tlm_frame_166_data;
    DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_167_t cubeadcs_gen2_tlm_frame_167_data;
    DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_168_t cubeadcs_gen2_tlm_frame_168_data;
    DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_169_t cubeadcs_gen2_tlm_frame_169_data;
    DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_170_t cubeadcs_gen2_tlm_frame_170_data;
    DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_171_t cubeadcs_gen2_tlm_frame_171_data;
    DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_172_t cubeadcs_gen2_tlm_frame_172_data;
    DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_173_t cubeadcs_gen2_tlm_frame_173_data;
    DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_174_t cubeadcs_gen2_tlm_frame_174_data;
    DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_175_t cubeadcs_gen2_tlm_frame_175_data;
    DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_176_t cubeadcs_gen2_tlm_frame_176_data;
    DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_177_t cubeadcs_gen2_tlm_frame_177_data;
    DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_178_t cubeadcs_gen2_tlm_frame_178_data;
    DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_179_t cubeadcs_gen2_tlm_frame_179_data;
    DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_180_t cubeadcs_gen2_tlm_frame_180_data;
    DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_203_t cubeadcs_gen2_tlm_frame_203_data;
    DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_204_t cubeadcs_gen2_tlm_frame_204_data;
    DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_205_t cubeadcs_gen2_tlm_frame_205_data;
    DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_206_t cubeadcs_gen2_tlm_frame_206_data;
    DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_207_t cubeadcs_gen2_tlm_frame_207_data;
    DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_208_1_t cubeadcs_gen2_tlm_frame_208_1_data;
    DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_208_2_t cubeadcs_gen2_tlm_frame_208_2_data;
    DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_209_t cubeadcs_gen2_tlm_frame_209_data;
    DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_210_t cubeadcs_gen2_tlm_frame_210_data;
    DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_211_t cubeadcs_gen2_tlm_frame_211_data;
    DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_212_t cubeadcs_gen2_tlm_frame_212_data;
    DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_213_t cubeadcs_gen2_tlm_frame_213_data;
    DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_214_t cubeadcs_gen2_tlm_frame_214_data;
    DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_216_t cubeadcs_gen2_tlm_frame_216_data;
    DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_217_t cubeadcs_gen2_tlm_frame_217_data;
    DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_218_t cubeadcs_gen2_tlm_frame_218_data;
    DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_225_t cubeadcs_gen2_tlm_frame_225_data;
    DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_226_t cubeadcs_gen2_tlm_frame_226_data;
    DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_165_t cubeadcs_gen2_tlm_frame_165_data;
    DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_221_t cubeadcs_gen2_tlm_frame_221_data;
    DATA_CACHE_GNSS_TIME_t gnss_time_data;
    DATA_CACHE_GNSS_BESTXYZ_t gnss_bestxyz_data;
    DATA_CACHE_SAT_STATE_VECTOR_FROM_PROPAGATOR_t sat_state_vector_from_propagator_data;
    DATA_CACHE_SAT_MAG_FIELD_VECTOR_FROM_MODEL_t sat_mag_field_vector_from_model_data;
    DATA_CACHE_SAT_MAG_FIELD_VECTOR_FROM_SENSOR_t sat_mag_field_vector_from_sensor_data;
    DATA_CACHE_FDIR_EPS_I_CMD_EXEC_STATUS_t fdir_eps_i_cmd_exec_status_data;
    DATA_CACHE_FDIR_EPS_II_PDM_CMD_EXEC_STATUS_t fdir_eps_ii_pdm_cmd_exec_status_data;
    DATA_CACHE_FDIR_CUBEADCS_CMD_EXEC_STATUS_t fdir_cubeadcs_cmd_exec_status_data;
    DATA_CACHE_FDIR_CUBEADCS_GEN2_CMD_EXEC_STATUS_t fdir_cubeadcs_gen2_cmd_exec_status_data;
    DATA_CACHE_FDIR_CUBEADCS_GEN2_EVENTS_t fdir_cubeadcs_gen2_events_data;
    DATA_CACHE_FDIR_S_BAND_TMTC_CMD_EXEC_STATUS_t fdir_s_band_tmtc_cmd_exec_status_data;
    DATA_CACHE_FDIR_UHF_CMD_EXEC_STATUS_t fdir_uhf_cmd_exec_status_data;
    DATA_CACHE_FDIR_GNSS_CMD_EXEC_STATUS_t fdir_gnss_cmd_exec_status_data;
    DATA_CACHE_FDIR_SDR_CMD_EXEC_STATUS_t fdir_sdr_cmd_exec_status_data;
    DATA_CACHE_FDIR_S_X_BAND_CMD_EXEC_STATUS_t fdir_s_x_band_cmd_exec_status_data;
    DATA_CACHE_FDIR_THRUSTER_CMD_EXEC_STATUS_t fdir_thruster_cmd_exec_status_data;
    DATA_CACHE_XBandFeTelemetry_t xband_fe_data;
    DATA_CACHE_EpsOverallBatteryInfoType_t epsoverallbatteryinfo_data;
    DATA_CACHE_PPS_Telemetry_t pps_telemetry_data;
    DATA_CACHE_FDIR_EPS_III_PDM_CMD_EXEC_STATUS_t fdir_eps_iii_pdm_cmd_exec_status_data;
    DATA_CACHE_Eps2Inst0BatteryInfoType_t eps2_bp_inst0_bp_info_data;
    DATA_CACHE_Eps2Inst0DeviceHealthInfoType_t eps2_bp_inst0_device_health_info_data;
    DATA_CACHE_Eps2Inst0InaSensors1Type_t eps2_bp_inst0_ina_sensor1_data;
    DATA_CACHE_Eps2Inst0InaSensors2Type_t eps2_bp_inst0_ina_sensor2_data;
    DATA_CACHE_Eps2Inst0BalancerInfoType_t eps2_bp_inst0_balancer_info_data;
    DATA_CACHE_Eps2Inst0BalancerStatusType_t eps2_bp_inst0_balancer_status_data;
    DATA_CACHE_Eps2Inst0BalancerCellsInfoType_t eps2_bp_inst0_balancer_cells_info_data;
    DATA_CACHE_Eps2Inst0ChargerXpType_t eps2_bp_inst0_charger_xp_data;
    DATA_CACHE_Eps2Inst0ChargerXrType_t eps2_bp_inst0_charger_xr_data;
    DATA_CACHE_Eps2Inst0ChargerYpType_t eps2_bp_inst0_charger_yp_data;
    DATA_CACHE_Eps2Inst0ChargerYrType_t eps2_bp_inst0_charger_yr_data;
    DATA_CACHE_Eps2Inst0ChargerZpType_t eps2_bp_inst0_charger_zp_data;
    DATA_CACHE_Eps2Inst0ChargerZrType_t eps2_bp_inst0_charger_zr_data;
    DATA_CACHE_Eps2Inst0_FDIR_CMD_EXEC_STATUS_type_t fdir_eps_ii_bp_inst0_cmd_exec_status_data;
    DATA_CACHE_Eps3Inst0_UpTimeInSecondsType_t eps3_bp_inst0_uptime_in_seconds;
    DATA_CACHE_Eps3Inst0CommonMeasurementType_t eps3_bp_inst0common;
    DATA_CACHE_Eps3Inst0HIBModeStatusType_t eps3_bp_inst0hib_mode_status;
    DATA_CACHE_Eps3Inst0MeasurementsType_t eps3_bp_inst0measurements;
    DATA_CACHE_Eps3Inst0DischargeStateType_t eps3_bp_inst0discharging_state;
    DATA_CACHE_Eps3Inst0ChargeOnStatusType_t eps3_bp_inst0charge_status;
    DATA_CACHE_Eps3Inst0BalancersStatusType_t eps3_bp_inst0balancers_status;
    DATA_CACHE_Eps3Inst0BatteryCellsStatusType_t eps3_bp_inst0battery_cells_status;
    DATA_CACHE_Eps3Inst0HeatersStatusType_t eps3_bp_inst0heaters_status;
    DATA_CACHE_Eps3Inst0_FDIR_CMD_EXEC_STATUS_type_t eps3_bp_inst0_cmd_exec_status_data;
    DATA_CACHE_VoltAmps_t dumb_data;
    DATA_CACHE_VoltAllAmps_t dumb_data1;
    DATA_CACHE_MpptState_str_t dumb_data3;
    DATA_CACHE_ReadEnDftStatus_t dumb_data4;
    DATA_CACHE_OnOffStatus_t dumb_data5;
    DATA_CACHE_ReadLvlState_t dumb_data6;
    DATA_CACHE_Eps3_PDM_A_Inst0_UpTimeInSecondsType_t eps3_pdm_a_inst0_uptime_in_seconds;
    DATA_CACHE_Eps3_PDM_A_Inst0_CommonMesurementsType_t eps3_pdm_a_inst0_common;
    DATA_CACHE_Eps3_PDM_A_Inst0_HibModeType_t eps3_pdm_a_inst0_hib_mode;
    DATA_CACHE_Eps3_PDM_A_Inst0_OutputsStatusType_t eps3_pdm_a_inst0_general_outputs;
    DATA_CACHE_Eps3_PDM_A_Inst0_FaultsStatusType_t eps3_pdm_a_inst0_general_faults;
    DATA_CACHE_Eps3_PDM_A_Inst0_VoltAmpsMeasurementsType_t eps3_pdm_a_inst0_all_measurements;
    DATA_CACHE_Eps3_PDM_A_Inst0_FDIR_CMD_EXEC_STATUS_type_t eps3_pdm_a_inst0_cmd_exec_status_data;
    DATA_CACHE_Eps3_PDM_B_Inst0_FDIR_CMD_EXEC_STATUS_type_t eps3_pdm_b_inst0_cmd_exec_status_data;
    DATA_CACHE_Eps3_PDM_B_Inst0_UpTimeInSecondsType_t eps3_pdm_b_inst0_uptime_in_seconds;
    DATA_CACHE_Eps3_PDM_B_Inst0_CommonMeasurementType_t eps3_pdm_b_inst0_common;
    DATA_CACHE_Eps3_PDM_B_Inst0_hib_mode_Type_t eps3_pdm_b_inst0_hib_mode;
    DATA_CACHE_Eps3_PDM_B_Inst0_OutputsStatus_type_t eps3_pdm_b_inst0_general_outputs;
    DATA_CACHE_Eps3_PDM_B_Inst0_ChannelFlagState_type_t eps3_pdm_b_inst0_channel_flag_state;
    DATA_CACHE_Eps3_PDM_B_Inst0_Temps_type_t eps3_pdm_b_inst0_temperature;
    DATA_CACHE_Eps3_PDM_B_Inst0_VoltAmpsMeasurements_type_t eps3_pdm_b_inst0_all_measurements;
    DATA_CACHE_Eps3_EXPANDER_Inst0_FDIR_CMD_EXEC_STATUS_type_t eps3_expander_inst0_cmd_exec_status_data;
    DATA_CACHE_Eps3_EXPANDER_Inst0_UpTimeInSecondsType_t eps3_expander_inst0_uptime_in_seconds;
    DATA_CACHE_Eps3_EXPANDER_Inst0_CommonMeasurementType_t eps3_expander_inst0_common;
    DATA_CACHE_Eps3_EXPANDER_Inst0_DigitalOutputsType_t eps3_expander_inst0_outputs;
    DATA_CACHE_Eps3_EXPANDER_Inst0_GeneralInputType_t eps3_expander_inst0_general_inputs;
    DATA_CACHE_Eps3_EXPANDER_Inst0_FeedbackType_t eps3_expander_inst0_feedbacks;
    DATA_CACHE_Eps3_EXPANDER_Inst0_CurrentLimitersType_t eps3_expander_inst0_volt_amp_measurements;
    DATA_CACHE_Eps3_INPUT_STAGE_Inst0_UpTimeInSecondsType_t eps3_input_stage_inst0_uptime_in_seconds;
    DATA_CACHE_Eps3_INPUT_STAGE_Inst0CommonMeasurementType_t eps3_input_stage_inst0common;
    DATA_CACHE_Eps3_INPUT_STAGE_Inst0hib_mode_status_type_t eps3_input_stage_inst0hib_mode_status;
    DATA_CACHE_Eps3_INPUT_STAGE_Inst0selflock_on_type_t eps3_input_stage_inst0selflock_on;
    DATA_CACHE_Eps3_INPUT_STAGE_Inst0Sp1InputDataType_t eps3_input_stage_inst0sp1;
    DATA_CACHE_Eps3_INPUT_STAGE_Inst0Sp2InputDataType_t eps3_input_stage_inst0sp2;
    DATA_CACHE_Eps3_INPUT_STAGE_Inst0Sp3InputDataType_t eps3_input_stage_inst0sp3;
    DATA_CACHE_Eps3_INPUT_STAGE_Inst0SystemBusType_t eps3_input_stage_inst0system_bus;
    DATA_CACHE_Eps3_INPUT_STAGE_Inst0Bus7v5Type_t eps3_input_stage_inst0bus_7v5;
    DATA_CACHE_Eps3_INPUT_STAGE_Inst0bus_7v5_power_good_type_t eps3_input_stage_inst0bus_7v5_power_good;
    DATA_CACHE_Eps3_INPUT_STAGE_Inst0undervoltage_7V5_type_t eps3_input_stage_inst0undervoltage_7v5;
    DATA_CACHE_Eps3_INPUT_STAGE_Inst0Bbus3v3Type_t eps3_input_stage_inst0bus_3v3;
    DATA_CACHE_Eps3_INPUT_STAGE_Inst0undervoltage_3V3_type_t eps3_input_stage_inst0undervoltage_3v3;
    DATA_CACHE_Eps3_INPUT_STAGE_Inst0_FDIR_CMD_EXEC_STATUS_type_t eps3_input_stage_inst0_cmd_exec_status_data;
    DATA_CACHE_CubeMag_Telemetry_t magdata;
    DATA_CACHE_CubeWheel1_Telemetry_t wheeldata1;
    DATA_CACHE_CubeWheel2_Telemetry_t wheeldata2;
    DATA_CACHE_FSS1_Data_type_t fss1_data;
    DATA_CACHE_FSS2_Data_type_t fss2_data;
    DATA_CACHE_FSS3_Data_type_t fss3_data;
    DATA_CACHE_FSS4_Data_type_t fss4_data;
    DATA_CACHE_FSS5_Data_type_t fss5_data;
    DATA_CACHE_ADCS_FSS_t adcs_fss_data;
    DATA_CACHE_ADCS_MAG_t adcs_mag_data;
    DATA_CACHE_ADCS_IMU_t adcs_imu_data;
    DATA_CACHE_ADCS_RW_t adcs_rw_data;
    DATA_CACHE_ADCS_MTQ_t adcs_mtq_data;
    DATA_CACHE_SBpModeChangeInfo_t eps2_bp_inst0_sbpmodechange_data;
    DATA_CACHE_Eps2Inst0_BpModeSmRollingTrace_type_t eps2_bp_bpmodesmrollingtrace_data;
    DATA_CACHE_EPSII_PDM_SBSEDE_ConopsMode_t eps2_pdm_sbsede_conopsmode_data;
    DATA_CACHE_EPSII_PDM_1_SBSED_Bitmask_t_t eps2_pdm_sbsed_bitmask_data;
    DATA_CACHE_EPSII_PDM_1_SBasicSettings_t eps2_pdm_sbasicsettings_data;
    DATA_CACHE_EPSII_PDM_1_SetBasicSettings_t eps2_pdm_setbasicsettings_data;
    DATA_CACHE_EPSII_PDM_1_SBS_GetError_t eps2_pdm_sbs_geterror_data;
    DATA_CACHE_Eps2Inst0_SBasicSettings_type_t eps2inst0_pdm_sbasicsettings_data;
    DATA_CACHE_VN100_Data_type_t vn100_data;
    DATA_CACHE_MPU6050_1_Data_type_t mpu6050_1_data;
    DATA_CACHE_MPU6050_2_Data_type_t mpu6050_2_data;
    DATA_CACHE_MTQ_ALL_Command_Data_type_t mtq_all_cmd_data;
    DATA_CACHE_EPSII_BP_1_SDiagErrCounter2_t eps2inst0_bp_sdiagerrcounter2_data;
    DATA_CACHE_Eps2Inst0__GetMainAppErrCounters2ype_t eps2inst0_bp_getmainapperrcounters2_data;
    DATA_CACHE_INA_Data_type_t ina_data;
    DATA_CACHE_ANG_Data_type_t ang_data;
    DATA_CACHE_CAMERA_MODE_Data_type_t camera_mode_data;
    DATA_CACHE_ADCS_mode_type_t adcs_mode;
    DATA_CACHE_ADCS_flag_alg_type_t adcs_flag_alg;
    DATA_CACHE_ADCS_result_type_t adcs_result;
    DATA_CACHE_ADCS_HW_type_t adcs_hw;
    DATA_CACHE_CubeSpace_Telecommand_Flag_t tc_flag;
} PACKED_STRUCT datacache_t;

/**********************************************************************
 *
 *  Static variables
 *
 **********************************************************************/

static uint8_t dc_initialized = FALSE;

/** \brief Main DataCache instance in RAM */
static datacache_t dc_instance;

/** \brief Immutable Data Cache configuration */
static dc_data_rtctx_t dc_data_rt[DC_DID_MAX];

static const dc_cfg_entry_immut_t dc_data_cfg[DC_DID_MAX] =
{
    // obc_0_data
    {
        .data_id = DC_ATTR_ID_OBC_0_DATA,
        .p_data_raw = &dc_instance.obc_0_data,
        .data_size = sizeof(dc_instance.obc_0_data),
        .data_timeout = 5000U
    },
    // adcs_0_data
    {
        .data_id = DC_ATTR_ID_ADCS_0_DATA,
        .p_data_raw = &dc_instance.adcs_0_data,
        .data_size = sizeof(dc_instance.adcs_0_data),
        .data_timeout = 5000U
    },
    // adcs_1_data
    {
        .data_id = DC_ATTR_ID_ADCS_1_DATA,
        .p_data_raw = &dc_instance.adcs_1_data,
        .data_size = sizeof(dc_instance.adcs_1_data),
        .data_timeout = 5000U
    },
    // adcs_2_data
    {
        .data_id = DC_ATTR_ID_ADCS_2_DATA,
        .p_data_raw = &dc_instance.adcs_2_data,
        .data_size = sizeof(dc_instance.adcs_2_data),
        .data_timeout = 5000U
    },
    // eps_0_data
    {
        .data_id = DC_ATTR_ID_EPS_0_DATA,
        .p_data_raw = &dc_instance.eps_0_data,
        .data_size = sizeof(dc_instance.eps_0_data),
        .data_timeout = 5000U
    },
    // ssp_0_data
    {
        .data_id = DC_ATTR_ID_SSP_0_DATA,
        .p_data_raw = &dc_instance.ssp_0_data,
        .data_size = sizeof(dc_instance.ssp_0_data),
        .data_timeout = 5000U
    },
    // ssp_1_data
    {
        .data_id = DC_ATTR_ID_SSP_1_DATA,
        .p_data_raw = &dc_instance.ssp_1_data,
        .data_size = sizeof(dc_instance.ssp_1_data),
        .data_timeout = 5000U
    },
    // ssp_2_data
    {
        .data_id = DC_ATTR_ID_SSP_2_DATA,
        .p_data_raw = &dc_instance.ssp_2_data,
        .data_size = sizeof(dc_instance.ssp_2_data),
        .data_timeout = 5000U
    },
    // ssp_3_data
    {
        .data_id = DC_ATTR_ID_SSP_3_DATA,
        .p_data_raw = &dc_instance.ssp_3_data,
        .data_size = sizeof(dc_instance.ssp_3_data),
        .data_timeout = 5000U
    },
    // aocs_cntrl_tlm_data
    {
        .data_id = DC_ATTR_ID_AOCS_CNTRL_TLM_DATA,
        .p_data_raw = &dc_instance.aocs_cntrl_tlm_data,
        .data_size = sizeof(dc_instance.aocs_cntrl_tlm_data),
        .data_timeout = 5000U
    },
    // aocs_cntrl_sys_state_data
    {
        .data_id = DC_ATTR_ID_AOCS_CNTRL_SYS_STATE_DATA,
        .p_data_raw = &dc_instance.aocs_cntrl_sys_state_data,
        .data_size = sizeof(dc_instance.aocs_cntrl_sys_state_data),
        .data_timeout = 5000U
    },
    // aocs_cntrl_ref_params_data
    {
        .data_id = DC_ATTR_ID_AOCS_CNTRL_REF_PARAMS_DATA,
        .p_data_raw = &dc_instance.aocs_cntrl_ref_params_data,
        .data_size = sizeof(dc_instance.aocs_cntrl_ref_params_data),
        .data_timeout = 5000U
    },
    // sensor_gyro_sensor_frame_data
    {
        .data_id = DC_ATTR_ID_SENSOR_GYRO_SENSOR_FRAME_DATA,
        .p_data_raw = &dc_instance.sensor_gyro_sensor_frame_data,
        .data_size = sizeof(dc_instance.sensor_gyro_sensor_frame_data),
        .data_timeout = 5000U
    },
    // sensor_gyro_body_frame_data
    {
        .data_id = DC_ATTR_ID_SENSOR_GYRO_BODY_FRAME_DATA,
        .p_data_raw = &dc_instance.sensor_gyro_body_frame_data,
        .data_size = sizeof(dc_instance.sensor_gyro_body_frame_data),
        .data_timeout = 5000U
    },
    // sensor_mag_primary_sensor_frame_data
    {
        .data_id = DC_ATTR_ID_SENSOR_MAG_PRIMARY_SENSOR_FRAME_DATA,
        .p_data_raw = &dc_instance.sensor_mag_primary_sensor_frame_data,
        .data_size = sizeof(dc_instance.sensor_mag_primary_sensor_frame_data),
        .data_timeout = 5000U
    },
    // sensor_mag_primary_body_frame_data
    {
        .data_id = DC_ATTR_ID_SENSOR_MAG_PRIMARY_BODY_FRAME_DATA,
        .p_data_raw = &dc_instance.sensor_mag_primary_body_frame_data,
        .data_size = sizeof(dc_instance.sensor_mag_primary_body_frame_data),
        .data_timeout = 5000U
    },
    // sensor_mag_secondary_sensor_frame_data
    {
        .data_id = DC_ATTR_ID_SENSOR_MAG_SECONDARY_SENSOR_FRAME_DATA,
        .p_data_raw = &dc_instance.sensor_mag_secondary_sensor_frame_data,
        .data_size = sizeof(dc_instance.sensor_mag_secondary_sensor_frame_data),
        .data_timeout = 5000U
    },
    // sensor_mag_secondary_body_frame_data
    {
        .data_id = DC_ATTR_ID_SENSOR_MAG_SECONDARY_BODY_FRAME_DATA,
        .p_data_raw = &dc_instance.sensor_mag_secondary_body_frame_data,
        .data_size = sizeof(dc_instance.sensor_mag_secondary_body_frame_data),
        .data_timeout = 5000U
    },
    // sensor_coarse_sun_sensor_frame_data
    {
        .data_id = DC_ATTR_ID_SENSOR_COARSE_SUN_SENSOR_FRAME_DATA,
        .p_data_raw = &dc_instance.sensor_coarse_sun_sensor_frame_data,
        .data_size = sizeof(dc_instance.sensor_coarse_sun_sensor_frame_data),
        .data_timeout = 5000U
    },
    // sensor_coarse_sun_body_frame_data
    {
        .data_id = DC_ATTR_ID_SENSOR_COARSE_SUN_BODY_FRAME_DATA,
        .p_data_raw = &dc_instance.sensor_coarse_sun_body_frame_data,
        .data_size = sizeof(dc_instance.sensor_coarse_sun_body_frame_data),
        .data_timeout = 5000U
    },
    // sensor_panel_temp_sensor_frame_data
    {
        .data_id = DC_ATTR_ID_SENSOR_PANEL_TEMP_SENSOR_FRAME_DATA,
        .p_data_raw = &dc_instance.sensor_panel_temp_sensor_frame_data,
        .data_size = sizeof(dc_instance.sensor_panel_temp_sensor_frame_data),
        .data_timeout = 5000U
    },
    // sensor_panel_temp_body_frame_data
    {
        .data_id = DC_ATTR_ID_SENSOR_PANEL_TEMP_BODY_FRAME_DATA,
        .p_data_raw = &dc_instance.sensor_panel_temp_body_frame_data,
        .data_size = sizeof(dc_instance.sensor_panel_temp_body_frame_data),
        .data_timeout = 5000U
    },
    // sensor_gyro_temp_sensor_frame_data
    {
        .data_id = DC_ATTR_ID_SENSOR_GYRO_TEMP_SENSOR_FRAME_DATA,
        .p_data_raw = &dc_instance.sensor_gyro_temp_sensor_frame_data,
        .data_size = sizeof(dc_instance.sensor_gyro_temp_sensor_frame_data),
        .data_timeout = 5000U
    },
    // sensor_gyro_temp_body_frame_data
    {
        .data_id = DC_ATTR_ID_SENSOR_GYRO_TEMP_BODY_FRAME_DATA,
        .p_data_raw = &dc_instance.sensor_gyro_temp_body_frame_data,
        .data_size = sizeof(dc_instance.sensor_gyro_temp_body_frame_data),
        .data_timeout = 5000U
    },
    // actuator_mtq_values_data
    {
        .data_id = DC_ATTR_ID_ACTUATOR_MTQ_VALUES_DATA,
        .p_data_raw = &dc_instance.actuator_mtq_values_data,
        .data_size = sizeof(dc_instance.actuator_mtq_values_data),
        .data_timeout = 5000U
    },
    // actuator_torque_values_data
    {
        .data_id = DC_ATTR_ID_ACTUATOR_TORQUE_VALUES_DATA,
        .p_data_raw = &dc_instance.actuator_torque_values_data,
        .data_size = sizeof(dc_instance.actuator_torque_values_data),
        .data_timeout = 5000U
    },
    // adcs_3_data
    {
        .data_id = DC_ATTR_ID_ADCS_3_DATA,
        .p_data_raw = &dc_instance.adcs_3_data,
        .data_size = sizeof(dc_instance.adcs_3_data),
        .data_timeout = 5000U
    },
    // adcs_4_data
    {
        .data_id = DC_ATTR_ID_ADCS_4_DATA,
        .p_data_raw = &dc_instance.adcs_4_data,
        .data_size = sizeof(dc_instance.adcs_4_data),
        .data_timeout = 5000U
    },
    // eps_9_data
    {
        .data_id = DC_ATTR_ID_EPS_9_DATA,
        .p_data_raw = &dc_instance.eps_9_data,
        .data_size = sizeof(dc_instance.eps_9_data),
        .data_timeout = 30000U
    },
    // eps_10_data
    {
        .data_id = DC_ATTR_ID_EPS_10_DATA,
        .p_data_raw = &dc_instance.eps_10_data,
        .data_size = sizeof(dc_instance.eps_10_data),
        .data_timeout = 30000U
    },
    // eps_14_data
    {
        .data_id = DC_ATTR_ID_EPS_14_DATA,
        .p_data_raw = &dc_instance.eps_14_data,
        .data_size = sizeof(dc_instance.eps_14_data),
        .data_timeout = 30000U
    },
    // cubeadcs_gen2_op_status_common_data
    {
        .data_id = DC_ATTR_ID_CUBEADCS_GEN2_OP_STATUS_COMMON_DATA,
        .p_data_raw = &dc_instance.cubeadcs_gen2_op_status_common_data,
        .data_size = sizeof(dc_instance.cubeadcs_gen2_op_status_common_data),
        .data_timeout = 10000U
    },
    // cubeadcs_gen2_op_status_app_data
    {
        .data_id = DC_ATTR_ID_CUBEADCS_GEN2_OP_STATUS_APP_DATA,
        .p_data_raw = &dc_instance.cubeadcs_gen2_op_status_app_data,
        .data_size = sizeof(dc_instance.cubeadcs_gen2_op_status_app_data),
        .data_timeout = 10000U
    },
    // cubeadcs_gen2_tlm_frame_166_data
    {
        .data_id = DC_ATTR_ID_CUBEADCS_GEN2_TLM_FRAME_166_DATA,
        .p_data_raw = &dc_instance.cubeadcs_gen2_tlm_frame_166_data,
        .data_size = sizeof(dc_instance.cubeadcs_gen2_tlm_frame_166_data),
        .data_timeout = 5000U
    },
    // cubeadcs_gen2_tlm_frame_167_data
    {
        .data_id = DC_ATTR_ID_CUBEADCS_GEN2_TLM_FRAME_167_DATA,
        .p_data_raw = &dc_instance.cubeadcs_gen2_tlm_frame_167_data,
        .data_size = sizeof(dc_instance.cubeadcs_gen2_tlm_frame_167_data),
        .data_timeout = 5000U
    },
    // cubeadcs_gen2_tlm_frame_168_data
    {
        .data_id = DC_ATTR_ID_CUBEADCS_GEN2_TLM_FRAME_168_DATA,
        .p_data_raw = &dc_instance.cubeadcs_gen2_tlm_frame_168_data,
        .data_size = sizeof(dc_instance.cubeadcs_gen2_tlm_frame_168_data),
        .data_timeout = 5000U
    },
    // cubeadcs_gen2_tlm_frame_169_data
    {
        .data_id = DC_ATTR_ID_CUBEADCS_GEN2_TLM_FRAME_169_DATA,
        .p_data_raw = &dc_instance.cubeadcs_gen2_tlm_frame_169_data,
        .data_size = sizeof(dc_instance.cubeadcs_gen2_tlm_frame_169_data),
        .data_timeout = 5000U
    },
    // cubeadcs_gen2_tlm_frame_170_data
    {
        .data_id = DC_ATTR_ID_CUBEADCS_GEN2_TLM_FRAME_170_DATA,
        .p_data_raw = &dc_instance.cubeadcs_gen2_tlm_frame_170_data,
        .data_size = sizeof(dc_instance.cubeadcs_gen2_tlm_frame_170_data),
        .data_timeout = 5000U
    },
    // cubeadcs_gen2_tlm_frame_171_data
    {
        .data_id = DC_ATTR_ID_CUBEADCS_GEN2_TLM_FRAME_171_DATA,
        .p_data_raw = &dc_instance.cubeadcs_gen2_tlm_frame_171_data,
        .data_size = sizeof(dc_instance.cubeadcs_gen2_tlm_frame_171_data),
        .data_timeout = 5000U
    },
    // cubeadcs_gen2_tlm_frame_172_data
    {
        .data_id = DC_ATTR_ID_CUBEADCS_GEN2_TLM_FRAME_172_DATA,
        .p_data_raw = &dc_instance.cubeadcs_gen2_tlm_frame_172_data,
        .data_size = sizeof(dc_instance.cubeadcs_gen2_tlm_frame_172_data),
        .data_timeout = 5000U
    },
    // cubeadcs_gen2_tlm_frame_173_data
    {
        .data_id = DC_ATTR_ID_CUBEADCS_GEN2_TLM_FRAME_173_DATA,
        .p_data_raw = &dc_instance.cubeadcs_gen2_tlm_frame_173_data,
        .data_size = sizeof(dc_instance.cubeadcs_gen2_tlm_frame_173_data),
        .data_timeout = 5000U
    },
    // cubeadcs_gen2_tlm_frame_174_data
    {
        .data_id = DC_ATTR_ID_CUBEADCS_GEN2_TLM_FRAME_174_DATA,
        .p_data_raw = &dc_instance.cubeadcs_gen2_tlm_frame_174_data,
        .data_size = sizeof(dc_instance.cubeadcs_gen2_tlm_frame_174_data),
        .data_timeout = 5000U
    },
    // cubeadcs_gen2_tlm_frame_175_data
    {
        .data_id = DC_ATTR_ID_CUBEADCS_GEN2_TLM_FRAME_175_DATA,
        .p_data_raw = &dc_instance.cubeadcs_gen2_tlm_frame_175_data,
        .data_size = sizeof(dc_instance.cubeadcs_gen2_tlm_frame_175_data),
        .data_timeout = 5000U
    },
    // cubeadcs_gen2_tlm_frame_176_data
    {
        .data_id = DC_ATTR_ID_CUBEADCS_GEN2_TLM_FRAME_176_DATA,
        .p_data_raw = &dc_instance.cubeadcs_gen2_tlm_frame_176_data,
        .data_size = sizeof(dc_instance.cubeadcs_gen2_tlm_frame_176_data),
        .data_timeout = 5000U
    },
    // cubeadcs_gen2_tlm_frame_177_data
    {
        .data_id = DC_ATTR_ID_CUBEADCS_GEN2_TLM_FRAME_177_DATA,
        .p_data_raw = &dc_instance.cubeadcs_gen2_tlm_frame_177_data,
        .data_size = sizeof(dc_instance.cubeadcs_gen2_tlm_frame_177_data),
        .data_timeout = 5000U
    },
    // cubeadcs_gen2_tlm_frame_178_data
    {
        .data_id = DC_ATTR_ID_CUBEADCS_GEN2_TLM_FRAME_178_DATA,
        .p_data_raw = &dc_instance.cubeadcs_gen2_tlm_frame_178_data,
        .data_size = sizeof(dc_instance.cubeadcs_gen2_tlm_frame_178_data),
        .data_timeout = 5000U
    },
    // cubeadcs_gen2_tlm_frame_179_data
    {
        .data_id = DC_ATTR_ID_CUBEADCS_GEN2_TLM_FRAME_179_DATA,
        .p_data_raw = &dc_instance.cubeadcs_gen2_tlm_frame_179_data,
        .data_size = sizeof(dc_instance.cubeadcs_gen2_tlm_frame_179_data),
        .data_timeout = 5000U
    },
    // cubeadcs_gen2_tlm_frame_180_data
    {
        .data_id = DC_ATTR_ID_CUBEADCS_GEN2_TLM_FRAME_180_DATA,
        .p_data_raw = &dc_instance.cubeadcs_gen2_tlm_frame_180_data,
        .data_size = sizeof(dc_instance.cubeadcs_gen2_tlm_frame_180_data),
        .data_timeout = 5000U
    },
    // cubeadcs_gen2_tlm_frame_203_data
    {
        .data_id = DC_ATTR_ID_CUBEADCS_GEN2_TLM_FRAME_203_DATA,
        .p_data_raw = &dc_instance.cubeadcs_gen2_tlm_frame_203_data,
        .data_size = sizeof(dc_instance.cubeadcs_gen2_tlm_frame_203_data),
        .data_timeout = 5000U
    },
    // cubeadcs_gen2_tlm_frame_204_data
    {
        .data_id = DC_ATTR_ID_CUBEADCS_GEN2_TLM_FRAME_204_DATA,
        .p_data_raw = &dc_instance.cubeadcs_gen2_tlm_frame_204_data,
        .data_size = sizeof(dc_instance.cubeadcs_gen2_tlm_frame_204_data),
        .data_timeout = 5000U
    },
    // cubeadcs_gen2_tlm_frame_205_data
    {
        .data_id = DC_ATTR_ID_CUBEADCS_GEN2_TLM_FRAME_205_DATA,
        .p_data_raw = &dc_instance.cubeadcs_gen2_tlm_frame_205_data,
        .data_size = sizeof(dc_instance.cubeadcs_gen2_tlm_frame_205_data),
        .data_timeout = 5000U
    },
    // cubeadcs_gen2_tlm_frame_206_data
    {
        .data_id = DC_ATTR_ID_CUBEADCS_GEN2_TLM_FRAME_206_DATA,
        .p_data_raw = &dc_instance.cubeadcs_gen2_tlm_frame_206_data,
        .data_size = sizeof(dc_instance.cubeadcs_gen2_tlm_frame_206_data),
        .data_timeout = 5000U
    },
    // cubeadcs_gen2_tlm_frame_207_data
    {
        .data_id = DC_ATTR_ID_CUBEADCS_GEN2_TLM_FRAME_207_DATA,
        .p_data_raw = &dc_instance.cubeadcs_gen2_tlm_frame_207_data,
        .data_size = sizeof(dc_instance.cubeadcs_gen2_tlm_frame_207_data),
        .data_timeout = 5000U
    },
    // cubeadcs_gen2_tlm_frame_208_1_data
    {
        .data_id = DC_ATTR_ID_CUBEADCS_GEN2_TLM_FRAME_208_1_DATA,
        .p_data_raw = &dc_instance.cubeadcs_gen2_tlm_frame_208_1_data,
        .data_size = sizeof(dc_instance.cubeadcs_gen2_tlm_frame_208_1_data),
        .data_timeout = 5000U
    },
    // cubeadcs_gen2_tlm_frame_208_2_data
    {
        .data_id = DC_ATTR_ID_CUBEADCS_GEN2_TLM_FRAME_208_2_DATA,
        .p_data_raw = &dc_instance.cubeadcs_gen2_tlm_frame_208_2_data,
        .data_size = sizeof(dc_instance.cubeadcs_gen2_tlm_frame_208_2_data),
        .data_timeout = 5000U
    },
    // cubeadcs_gen2_tlm_frame_209_data
    {
        .data_id = DC_ATTR_ID_CUBEADCS_GEN2_TLM_FRAME_209_DATA,
        .p_data_raw = &dc_instance.cubeadcs_gen2_tlm_frame_209_data,
        .data_size = sizeof(dc_instance.cubeadcs_gen2_tlm_frame_209_data),
        .data_timeout = 5000U
    },
    // cubeadcs_gen2_tlm_frame_210_data
    {
        .data_id = DC_ATTR_ID_CUBEADCS_GEN2_TLM_FRAME_210_DATA,
        .p_data_raw = &dc_instance.cubeadcs_gen2_tlm_frame_210_data,
        .data_size = sizeof(dc_instance.cubeadcs_gen2_tlm_frame_210_data),
        .data_timeout = 5000U
    },
    // cubeadcs_gen2_tlm_frame_211_data
    {
        .data_id = DC_ATTR_ID_CUBEADCS_GEN2_TLM_FRAME_211_DATA,
        .p_data_raw = &dc_instance.cubeadcs_gen2_tlm_frame_211_data,
        .data_size = sizeof(dc_instance.cubeadcs_gen2_tlm_frame_211_data),
        .data_timeout = 5000U
    },
    // cubeadcs_gen2_tlm_frame_212_data
    {
        .data_id = DC_ATTR_ID_CUBEADCS_GEN2_TLM_FRAME_212_DATA,
        .p_data_raw = &dc_instance.cubeadcs_gen2_tlm_frame_212_data,
        .data_size = sizeof(dc_instance.cubeadcs_gen2_tlm_frame_212_data),
        .data_timeout = 5000U
    },
    // cubeadcs_gen2_tlm_frame_213_data
    {
        .data_id = DC_ATTR_ID_CUBEADCS_GEN2_TLM_FRAME_213_DATA,
        .p_data_raw = &dc_instance.cubeadcs_gen2_tlm_frame_213_data,
        .data_size = sizeof(dc_instance.cubeadcs_gen2_tlm_frame_213_data),
        .data_timeout = 5000U
    },
    // cubeadcs_gen2_tlm_frame_214_data
    {
        .data_id = DC_ATTR_ID_CUBEADCS_GEN2_TLM_FRAME_214_DATA,
        .p_data_raw = &dc_instance.cubeadcs_gen2_tlm_frame_214_data,
        .data_size = sizeof(dc_instance.cubeadcs_gen2_tlm_frame_214_data),
        .data_timeout = 5000U
    },
    // cubeadcs_gen2_tlm_frame_216_data
    {
        .data_id = DC_ATTR_ID_CUBEADCS_GEN2_TLM_FRAME_216_DATA,
        .p_data_raw = &dc_instance.cubeadcs_gen2_tlm_frame_216_data,
        .data_size = sizeof(dc_instance.cubeadcs_gen2_tlm_frame_216_data),
        .data_timeout = 5000U
    },
    // cubeadcs_gen2_tlm_frame_217_data
    {
        .data_id = DC_ATTR_ID_CUBEADCS_GEN2_TLM_FRAME_217_DATA,
        .p_data_raw = &dc_instance.cubeadcs_gen2_tlm_frame_217_data,
        .data_size = sizeof(dc_instance.cubeadcs_gen2_tlm_frame_217_data),
        .data_timeout = 5000U
    },
    // cubeadcs_gen2_tlm_frame_218_data
    {
        .data_id = DC_ATTR_ID_CUBEADCS_GEN2_TLM_FRAME_218_DATA,
        .p_data_raw = &dc_instance.cubeadcs_gen2_tlm_frame_218_data,
        .data_size = sizeof(dc_instance.cubeadcs_gen2_tlm_frame_218_data),
        .data_timeout = 5000U
    },
    // cubeadcs_gen2_tlm_frame_225_data
    {
        .data_id = DC_ATTR_ID_CUBEADCS_GEN2_TLM_FRAME_225_DATA,
        .p_data_raw = &dc_instance.cubeadcs_gen2_tlm_frame_225_data,
        .data_size = sizeof(dc_instance.cubeadcs_gen2_tlm_frame_225_data),
        .data_timeout = 5000U
    },
    // cubeadcs_gen2_tlm_frame_226_data
    {
        .data_id = DC_ATTR_ID_CUBEADCS_GEN2_TLM_FRAME_226_DATA,
        .p_data_raw = &dc_instance.cubeadcs_gen2_tlm_frame_226_data,
        .data_size = sizeof(dc_instance.cubeadcs_gen2_tlm_frame_226_data),
        .data_timeout = 5000U
    },
    // cubeadcs_gen2_tlm_frame_165_data
    {
        .data_id = DC_ATTR_ID_CUBEADCS_GEN2_TLM_FRAME_165_DATA,
        .p_data_raw = &dc_instance.cubeadcs_gen2_tlm_frame_165_data,
        .data_size = sizeof(dc_instance.cubeadcs_gen2_tlm_frame_165_data),
        .data_timeout = 5000U
    },
    // cubeadcs_gen2_tlm_frame_221_data
    {
        .data_id = DC_ATTR_ID_CUBEADCS_GEN2_TLM_FRAME_221_DATA,
        .p_data_raw = &dc_instance.cubeadcs_gen2_tlm_frame_221_data,
        .data_size = sizeof(dc_instance.cubeadcs_gen2_tlm_frame_221_data),
        .data_timeout = 5000U
    },
    // gnss_time_data
    {
        .data_id = DC_ATTR_ID_GNSS_TIME_DATA,
        .p_data_raw = &dc_instance.gnss_time_data,
        .data_size = sizeof(dc_instance.gnss_time_data),
        .data_timeout = 5000U
    },
    // gnss_bestxyz_data
    {
        .data_id = DC_ATTR_ID_GNSS_BESTXYZ_DATA,
        .p_data_raw = &dc_instance.gnss_bestxyz_data,
        .data_size = sizeof(dc_instance.gnss_bestxyz_data),
        .data_timeout = 5000U
    },
    // sat_state_vector_from_propagator_data
    {
        .data_id = DC_ATTR_ID_SAT_STATE_VECTOR_FROM_PROPAGATOR_DATA,
        .p_data_raw = &dc_instance.sat_state_vector_from_propagator_data,
        .data_size = sizeof(dc_instance.sat_state_vector_from_propagator_data),
        .data_timeout = 5000U
    },
    // sat_mag_field_vector_from_model_data
    {
        .data_id = DC_ATTR_ID_SAT_MAG_FIELD_VECTOR_FROM_MODEL_DATA,
        .p_data_raw = &dc_instance.sat_mag_field_vector_from_model_data,
        .data_size = sizeof(dc_instance.sat_mag_field_vector_from_model_data),
        .data_timeout = 5000U
    },
    // sat_mag_field_vector_from_sensor_data
    {
        .data_id = DC_ATTR_ID_SAT_MAG_FIELD_VECTOR_FROM_SENSOR_DATA,
        .p_data_raw = &dc_instance.sat_mag_field_vector_from_sensor_data,
        .data_size = sizeof(dc_instance.sat_mag_field_vector_from_sensor_data),
        .data_timeout = 5000U
    },
    // fdir_eps_i_cmd_exec_status_data
    {
        .data_id = DC_ATTR_ID_FDIR_EPS_I_CMD_EXEC_STATUS_DATA,
        .p_data_raw = &dc_instance.fdir_eps_i_cmd_exec_status_data,
        .data_size = sizeof(dc_instance.fdir_eps_i_cmd_exec_status_data),
        .data_timeout = 5000U
    },
    // fdir_eps_ii_pdm_cmd_exec_status_data
    {
        .data_id = DC_ATTR_ID_FDIR_EPS_II_PDM_CMD_EXEC_STATUS_DATA,
        .p_data_raw = &dc_instance.fdir_eps_ii_pdm_cmd_exec_status_data,
        .data_size = sizeof(dc_instance.fdir_eps_ii_pdm_cmd_exec_status_data),
        .data_timeout = 5000U
    },
    // fdir_cubeadcs_cmd_exec_status_data
    {
        .data_id = DC_ATTR_ID_FDIR_CUBEADCS_CMD_EXEC_STATUS_DATA,
        .p_data_raw = &dc_instance.fdir_cubeadcs_cmd_exec_status_data,
        .data_size = sizeof(dc_instance.fdir_cubeadcs_cmd_exec_status_data),
        .data_timeout = 5000U
    },
    // fdir_cubeadcs_gen2_cmd_exec_status_data
    {
        .data_id = DC_ATTR_ID_FDIR_CUBEADCS_GEN2_CMD_EXEC_STATUS_DATA,
        .p_data_raw = &dc_instance.fdir_cubeadcs_gen2_cmd_exec_status_data,
        .data_size = sizeof(dc_instance.fdir_cubeadcs_gen2_cmd_exec_status_data),
        .data_timeout = 5000U
    },
    // fdir_cubeadcs_gen2_events_data
    {
        .data_id = DC_ATTR_ID_FDIR_CUBEADCS_GEN2_EVENTS_DATA,
        .p_data_raw = &dc_instance.fdir_cubeadcs_gen2_events_data,
        .data_size = sizeof(dc_instance.fdir_cubeadcs_gen2_events_data),
        .data_timeout = 5000U
    },
    // fdir_s_band_tmtc_cmd_exec_status_data
    {
        .data_id = DC_ATTR_ID_FDIR_S_BAND_TMTC_CMD_EXEC_STATUS_DATA,
        .p_data_raw = &dc_instance.fdir_s_band_tmtc_cmd_exec_status_data,
        .data_size = sizeof(dc_instance.fdir_s_band_tmtc_cmd_exec_status_data),
        .data_timeout = 5000U
    },
    // fdir_uhf_cmd_exec_status_data
    {
        .data_id = DC_ATTR_ID_FDIR_UHF_CMD_EXEC_STATUS_DATA,
        .p_data_raw = &dc_instance.fdir_uhf_cmd_exec_status_data,
        .data_size = sizeof(dc_instance.fdir_uhf_cmd_exec_status_data),
        .data_timeout = 5000U
    },
    // fdir_gnss_cmd_exec_status_data
    {
        .data_id = DC_ATTR_ID_FDIR_GNSS_CMD_EXEC_STATUS_DATA,
        .p_data_raw = &dc_instance.fdir_gnss_cmd_exec_status_data,
        .data_size = sizeof(dc_instance.fdir_gnss_cmd_exec_status_data),
        .data_timeout = 5000U
    },
    // fdir_sdr_cmd_exec_status_data
    {
        .data_id = DC_ATTR_ID_FDIR_SDR_CMD_EXEC_STATUS_DATA,
        .p_data_raw = &dc_instance.fdir_sdr_cmd_exec_status_data,
        .data_size = sizeof(dc_instance.fdir_sdr_cmd_exec_status_data),
        .data_timeout = 5000U
    },
    // fdir_s_x_band_cmd_exec_status_data
    {
        .data_id = DC_ATTR_ID_FDIR_S_X_BAND_CMD_EXEC_STATUS_DATA,
        .p_data_raw = &dc_instance.fdir_s_x_band_cmd_exec_status_data,
        .data_size = sizeof(dc_instance.fdir_s_x_band_cmd_exec_status_data),
        .data_timeout = 5000U
    },
    // fdir_thruster_cmd_exec_status_data
    {
        .data_id = DC_ATTR_ID_FDIR_THRUSTER_CMD_EXEC_STATUS_DATA,
        .p_data_raw = &dc_instance.fdir_thruster_cmd_exec_status_data,
        .data_size = sizeof(dc_instance.fdir_thruster_cmd_exec_status_data),
        .data_timeout = 5000U
    },
    // xband_fe_data
    {
        .data_id = DC_ATTR_ID_XBAND_FE_DATA,
        .p_data_raw = &dc_instance.xband_fe_data,
        .data_size = sizeof(dc_instance.xband_fe_data),
        .data_timeout = 5000U
    },
    // epsoverallbatteryinfo_data
    {
        .data_id = DC_ATTR_ID_EPSOVERALLBATTERYINFO_DATA,
        .p_data_raw = &dc_instance.epsoverallbatteryinfo_data,
        .data_size = sizeof(dc_instance.epsoverallbatteryinfo_data),
        .data_timeout = 30000U
    },
    // pps_telemetry_data
    {
        .data_id = DC_ATTR_ID_PPS_TELEMETRY_DATA,
        .p_data_raw = &dc_instance.pps_telemetry_data,
        .data_size = sizeof(dc_instance.pps_telemetry_data),
        .data_timeout = 5000U
    },
    // fdir_eps_iii_pdm_cmd_exec_status_data
    {
        .data_id = DC_ATTR_ID_FDIR_EPS_III_PDM_CMD_EXEC_STATUS_DATA,
        .p_data_raw = &dc_instance.fdir_eps_iii_pdm_cmd_exec_status_data,
        .data_size = sizeof(dc_instance.fdir_eps_iii_pdm_cmd_exec_status_data),
        .data_timeout = 5000U
    },
    // eps2_bp_inst0_bp_info_data
    {
        .data_id = DC_ATTR_ID_EPS2_BP_INST0_BP_INFO_DATA,
        .p_data_raw = &dc_instance.eps2_bp_inst0_bp_info_data,
        .data_size = sizeof(dc_instance.eps2_bp_inst0_bp_info_data),
        .data_timeout = 30000U
    },
    // eps2_bp_inst0_device_health_info_data
    {
        .data_id = DC_ATTR_ID_EPS2_BP_INST0_DEVICE_HEALTH_INFO_DATA,
        .p_data_raw = &dc_instance.eps2_bp_inst0_device_health_info_data,
        .data_size = sizeof(dc_instance.eps2_bp_inst0_device_health_info_data),
        .data_timeout = 30000U
    },
    // eps2_bp_inst0_ina_sensor1_data
    {
        .data_id = DC_ATTR_ID_EPS2_BP_INST0_INA_SENSOR1_DATA,
        .p_data_raw = &dc_instance.eps2_bp_inst0_ina_sensor1_data,
        .data_size = sizeof(dc_instance.eps2_bp_inst0_ina_sensor1_data),
        .data_timeout = 30000U
    },
    // eps2_bp_inst0_ina_sensor2_data
    {
        .data_id = DC_ATTR_ID_EPS2_BP_INST0_INA_SENSOR2_DATA,
        .p_data_raw = &dc_instance.eps2_bp_inst0_ina_sensor2_data,
        .data_size = sizeof(dc_instance.eps2_bp_inst0_ina_sensor2_data),
        .data_timeout = 30000U
    },
    // eps2_bp_inst0_balancer_info_data
    {
        .data_id = DC_ATTR_ID_EPS2_BP_INST0_BALANCER_INFO_DATA,
        .p_data_raw = &dc_instance.eps2_bp_inst0_balancer_info_data,
        .data_size = sizeof(dc_instance.eps2_bp_inst0_balancer_info_data),
        .data_timeout = 30000U
    },
    // eps2_bp_inst0_balancer_status_data
    {
        .data_id = DC_ATTR_ID_EPS2_BP_INST0_BALANCER_STATUS_DATA,
        .p_data_raw = &dc_instance.eps2_bp_inst0_balancer_status_data,
        .data_size = sizeof(dc_instance.eps2_bp_inst0_balancer_status_data),
        .data_timeout = 30000U
    },
    // eps2_bp_inst0_balancer_cells_info_data
    {
        .data_id = DC_ATTR_ID_EPS2_BP_INST0_BALANCER_CELLS_INFO_DATA,
        .p_data_raw = &dc_instance.eps2_bp_inst0_balancer_cells_info_data,
        .data_size = sizeof(dc_instance.eps2_bp_inst0_balancer_cells_info_data),
        .data_timeout = 30000U
    },
    // eps2_bp_inst0_charger_xp_data
    {
        .data_id = DC_ATTR_ID_EPS2_BP_INST0_CHARGER_XP_DATA,
        .p_data_raw = &dc_instance.eps2_bp_inst0_charger_xp_data,
        .data_size = sizeof(dc_instance.eps2_bp_inst0_charger_xp_data),
        .data_timeout = 30000U
    },
    // eps2_bp_inst0_charger_xr_data
    {
        .data_id = DC_ATTR_ID_EPS2_BP_INST0_CHARGER_XR_DATA,
        .p_data_raw = &dc_instance.eps2_bp_inst0_charger_xr_data,
        .data_size = sizeof(dc_instance.eps2_bp_inst0_charger_xr_data),
        .data_timeout = 30000U
    },
    // eps2_bp_inst0_charger_yp_data
    {
        .data_id = DC_ATTR_ID_EPS2_BP_INST0_CHARGER_YP_DATA,
        .p_data_raw = &dc_instance.eps2_bp_inst0_charger_yp_data,
        .data_size = sizeof(dc_instance.eps2_bp_inst0_charger_yp_data),
        .data_timeout = 30000U
    },
    // eps2_bp_inst0_charger_yr_data
    {
        .data_id = DC_ATTR_ID_EPS2_BP_INST0_CHARGER_YR_DATA,
        .p_data_raw = &dc_instance.eps2_bp_inst0_charger_yr_data,
        .data_size = sizeof(dc_instance.eps2_bp_inst0_charger_yr_data),
        .data_timeout = 30000U
    },
    // eps2_bp_inst0_charger_zp_data
    {
        .data_id = DC_ATTR_ID_EPS2_BP_INST0_CHARGER_ZP_DATA,
        .p_data_raw = &dc_instance.eps2_bp_inst0_charger_zp_data,
        .data_size = sizeof(dc_instance.eps2_bp_inst0_charger_zp_data),
        .data_timeout = 30000U
    },
    // eps2_bp_inst0_charger_zr_data
    {
        .data_id = DC_ATTR_ID_EPS2_BP_INST0_CHARGER_ZR_DATA,
        .p_data_raw = &dc_instance.eps2_bp_inst0_charger_zr_data,
        .data_size = sizeof(dc_instance.eps2_bp_inst0_charger_zr_data),
        .data_timeout = 30000U
    },
    // fdir_eps_ii_bp_inst0_cmd_exec_status_data
    {
        .data_id = DC_ATTR_ID_FDIR_EPS_II_BP_INST0_CMD_EXEC_STATUS_DATA,
        .p_data_raw = &dc_instance.fdir_eps_ii_bp_inst0_cmd_exec_status_data,
        .data_size = sizeof(dc_instance.fdir_eps_ii_bp_inst0_cmd_exec_status_data),
        .data_timeout = 40000U
    },
    // eps3_bp_inst0_uptime_in_seconds
    {
        .data_id = DC_ATTR_ID_EPS3_BP_INST0_UPTIME_IN_SECONDS,
        .p_data_raw = &dc_instance.eps3_bp_inst0_uptime_in_seconds,
        .data_size = sizeof(dc_instance.eps3_bp_inst0_uptime_in_seconds),
        .data_timeout = 30000U
    },
    // eps3_bp_inst0common
    {
        .data_id = DC_ATTR_ID_EPS3_BP_INST0COMMON,
        .p_data_raw = &dc_instance.eps3_bp_inst0common,
        .data_size = sizeof(dc_instance.eps3_bp_inst0common),
        .data_timeout = 30000U
    },
    // eps3_bp_inst0hib_mode_status
    {
        .data_id = DC_ATTR_ID_EPS3_BP_INST0HIB_MODE_STATUS,
        .p_data_raw = &dc_instance.eps3_bp_inst0hib_mode_status,
        .data_size = sizeof(dc_instance.eps3_bp_inst0hib_mode_status),
        .data_timeout = 30000U
    },
    // eps3_bp_inst0measurements
    {
        .data_id = DC_ATTR_ID_EPS3_BP_INST0MEASUREMENTS,
        .p_data_raw = &dc_instance.eps3_bp_inst0measurements,
        .data_size = sizeof(dc_instance.eps3_bp_inst0measurements),
        .data_timeout = 30000U
    },
    // eps3_bp_inst0discharging_state
    {
        .data_id = DC_ATTR_ID_EPS3_BP_INST0DISCHARGING_STATE,
        .p_data_raw = &dc_instance.eps3_bp_inst0discharging_state,
        .data_size = sizeof(dc_instance.eps3_bp_inst0discharging_state),
        .data_timeout = 30000U
    },
    // eps3_bp_inst0charge_status
    {
        .data_id = DC_ATTR_ID_EPS3_BP_INST0CHARGE_STATUS,
        .p_data_raw = &dc_instance.eps3_bp_inst0charge_status,
        .data_size = sizeof(dc_instance.eps3_bp_inst0charge_status),
        .data_timeout = 30000U
    },
    // eps3_bp_inst0balancers_status
    {
        .data_id = DC_ATTR_ID_EPS3_BP_INST0BALANCERS_STATUS,
        .p_data_raw = &dc_instance.eps3_bp_inst0balancers_status,
        .data_size = sizeof(dc_instance.eps3_bp_inst0balancers_status),
        .data_timeout = 30000U
    },
    // eps3_bp_inst0battery_cells_status
    {
        .data_id = DC_ATTR_ID_EPS3_BP_INST0BATTERY_CELLS_STATUS,
        .p_data_raw = &dc_instance.eps3_bp_inst0battery_cells_status,
        .data_size = sizeof(dc_instance.eps3_bp_inst0battery_cells_status),
        .data_timeout = 30000U
    },
    // eps3_bp_inst0heaters_status
    {
        .data_id = DC_ATTR_ID_EPS3_BP_INST0HEATERS_STATUS,
        .p_data_raw = &dc_instance.eps3_bp_inst0heaters_status,
        .data_size = sizeof(dc_instance.eps3_bp_inst0heaters_status),
        .data_timeout = 30000U
    },
    // eps3_bp_inst0_cmd_exec_status_data
    {
        .data_id = DC_ATTR_ID_EPS3_BP_INST0_CMD_EXEC_STATUS_DATA,
        .p_data_raw = &dc_instance.eps3_bp_inst0_cmd_exec_status_data,
        .data_size = sizeof(dc_instance.eps3_bp_inst0_cmd_exec_status_data),
        .data_timeout = 40000U
    },
    // dumb_data
    {
        .data_id = DC_ATTR_ID_DUMB_DATA,
        .p_data_raw = &dc_instance.dumb_data,
        .data_size = sizeof(dc_instance.dumb_data),
        .data_timeout = 5000U
    },
    // dumb_data1
    {
        .data_id = DC_ATTR_ID_DUMB_DATA1,
        .p_data_raw = &dc_instance.dumb_data1,
        .data_size = sizeof(dc_instance.dumb_data1),
        .data_timeout = 5000U
    },
    // dumb_data3
    {
        .data_id = DC_ATTR_ID_DUMB_DATA3,
        .p_data_raw = &dc_instance.dumb_data3,
        .data_size = sizeof(dc_instance.dumb_data3),
        .data_timeout = 5000U
    },
    // dumb_data4
    {
        .data_id = DC_ATTR_ID_DUMB_DATA4,
        .p_data_raw = &dc_instance.dumb_data4,
        .data_size = sizeof(dc_instance.dumb_data4),
        .data_timeout = 5000U
    },
    // dumb_data5
    {
        .data_id = DC_ATTR_ID_DUMB_DATA5,
        .p_data_raw = &dc_instance.dumb_data5,
        .data_size = sizeof(dc_instance.dumb_data5),
        .data_timeout = 5000U
    },
    // dumb_data6
    {
        .data_id = DC_ATTR_ID_DUMB_DATA6,
        .p_data_raw = &dc_instance.dumb_data6,
        .data_size = sizeof(dc_instance.dumb_data6),
        .data_timeout = 5000U
    },
    // eps3_pdm_a_inst0_uptime_in_seconds
    {
        .data_id = DC_ATTR_ID_EPS3_PDM_A_INST0_UPTIME_IN_SECONDS,
        .p_data_raw = &dc_instance.eps3_pdm_a_inst0_uptime_in_seconds,
        .data_size = sizeof(dc_instance.eps3_pdm_a_inst0_uptime_in_seconds),
        .data_timeout = 30000U
    },
    // eps3_pdm_a_inst0_common
    {
        .data_id = DC_ATTR_ID_EPS3_PDM_A_INST0_COMMON,
        .p_data_raw = &dc_instance.eps3_pdm_a_inst0_common,
        .data_size = sizeof(dc_instance.eps3_pdm_a_inst0_common),
        .data_timeout = 30000U
    },
    // eps3_pdm_a_inst0_hib_mode
    {
        .data_id = DC_ATTR_ID_EPS3_PDM_A_INST0_HIB_MODE,
        .p_data_raw = &dc_instance.eps3_pdm_a_inst0_hib_mode,
        .data_size = sizeof(dc_instance.eps3_pdm_a_inst0_hib_mode),
        .data_timeout = 30000U
    },
    // eps3_pdm_a_inst0_general_outputs
    {
        .data_id = DC_ATTR_ID_EPS3_PDM_A_INST0_GENERAL_OUTPUTS,
        .p_data_raw = &dc_instance.eps3_pdm_a_inst0_general_outputs,
        .data_size = sizeof(dc_instance.eps3_pdm_a_inst0_general_outputs),
        .data_timeout = 30000U
    },
    // eps3_pdm_a_inst0_general_faults
    {
        .data_id = DC_ATTR_ID_EPS3_PDM_A_INST0_GENERAL_FAULTS,
        .p_data_raw = &dc_instance.eps3_pdm_a_inst0_general_faults,
        .data_size = sizeof(dc_instance.eps3_pdm_a_inst0_general_faults),
        .data_timeout = 30000U
    },
    // eps3_pdm_a_inst0_all_measurements
    {
        .data_id = DC_ATTR_ID_EPS3_PDM_A_INST0_ALL_MEASUREMENTS,
        .p_data_raw = &dc_instance.eps3_pdm_a_inst0_all_measurements,
        .data_size = sizeof(dc_instance.eps3_pdm_a_inst0_all_measurements),
        .data_timeout = 30000U
    },
    // eps3_pdm_a_inst0_cmd_exec_status_data
    {
        .data_id = DC_ATTR_ID_EPS3_PDM_A_INST0_CMD_EXEC_STATUS_DATA,
        .p_data_raw = &dc_instance.eps3_pdm_a_inst0_cmd_exec_status_data,
        .data_size = sizeof(dc_instance.eps3_pdm_a_inst0_cmd_exec_status_data),
        .data_timeout = 40000U
    },
    // eps3_pdm_b_inst0_cmd_exec_status_data
    {
        .data_id = DC_ATTR_ID_EPS3_PDM_B_INST0_CMD_EXEC_STATUS_DATA,
        .p_data_raw = &dc_instance.eps3_pdm_b_inst0_cmd_exec_status_data,
        .data_size = sizeof(dc_instance.eps3_pdm_b_inst0_cmd_exec_status_data),
        .data_timeout = 40000U
    },
    // eps3_pdm_b_inst0_uptime_in_seconds
    {
        .data_id = DC_ATTR_ID_EPS3_PDM_B_INST0_UPTIME_IN_SECONDS,
        .p_data_raw = &dc_instance.eps3_pdm_b_inst0_uptime_in_seconds,
        .data_size = sizeof(dc_instance.eps3_pdm_b_inst0_uptime_in_seconds),
        .data_timeout = 30000U
    },
    // eps3_pdm_b_inst0_common
    {
        .data_id = DC_ATTR_ID_EPS3_PDM_B_INST0_COMMON,
        .p_data_raw = &dc_instance.eps3_pdm_b_inst0_common,
        .data_size = sizeof(dc_instance.eps3_pdm_b_inst0_common),
        .data_timeout = 30000U
    },
    // eps3_pdm_b_inst0_hib_mode
    {
        .data_id = DC_ATTR_ID_EPS3_PDM_B_INST0_HIB_MODE,
        .p_data_raw = &dc_instance.eps3_pdm_b_inst0_hib_mode,
        .data_size = sizeof(dc_instance.eps3_pdm_b_inst0_hib_mode),
        .data_timeout = 30000U
    },
    // eps3_pdm_b_inst0_general_outputs
    {
        .data_id = DC_ATTR_ID_EPS3_PDM_B_INST0_GENERAL_OUTPUTS,
        .p_data_raw = &dc_instance.eps3_pdm_b_inst0_general_outputs,
        .data_size = sizeof(dc_instance.eps3_pdm_b_inst0_general_outputs),
        .data_timeout = 30000U
    },
    // eps3_pdm_b_inst0_channel_flag_state
    {
        .data_id = DC_ATTR_ID_EPS3_PDM_B_INST0_CHANNEL_FLAG_STATE,
        .p_data_raw = &dc_instance.eps3_pdm_b_inst0_channel_flag_state,
        .data_size = sizeof(dc_instance.eps3_pdm_b_inst0_channel_flag_state),
        .data_timeout = 30000U
    },
    // eps3_pdm_b_inst0_temperature
    {
        .data_id = DC_ATTR_ID_EPS3_PDM_B_INST0_TEMPERATURE,
        .p_data_raw = &dc_instance.eps3_pdm_b_inst0_temperature,
        .data_size = sizeof(dc_instance.eps3_pdm_b_inst0_temperature),
        .data_timeout = 30000U
    },
    // eps3_pdm_b_inst0_all_measurements
    {
        .data_id = DC_ATTR_ID_EPS3_PDM_B_INST0_ALL_MEASUREMENTS,
        .p_data_raw = &dc_instance.eps3_pdm_b_inst0_all_measurements,
        .data_size = sizeof(dc_instance.eps3_pdm_b_inst0_all_measurements),
        .data_timeout = 30000U
    },
    // eps3_expander_inst0_cmd_exec_status_data
    {
        .data_id = DC_ATTR_ID_EPS3_EXPANDER_INST0_CMD_EXEC_STATUS_DATA,
        .p_data_raw = &dc_instance.eps3_expander_inst0_cmd_exec_status_data,
        .data_size = sizeof(dc_instance.eps3_expander_inst0_cmd_exec_status_data),
        .data_timeout = 40000U
    },
    // eps3_expander_inst0_uptime_in_seconds
    {
        .data_id = DC_ATTR_ID_EPS3_EXPANDER_INST0_UPTIME_IN_SECONDS,
        .p_data_raw = &dc_instance.eps3_expander_inst0_uptime_in_seconds,
        .data_size = sizeof(dc_instance.eps3_expander_inst0_uptime_in_seconds),
        .data_timeout = 30000U
    },
    // eps3_expander_inst0_common
    {
        .data_id = DC_ATTR_ID_EPS3_EXPANDER_INST0_COMMON,
        .p_data_raw = &dc_instance.eps3_expander_inst0_common,
        .data_size = sizeof(dc_instance.eps3_expander_inst0_common),
        .data_timeout = 30000U
    },
    // eps3_expander_inst0_outputs
    {
        .data_id = DC_ATTR_ID_EPS3_EXPANDER_INST0_OUTPUTS,
        .p_data_raw = &dc_instance.eps3_expander_inst0_outputs,
        .data_size = sizeof(dc_instance.eps3_expander_inst0_outputs),
        .data_timeout = 30000U
    },
    // eps3_expander_inst0_general_inputs
    {
        .data_id = DC_ATTR_ID_EPS3_EXPANDER_INST0_GENERAL_INPUTS,
        .p_data_raw = &dc_instance.eps3_expander_inst0_general_inputs,
        .data_size = sizeof(dc_instance.eps3_expander_inst0_general_inputs),
        .data_timeout = 30000U
    },
    // eps3_expander_inst0_feedbacks
    {
        .data_id = DC_ATTR_ID_EPS3_EXPANDER_INST0_FEEDBACKS,
        .p_data_raw = &dc_instance.eps3_expander_inst0_feedbacks,
        .data_size = sizeof(dc_instance.eps3_expander_inst0_feedbacks),
        .data_timeout = 30000U
    },
    // eps3_expander_inst0_volt_amp_measurements
    {
        .data_id = DC_ATTR_ID_EPS3_EXPANDER_INST0_VOLT_AMP_MEASUREMENTS,
        .p_data_raw = &dc_instance.eps3_expander_inst0_volt_amp_measurements,
        .data_size = sizeof(dc_instance.eps3_expander_inst0_volt_amp_measurements),
        .data_timeout = 30000U
    },
    // eps3_input_stage_inst0_uptime_in_seconds
    {
        .data_id = DC_ATTR_ID_EPS3_INPUT_STAGE_INST0_UPTIME_IN_SECONDS,
        .p_data_raw = &dc_instance.eps3_input_stage_inst0_uptime_in_seconds,
        .data_size = sizeof(dc_instance.eps3_input_stage_inst0_uptime_in_seconds),
        .data_timeout = 30000U
    },
    // eps3_input_stage_inst0common
    {
        .data_id = DC_ATTR_ID_EPS3_INPUT_STAGE_INST0COMMON,
        .p_data_raw = &dc_instance.eps3_input_stage_inst0common,
        .data_size = sizeof(dc_instance.eps3_input_stage_inst0common),
        .data_timeout = 30000U
    },
    // eps3_input_stage_inst0hib_mode_status
    {
        .data_id = DC_ATTR_ID_EPS3_INPUT_STAGE_INST0HIB_MODE_STATUS,
        .p_data_raw = &dc_instance.eps3_input_stage_inst0hib_mode_status,
        .data_size = sizeof(dc_instance.eps3_input_stage_inst0hib_mode_status),
        .data_timeout = 30000U
    },
    // eps3_input_stage_inst0selflock_on
    {
        .data_id = DC_ATTR_ID_EPS3_INPUT_STAGE_INST0SELFLOCK_ON,
        .p_data_raw = &dc_instance.eps3_input_stage_inst0selflock_on,
        .data_size = sizeof(dc_instance.eps3_input_stage_inst0selflock_on),
        .data_timeout = 30000U
    },
    // eps3_input_stage_inst0sp1
    {
        .data_id = DC_ATTR_ID_EPS3_INPUT_STAGE_INST0SP1,
        .p_data_raw = &dc_instance.eps3_input_stage_inst0sp1,
        .data_size = sizeof(dc_instance.eps3_input_stage_inst0sp1),
        .data_timeout = 30000U
    },
    // eps3_input_stage_inst0sp2
    {
        .data_id = DC_ATTR_ID_EPS3_INPUT_STAGE_INST0SP2,
        .p_data_raw = &dc_instance.eps3_input_stage_inst0sp2,
        .data_size = sizeof(dc_instance.eps3_input_stage_inst0sp2),
        .data_timeout = 30000U
    },
    // eps3_input_stage_inst0sp3
    {
        .data_id = DC_ATTR_ID_EPS3_INPUT_STAGE_INST0SP3,
        .p_data_raw = &dc_instance.eps3_input_stage_inst0sp3,
        .data_size = sizeof(dc_instance.eps3_input_stage_inst0sp3),
        .data_timeout = 30000U
    },
    // eps3_input_stage_inst0system_bus
    {
        .data_id = DC_ATTR_ID_EPS3_INPUT_STAGE_INST0SYSTEM_BUS,
        .p_data_raw = &dc_instance.eps3_input_stage_inst0system_bus,
        .data_size = sizeof(dc_instance.eps3_input_stage_inst0system_bus),
        .data_timeout = 30000U
    },
    // eps3_input_stage_inst0bus_7v5
    {
        .data_id = DC_ATTR_ID_EPS3_INPUT_STAGE_INST0BUS_7V5,
        .p_data_raw = &dc_instance.eps3_input_stage_inst0bus_7v5,
        .data_size = sizeof(dc_instance.eps3_input_stage_inst0bus_7v5),
        .data_timeout = 30000U
    },
    // eps3_input_stage_inst0bus_7v5_power_good
    {
        .data_id = DC_ATTR_ID_EPS3_INPUT_STAGE_INST0BUS_7V5_POWER_GOOD,
        .p_data_raw = &dc_instance.eps3_input_stage_inst0bus_7v5_power_good,
        .data_size = sizeof(dc_instance.eps3_input_stage_inst0bus_7v5_power_good),
        .data_timeout = 30000U
    },
    // eps3_input_stage_inst0undervoltage_7v5
    {
        .data_id = DC_ATTR_ID_EPS3_INPUT_STAGE_INST0UNDERVOLTAGE_7V5,
        .p_data_raw = &dc_instance.eps3_input_stage_inst0undervoltage_7v5,
        .data_size = sizeof(dc_instance.eps3_input_stage_inst0undervoltage_7v5),
        .data_timeout = 30000U
    },
    // eps3_input_stage_inst0bus_3v3
    {
        .data_id = DC_ATTR_ID_EPS3_INPUT_STAGE_INST0BUS_3V3,
        .p_data_raw = &dc_instance.eps3_input_stage_inst0bus_3v3,
        .data_size = sizeof(dc_instance.eps3_input_stage_inst0bus_3v3),
        .data_timeout = 30000U
    },
    // eps3_input_stage_inst0undervoltage_3v3
    {
        .data_id = DC_ATTR_ID_EPS3_INPUT_STAGE_INST0UNDERVOLTAGE_3V3,
        .p_data_raw = &dc_instance.eps3_input_stage_inst0undervoltage_3v3,
        .data_size = sizeof(dc_instance.eps3_input_stage_inst0undervoltage_3v3),
        .data_timeout = 30000U
    },
    // eps3_input_stage_inst0_cmd_exec_status_data
    {
        .data_id = DC_ATTR_ID_EPS3_INPUT_STAGE_INST0_CMD_EXEC_STATUS_DATA,
        .p_data_raw = &dc_instance.eps3_input_stage_inst0_cmd_exec_status_data,
        .data_size = sizeof(dc_instance.eps3_input_stage_inst0_cmd_exec_status_data),
        .data_timeout = 40000U
    },
    // magdata
    {
        .data_id = DC_ATTR_ID_MAGDATA,
        .p_data_raw = &dc_instance.magdata,
        .data_size = sizeof(dc_instance.magdata),
        .data_timeout = 5000U
    },
    // wheeldata1
    {
        .data_id = DC_ATTR_ID_WHEELDATA1,
        .p_data_raw = &dc_instance.wheeldata1,
        .data_size = sizeof(dc_instance.wheeldata1),
        .data_timeout = 5000U
    },
    // wheeldata2
    {
        .data_id = DC_ATTR_ID_WHEELDATA2,
        .p_data_raw = &dc_instance.wheeldata2,
        .data_size = sizeof(dc_instance.wheeldata2),
        .data_timeout = 5000U
    },
    // fss1_data
    {
        .data_id = DC_ATTR_ID_FSS1_DATA,
        .p_data_raw = &dc_instance.fss1_data,
        .data_size = sizeof(dc_instance.fss1_data),
        .data_timeout = 5000U
    },
    // fss2_data
    {
        .data_id = DC_ATTR_ID_FSS2_DATA,
        .p_data_raw = &dc_instance.fss2_data,
        .data_size = sizeof(dc_instance.fss2_data),
        .data_timeout = 5000U
    },
    // fss3_data
    {
        .data_id = DC_ATTR_ID_FSS3_DATA,
        .p_data_raw = &dc_instance.fss3_data,
        .data_size = sizeof(dc_instance.fss3_data),
        .data_timeout = 5000U
    },
    // fss4_data
    {
        .data_id = DC_ATTR_ID_FSS4_DATA,
        .p_data_raw = &dc_instance.fss4_data,
        .data_size = sizeof(dc_instance.fss4_data),
        .data_timeout = 5000U
    },
    // fss5_data
    {
        .data_id = DC_ATTR_ID_FSS5_DATA,
        .p_data_raw = &dc_instance.fss5_data,
        .data_size = sizeof(dc_instance.fss5_data),
        .data_timeout = 5000U
    },
    // adcs_fss_data
    {
        .data_id = DC_ATTR_ID_ADCS_FSS_DATA,
        .p_data_raw = &dc_instance.adcs_fss_data,
        .data_size = sizeof(dc_instance.adcs_fss_data),
        .data_timeout = 5000U
    },
    // adcs_mag_data
    {
        .data_id = DC_ATTR_ID_ADCS_MAG_DATA,
        .p_data_raw = &dc_instance.adcs_mag_data,
        .data_size = sizeof(dc_instance.adcs_mag_data),
        .data_timeout = 5000U
    },
    // adcs_imu_data
    {
        .data_id = DC_ATTR_ID_ADCS_IMU_DATA,
        .p_data_raw = &dc_instance.adcs_imu_data,
        .data_size = sizeof(dc_instance.adcs_imu_data),
        .data_timeout = 5000U
    },
    // adcs_rw_data
    {
        .data_id = DC_ATTR_ID_ADCS_RW_DATA,
        .p_data_raw = &dc_instance.adcs_rw_data,
        .data_size = sizeof(dc_instance.adcs_rw_data),
        .data_timeout = 5000U
    },
    // adcs_mtq_data
    {
        .data_id = DC_ATTR_ID_ADCS_MTQ_DATA,
        .p_data_raw = &dc_instance.adcs_mtq_data,
        .data_size = sizeof(dc_instance.adcs_mtq_data),
        .data_timeout = 5000U
    },
    // eps2_bp_inst0_sbpmodechange_data
    {
        .data_id = DC_ATTR_ID_EPS2_BP_INST0_SBPMODECHANGE_DATA,
        .p_data_raw = &dc_instance.eps2_bp_inst0_sbpmodechange_data,
        .data_size = sizeof(dc_instance.eps2_bp_inst0_sbpmodechange_data),
        .data_timeout = 5000U
    },
    // eps2_bp_bpmodesmrollingtrace_data
    {
        .data_id = DC_ATTR_ID_EPS2_BP_BPMODESMROLLINGTRACE_DATA,
        .p_data_raw = &dc_instance.eps2_bp_bpmodesmrollingtrace_data,
        .data_size = sizeof(dc_instance.eps2_bp_bpmodesmrollingtrace_data),
        .data_timeout = 5000U
    },
    // eps2_pdm_sbsede_conopsmode_data
    {
        .data_id = DC_ATTR_ID_EPS2_PDM_SBSEDE_CONOPSMODE_DATA,
        .p_data_raw = &dc_instance.eps2_pdm_sbsede_conopsmode_data,
        .data_size = sizeof(dc_instance.eps2_pdm_sbsede_conopsmode_data),
        .data_timeout = 5000U
    },
    // eps2_pdm_sbsed_bitmask_data
    {
        .data_id = DC_ATTR_ID_EPS2_PDM_SBSED_BITMASK_DATA,
        .p_data_raw = &dc_instance.eps2_pdm_sbsed_bitmask_data,
        .data_size = sizeof(dc_instance.eps2_pdm_sbsed_bitmask_data),
        .data_timeout = 5000U
    },
    // eps2_pdm_sbasicsettings_data
    {
        .data_id = DC_ATTR_ID_EPS2_PDM_SBASICSETTINGS_DATA,
        .p_data_raw = &dc_instance.eps2_pdm_sbasicsettings_data,
        .data_size = sizeof(dc_instance.eps2_pdm_sbasicsettings_data),
        .data_timeout = 5000U
    },
    // eps2_pdm_setbasicsettings_data
    {
        .data_id = DC_ATTR_ID_EPS2_PDM_SETBASICSETTINGS_DATA,
        .p_data_raw = &dc_instance.eps2_pdm_setbasicsettings_data,
        .data_size = sizeof(dc_instance.eps2_pdm_setbasicsettings_data),
        .data_timeout = 5000U
    },
    // eps2_pdm_sbs_geterror_data
    {
        .data_id = DC_ATTR_ID_EPS2_PDM_SBS_GETERROR_DATA,
        .p_data_raw = &dc_instance.eps2_pdm_sbs_geterror_data,
        .data_size = sizeof(dc_instance.eps2_pdm_sbs_geterror_data),
        .data_timeout = 5000U
    },
    // eps2inst0_pdm_sbasicsettings_data
    {
        .data_id = DC_ATTR_ID_EPS2INST0_PDM_SBASICSETTINGS_DATA,
        .p_data_raw = &dc_instance.eps2inst0_pdm_sbasicsettings_data,
        .data_size = sizeof(dc_instance.eps2inst0_pdm_sbasicsettings_data),
        .data_timeout = 5000U
    },
    // vn100_data
    {
        .data_id = DC_ATTR_ID_VN100_DATA,
        .p_data_raw = &dc_instance.vn100_data,
        .data_size = sizeof(dc_instance.vn100_data),
        .data_timeout = 5000U
    },
    // mpu6050_1_data
    {
        .data_id = DC_ATTR_ID_MPU6050_1_DATA,
        .p_data_raw = &dc_instance.mpu6050_1_data,
        .data_size = sizeof(dc_instance.mpu6050_1_data),
        .data_timeout = 5000U
    },
    // mpu6050_2_data
    {
        .data_id = DC_ATTR_ID_MPU6050_2_DATA,
        .p_data_raw = &dc_instance.mpu6050_2_data,
        .data_size = sizeof(dc_instance.mpu6050_2_data),
        .data_timeout = 5000U
    },
    // mtq_all_cmd_data
    {
        .data_id = DC_ATTR_ID_MTQ_ALL_CMD_DATA,
        .p_data_raw = &dc_instance.mtq_all_cmd_data,
        .data_size = sizeof(dc_instance.mtq_all_cmd_data),
        .data_timeout = 5000U
    },
    // eps2inst0_bp_sdiagerrcounter2_data
    {
        .data_id = DC_ATTR_ID_EPS2INST0_BP_SDIAGERRCOUNTER2_DATA,
        .p_data_raw = &dc_instance.eps2inst0_bp_sdiagerrcounter2_data,
        .data_size = sizeof(dc_instance.eps2inst0_bp_sdiagerrcounter2_data),
        .data_timeout = 5000U
    },
    // eps2inst0_bp_getmainapperrcounters2_data
    {
        .data_id = DC_ATTR_ID_EPS2INST0_BP_GETMAINAPPERRCOUNTERS2_DATA,
        .p_data_raw = &dc_instance.eps2inst0_bp_getmainapperrcounters2_data,
        .data_size = sizeof(dc_instance.eps2inst0_bp_getmainapperrcounters2_data),
        .data_timeout = 5000U
    },
    // ina_data
    {
        .data_id = DC_ATTR_ID_INA_DATA,
        .p_data_raw = &dc_instance.ina_data,
        .data_size = sizeof(dc_instance.ina_data),
        .data_timeout = 5000U
    },
    // ang_data
    {
        .data_id = DC_ATTR_ID_ANG_DATA,
        .p_data_raw = &dc_instance.ang_data,
        .data_size = sizeof(dc_instance.ang_data),
        .data_timeout = 5000U
    },
    // camera_mode_data
    {
        .data_id = DC_ATTR_ID_CAMERA_MODE_DATA,
        .p_data_raw = &dc_instance.camera_mode_data,
        .data_size = sizeof(dc_instance.camera_mode_data),
        .data_timeout = 5000U
    },
    // adcs_mode
    {
        .data_id = DC_ATTR_ID_ADCS_MODE,
        .p_data_raw = &dc_instance.adcs_mode,
        .data_size = sizeof(dc_instance.adcs_mode),
        .data_timeout = 5000U
    },
    // adcs_flag_alg
    {
        .data_id = DC_ATTR_ID_ADCS_FLAG_ALG,
        .p_data_raw = &dc_instance.adcs_flag_alg,
        .data_size = sizeof(dc_instance.adcs_flag_alg),
        .data_timeout = 5000U
    },
    // adcs_result
    {
        .data_id = DC_ATTR_ID_ADCS_RESULT,
        .p_data_raw = &dc_instance.adcs_result,
        .data_size = sizeof(dc_instance.adcs_result),
        .data_timeout = 5000U
    },
    // adcs_hw
    {
        .data_id = DC_ATTR_ID_ADCS_HW,
        .p_data_raw = &dc_instance.adcs_hw,
        .data_size = sizeof(dc_instance.adcs_hw),
        .data_timeout = 5000U
    },
    // tc_flag
    {
        .data_id = DC_ATTR_ID_TC_FLAG,
        .p_data_raw = &dc_instance.tc_flag,
        .data_size = sizeof(dc_instance.tc_flag),
        .data_timeout = 5000U
    }
};

/**********************************************************************
 *
 *  Public functions
 *
 **********************************************************************/

/*!
* @brief Init routine for the DataCache component
*/
void dc_init(void)
{
    // timestamps are assumed to be 32-bits in this code and if this conditions is not met,
    // that should be signalled to the user
    DC_ASSERT(sizeof(dc_data_rt[0U].last_update_tstamp) == 4U);

    for (uint16_t i = 0; i < DC_DID_MAX; i++)
    {
        dc_data_rt[i].last_input_type = DC_DATA_INPUT_INTERNAL;
        dc_data_rt[i].last_data_status = DC_NOT_INITIALIZED;
        dc_data_rt[i].last_update_tstamp = 0U;

#ifdef DC_DATA_ACCESS_SYNC_ENABLED
        char lock_name[16U];
        sprintf(lock_name, "dc_lock_%03d", i);
        dc_data_rt[i].data_lock = dc_cfg_lock_new(lock_name);
#endif
    }

    dc_initialized = TRUE;

    // call system-specific init to schedule the task execution...
    dc_cfg_init();
}

/*!
* @brief Main Data Cache task function
* @warning Should not be called too often because it locks the data in order to modify it and
*          could interfere with the set/get operations called by DC clients.
*/
void dc_task(void)
{
    if (TRUE == dc_initialized)
    {
        for (uint16_t i = 0U; i < sizeof(dc_data_rt) / sizeof(dc_data_rt[0]); i++)
        {
            // if timeout is 0, tracking is not performed at all
            if ((dc_data_cfg[i].data_timeout > 0U) &&
                (DC_DATA_STATUS_OK == dc_data_rt[i].last_data_status))
            {
                uint32_t current_tstamp = dc_cfg_get_sys_timestamp();
                uint32_t delta = 0U;

                DC_DATA_LOCK(i);

                if (current_tstamp >= dc_data_rt[i].last_update_tstamp)
                {
                    delta = current_tstamp - dc_data_rt[i].last_update_tstamp;
                }
                else
                {
                    // if the last_update_tstamp type size is changed, the UINT_MAX value below has to be updated to
                    // properly calculate roll-over deltas
                    delta = current_tstamp + (UINT_MAX - dc_data_rt[i].last_update_tstamp);
                }

                if (delta >= dc_data_cfg[i].data_timeout)
                    dc_data_rt[i].last_data_status = DC_DATA_STATUS_TOUT;

                DC_DATA_UNLOCK(i);
            }
        }
    }
}

dc_data_status_t dc_get_raw_data(const dc_did_id id,
                                 void * const p_data,
                                 const uint32_t user_buf_size,
                                 const uint32_t start_offset,
                                 const uint32_t bytes_to_read)
{
    dc_data_status_t res = DC_NOT_INITIALIZED;

    DC_ASSERT(TRUE == dc_initialized);
    DC_ASSERT(id < DC_DID_MAX);
    DC_ASSERT(user_buf_size >= bytes_to_read);
    DC_ASSERT(start_offset + bytes_to_read <= dc_data_cfg[id].data_size);

    DC_DATA_LOCK(id);

    // perform data copy
    (void) memcpy(p_data, &((const uint8_t *) dc_data_cfg[id].p_data_raw)[start_offset], bytes_to_read);

    res = dc_data_rt[id].last_data_status;

    DC_DATA_UNLOCK(id);

    return res;
}

void dc_set_raw_data(const dc_data_input_t input_type, const dc_did_id id, const void * const p_new_data, const uint32_t data_size)
{
    DC_ASSERT(TRUE == dc_initialized);
    DC_ASSERT(id < DC_DID_MAX);
    DC_ASSERT(input_type < DC_DATA_INPUT_MAX);
    DC_ASSERT(data_size == dc_data_cfg[id].data_size);

    // internal data cannot be fed while in sim mode
    if ((DC_DATA_INPUT_INTERNAL == input_type) && (DC_DATA_INPUT_EXTERNAL == dc_data_rt[id].last_input_type))
        return;

    DC_DATA_LOCK(id);

    // perform data copy to local buffer
    (void) memcpy(dc_data_cfg[id].p_data_raw, p_new_data, dc_data_cfg[id].data_size);
    // update local data_status and timestamp
    dc_data_rt[id].last_input_type = input_type;
    dc_data_rt[id].last_data_status = DC_DATA_STATUS_OK;
    dc_data_rt[id].last_update_tstamp = dc_cfg_get_sys_timestamp();

    DC_DATA_UNLOCK(id);
}

uint32_t dc_get_data_size(const dc_did_id id)
{
    DC_ASSERT(TRUE == dc_initialized);
    DC_ASSERT(id < DC_DID_MAX);

    return dc_data_cfg[id].data_size;
}

dc_did_id dc_get_index_by_data_id(const uint16_t data_id)
{
    dc_did_id int_id = DC_DID_MAX;

    for (uint16_t idx = 0U; idx < DC_DID_MAX; idx++)
    {
        if (data_id == dc_data_cfg[idx].data_id)
        {
            int_id = idx;
            break;
        }
    }

    return int_id;
}

void dc_set_input_mode(const dc_did_id id, dc_data_input_t input_type)
{
    DC_ASSERT(id < DC_DID_MAX);
    DC_ASSERT(input_type < DC_DATA_INPUT_MAX);

    switch (id)
    {
        case DC_DID_MAX:
        {
            for (uint8_t idx = 0U; idx < DC_DID_MAX; idx++)
            {
                dc_data_rt[idx].last_input_type = input_type;
            }

            break;
        }

        default:
        {
            dc_data_rt[id].last_input_type = input_type;

            break;
        }
    }
}

dc_data_status_t dc_get_obc_0_data(DATA_CACHE_OBC_0_t * const p_data)
{
    return dc_get_raw_data(DC_DID_OBC_0_DATA,
                           p_data,
                           sizeof(DATA_CACHE_OBC_0_t),
                           0U,
                           sizeof(DATA_CACHE_OBC_0_t));
}

void dc_set_obc_0_data(DATA_CACHE_OBC_0_t * const p_new_data)
{
    dc_set_raw_data(DC_DATA_INPUT_INTERNAL, DC_DID_OBC_0_DATA, p_new_data, sizeof(DATA_CACHE_OBC_0_t));
}

dc_data_status_t dc_get_adcs_0_data(DATA_CACHE_ADCS_0_t * const p_data)
{
    return dc_get_raw_data(DC_DID_ADCS_0_DATA,
                           p_data,
                           sizeof(DATA_CACHE_ADCS_0_t),
                           0U,
                           sizeof(DATA_CACHE_ADCS_0_t));
}

void dc_set_adcs_0_data(DATA_CACHE_ADCS_0_t * const p_new_data)
{
    dc_set_raw_data(DC_DATA_INPUT_INTERNAL, DC_DID_ADCS_0_DATA, p_new_data, sizeof(DATA_CACHE_ADCS_0_t));
}

dc_data_status_t dc_get_adcs_1_data(DATA_CACHE_ADCS_1_t * const p_data)
{
    return dc_get_raw_data(DC_DID_ADCS_1_DATA,
                           p_data,
                           sizeof(DATA_CACHE_ADCS_1_t),
                           0U,
                           sizeof(DATA_CACHE_ADCS_1_t));
}

void dc_set_adcs_1_data(DATA_CACHE_ADCS_1_t * const p_new_data)
{
    dc_set_raw_data(DC_DATA_INPUT_INTERNAL, DC_DID_ADCS_1_DATA, p_new_data, sizeof(DATA_CACHE_ADCS_1_t));
}

dc_data_status_t dc_get_adcs_2_data(DATA_CACHE_ADCS_2_t * const p_data)
{
    return dc_get_raw_data(DC_DID_ADCS_2_DATA,
                           p_data,
                           sizeof(DATA_CACHE_ADCS_2_t),
                           0U,
                           sizeof(DATA_CACHE_ADCS_2_t));
}

void dc_set_adcs_2_data(DATA_CACHE_ADCS_2_t * const p_new_data)
{
    dc_set_raw_data(DC_DATA_INPUT_INTERNAL, DC_DID_ADCS_2_DATA, p_new_data, sizeof(DATA_CACHE_ADCS_2_t));
}

dc_data_status_t dc_get_eps_0_data(DATA_CACHE_EPS_0_t * const p_data)
{
    return dc_get_raw_data(DC_DID_EPS_0_DATA,
                           p_data,
                           sizeof(DATA_CACHE_EPS_0_t),
                           0U,
                           sizeof(DATA_CACHE_EPS_0_t));
}

void dc_set_eps_0_data(DATA_CACHE_EPS_0_t * const p_new_data)
{
    dc_set_raw_data(DC_DATA_INPUT_INTERNAL, DC_DID_EPS_0_DATA, p_new_data, sizeof(DATA_CACHE_EPS_0_t));
}

dc_data_status_t dc_get_ssp_0_data(DATA_CACHE_SSP_0_Telemetry_t * const p_data)
{
    return dc_get_raw_data(DC_DID_SSP_0_DATA,
                           p_data,
                           sizeof(DATA_CACHE_SSP_0_Telemetry_t),
                           0U,
                           sizeof(DATA_CACHE_SSP_0_Telemetry_t));
}

void dc_set_ssp_0_data(DATA_CACHE_SSP_0_Telemetry_t * const p_new_data)
{
    dc_set_raw_data(DC_DATA_INPUT_INTERNAL, DC_DID_SSP_0_DATA, p_new_data, sizeof(DATA_CACHE_SSP_0_Telemetry_t));
}

dc_data_status_t dc_get_ssp_1_data(DATA_CACHE_SSP_1_Telemetry_t * const p_data)
{
    return dc_get_raw_data(DC_DID_SSP_1_DATA,
                           p_data,
                           sizeof(DATA_CACHE_SSP_1_Telemetry_t),
                           0U,
                           sizeof(DATA_CACHE_SSP_1_Telemetry_t));
}

void dc_set_ssp_1_data(DATA_CACHE_SSP_1_Telemetry_t * const p_new_data)
{
    dc_set_raw_data(DC_DATA_INPUT_INTERNAL, DC_DID_SSP_1_DATA, p_new_data, sizeof(DATA_CACHE_SSP_1_Telemetry_t));
}

dc_data_status_t dc_get_ssp_2_data(DATA_CACHE_SSP_2_Telemetry_t * const p_data)
{
    return dc_get_raw_data(DC_DID_SSP_2_DATA,
                           p_data,
                           sizeof(DATA_CACHE_SSP_2_Telemetry_t),
                           0U,
                           sizeof(DATA_CACHE_SSP_2_Telemetry_t));
}

void dc_set_ssp_2_data(DATA_CACHE_SSP_2_Telemetry_t * const p_new_data)
{
    dc_set_raw_data(DC_DATA_INPUT_INTERNAL, DC_DID_SSP_2_DATA, p_new_data, sizeof(DATA_CACHE_SSP_2_Telemetry_t));
}

dc_data_status_t dc_get_ssp_3_data(DATA_CACHE_SSP_3_Telemetry_t * const p_data)
{
    return dc_get_raw_data(DC_DID_SSP_3_DATA,
                           p_data,
                           sizeof(DATA_CACHE_SSP_3_Telemetry_t),
                           0U,
                           sizeof(DATA_CACHE_SSP_3_Telemetry_t));
}

void dc_set_ssp_3_data(DATA_CACHE_SSP_3_Telemetry_t * const p_new_data)
{
    dc_set_raw_data(DC_DATA_INPUT_INTERNAL, DC_DID_SSP_3_DATA, p_new_data, sizeof(DATA_CACHE_SSP_3_Telemetry_t));
}

dc_data_status_t dc_get_aocs_cntrl_tlm_data(DATA_CACHE_AOCS_CNTRL_TLM_t * const p_data)
{
    return dc_get_raw_data(DC_DID_AOCS_CNTRL_TLM_DATA,
                           p_data,
                           sizeof(DATA_CACHE_AOCS_CNTRL_TLM_t),
                           0U,
                           sizeof(DATA_CACHE_AOCS_CNTRL_TLM_t));
}

void dc_set_aocs_cntrl_tlm_data(DATA_CACHE_AOCS_CNTRL_TLM_t * const p_new_data)
{
    dc_set_raw_data(DC_DATA_INPUT_INTERNAL, DC_DID_AOCS_CNTRL_TLM_DATA, p_new_data, sizeof(DATA_CACHE_AOCS_CNTRL_TLM_t));
}

dc_data_status_t dc_get_aocs_cntrl_sys_state_data(DATA_CACHE_AOCS_CNTRL_SYS_STATE_t * const p_data)
{
    return dc_get_raw_data(DC_DID_AOCS_CNTRL_SYS_STATE_DATA,
                           p_data,
                           sizeof(DATA_CACHE_AOCS_CNTRL_SYS_STATE_t),
                           0U,
                           sizeof(DATA_CACHE_AOCS_CNTRL_SYS_STATE_t));
}

void dc_set_aocs_cntrl_sys_state_data(DATA_CACHE_AOCS_CNTRL_SYS_STATE_t * const p_new_data)
{
    dc_set_raw_data(DC_DATA_INPUT_INTERNAL, DC_DID_AOCS_CNTRL_SYS_STATE_DATA, p_new_data, sizeof(DATA_CACHE_AOCS_CNTRL_SYS_STATE_t));
}

dc_data_status_t dc_get_aocs_cntrl_ref_params_data(DATA_CACHE_AOCS_CNTRL_REF_PARAMS_t * const p_data)
{
    return dc_get_raw_data(DC_DID_AOCS_CNTRL_REF_PARAMS_DATA,
                           p_data,
                           sizeof(DATA_CACHE_AOCS_CNTRL_REF_PARAMS_t),
                           0U,
                           sizeof(DATA_CACHE_AOCS_CNTRL_REF_PARAMS_t));
}

void dc_set_aocs_cntrl_ref_params_data(DATA_CACHE_AOCS_CNTRL_REF_PARAMS_t * const p_new_data)
{
    dc_set_raw_data(DC_DATA_INPUT_INTERNAL, DC_DID_AOCS_CNTRL_REF_PARAMS_DATA, p_new_data, sizeof(DATA_CACHE_AOCS_CNTRL_REF_PARAMS_t));
}

dc_data_status_t dc_get_sensor_gyro_sensor_frame_data(DATA_CACHE_SENSOR_GYRO_SENSOR_FRAME_t * const p_data)
{
    return dc_get_raw_data(DC_DID_SENSOR_GYRO_SENSOR_FRAME_DATA,
                           p_data,
                           sizeof(DATA_CACHE_SENSOR_GYRO_SENSOR_FRAME_t),
                           0U,
                           sizeof(DATA_CACHE_SENSOR_GYRO_SENSOR_FRAME_t));
}

void dc_set_sensor_gyro_sensor_frame_data(DATA_CACHE_SENSOR_GYRO_SENSOR_FRAME_t * const p_new_data)
{
    dc_set_raw_data(DC_DATA_INPUT_INTERNAL, DC_DID_SENSOR_GYRO_SENSOR_FRAME_DATA, p_new_data, sizeof(DATA_CACHE_SENSOR_GYRO_SENSOR_FRAME_t));
}

dc_data_status_t dc_get_sensor_gyro_body_frame_data(DATA_CACHE_SENSOR_GYRO_BODY_FRAME_t * const p_data)
{
    return dc_get_raw_data(DC_DID_SENSOR_GYRO_BODY_FRAME_DATA,
                           p_data,
                           sizeof(DATA_CACHE_SENSOR_GYRO_BODY_FRAME_t),
                           0U,
                           sizeof(DATA_CACHE_SENSOR_GYRO_BODY_FRAME_t));
}

void dc_set_sensor_gyro_body_frame_data(DATA_CACHE_SENSOR_GYRO_BODY_FRAME_t * const p_new_data)
{
    dc_set_raw_data(DC_DATA_INPUT_INTERNAL, DC_DID_SENSOR_GYRO_BODY_FRAME_DATA, p_new_data, sizeof(DATA_CACHE_SENSOR_GYRO_BODY_FRAME_t));
}

dc_data_status_t dc_get_sensor_mag_primary_sensor_frame_data(DATA_CACHE_SENSOR_MAG_PRIMARY_SENSOR_FRAME_t * const p_data)
{
    return dc_get_raw_data(DC_DID_SENSOR_MAG_PRIMARY_SENSOR_FRAME_DATA,
                           p_data,
                           sizeof(DATA_CACHE_SENSOR_MAG_PRIMARY_SENSOR_FRAME_t),
                           0U,
                           sizeof(DATA_CACHE_SENSOR_MAG_PRIMARY_SENSOR_FRAME_t));
}

void dc_set_sensor_mag_primary_sensor_frame_data(DATA_CACHE_SENSOR_MAG_PRIMARY_SENSOR_FRAME_t * const p_new_data)
{
    dc_set_raw_data(DC_DATA_INPUT_INTERNAL, DC_DID_SENSOR_MAG_PRIMARY_SENSOR_FRAME_DATA, p_new_data, sizeof(DATA_CACHE_SENSOR_MAG_PRIMARY_SENSOR_FRAME_t));
}

dc_data_status_t dc_get_sensor_mag_primary_body_frame_data(DATA_CACHE_SENSOR_MAG_PRIMARY_BODY_FRAME_t * const p_data)
{
    return dc_get_raw_data(DC_DID_SENSOR_MAG_PRIMARY_BODY_FRAME_DATA,
                           p_data,
                           sizeof(DATA_CACHE_SENSOR_MAG_PRIMARY_BODY_FRAME_t),
                           0U,
                           sizeof(DATA_CACHE_SENSOR_MAG_PRIMARY_BODY_FRAME_t));
}

void dc_set_sensor_mag_primary_body_frame_data(DATA_CACHE_SENSOR_MAG_PRIMARY_BODY_FRAME_t * const p_new_data)
{
    dc_set_raw_data(DC_DATA_INPUT_INTERNAL, DC_DID_SENSOR_MAG_PRIMARY_BODY_FRAME_DATA, p_new_data, sizeof(DATA_CACHE_SENSOR_MAG_PRIMARY_BODY_FRAME_t));
}

dc_data_status_t dc_get_sensor_mag_secondary_sensor_frame_data(DATA_CACHE_SENSOR_MAG_SECONDARY_SENSOR_FRAME_t * const p_data)
{
    return dc_get_raw_data(DC_DID_SENSOR_MAG_SECONDARY_SENSOR_FRAME_DATA,
                           p_data,
                           sizeof(DATA_CACHE_SENSOR_MAG_SECONDARY_SENSOR_FRAME_t),
                           0U,
                           sizeof(DATA_CACHE_SENSOR_MAG_SECONDARY_SENSOR_FRAME_t));
}

void dc_set_sensor_mag_secondary_sensor_frame_data(DATA_CACHE_SENSOR_MAG_SECONDARY_SENSOR_FRAME_t * const p_new_data)
{
    dc_set_raw_data(DC_DATA_INPUT_INTERNAL, DC_DID_SENSOR_MAG_SECONDARY_SENSOR_FRAME_DATA, p_new_data, sizeof(DATA_CACHE_SENSOR_MAG_SECONDARY_SENSOR_FRAME_t));
}

dc_data_status_t dc_get_sensor_mag_secondary_body_frame_data(DATA_CACHE_SENSOR_MAG_SECONDARY_BODY_FRAME_t * const p_data)
{
    return dc_get_raw_data(DC_DID_SENSOR_MAG_SECONDARY_BODY_FRAME_DATA,
                           p_data,
                           sizeof(DATA_CACHE_SENSOR_MAG_SECONDARY_BODY_FRAME_t),
                           0U,
                           sizeof(DATA_CACHE_SENSOR_MAG_SECONDARY_BODY_FRAME_t));
}

void dc_set_sensor_mag_secondary_body_frame_data(DATA_CACHE_SENSOR_MAG_SECONDARY_BODY_FRAME_t * const p_new_data)
{
    dc_set_raw_data(DC_DATA_INPUT_INTERNAL, DC_DID_SENSOR_MAG_SECONDARY_BODY_FRAME_DATA, p_new_data, sizeof(DATA_CACHE_SENSOR_MAG_SECONDARY_BODY_FRAME_t));
}

dc_data_status_t dc_get_sensor_coarse_sun_sensor_frame_data(DATA_CACHE_SENSOR_COARSE_SUN_SENSOR_FRAME_t * const p_data)
{
    return dc_get_raw_data(DC_DID_SENSOR_COARSE_SUN_SENSOR_FRAME_DATA,
                           p_data,
                           sizeof(DATA_CACHE_SENSOR_COARSE_SUN_SENSOR_FRAME_t),
                           0U,
                           sizeof(DATA_CACHE_SENSOR_COARSE_SUN_SENSOR_FRAME_t));
}

void dc_set_sensor_coarse_sun_sensor_frame_data(DATA_CACHE_SENSOR_COARSE_SUN_SENSOR_FRAME_t * const p_new_data)
{
    dc_set_raw_data(DC_DATA_INPUT_INTERNAL, DC_DID_SENSOR_COARSE_SUN_SENSOR_FRAME_DATA, p_new_data, sizeof(DATA_CACHE_SENSOR_COARSE_SUN_SENSOR_FRAME_t));
}

dc_data_status_t dc_get_sensor_coarse_sun_body_frame_data(DATA_CACHE_SENSOR_COARSE_SUN_BODY_FRAME_t * const p_data)
{
    return dc_get_raw_data(DC_DID_SENSOR_COARSE_SUN_BODY_FRAME_DATA,
                           p_data,
                           sizeof(DATA_CACHE_SENSOR_COARSE_SUN_BODY_FRAME_t),
                           0U,
                           sizeof(DATA_CACHE_SENSOR_COARSE_SUN_BODY_FRAME_t));
}

void dc_set_sensor_coarse_sun_body_frame_data(DATA_CACHE_SENSOR_COARSE_SUN_BODY_FRAME_t * const p_new_data)
{
    dc_set_raw_data(DC_DATA_INPUT_INTERNAL, DC_DID_SENSOR_COARSE_SUN_BODY_FRAME_DATA, p_new_data, sizeof(DATA_CACHE_SENSOR_COARSE_SUN_BODY_FRAME_t));
}

dc_data_status_t dc_get_sensor_panel_temp_sensor_frame_data(DATA_CACHE_SENSOR_PANEL_TEMP_SENSOR_FRAME_t * const p_data)
{
    return dc_get_raw_data(DC_DID_SENSOR_PANEL_TEMP_SENSOR_FRAME_DATA,
                           p_data,
                           sizeof(DATA_CACHE_SENSOR_PANEL_TEMP_SENSOR_FRAME_t),
                           0U,
                           sizeof(DATA_CACHE_SENSOR_PANEL_TEMP_SENSOR_FRAME_t));
}

void dc_set_sensor_panel_temp_sensor_frame_data(DATA_CACHE_SENSOR_PANEL_TEMP_SENSOR_FRAME_t * const p_new_data)
{
    dc_set_raw_data(DC_DATA_INPUT_INTERNAL, DC_DID_SENSOR_PANEL_TEMP_SENSOR_FRAME_DATA, p_new_data, sizeof(DATA_CACHE_SENSOR_PANEL_TEMP_SENSOR_FRAME_t));
}

dc_data_status_t dc_get_sensor_panel_temp_body_frame_data(DATA_CACHE_SENSOR_PANEL_TEMP_BODY_FRAME_t * const p_data)
{
    return dc_get_raw_data(DC_DID_SENSOR_PANEL_TEMP_BODY_FRAME_DATA,
                           p_data,
                           sizeof(DATA_CACHE_SENSOR_PANEL_TEMP_BODY_FRAME_t),
                           0U,
                           sizeof(DATA_CACHE_SENSOR_PANEL_TEMP_BODY_FRAME_t));
}

void dc_set_sensor_panel_temp_body_frame_data(DATA_CACHE_SENSOR_PANEL_TEMP_BODY_FRAME_t * const p_new_data)
{
    dc_set_raw_data(DC_DATA_INPUT_INTERNAL, DC_DID_SENSOR_PANEL_TEMP_BODY_FRAME_DATA, p_new_data, sizeof(DATA_CACHE_SENSOR_PANEL_TEMP_BODY_FRAME_t));
}

dc_data_status_t dc_get_sensor_gyro_temp_sensor_frame_data(DATA_CACHE_SENSOR_GYRO_TEMP_SENSOR_FRAME_t * const p_data)
{
    return dc_get_raw_data(DC_DID_SENSOR_GYRO_TEMP_SENSOR_FRAME_DATA,
                           p_data,
                           sizeof(DATA_CACHE_SENSOR_GYRO_TEMP_SENSOR_FRAME_t),
                           0U,
                           sizeof(DATA_CACHE_SENSOR_GYRO_TEMP_SENSOR_FRAME_t));
}

void dc_set_sensor_gyro_temp_sensor_frame_data(DATA_CACHE_SENSOR_GYRO_TEMP_SENSOR_FRAME_t * const p_new_data)
{
    dc_set_raw_data(DC_DATA_INPUT_INTERNAL, DC_DID_SENSOR_GYRO_TEMP_SENSOR_FRAME_DATA, p_new_data, sizeof(DATA_CACHE_SENSOR_GYRO_TEMP_SENSOR_FRAME_t));
}

dc_data_status_t dc_get_sensor_gyro_temp_body_frame_data(DATA_CACHE_SENSOR_GYRO_TEMP_BODY_FRAME_t * const p_data)
{
    return dc_get_raw_data(DC_DID_SENSOR_GYRO_TEMP_BODY_FRAME_DATA,
                           p_data,
                           sizeof(DATA_CACHE_SENSOR_GYRO_TEMP_BODY_FRAME_t),
                           0U,
                           sizeof(DATA_CACHE_SENSOR_GYRO_TEMP_BODY_FRAME_t));
}

void dc_set_sensor_gyro_temp_body_frame_data(DATA_CACHE_SENSOR_GYRO_TEMP_BODY_FRAME_t * const p_new_data)
{
    dc_set_raw_data(DC_DATA_INPUT_INTERNAL, DC_DID_SENSOR_GYRO_TEMP_BODY_FRAME_DATA, p_new_data, sizeof(DATA_CACHE_SENSOR_GYRO_TEMP_BODY_FRAME_t));
}

dc_data_status_t dc_get_actuator_mtq_values_data(DATA_CACHE_ACTUATOR_MTQ_VALUES_t * const p_data)
{
    return dc_get_raw_data(DC_DID_ACTUATOR_MTQ_VALUES_DATA,
                           p_data,
                           sizeof(DATA_CACHE_ACTUATOR_MTQ_VALUES_t),
                           0U,
                           sizeof(DATA_CACHE_ACTUATOR_MTQ_VALUES_t));
}

void dc_set_actuator_mtq_values_data(DATA_CACHE_ACTUATOR_MTQ_VALUES_t * const p_new_data)
{
    dc_set_raw_data(DC_DATA_INPUT_INTERNAL, DC_DID_ACTUATOR_MTQ_VALUES_DATA, p_new_data, sizeof(DATA_CACHE_ACTUATOR_MTQ_VALUES_t));
}

dc_data_status_t dc_get_actuator_torque_values_data(DATA_CACHE_ACTUATOR_TORQUE_VALUES_t * const p_data)
{
    return dc_get_raw_data(DC_DID_ACTUATOR_TORQUE_VALUES_DATA,
                           p_data,
                           sizeof(DATA_CACHE_ACTUATOR_TORQUE_VALUES_t),
                           0U,
                           sizeof(DATA_CACHE_ACTUATOR_TORQUE_VALUES_t));
}

void dc_set_actuator_torque_values_data(DATA_CACHE_ACTUATOR_TORQUE_VALUES_t * const p_new_data)
{
    dc_set_raw_data(DC_DATA_INPUT_INTERNAL, DC_DID_ACTUATOR_TORQUE_VALUES_DATA, p_new_data, sizeof(DATA_CACHE_ACTUATOR_TORQUE_VALUES_t));
}

dc_data_status_t dc_get_adcs_3_data(DATA_CACHE_ADCS_3_t * const p_data)
{
    return dc_get_raw_data(DC_DID_ADCS_3_DATA,
                           p_data,
                           sizeof(DATA_CACHE_ADCS_3_t),
                           0U,
                           sizeof(DATA_CACHE_ADCS_3_t));
}

void dc_set_adcs_3_data(DATA_CACHE_ADCS_3_t * const p_new_data)
{
    dc_set_raw_data(DC_DATA_INPUT_INTERNAL, DC_DID_ADCS_3_DATA, p_new_data, sizeof(DATA_CACHE_ADCS_3_t));
}

dc_data_status_t dc_get_adcs_4_data(DATA_CACHE_ADCS_4_t * const p_data)
{
    return dc_get_raw_data(DC_DID_ADCS_4_DATA,
                           p_data,
                           sizeof(DATA_CACHE_ADCS_4_t),
                           0U,
                           sizeof(DATA_CACHE_ADCS_4_t));
}

void dc_set_adcs_4_data(DATA_CACHE_ADCS_4_t * const p_new_data)
{
    dc_set_raw_data(DC_DATA_INPUT_INTERNAL, DC_DID_ADCS_4_DATA, p_new_data, sizeof(DATA_CACHE_ADCS_4_t));
}

dc_data_status_t dc_get_eps_9_data(DATA_CACHE_EPS_9_t * const p_data)
{
    return dc_get_raw_data(DC_DID_EPS_9_DATA,
                           p_data,
                           sizeof(DATA_CACHE_EPS_9_t),
                           0U,
                           sizeof(DATA_CACHE_EPS_9_t));
}

void dc_set_eps_9_data(DATA_CACHE_EPS_9_t * const p_new_data)
{
    dc_set_raw_data(DC_DATA_INPUT_INTERNAL, DC_DID_EPS_9_DATA, p_new_data, sizeof(DATA_CACHE_EPS_9_t));
}

dc_data_status_t dc_get_eps_10_data(DATA_CACHE_EPS_10_t * const p_data)
{
    return dc_get_raw_data(DC_DID_EPS_10_DATA,
                           p_data,
                           sizeof(DATA_CACHE_EPS_10_t),
                           0U,
                           sizeof(DATA_CACHE_EPS_10_t));
}

void dc_set_eps_10_data(DATA_CACHE_EPS_10_t * const p_new_data)
{
    dc_set_raw_data(DC_DATA_INPUT_INTERNAL, DC_DID_EPS_10_DATA, p_new_data, sizeof(DATA_CACHE_EPS_10_t));
}

dc_data_status_t dc_get_eps_14_data(DATA_CACHE_EPS_14_t * const p_data)
{
    return dc_get_raw_data(DC_DID_EPS_14_DATA,
                           p_data,
                           sizeof(DATA_CACHE_EPS_14_t),
                           0U,
                           sizeof(DATA_CACHE_EPS_14_t));
}

void dc_set_eps_14_data(DATA_CACHE_EPS_14_t * const p_new_data)
{
    dc_set_raw_data(DC_DATA_INPUT_INTERNAL, DC_DID_EPS_14_DATA, p_new_data, sizeof(DATA_CACHE_EPS_14_t));
}

dc_data_status_t dc_get_cubeadcs_gen2_op_status_common_data(DATA_CACHE_CUBEADCS_GEN2_OP_STATUS_COMMON_t * const p_data)
{
    return dc_get_raw_data(DC_DID_CUBEADCS_GEN2_OP_STATUS_COMMON_DATA,
                           p_data,
                           sizeof(DATA_CACHE_CUBEADCS_GEN2_OP_STATUS_COMMON_t),
                           0U,
                           sizeof(DATA_CACHE_CUBEADCS_GEN2_OP_STATUS_COMMON_t));
}

void dc_set_cubeadcs_gen2_op_status_common_data(DATA_CACHE_CUBEADCS_GEN2_OP_STATUS_COMMON_t * const p_new_data)
{
    dc_set_raw_data(DC_DATA_INPUT_INTERNAL, DC_DID_CUBEADCS_GEN2_OP_STATUS_COMMON_DATA, p_new_data, sizeof(DATA_CACHE_CUBEADCS_GEN2_OP_STATUS_COMMON_t));
}

dc_data_status_t dc_get_cubeadcs_gen2_op_status_app_data(DATA_CACHE_CUBEADCS_GEN2_OP_STATUS_APP_t * const p_data)
{
    return dc_get_raw_data(DC_DID_CUBEADCS_GEN2_OP_STATUS_APP_DATA,
                           p_data,
                           sizeof(DATA_CACHE_CUBEADCS_GEN2_OP_STATUS_APP_t),
                           0U,
                           sizeof(DATA_CACHE_CUBEADCS_GEN2_OP_STATUS_APP_t));
}

void dc_set_cubeadcs_gen2_op_status_app_data(DATA_CACHE_CUBEADCS_GEN2_OP_STATUS_APP_t * const p_new_data)
{
    dc_set_raw_data(DC_DATA_INPUT_INTERNAL, DC_DID_CUBEADCS_GEN2_OP_STATUS_APP_DATA, p_new_data, sizeof(DATA_CACHE_CUBEADCS_GEN2_OP_STATUS_APP_t));
}

dc_data_status_t dc_get_cubeadcs_gen2_tlm_frame_166_data(DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_166_t * const p_data)
{
    return dc_get_raw_data(DC_DID_CUBEADCS_GEN2_TLM_FRAME_166_DATA,
                           p_data,
                           sizeof(DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_166_t),
                           0U,
                           sizeof(DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_166_t));
}

void dc_set_cubeadcs_gen2_tlm_frame_166_data(DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_166_t * const p_new_data)
{
    dc_set_raw_data(DC_DATA_INPUT_INTERNAL, DC_DID_CUBEADCS_GEN2_TLM_FRAME_166_DATA, p_new_data, sizeof(DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_166_t));
}

dc_data_status_t dc_get_cubeadcs_gen2_tlm_frame_167_data(DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_167_t * const p_data)
{
    return dc_get_raw_data(DC_DID_CUBEADCS_GEN2_TLM_FRAME_167_DATA,
                           p_data,
                           sizeof(DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_167_t),
                           0U,
                           sizeof(DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_167_t));
}

void dc_set_cubeadcs_gen2_tlm_frame_167_data(DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_167_t * const p_new_data)
{
    dc_set_raw_data(DC_DATA_INPUT_INTERNAL, DC_DID_CUBEADCS_GEN2_TLM_FRAME_167_DATA, p_new_data, sizeof(DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_167_t));
}

dc_data_status_t dc_get_cubeadcs_gen2_tlm_frame_168_data(DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_168_t * const p_data)
{
    return dc_get_raw_data(DC_DID_CUBEADCS_GEN2_TLM_FRAME_168_DATA,
                           p_data,
                           sizeof(DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_168_t),
                           0U,
                           sizeof(DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_168_t));
}

void dc_set_cubeadcs_gen2_tlm_frame_168_data(DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_168_t * const p_new_data)
{
    dc_set_raw_data(DC_DATA_INPUT_INTERNAL, DC_DID_CUBEADCS_GEN2_TLM_FRAME_168_DATA, p_new_data, sizeof(DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_168_t));
}

dc_data_status_t dc_get_cubeadcs_gen2_tlm_frame_169_data(DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_169_t * const p_data)
{
    return dc_get_raw_data(DC_DID_CUBEADCS_GEN2_TLM_FRAME_169_DATA,
                           p_data,
                           sizeof(DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_169_t),
                           0U,
                           sizeof(DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_169_t));
}

void dc_set_cubeadcs_gen2_tlm_frame_169_data(DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_169_t * const p_new_data)
{
    dc_set_raw_data(DC_DATA_INPUT_INTERNAL, DC_DID_CUBEADCS_GEN2_TLM_FRAME_169_DATA, p_new_data, sizeof(DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_169_t));
}

dc_data_status_t dc_get_cubeadcs_gen2_tlm_frame_170_data(DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_170_t * const p_data)
{
    return dc_get_raw_data(DC_DID_CUBEADCS_GEN2_TLM_FRAME_170_DATA,
                           p_data,
                           sizeof(DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_170_t),
                           0U,
                           sizeof(DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_170_t));
}

void dc_set_cubeadcs_gen2_tlm_frame_170_data(DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_170_t * const p_new_data)
{
    dc_set_raw_data(DC_DATA_INPUT_INTERNAL, DC_DID_CUBEADCS_GEN2_TLM_FRAME_170_DATA, p_new_data, sizeof(DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_170_t));
}

dc_data_status_t dc_get_cubeadcs_gen2_tlm_frame_171_data(DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_171_t * const p_data)
{
    return dc_get_raw_data(DC_DID_CUBEADCS_GEN2_TLM_FRAME_171_DATA,
                           p_data,
                           sizeof(DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_171_t),
                           0U,
                           sizeof(DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_171_t));
}

void dc_set_cubeadcs_gen2_tlm_frame_171_data(DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_171_t * const p_new_data)
{
    dc_set_raw_data(DC_DATA_INPUT_INTERNAL, DC_DID_CUBEADCS_GEN2_TLM_FRAME_171_DATA, p_new_data, sizeof(DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_171_t));
}

dc_data_status_t dc_get_cubeadcs_gen2_tlm_frame_172_data(DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_172_t * const p_data)
{
    return dc_get_raw_data(DC_DID_CUBEADCS_GEN2_TLM_FRAME_172_DATA,
                           p_data,
                           sizeof(DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_172_t),
                           0U,
                           sizeof(DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_172_t));
}

void dc_set_cubeadcs_gen2_tlm_frame_172_data(DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_172_t * const p_new_data)
{
    dc_set_raw_data(DC_DATA_INPUT_INTERNAL, DC_DID_CUBEADCS_GEN2_TLM_FRAME_172_DATA, p_new_data, sizeof(DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_172_t));
}

dc_data_status_t dc_get_cubeadcs_gen2_tlm_frame_173_data(DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_173_t * const p_data)
{
    return dc_get_raw_data(DC_DID_CUBEADCS_GEN2_TLM_FRAME_173_DATA,
                           p_data,
                           sizeof(DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_173_t),
                           0U,
                           sizeof(DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_173_t));
}

void dc_set_cubeadcs_gen2_tlm_frame_173_data(DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_173_t * const p_new_data)
{
    dc_set_raw_data(DC_DATA_INPUT_INTERNAL, DC_DID_CUBEADCS_GEN2_TLM_FRAME_173_DATA, p_new_data, sizeof(DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_173_t));
}

dc_data_status_t dc_get_cubeadcs_gen2_tlm_frame_174_data(DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_174_t * const p_data)
{
    return dc_get_raw_data(DC_DID_CUBEADCS_GEN2_TLM_FRAME_174_DATA,
                           p_data,
                           sizeof(DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_174_t),
                           0U,
                           sizeof(DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_174_t));
}

void dc_set_cubeadcs_gen2_tlm_frame_174_data(DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_174_t * const p_new_data)
{
    dc_set_raw_data(DC_DATA_INPUT_INTERNAL, DC_DID_CUBEADCS_GEN2_TLM_FRAME_174_DATA, p_new_data, sizeof(DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_174_t));
}

dc_data_status_t dc_get_cubeadcs_gen2_tlm_frame_175_data(DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_175_t * const p_data)
{
    return dc_get_raw_data(DC_DID_CUBEADCS_GEN2_TLM_FRAME_175_DATA,
                           p_data,
                           sizeof(DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_175_t),
                           0U,
                           sizeof(DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_175_t));
}

void dc_set_cubeadcs_gen2_tlm_frame_175_data(DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_175_t * const p_new_data)
{
    dc_set_raw_data(DC_DATA_INPUT_INTERNAL, DC_DID_CUBEADCS_GEN2_TLM_FRAME_175_DATA, p_new_data, sizeof(DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_175_t));
}

dc_data_status_t dc_get_cubeadcs_gen2_tlm_frame_176_data(DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_176_t * const p_data)
{
    return dc_get_raw_data(DC_DID_CUBEADCS_GEN2_TLM_FRAME_176_DATA,
                           p_data,
                           sizeof(DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_176_t),
                           0U,
                           sizeof(DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_176_t));
}

void dc_set_cubeadcs_gen2_tlm_frame_176_data(DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_176_t * const p_new_data)
{
    dc_set_raw_data(DC_DATA_INPUT_INTERNAL, DC_DID_CUBEADCS_GEN2_TLM_FRAME_176_DATA, p_new_data, sizeof(DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_176_t));
}

dc_data_status_t dc_get_cubeadcs_gen2_tlm_frame_177_data(DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_177_t * const p_data)
{
    return dc_get_raw_data(DC_DID_CUBEADCS_GEN2_TLM_FRAME_177_DATA,
                           p_data,
                           sizeof(DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_177_t),
                           0U,
                           sizeof(DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_177_t));
}

void dc_set_cubeadcs_gen2_tlm_frame_177_data(DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_177_t * const p_new_data)
{
    dc_set_raw_data(DC_DATA_INPUT_INTERNAL, DC_DID_CUBEADCS_GEN2_TLM_FRAME_177_DATA, p_new_data, sizeof(DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_177_t));
}

dc_data_status_t dc_get_cubeadcs_gen2_tlm_frame_178_data(DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_178_t * const p_data)
{
    return dc_get_raw_data(DC_DID_CUBEADCS_GEN2_TLM_FRAME_178_DATA,
                           p_data,
                           sizeof(DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_178_t),
                           0U,
                           sizeof(DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_178_t));
}

void dc_set_cubeadcs_gen2_tlm_frame_178_data(DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_178_t * const p_new_data)
{
    dc_set_raw_data(DC_DATA_INPUT_INTERNAL, DC_DID_CUBEADCS_GEN2_TLM_FRAME_178_DATA, p_new_data, sizeof(DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_178_t));
}

dc_data_status_t dc_get_cubeadcs_gen2_tlm_frame_179_data(DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_179_t * const p_data)
{
    return dc_get_raw_data(DC_DID_CUBEADCS_GEN2_TLM_FRAME_179_DATA,
                           p_data,
                           sizeof(DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_179_t),
                           0U,
                           sizeof(DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_179_t));
}

void dc_set_cubeadcs_gen2_tlm_frame_179_data(DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_179_t * const p_new_data)
{
    dc_set_raw_data(DC_DATA_INPUT_INTERNAL, DC_DID_CUBEADCS_GEN2_TLM_FRAME_179_DATA, p_new_data, sizeof(DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_179_t));
}

dc_data_status_t dc_get_cubeadcs_gen2_tlm_frame_180_data(DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_180_t * const p_data)
{
    return dc_get_raw_data(DC_DID_CUBEADCS_GEN2_TLM_FRAME_180_DATA,
                           p_data,
                           sizeof(DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_180_t),
                           0U,
                           sizeof(DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_180_t));
}

void dc_set_cubeadcs_gen2_tlm_frame_180_data(DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_180_t * const p_new_data)
{
    dc_set_raw_data(DC_DATA_INPUT_INTERNAL, DC_DID_CUBEADCS_GEN2_TLM_FRAME_180_DATA, p_new_data, sizeof(DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_180_t));
}

dc_data_status_t dc_get_cubeadcs_gen2_tlm_frame_203_data(DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_203_t * const p_data)
{
    return dc_get_raw_data(DC_DID_CUBEADCS_GEN2_TLM_FRAME_203_DATA,
                           p_data,
                           sizeof(DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_203_t),
                           0U,
                           sizeof(DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_203_t));
}

void dc_set_cubeadcs_gen2_tlm_frame_203_data(DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_203_t * const p_new_data)
{
    dc_set_raw_data(DC_DATA_INPUT_INTERNAL, DC_DID_CUBEADCS_GEN2_TLM_FRAME_203_DATA, p_new_data, sizeof(DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_203_t));
}

dc_data_status_t dc_get_cubeadcs_gen2_tlm_frame_204_data(DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_204_t * const p_data)
{
    return dc_get_raw_data(DC_DID_CUBEADCS_GEN2_TLM_FRAME_204_DATA,
                           p_data,
                           sizeof(DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_204_t),
                           0U,
                           sizeof(DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_204_t));
}

void dc_set_cubeadcs_gen2_tlm_frame_204_data(DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_204_t * const p_new_data)
{
    dc_set_raw_data(DC_DATA_INPUT_INTERNAL, DC_DID_CUBEADCS_GEN2_TLM_FRAME_204_DATA, p_new_data, sizeof(DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_204_t));
}

dc_data_status_t dc_get_cubeadcs_gen2_tlm_frame_205_data(DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_205_t * const p_data)
{
    return dc_get_raw_data(DC_DID_CUBEADCS_GEN2_TLM_FRAME_205_DATA,
                           p_data,
                           sizeof(DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_205_t),
                           0U,
                           sizeof(DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_205_t));
}

void dc_set_cubeadcs_gen2_tlm_frame_205_data(DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_205_t * const p_new_data)
{
    dc_set_raw_data(DC_DATA_INPUT_INTERNAL, DC_DID_CUBEADCS_GEN2_TLM_FRAME_205_DATA, p_new_data, sizeof(DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_205_t));
}

dc_data_status_t dc_get_cubeadcs_gen2_tlm_frame_206_data(DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_206_t * const p_data)
{
    return dc_get_raw_data(DC_DID_CUBEADCS_GEN2_TLM_FRAME_206_DATA,
                           p_data,
                           sizeof(DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_206_t),
                           0U,
                           sizeof(DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_206_t));
}

void dc_set_cubeadcs_gen2_tlm_frame_206_data(DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_206_t * const p_new_data)
{
    dc_set_raw_data(DC_DATA_INPUT_INTERNAL, DC_DID_CUBEADCS_GEN2_TLM_FRAME_206_DATA, p_new_data, sizeof(DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_206_t));
}

dc_data_status_t dc_get_cubeadcs_gen2_tlm_frame_207_data(DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_207_t * const p_data)
{
    return dc_get_raw_data(DC_DID_CUBEADCS_GEN2_TLM_FRAME_207_DATA,
                           p_data,
                           sizeof(DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_207_t),
                           0U,
                           sizeof(DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_207_t));
}

void dc_set_cubeadcs_gen2_tlm_frame_207_data(DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_207_t * const p_new_data)
{
    dc_set_raw_data(DC_DATA_INPUT_INTERNAL, DC_DID_CUBEADCS_GEN2_TLM_FRAME_207_DATA, p_new_data, sizeof(DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_207_t));
}

dc_data_status_t dc_get_cubeadcs_gen2_tlm_frame_208_1_data(DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_208_1_t * const p_data)
{
    return dc_get_raw_data(DC_DID_CUBEADCS_GEN2_TLM_FRAME_208_1_DATA,
                           p_data,
                           sizeof(DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_208_1_t),
                           0U,
                           sizeof(DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_208_1_t));
}

void dc_set_cubeadcs_gen2_tlm_frame_208_1_data(DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_208_1_t * const p_new_data)
{
    dc_set_raw_data(DC_DATA_INPUT_INTERNAL, DC_DID_CUBEADCS_GEN2_TLM_FRAME_208_1_DATA, p_new_data, sizeof(DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_208_1_t));
}

dc_data_status_t dc_get_cubeadcs_gen2_tlm_frame_208_2_data(DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_208_2_t * const p_data)
{
    return dc_get_raw_data(DC_DID_CUBEADCS_GEN2_TLM_FRAME_208_2_DATA,
                           p_data,
                           sizeof(DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_208_2_t),
                           0U,
                           sizeof(DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_208_2_t));
}

void dc_set_cubeadcs_gen2_tlm_frame_208_2_data(DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_208_2_t * const p_new_data)
{
    dc_set_raw_data(DC_DATA_INPUT_INTERNAL, DC_DID_CUBEADCS_GEN2_TLM_FRAME_208_2_DATA, p_new_data, sizeof(DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_208_2_t));
}

dc_data_status_t dc_get_cubeadcs_gen2_tlm_frame_209_data(DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_209_t * const p_data)
{
    return dc_get_raw_data(DC_DID_CUBEADCS_GEN2_TLM_FRAME_209_DATA,
                           p_data,
                           sizeof(DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_209_t),
                           0U,
                           sizeof(DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_209_t));
}

void dc_set_cubeadcs_gen2_tlm_frame_209_data(DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_209_t * const p_new_data)
{
    dc_set_raw_data(DC_DATA_INPUT_INTERNAL, DC_DID_CUBEADCS_GEN2_TLM_FRAME_209_DATA, p_new_data, sizeof(DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_209_t));
}

dc_data_status_t dc_get_cubeadcs_gen2_tlm_frame_210_data(DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_210_t * const p_data)
{
    return dc_get_raw_data(DC_DID_CUBEADCS_GEN2_TLM_FRAME_210_DATA,
                           p_data,
                           sizeof(DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_210_t),
                           0U,
                           sizeof(DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_210_t));
}

void dc_set_cubeadcs_gen2_tlm_frame_210_data(DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_210_t * const p_new_data)
{
    dc_set_raw_data(DC_DATA_INPUT_INTERNAL, DC_DID_CUBEADCS_GEN2_TLM_FRAME_210_DATA, p_new_data, sizeof(DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_210_t));
}

dc_data_status_t dc_get_cubeadcs_gen2_tlm_frame_211_data(DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_211_t * const p_data)
{
    return dc_get_raw_data(DC_DID_CUBEADCS_GEN2_TLM_FRAME_211_DATA,
                           p_data,
                           sizeof(DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_211_t),
                           0U,
                           sizeof(DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_211_t));
}

void dc_set_cubeadcs_gen2_tlm_frame_211_data(DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_211_t * const p_new_data)
{
    dc_set_raw_data(DC_DATA_INPUT_INTERNAL, DC_DID_CUBEADCS_GEN2_TLM_FRAME_211_DATA, p_new_data, sizeof(DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_211_t));
}

dc_data_status_t dc_get_cubeadcs_gen2_tlm_frame_212_data(DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_212_t * const p_data)
{
    return dc_get_raw_data(DC_DID_CUBEADCS_GEN2_TLM_FRAME_212_DATA,
                           p_data,
                           sizeof(DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_212_t),
                           0U,
                           sizeof(DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_212_t));
}

void dc_set_cubeadcs_gen2_tlm_frame_212_data(DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_212_t * const p_new_data)
{
    dc_set_raw_data(DC_DATA_INPUT_INTERNAL, DC_DID_CUBEADCS_GEN2_TLM_FRAME_212_DATA, p_new_data, sizeof(DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_212_t));
}

dc_data_status_t dc_get_cubeadcs_gen2_tlm_frame_213_data(DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_213_t * const p_data)
{
    return dc_get_raw_data(DC_DID_CUBEADCS_GEN2_TLM_FRAME_213_DATA,
                           p_data,
                           sizeof(DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_213_t),
                           0U,
                           sizeof(DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_213_t));
}

void dc_set_cubeadcs_gen2_tlm_frame_213_data(DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_213_t * const p_new_data)
{
    dc_set_raw_data(DC_DATA_INPUT_INTERNAL, DC_DID_CUBEADCS_GEN2_TLM_FRAME_213_DATA, p_new_data, sizeof(DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_213_t));
}

dc_data_status_t dc_get_cubeadcs_gen2_tlm_frame_214_data(DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_214_t * const p_data)
{
    return dc_get_raw_data(DC_DID_CUBEADCS_GEN2_TLM_FRAME_214_DATA,
                           p_data,
                           sizeof(DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_214_t),
                           0U,
                           sizeof(DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_214_t));
}

void dc_set_cubeadcs_gen2_tlm_frame_214_data(DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_214_t * const p_new_data)
{
    dc_set_raw_data(DC_DATA_INPUT_INTERNAL, DC_DID_CUBEADCS_GEN2_TLM_FRAME_214_DATA, p_new_data, sizeof(DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_214_t));
}

dc_data_status_t dc_get_cubeadcs_gen2_tlm_frame_216_data(DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_216_t * const p_data)
{
    return dc_get_raw_data(DC_DID_CUBEADCS_GEN2_TLM_FRAME_216_DATA,
                           p_data,
                           sizeof(DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_216_t),
                           0U,
                           sizeof(DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_216_t));
}

void dc_set_cubeadcs_gen2_tlm_frame_216_data(DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_216_t * const p_new_data)
{
    dc_set_raw_data(DC_DATA_INPUT_INTERNAL, DC_DID_CUBEADCS_GEN2_TLM_FRAME_216_DATA, p_new_data, sizeof(DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_216_t));
}

dc_data_status_t dc_get_cubeadcs_gen2_tlm_frame_217_data(DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_217_t * const p_data)
{
    return dc_get_raw_data(DC_DID_CUBEADCS_GEN2_TLM_FRAME_217_DATA,
                           p_data,
                           sizeof(DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_217_t),
                           0U,
                           sizeof(DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_217_t));
}

void dc_set_cubeadcs_gen2_tlm_frame_217_data(DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_217_t * const p_new_data)
{
    dc_set_raw_data(DC_DATA_INPUT_INTERNAL, DC_DID_CUBEADCS_GEN2_TLM_FRAME_217_DATA, p_new_data, sizeof(DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_217_t));
}

dc_data_status_t dc_get_cubeadcs_gen2_tlm_frame_218_data(DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_218_t * const p_data)
{
    return dc_get_raw_data(DC_DID_CUBEADCS_GEN2_TLM_FRAME_218_DATA,
                           p_data,
                           sizeof(DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_218_t),
                           0U,
                           sizeof(DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_218_t));
}

void dc_set_cubeadcs_gen2_tlm_frame_218_data(DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_218_t * const p_new_data)
{
    dc_set_raw_data(DC_DATA_INPUT_INTERNAL, DC_DID_CUBEADCS_GEN2_TLM_FRAME_218_DATA, p_new_data, sizeof(DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_218_t));
}

dc_data_status_t dc_get_cubeadcs_gen2_tlm_frame_225_data(DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_225_t * const p_data)
{
    return dc_get_raw_data(DC_DID_CUBEADCS_GEN2_TLM_FRAME_225_DATA,
                           p_data,
                           sizeof(DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_225_t),
                           0U,
                           sizeof(DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_225_t));
}

void dc_set_cubeadcs_gen2_tlm_frame_225_data(DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_225_t * const p_new_data)
{
    dc_set_raw_data(DC_DATA_INPUT_INTERNAL, DC_DID_CUBEADCS_GEN2_TLM_FRAME_225_DATA, p_new_data, sizeof(DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_225_t));
}

dc_data_status_t dc_get_cubeadcs_gen2_tlm_frame_226_data(DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_226_t * const p_data)
{
    return dc_get_raw_data(DC_DID_CUBEADCS_GEN2_TLM_FRAME_226_DATA,
                           p_data,
                           sizeof(DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_226_t),
                           0U,
                           sizeof(DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_226_t));
}

void dc_set_cubeadcs_gen2_tlm_frame_226_data(DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_226_t * const p_new_data)
{
    dc_set_raw_data(DC_DATA_INPUT_INTERNAL, DC_DID_CUBEADCS_GEN2_TLM_FRAME_226_DATA, p_new_data, sizeof(DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_226_t));
}

dc_data_status_t dc_get_cubeadcs_gen2_tlm_frame_165_data(DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_165_t * const p_data)
{
    return dc_get_raw_data(DC_DID_CUBEADCS_GEN2_TLM_FRAME_165_DATA,
                           p_data,
                           sizeof(DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_165_t),
                           0U,
                           sizeof(DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_165_t));
}

void dc_set_cubeadcs_gen2_tlm_frame_165_data(DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_165_t * const p_new_data)
{
    dc_set_raw_data(DC_DATA_INPUT_INTERNAL, DC_DID_CUBEADCS_GEN2_TLM_FRAME_165_DATA, p_new_data, sizeof(DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_165_t));
}

dc_data_status_t dc_get_cubeadcs_gen2_tlm_frame_221_data(DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_221_t * const p_data)
{
    return dc_get_raw_data(DC_DID_CUBEADCS_GEN2_TLM_FRAME_221_DATA,
                           p_data,
                           sizeof(DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_221_t),
                           0U,
                           sizeof(DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_221_t));
}

void dc_set_cubeadcs_gen2_tlm_frame_221_data(DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_221_t * const p_new_data)
{
    dc_set_raw_data(DC_DATA_INPUT_INTERNAL, DC_DID_CUBEADCS_GEN2_TLM_FRAME_221_DATA, p_new_data, sizeof(DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_221_t));
}

dc_data_status_t dc_get_gnss_time_data(DATA_CACHE_GNSS_TIME_t * const p_data)
{
    return dc_get_raw_data(DC_DID_GNSS_TIME_DATA,
                           p_data,
                           sizeof(DATA_CACHE_GNSS_TIME_t),
                           0U,
                           sizeof(DATA_CACHE_GNSS_TIME_t));
}

void dc_set_gnss_time_data(DATA_CACHE_GNSS_TIME_t * const p_new_data)
{
    dc_set_raw_data(DC_DATA_INPUT_INTERNAL, DC_DID_GNSS_TIME_DATA, p_new_data, sizeof(DATA_CACHE_GNSS_TIME_t));
}

dc_data_status_t dc_get_gnss_bestxyz_data(DATA_CACHE_GNSS_BESTXYZ_t * const p_data)
{
    return dc_get_raw_data(DC_DID_GNSS_BESTXYZ_DATA,
                           p_data,
                           sizeof(DATA_CACHE_GNSS_BESTXYZ_t),
                           0U,
                           sizeof(DATA_CACHE_GNSS_BESTXYZ_t));
}

void dc_set_gnss_bestxyz_data(DATA_CACHE_GNSS_BESTXYZ_t * const p_new_data)
{
    dc_set_raw_data(DC_DATA_INPUT_INTERNAL, DC_DID_GNSS_BESTXYZ_DATA, p_new_data, sizeof(DATA_CACHE_GNSS_BESTXYZ_t));
}

dc_data_status_t dc_get_sat_state_vector_from_propagator_data(DATA_CACHE_SAT_STATE_VECTOR_FROM_PROPAGATOR_t * const p_data)
{
    return dc_get_raw_data(DC_DID_SAT_STATE_VECTOR_FROM_PROPAGATOR_DATA,
                           p_data,
                           sizeof(DATA_CACHE_SAT_STATE_VECTOR_FROM_PROPAGATOR_t),
                           0U,
                           sizeof(DATA_CACHE_SAT_STATE_VECTOR_FROM_PROPAGATOR_t));
}

void dc_set_sat_state_vector_from_propagator_data(DATA_CACHE_SAT_STATE_VECTOR_FROM_PROPAGATOR_t * const p_new_data)
{
    dc_set_raw_data(DC_DATA_INPUT_INTERNAL, DC_DID_SAT_STATE_VECTOR_FROM_PROPAGATOR_DATA, p_new_data, sizeof(DATA_CACHE_SAT_STATE_VECTOR_FROM_PROPAGATOR_t));
}

dc_data_status_t dc_get_sat_mag_field_vector_from_model_data(DATA_CACHE_SAT_MAG_FIELD_VECTOR_FROM_MODEL_t * const p_data)
{
    return dc_get_raw_data(DC_DID_SAT_MAG_FIELD_VECTOR_FROM_MODEL_DATA,
                           p_data,
                           sizeof(DATA_CACHE_SAT_MAG_FIELD_VECTOR_FROM_MODEL_t),
                           0U,
                           sizeof(DATA_CACHE_SAT_MAG_FIELD_VECTOR_FROM_MODEL_t));
}

void dc_set_sat_mag_field_vector_from_model_data(DATA_CACHE_SAT_MAG_FIELD_VECTOR_FROM_MODEL_t * const p_new_data)
{
    dc_set_raw_data(DC_DATA_INPUT_INTERNAL, DC_DID_SAT_MAG_FIELD_VECTOR_FROM_MODEL_DATA, p_new_data, sizeof(DATA_CACHE_SAT_MAG_FIELD_VECTOR_FROM_MODEL_t));
}

dc_data_status_t dc_get_sat_mag_field_vector_from_sensor_data(DATA_CACHE_SAT_MAG_FIELD_VECTOR_FROM_SENSOR_t * const p_data)
{
    return dc_get_raw_data(DC_DID_SAT_MAG_FIELD_VECTOR_FROM_SENSOR_DATA,
                           p_data,
                           sizeof(DATA_CACHE_SAT_MAG_FIELD_VECTOR_FROM_SENSOR_t),
                           0U,
                           sizeof(DATA_CACHE_SAT_MAG_FIELD_VECTOR_FROM_SENSOR_t));
}

void dc_set_sat_mag_field_vector_from_sensor_data(DATA_CACHE_SAT_MAG_FIELD_VECTOR_FROM_SENSOR_t * const p_new_data)
{
    dc_set_raw_data(DC_DATA_INPUT_INTERNAL, DC_DID_SAT_MAG_FIELD_VECTOR_FROM_SENSOR_DATA, p_new_data, sizeof(DATA_CACHE_SAT_MAG_FIELD_VECTOR_FROM_SENSOR_t));
}

dc_data_status_t dc_get_fdir_eps_i_cmd_exec_status_data(DATA_CACHE_FDIR_EPS_I_CMD_EXEC_STATUS_t * const p_data)
{
    return dc_get_raw_data(DC_DID_FDIR_EPS_I_CMD_EXEC_STATUS_DATA,
                           p_data,
                           sizeof(DATA_CACHE_FDIR_EPS_I_CMD_EXEC_STATUS_t),
                           0U,
                           sizeof(DATA_CACHE_FDIR_EPS_I_CMD_EXEC_STATUS_t));
}

void dc_set_fdir_eps_i_cmd_exec_status_data(DATA_CACHE_FDIR_EPS_I_CMD_EXEC_STATUS_t * const p_new_data)
{
    dc_set_raw_data(DC_DATA_INPUT_INTERNAL, DC_DID_FDIR_EPS_I_CMD_EXEC_STATUS_DATA, p_new_data, sizeof(DATA_CACHE_FDIR_EPS_I_CMD_EXEC_STATUS_t));
}

dc_data_status_t dc_get_fdir_eps_ii_pdm_cmd_exec_status_data(DATA_CACHE_FDIR_EPS_II_PDM_CMD_EXEC_STATUS_t * const p_data)
{
    return dc_get_raw_data(DC_DID_FDIR_EPS_II_PDM_CMD_EXEC_STATUS_DATA,
                           p_data,
                           sizeof(DATA_CACHE_FDIR_EPS_II_PDM_CMD_EXEC_STATUS_t),
                           0U,
                           sizeof(DATA_CACHE_FDIR_EPS_II_PDM_CMD_EXEC_STATUS_t));
}

void dc_set_fdir_eps_ii_pdm_cmd_exec_status_data(DATA_CACHE_FDIR_EPS_II_PDM_CMD_EXEC_STATUS_t * const p_new_data)
{
    dc_set_raw_data(DC_DATA_INPUT_INTERNAL, DC_DID_FDIR_EPS_II_PDM_CMD_EXEC_STATUS_DATA, p_new_data, sizeof(DATA_CACHE_FDIR_EPS_II_PDM_CMD_EXEC_STATUS_t));
}

dc_data_status_t dc_get_fdir_cubeadcs_cmd_exec_status_data(DATA_CACHE_FDIR_CUBEADCS_CMD_EXEC_STATUS_t * const p_data)
{
    return dc_get_raw_data(DC_DID_FDIR_CUBEADCS_CMD_EXEC_STATUS_DATA,
                           p_data,
                           sizeof(DATA_CACHE_FDIR_CUBEADCS_CMD_EXEC_STATUS_t),
                           0U,
                           sizeof(DATA_CACHE_FDIR_CUBEADCS_CMD_EXEC_STATUS_t));
}

void dc_set_fdir_cubeadcs_cmd_exec_status_data(DATA_CACHE_FDIR_CUBEADCS_CMD_EXEC_STATUS_t * const p_new_data)
{
    dc_set_raw_data(DC_DATA_INPUT_INTERNAL, DC_DID_FDIR_CUBEADCS_CMD_EXEC_STATUS_DATA, p_new_data, sizeof(DATA_CACHE_FDIR_CUBEADCS_CMD_EXEC_STATUS_t));
}

dc_data_status_t dc_get_fdir_cubeadcs_gen2_cmd_exec_status_data(DATA_CACHE_FDIR_CUBEADCS_GEN2_CMD_EXEC_STATUS_t * const p_data)
{
    return dc_get_raw_data(DC_DID_FDIR_CUBEADCS_GEN2_CMD_EXEC_STATUS_DATA,
                           p_data,
                           sizeof(DATA_CACHE_FDIR_CUBEADCS_GEN2_CMD_EXEC_STATUS_t),
                           0U,
                           sizeof(DATA_CACHE_FDIR_CUBEADCS_GEN2_CMD_EXEC_STATUS_t));
}

void dc_set_fdir_cubeadcs_gen2_cmd_exec_status_data(DATA_CACHE_FDIR_CUBEADCS_GEN2_CMD_EXEC_STATUS_t * const p_new_data)
{
    dc_set_raw_data(DC_DATA_INPUT_INTERNAL, DC_DID_FDIR_CUBEADCS_GEN2_CMD_EXEC_STATUS_DATA, p_new_data, sizeof(DATA_CACHE_FDIR_CUBEADCS_GEN2_CMD_EXEC_STATUS_t));
}

dc_data_status_t dc_get_fdir_cubeadcs_gen2_events_data(DATA_CACHE_FDIR_CUBEADCS_GEN2_EVENTS_t * const p_data)
{
    return dc_get_raw_data(DC_DID_FDIR_CUBEADCS_GEN2_EVENTS_DATA,
                           p_data,
                           sizeof(DATA_CACHE_FDIR_CUBEADCS_GEN2_EVENTS_t),
                           0U,
                           sizeof(DATA_CACHE_FDIR_CUBEADCS_GEN2_EVENTS_t));
}

void dc_set_fdir_cubeadcs_gen2_events_data(DATA_CACHE_FDIR_CUBEADCS_GEN2_EVENTS_t * const p_new_data)
{
    dc_set_raw_data(DC_DATA_INPUT_INTERNAL, DC_DID_FDIR_CUBEADCS_GEN2_EVENTS_DATA, p_new_data, sizeof(DATA_CACHE_FDIR_CUBEADCS_GEN2_EVENTS_t));
}

dc_data_status_t dc_get_fdir_s_band_tmtc_cmd_exec_status_data(DATA_CACHE_FDIR_S_BAND_TMTC_CMD_EXEC_STATUS_t * const p_data)
{
    return dc_get_raw_data(DC_DID_FDIR_S_BAND_TMTC_CMD_EXEC_STATUS_DATA,
                           p_data,
                           sizeof(DATA_CACHE_FDIR_S_BAND_TMTC_CMD_EXEC_STATUS_t),
                           0U,
                           sizeof(DATA_CACHE_FDIR_S_BAND_TMTC_CMD_EXEC_STATUS_t));
}

void dc_set_fdir_s_band_tmtc_cmd_exec_status_data(DATA_CACHE_FDIR_S_BAND_TMTC_CMD_EXEC_STATUS_t * const p_new_data)
{
    dc_set_raw_data(DC_DATA_INPUT_INTERNAL, DC_DID_FDIR_S_BAND_TMTC_CMD_EXEC_STATUS_DATA, p_new_data, sizeof(DATA_CACHE_FDIR_S_BAND_TMTC_CMD_EXEC_STATUS_t));
}

dc_data_status_t dc_get_fdir_uhf_cmd_exec_status_data(DATA_CACHE_FDIR_UHF_CMD_EXEC_STATUS_t * const p_data)
{
    return dc_get_raw_data(DC_DID_FDIR_UHF_CMD_EXEC_STATUS_DATA,
                           p_data,
                           sizeof(DATA_CACHE_FDIR_UHF_CMD_EXEC_STATUS_t),
                           0U,
                           sizeof(DATA_CACHE_FDIR_UHF_CMD_EXEC_STATUS_t));
}

void dc_set_fdir_uhf_cmd_exec_status_data(DATA_CACHE_FDIR_UHF_CMD_EXEC_STATUS_t * const p_new_data)
{
    dc_set_raw_data(DC_DATA_INPUT_INTERNAL, DC_DID_FDIR_UHF_CMD_EXEC_STATUS_DATA, p_new_data, sizeof(DATA_CACHE_FDIR_UHF_CMD_EXEC_STATUS_t));
}

dc_data_status_t dc_get_fdir_gnss_cmd_exec_status_data(DATA_CACHE_FDIR_GNSS_CMD_EXEC_STATUS_t * const p_data)
{
    return dc_get_raw_data(DC_DID_FDIR_GNSS_CMD_EXEC_STATUS_DATA,
                           p_data,
                           sizeof(DATA_CACHE_FDIR_GNSS_CMD_EXEC_STATUS_t),
                           0U,
                           sizeof(DATA_CACHE_FDIR_GNSS_CMD_EXEC_STATUS_t));
}

void dc_set_fdir_gnss_cmd_exec_status_data(DATA_CACHE_FDIR_GNSS_CMD_EXEC_STATUS_t * const p_new_data)
{
    dc_set_raw_data(DC_DATA_INPUT_INTERNAL, DC_DID_FDIR_GNSS_CMD_EXEC_STATUS_DATA, p_new_data, sizeof(DATA_CACHE_FDIR_GNSS_CMD_EXEC_STATUS_t));
}

dc_data_status_t dc_get_fdir_sdr_cmd_exec_status_data(DATA_CACHE_FDIR_SDR_CMD_EXEC_STATUS_t * const p_data)
{
    return dc_get_raw_data(DC_DID_FDIR_SDR_CMD_EXEC_STATUS_DATA,
                           p_data,
                           sizeof(DATA_CACHE_FDIR_SDR_CMD_EXEC_STATUS_t),
                           0U,
                           sizeof(DATA_CACHE_FDIR_SDR_CMD_EXEC_STATUS_t));
}

void dc_set_fdir_sdr_cmd_exec_status_data(DATA_CACHE_FDIR_SDR_CMD_EXEC_STATUS_t * const p_new_data)
{
    dc_set_raw_data(DC_DATA_INPUT_INTERNAL, DC_DID_FDIR_SDR_CMD_EXEC_STATUS_DATA, p_new_data, sizeof(DATA_CACHE_FDIR_SDR_CMD_EXEC_STATUS_t));
}

dc_data_status_t dc_get_fdir_s_x_band_cmd_exec_status_data(DATA_CACHE_FDIR_S_X_BAND_CMD_EXEC_STATUS_t * const p_data)
{
    return dc_get_raw_data(DC_DID_FDIR_S_X_BAND_CMD_EXEC_STATUS_DATA,
                           p_data,
                           sizeof(DATA_CACHE_FDIR_S_X_BAND_CMD_EXEC_STATUS_t),
                           0U,
                           sizeof(DATA_CACHE_FDIR_S_X_BAND_CMD_EXEC_STATUS_t));
}

void dc_set_fdir_s_x_band_cmd_exec_status_data(DATA_CACHE_FDIR_S_X_BAND_CMD_EXEC_STATUS_t * const p_new_data)
{
    dc_set_raw_data(DC_DATA_INPUT_INTERNAL, DC_DID_FDIR_S_X_BAND_CMD_EXEC_STATUS_DATA, p_new_data, sizeof(DATA_CACHE_FDIR_S_X_BAND_CMD_EXEC_STATUS_t));
}

dc_data_status_t dc_get_fdir_thruster_cmd_exec_status_data(DATA_CACHE_FDIR_THRUSTER_CMD_EXEC_STATUS_t * const p_data)
{
    return dc_get_raw_data(DC_DID_FDIR_THRUSTER_CMD_EXEC_STATUS_DATA,
                           p_data,
                           sizeof(DATA_CACHE_FDIR_THRUSTER_CMD_EXEC_STATUS_t),
                           0U,
                           sizeof(DATA_CACHE_FDIR_THRUSTER_CMD_EXEC_STATUS_t));
}

void dc_set_fdir_thruster_cmd_exec_status_data(DATA_CACHE_FDIR_THRUSTER_CMD_EXEC_STATUS_t * const p_new_data)
{
    dc_set_raw_data(DC_DATA_INPUT_INTERNAL, DC_DID_FDIR_THRUSTER_CMD_EXEC_STATUS_DATA, p_new_data, sizeof(DATA_CACHE_FDIR_THRUSTER_CMD_EXEC_STATUS_t));
}

dc_data_status_t dc_get_xband_fe_data(DATA_CACHE_XBandFeTelemetry_t * const p_data)
{
    return dc_get_raw_data(DC_DID_XBAND_FE_DATA,
                           p_data,
                           sizeof(DATA_CACHE_XBandFeTelemetry_t),
                           0U,
                           sizeof(DATA_CACHE_XBandFeTelemetry_t));
}

void dc_set_xband_fe_data(DATA_CACHE_XBandFeTelemetry_t * const p_new_data)
{
    dc_set_raw_data(DC_DATA_INPUT_INTERNAL, DC_DID_XBAND_FE_DATA, p_new_data, sizeof(DATA_CACHE_XBandFeTelemetry_t));
}

dc_data_status_t dc_get_epsoverallbatteryinfo_data(DATA_CACHE_EpsOverallBatteryInfoType_t * const p_data)
{
    return dc_get_raw_data(DC_DID_EPSOVERALLBATTERYINFO_DATA,
                           p_data,
                           sizeof(DATA_CACHE_EpsOverallBatteryInfoType_t),
                           0U,
                           sizeof(DATA_CACHE_EpsOverallBatteryInfoType_t));
}

void dc_set_epsoverallbatteryinfo_data(DATA_CACHE_EpsOverallBatteryInfoType_t * const p_new_data)
{
    dc_set_raw_data(DC_DATA_INPUT_INTERNAL, DC_DID_EPSOVERALLBATTERYINFO_DATA, p_new_data, sizeof(DATA_CACHE_EpsOverallBatteryInfoType_t));
}

dc_data_status_t dc_get_pps_telemetry_data(DATA_CACHE_PPS_Telemetry_t * const p_data)
{
    return dc_get_raw_data(DC_DID_PPS_TELEMETRY_DATA,
                           p_data,
                           sizeof(DATA_CACHE_PPS_Telemetry_t),
                           0U,
                           sizeof(DATA_CACHE_PPS_Telemetry_t));
}

void dc_set_pps_telemetry_data(DATA_CACHE_PPS_Telemetry_t * const p_new_data)
{
    dc_set_raw_data(DC_DATA_INPUT_INTERNAL, DC_DID_PPS_TELEMETRY_DATA, p_new_data, sizeof(DATA_CACHE_PPS_Telemetry_t));
}

dc_data_status_t dc_get_fdir_eps_iii_pdm_cmd_exec_status_data(DATA_CACHE_FDIR_EPS_III_PDM_CMD_EXEC_STATUS_t * const p_data)
{
    return dc_get_raw_data(DC_DID_FDIR_EPS_III_PDM_CMD_EXEC_STATUS_DATA,
                           p_data,
                           sizeof(DATA_CACHE_FDIR_EPS_III_PDM_CMD_EXEC_STATUS_t),
                           0U,
                           sizeof(DATA_CACHE_FDIR_EPS_III_PDM_CMD_EXEC_STATUS_t));
}

void dc_set_fdir_eps_iii_pdm_cmd_exec_status_data(DATA_CACHE_FDIR_EPS_III_PDM_CMD_EXEC_STATUS_t * const p_new_data)
{
    dc_set_raw_data(DC_DATA_INPUT_INTERNAL, DC_DID_FDIR_EPS_III_PDM_CMD_EXEC_STATUS_DATA, p_new_data, sizeof(DATA_CACHE_FDIR_EPS_III_PDM_CMD_EXEC_STATUS_t));
}

dc_data_status_t dc_get_eps2_bp_inst0_bp_info_data(DATA_CACHE_Eps2Inst0BatteryInfoType_t * const p_data)
{
    return dc_get_raw_data(DC_DID_EPS2_BP_INST0_BP_INFO_DATA,
                           p_data,
                           sizeof(DATA_CACHE_Eps2Inst0BatteryInfoType_t),
                           0U,
                           sizeof(DATA_CACHE_Eps2Inst0BatteryInfoType_t));
}

void dc_set_eps2_bp_inst0_bp_info_data(DATA_CACHE_Eps2Inst0BatteryInfoType_t * const p_new_data)
{
    dc_set_raw_data(DC_DATA_INPUT_INTERNAL, DC_DID_EPS2_BP_INST0_BP_INFO_DATA, p_new_data, sizeof(DATA_CACHE_Eps2Inst0BatteryInfoType_t));
}

dc_data_status_t dc_get_eps2_bp_inst0_device_health_info_data(DATA_CACHE_Eps2Inst0DeviceHealthInfoType_t * const p_data)
{
    return dc_get_raw_data(DC_DID_EPS2_BP_INST0_DEVICE_HEALTH_INFO_DATA,
                           p_data,
                           sizeof(DATA_CACHE_Eps2Inst0DeviceHealthInfoType_t),
                           0U,
                           sizeof(DATA_CACHE_Eps2Inst0DeviceHealthInfoType_t));
}

void dc_set_eps2_bp_inst0_device_health_info_data(DATA_CACHE_Eps2Inst0DeviceHealthInfoType_t * const p_new_data)
{
    dc_set_raw_data(DC_DATA_INPUT_INTERNAL, DC_DID_EPS2_BP_INST0_DEVICE_HEALTH_INFO_DATA, p_new_data, sizeof(DATA_CACHE_Eps2Inst0DeviceHealthInfoType_t));
}

dc_data_status_t dc_get_eps2_bp_inst0_ina_sensor1_data(DATA_CACHE_Eps2Inst0InaSensors1Type_t * const p_data)
{
    return dc_get_raw_data(DC_DID_EPS2_BP_INST0_INA_SENSOR1_DATA,
                           p_data,
                           sizeof(DATA_CACHE_Eps2Inst0InaSensors1Type_t),
                           0U,
                           sizeof(DATA_CACHE_Eps2Inst0InaSensors1Type_t));
}

void dc_set_eps2_bp_inst0_ina_sensor1_data(DATA_CACHE_Eps2Inst0InaSensors1Type_t * const p_new_data)
{
    dc_set_raw_data(DC_DATA_INPUT_INTERNAL, DC_DID_EPS2_BP_INST0_INA_SENSOR1_DATA, p_new_data, sizeof(DATA_CACHE_Eps2Inst0InaSensors1Type_t));
}

dc_data_status_t dc_get_eps2_bp_inst0_ina_sensor2_data(DATA_CACHE_Eps2Inst0InaSensors2Type_t * const p_data)
{
    return dc_get_raw_data(DC_DID_EPS2_BP_INST0_INA_SENSOR2_DATA,
                           p_data,
                           sizeof(DATA_CACHE_Eps2Inst0InaSensors2Type_t),
                           0U,
                           sizeof(DATA_CACHE_Eps2Inst0InaSensors2Type_t));
}

void dc_set_eps2_bp_inst0_ina_sensor2_data(DATA_CACHE_Eps2Inst0InaSensors2Type_t * const p_new_data)
{
    dc_set_raw_data(DC_DATA_INPUT_INTERNAL, DC_DID_EPS2_BP_INST0_INA_SENSOR2_DATA, p_new_data, sizeof(DATA_CACHE_Eps2Inst0InaSensors2Type_t));
}

dc_data_status_t dc_get_eps2_bp_inst0_balancer_info_data(DATA_CACHE_Eps2Inst0BalancerInfoType_t * const p_data)
{
    return dc_get_raw_data(DC_DID_EPS2_BP_INST0_BALANCER_INFO_DATA,
                           p_data,
                           sizeof(DATA_CACHE_Eps2Inst0BalancerInfoType_t),
                           0U,
                           sizeof(DATA_CACHE_Eps2Inst0BalancerInfoType_t));
}

void dc_set_eps2_bp_inst0_balancer_info_data(DATA_CACHE_Eps2Inst0BalancerInfoType_t * const p_new_data)
{
    dc_set_raw_data(DC_DATA_INPUT_INTERNAL, DC_DID_EPS2_BP_INST0_BALANCER_INFO_DATA, p_new_data, sizeof(DATA_CACHE_Eps2Inst0BalancerInfoType_t));
}

dc_data_status_t dc_get_eps2_bp_inst0_balancer_status_data(DATA_CACHE_Eps2Inst0BalancerStatusType_t * const p_data)
{
    return dc_get_raw_data(DC_DID_EPS2_BP_INST0_BALANCER_STATUS_DATA,
                           p_data,
                           sizeof(DATA_CACHE_Eps2Inst0BalancerStatusType_t),
                           0U,
                           sizeof(DATA_CACHE_Eps2Inst0BalancerStatusType_t));
}

void dc_set_eps2_bp_inst0_balancer_status_data(DATA_CACHE_Eps2Inst0BalancerStatusType_t * const p_new_data)
{
    dc_set_raw_data(DC_DATA_INPUT_INTERNAL, DC_DID_EPS2_BP_INST0_BALANCER_STATUS_DATA, p_new_data, sizeof(DATA_CACHE_Eps2Inst0BalancerStatusType_t));
}

dc_data_status_t dc_get_eps2_bp_inst0_balancer_cells_info_data(DATA_CACHE_Eps2Inst0BalancerCellsInfoType_t * const p_data)
{
    return dc_get_raw_data(DC_DID_EPS2_BP_INST0_BALANCER_CELLS_INFO_DATA,
                           p_data,
                           sizeof(DATA_CACHE_Eps2Inst0BalancerCellsInfoType_t),
                           0U,
                           sizeof(DATA_CACHE_Eps2Inst0BalancerCellsInfoType_t));
}

void dc_set_eps2_bp_inst0_balancer_cells_info_data(DATA_CACHE_Eps2Inst0BalancerCellsInfoType_t * const p_new_data)
{
    dc_set_raw_data(DC_DATA_INPUT_INTERNAL, DC_DID_EPS2_BP_INST0_BALANCER_CELLS_INFO_DATA, p_new_data, sizeof(DATA_CACHE_Eps2Inst0BalancerCellsInfoType_t));
}

dc_data_status_t dc_get_eps2_bp_inst0_charger_xp_data(DATA_CACHE_Eps2Inst0ChargerXpType_t * const p_data)
{
    return dc_get_raw_data(DC_DID_EPS2_BP_INST0_CHARGER_XP_DATA,
                           p_data,
                           sizeof(DATA_CACHE_Eps2Inst0ChargerXpType_t),
                           0U,
                           sizeof(DATA_CACHE_Eps2Inst0ChargerXpType_t));
}

void dc_set_eps2_bp_inst0_charger_xp_data(DATA_CACHE_Eps2Inst0ChargerXpType_t * const p_new_data)
{
    dc_set_raw_data(DC_DATA_INPUT_INTERNAL, DC_DID_EPS2_BP_INST0_CHARGER_XP_DATA, p_new_data, sizeof(DATA_CACHE_Eps2Inst0ChargerXpType_t));
}

dc_data_status_t dc_get_eps2_bp_inst0_charger_xr_data(DATA_CACHE_Eps2Inst0ChargerXrType_t * const p_data)
{
    return dc_get_raw_data(DC_DID_EPS2_BP_INST0_CHARGER_XR_DATA,
                           p_data,
                           sizeof(DATA_CACHE_Eps2Inst0ChargerXrType_t),
                           0U,
                           sizeof(DATA_CACHE_Eps2Inst0ChargerXrType_t));
}

void dc_set_eps2_bp_inst0_charger_xr_data(DATA_CACHE_Eps2Inst0ChargerXrType_t * const p_new_data)
{
    dc_set_raw_data(DC_DATA_INPUT_INTERNAL, DC_DID_EPS2_BP_INST0_CHARGER_XR_DATA, p_new_data, sizeof(DATA_CACHE_Eps2Inst0ChargerXrType_t));
}

dc_data_status_t dc_get_eps2_bp_inst0_charger_yp_data(DATA_CACHE_Eps2Inst0ChargerYpType_t * const p_data)
{
    return dc_get_raw_data(DC_DID_EPS2_BP_INST0_CHARGER_YP_DATA,
                           p_data,
                           sizeof(DATA_CACHE_Eps2Inst0ChargerYpType_t),
                           0U,
                           sizeof(DATA_CACHE_Eps2Inst0ChargerYpType_t));
}

void dc_set_eps2_bp_inst0_charger_yp_data(DATA_CACHE_Eps2Inst0ChargerYpType_t * const p_new_data)
{
    dc_set_raw_data(DC_DATA_INPUT_INTERNAL, DC_DID_EPS2_BP_INST0_CHARGER_YP_DATA, p_new_data, sizeof(DATA_CACHE_Eps2Inst0ChargerYpType_t));
}

dc_data_status_t dc_get_eps2_bp_inst0_charger_yr_data(DATA_CACHE_Eps2Inst0ChargerYrType_t * const p_data)
{
    return dc_get_raw_data(DC_DID_EPS2_BP_INST0_CHARGER_YR_DATA,
                           p_data,
                           sizeof(DATA_CACHE_Eps2Inst0ChargerYrType_t),
                           0U,
                           sizeof(DATA_CACHE_Eps2Inst0ChargerYrType_t));
}

void dc_set_eps2_bp_inst0_charger_yr_data(DATA_CACHE_Eps2Inst0ChargerYrType_t * const p_new_data)
{
    dc_set_raw_data(DC_DATA_INPUT_INTERNAL, DC_DID_EPS2_BP_INST0_CHARGER_YR_DATA, p_new_data, sizeof(DATA_CACHE_Eps2Inst0ChargerYrType_t));
}

dc_data_status_t dc_get_eps2_bp_inst0_charger_zp_data(DATA_CACHE_Eps2Inst0ChargerZpType_t * const p_data)
{
    return dc_get_raw_data(DC_DID_EPS2_BP_INST0_CHARGER_ZP_DATA,
                           p_data,
                           sizeof(DATA_CACHE_Eps2Inst0ChargerZpType_t),
                           0U,
                           sizeof(DATA_CACHE_Eps2Inst0ChargerZpType_t));
}

void dc_set_eps2_bp_inst0_charger_zp_data(DATA_CACHE_Eps2Inst0ChargerZpType_t * const p_new_data)
{
    dc_set_raw_data(DC_DATA_INPUT_INTERNAL, DC_DID_EPS2_BP_INST0_CHARGER_ZP_DATA, p_new_data, sizeof(DATA_CACHE_Eps2Inst0ChargerZpType_t));
}

dc_data_status_t dc_get_eps2_bp_inst0_charger_zr_data(DATA_CACHE_Eps2Inst0ChargerZrType_t * const p_data)
{
    return dc_get_raw_data(DC_DID_EPS2_BP_INST0_CHARGER_ZR_DATA,
                           p_data,
                           sizeof(DATA_CACHE_Eps2Inst0ChargerZrType_t),
                           0U,
                           sizeof(DATA_CACHE_Eps2Inst0ChargerZrType_t));
}

void dc_set_eps2_bp_inst0_charger_zr_data(DATA_CACHE_Eps2Inst0ChargerZrType_t * const p_new_data)
{
    dc_set_raw_data(DC_DATA_INPUT_INTERNAL, DC_DID_EPS2_BP_INST0_CHARGER_ZR_DATA, p_new_data, sizeof(DATA_CACHE_Eps2Inst0ChargerZrType_t));
}

dc_data_status_t dc_get_fdir_eps_ii_bp_inst0_cmd_exec_status_data(DATA_CACHE_Eps2Inst0_FDIR_CMD_EXEC_STATUS_type_t * const p_data)
{
    return dc_get_raw_data(DC_DID_FDIR_EPS_II_BP_INST0_CMD_EXEC_STATUS_DATA,
                           p_data,
                           sizeof(DATA_CACHE_Eps2Inst0_FDIR_CMD_EXEC_STATUS_type_t),
                           0U,
                           sizeof(DATA_CACHE_Eps2Inst0_FDIR_CMD_EXEC_STATUS_type_t));
}

void dc_set_fdir_eps_ii_bp_inst0_cmd_exec_status_data(DATA_CACHE_Eps2Inst0_FDIR_CMD_EXEC_STATUS_type_t * const p_new_data)
{
    dc_set_raw_data(DC_DATA_INPUT_INTERNAL, DC_DID_FDIR_EPS_II_BP_INST0_CMD_EXEC_STATUS_DATA, p_new_data, sizeof(DATA_CACHE_Eps2Inst0_FDIR_CMD_EXEC_STATUS_type_t));
}

dc_data_status_t dc_get_eps3_bp_inst0_uptime_in_seconds(DATA_CACHE_Eps3Inst0_UpTimeInSecondsType_t * const p_data)
{
    return dc_get_raw_data(DC_DID_EPS3_BP_INST0_UPTIME_IN_SECONDS,
                           p_data,
                           sizeof(DATA_CACHE_Eps3Inst0_UpTimeInSecondsType_t),
                           0U,
                           sizeof(DATA_CACHE_Eps3Inst0_UpTimeInSecondsType_t));
}

void dc_set_eps3_bp_inst0_uptime_in_seconds(DATA_CACHE_Eps3Inst0_UpTimeInSecondsType_t * const p_new_data)
{
    dc_set_raw_data(DC_DATA_INPUT_INTERNAL, DC_DID_EPS3_BP_INST0_UPTIME_IN_SECONDS, p_new_data, sizeof(DATA_CACHE_Eps3Inst0_UpTimeInSecondsType_t));
}

dc_data_status_t dc_get_eps3_bp_inst0common(DATA_CACHE_Eps3Inst0CommonMeasurementType_t * const p_data)
{
    return dc_get_raw_data(DC_DID_EPS3_BP_INST0COMMON,
                           p_data,
                           sizeof(DATA_CACHE_Eps3Inst0CommonMeasurementType_t),
                           0U,
                           sizeof(DATA_CACHE_Eps3Inst0CommonMeasurementType_t));
}

void dc_set_eps3_bp_inst0common(DATA_CACHE_Eps3Inst0CommonMeasurementType_t * const p_new_data)
{
    dc_set_raw_data(DC_DATA_INPUT_INTERNAL, DC_DID_EPS3_BP_INST0COMMON, p_new_data, sizeof(DATA_CACHE_Eps3Inst0CommonMeasurementType_t));
}

dc_data_status_t dc_get_eps3_bp_inst0hib_mode_status(DATA_CACHE_Eps3Inst0HIBModeStatusType_t * const p_data)
{
    return dc_get_raw_data(DC_DID_EPS3_BP_INST0HIB_MODE_STATUS,
                           p_data,
                           sizeof(DATA_CACHE_Eps3Inst0HIBModeStatusType_t),
                           0U,
                           sizeof(DATA_CACHE_Eps3Inst0HIBModeStatusType_t));
}

void dc_set_eps3_bp_inst0hib_mode_status(DATA_CACHE_Eps3Inst0HIBModeStatusType_t * const p_new_data)
{
    dc_set_raw_data(DC_DATA_INPUT_INTERNAL, DC_DID_EPS3_BP_INST0HIB_MODE_STATUS, p_new_data, sizeof(DATA_CACHE_Eps3Inst0HIBModeStatusType_t));
}

dc_data_status_t dc_get_eps3_bp_inst0measurements(DATA_CACHE_Eps3Inst0MeasurementsType_t * const p_data)
{
    return dc_get_raw_data(DC_DID_EPS3_BP_INST0MEASUREMENTS,
                           p_data,
                           sizeof(DATA_CACHE_Eps3Inst0MeasurementsType_t),
                           0U,
                           sizeof(DATA_CACHE_Eps3Inst0MeasurementsType_t));
}

void dc_set_eps3_bp_inst0measurements(DATA_CACHE_Eps3Inst0MeasurementsType_t * const p_new_data)
{
    dc_set_raw_data(DC_DATA_INPUT_INTERNAL, DC_DID_EPS3_BP_INST0MEASUREMENTS, p_new_data, sizeof(DATA_CACHE_Eps3Inst0MeasurementsType_t));
}

dc_data_status_t dc_get_eps3_bp_inst0discharging_state(DATA_CACHE_Eps3Inst0DischargeStateType_t * const p_data)
{
    return dc_get_raw_data(DC_DID_EPS3_BP_INST0DISCHARGING_STATE,
                           p_data,
                           sizeof(DATA_CACHE_Eps3Inst0DischargeStateType_t),
                           0U,
                           sizeof(DATA_CACHE_Eps3Inst0DischargeStateType_t));
}

void dc_set_eps3_bp_inst0discharging_state(DATA_CACHE_Eps3Inst0DischargeStateType_t * const p_new_data)
{
    dc_set_raw_data(DC_DATA_INPUT_INTERNAL, DC_DID_EPS3_BP_INST0DISCHARGING_STATE, p_new_data, sizeof(DATA_CACHE_Eps3Inst0DischargeStateType_t));
}

dc_data_status_t dc_get_eps3_bp_inst0charge_status(DATA_CACHE_Eps3Inst0ChargeOnStatusType_t * const p_data)
{
    return dc_get_raw_data(DC_DID_EPS3_BP_INST0CHARGE_STATUS,
                           p_data,
                           sizeof(DATA_CACHE_Eps3Inst0ChargeOnStatusType_t),
                           0U,
                           sizeof(DATA_CACHE_Eps3Inst0ChargeOnStatusType_t));
}

void dc_set_eps3_bp_inst0charge_status(DATA_CACHE_Eps3Inst0ChargeOnStatusType_t * const p_new_data)
{
    dc_set_raw_data(DC_DATA_INPUT_INTERNAL, DC_DID_EPS3_BP_INST0CHARGE_STATUS, p_new_data, sizeof(DATA_CACHE_Eps3Inst0ChargeOnStatusType_t));
}

dc_data_status_t dc_get_eps3_bp_inst0balancers_status(DATA_CACHE_Eps3Inst0BalancersStatusType_t * const p_data)
{
    return dc_get_raw_data(DC_DID_EPS3_BP_INST0BALANCERS_STATUS,
                           p_data,
                           sizeof(DATA_CACHE_Eps3Inst0BalancersStatusType_t),
                           0U,
                           sizeof(DATA_CACHE_Eps3Inst0BalancersStatusType_t));
}

void dc_set_eps3_bp_inst0balancers_status(DATA_CACHE_Eps3Inst0BalancersStatusType_t * const p_new_data)
{
    dc_set_raw_data(DC_DATA_INPUT_INTERNAL, DC_DID_EPS3_BP_INST0BALANCERS_STATUS, p_new_data, sizeof(DATA_CACHE_Eps3Inst0BalancersStatusType_t));
}

dc_data_status_t dc_get_eps3_bp_inst0battery_cells_status(DATA_CACHE_Eps3Inst0BatteryCellsStatusType_t * const p_data)
{
    return dc_get_raw_data(DC_DID_EPS3_BP_INST0BATTERY_CELLS_STATUS,
                           p_data,
                           sizeof(DATA_CACHE_Eps3Inst0BatteryCellsStatusType_t),
                           0U,
                           sizeof(DATA_CACHE_Eps3Inst0BatteryCellsStatusType_t));
}

void dc_set_eps3_bp_inst0battery_cells_status(DATA_CACHE_Eps3Inst0BatteryCellsStatusType_t * const p_new_data)
{
    dc_set_raw_data(DC_DATA_INPUT_INTERNAL, DC_DID_EPS3_BP_INST0BATTERY_CELLS_STATUS, p_new_data, sizeof(DATA_CACHE_Eps3Inst0BatteryCellsStatusType_t));
}

dc_data_status_t dc_get_eps3_bp_inst0heaters_status(DATA_CACHE_Eps3Inst0HeatersStatusType_t * const p_data)
{
    return dc_get_raw_data(DC_DID_EPS3_BP_INST0HEATERS_STATUS,
                           p_data,
                           sizeof(DATA_CACHE_Eps3Inst0HeatersStatusType_t),
                           0U,
                           sizeof(DATA_CACHE_Eps3Inst0HeatersStatusType_t));
}

void dc_set_eps3_bp_inst0heaters_status(DATA_CACHE_Eps3Inst0HeatersStatusType_t * const p_new_data)
{
    dc_set_raw_data(DC_DATA_INPUT_INTERNAL, DC_DID_EPS3_BP_INST0HEATERS_STATUS, p_new_data, sizeof(DATA_CACHE_Eps3Inst0HeatersStatusType_t));
}

dc_data_status_t dc_get_eps3_bp_inst0_cmd_exec_status_data(DATA_CACHE_Eps3Inst0_FDIR_CMD_EXEC_STATUS_type_t * const p_data)
{
    return dc_get_raw_data(DC_DID_EPS3_BP_INST0_CMD_EXEC_STATUS_DATA,
                           p_data,
                           sizeof(DATA_CACHE_Eps3Inst0_FDIR_CMD_EXEC_STATUS_type_t),
                           0U,
                           sizeof(DATA_CACHE_Eps3Inst0_FDIR_CMD_EXEC_STATUS_type_t));
}

void dc_set_eps3_bp_inst0_cmd_exec_status_data(DATA_CACHE_Eps3Inst0_FDIR_CMD_EXEC_STATUS_type_t * const p_new_data)
{
    dc_set_raw_data(DC_DATA_INPUT_INTERNAL, DC_DID_EPS3_BP_INST0_CMD_EXEC_STATUS_DATA, p_new_data, sizeof(DATA_CACHE_Eps3Inst0_FDIR_CMD_EXEC_STATUS_type_t));
}

dc_data_status_t dc_get_dumb_data(DATA_CACHE_VoltAmps_t * const p_data)
{
    return dc_get_raw_data(DC_DID_DUMB_DATA,
                           p_data,
                           sizeof(DATA_CACHE_VoltAmps_t),
                           0U,
                           sizeof(DATA_CACHE_VoltAmps_t));
}

void dc_set_dumb_data(DATA_CACHE_VoltAmps_t * const p_new_data)
{
    dc_set_raw_data(DC_DATA_INPUT_INTERNAL, DC_DID_DUMB_DATA, p_new_data, sizeof(DATA_CACHE_VoltAmps_t));
}

dc_data_status_t dc_get_dumb_data1(DATA_CACHE_VoltAllAmps_t * const p_data)
{
    return dc_get_raw_data(DC_DID_DUMB_DATA1,
                           p_data,
                           sizeof(DATA_CACHE_VoltAllAmps_t),
                           0U,
                           sizeof(DATA_CACHE_VoltAllAmps_t));
}

void dc_set_dumb_data1(DATA_CACHE_VoltAllAmps_t * const p_new_data)
{
    dc_set_raw_data(DC_DATA_INPUT_INTERNAL, DC_DID_DUMB_DATA1, p_new_data, sizeof(DATA_CACHE_VoltAllAmps_t));
}

dc_data_status_t dc_get_dumb_data3(DATA_CACHE_MpptState_str_t * const p_data)
{
    return dc_get_raw_data(DC_DID_DUMB_DATA3,
                           p_data,
                           sizeof(DATA_CACHE_MpptState_str_t),
                           0U,
                           sizeof(DATA_CACHE_MpptState_str_t));
}

void dc_set_dumb_data3(DATA_CACHE_MpptState_str_t * const p_new_data)
{
    dc_set_raw_data(DC_DATA_INPUT_INTERNAL, DC_DID_DUMB_DATA3, p_new_data, sizeof(DATA_CACHE_MpptState_str_t));
}

dc_data_status_t dc_get_dumb_data4(DATA_CACHE_ReadEnDftStatus_t * const p_data)
{
    return dc_get_raw_data(DC_DID_DUMB_DATA4,
                           p_data,
                           sizeof(DATA_CACHE_ReadEnDftStatus_t),
                           0U,
                           sizeof(DATA_CACHE_ReadEnDftStatus_t));
}

void dc_set_dumb_data4(DATA_CACHE_ReadEnDftStatus_t * const p_new_data)
{
    dc_set_raw_data(DC_DATA_INPUT_INTERNAL, DC_DID_DUMB_DATA4, p_new_data, sizeof(DATA_CACHE_ReadEnDftStatus_t));
}

dc_data_status_t dc_get_dumb_data5(DATA_CACHE_OnOffStatus_t * const p_data)
{
    return dc_get_raw_data(DC_DID_DUMB_DATA5,
                           p_data,
                           sizeof(DATA_CACHE_OnOffStatus_t),
                           0U,
                           sizeof(DATA_CACHE_OnOffStatus_t));
}

void dc_set_dumb_data5(DATA_CACHE_OnOffStatus_t * const p_new_data)
{
    dc_set_raw_data(DC_DATA_INPUT_INTERNAL, DC_DID_DUMB_DATA5, p_new_data, sizeof(DATA_CACHE_OnOffStatus_t));
}

dc_data_status_t dc_get_dumb_data6(DATA_CACHE_ReadLvlState_t * const p_data)
{
    return dc_get_raw_data(DC_DID_DUMB_DATA6,
                           p_data,
                           sizeof(DATA_CACHE_ReadLvlState_t),
                           0U,
                           sizeof(DATA_CACHE_ReadLvlState_t));
}

void dc_set_dumb_data6(DATA_CACHE_ReadLvlState_t * const p_new_data)
{
    dc_set_raw_data(DC_DATA_INPUT_INTERNAL, DC_DID_DUMB_DATA6, p_new_data, sizeof(DATA_CACHE_ReadLvlState_t));
}

dc_data_status_t dc_get_eps3_pdm_a_inst0_uptime_in_seconds(DATA_CACHE_Eps3_PDM_A_Inst0_UpTimeInSecondsType_t * const p_data)
{
    return dc_get_raw_data(DC_DID_EPS3_PDM_A_INST0_UPTIME_IN_SECONDS,
                           p_data,
                           sizeof(DATA_CACHE_Eps3_PDM_A_Inst0_UpTimeInSecondsType_t),
                           0U,
                           sizeof(DATA_CACHE_Eps3_PDM_A_Inst0_UpTimeInSecondsType_t));
}

void dc_set_eps3_pdm_a_inst0_uptime_in_seconds(DATA_CACHE_Eps3_PDM_A_Inst0_UpTimeInSecondsType_t * const p_new_data)
{
    dc_set_raw_data(DC_DATA_INPUT_INTERNAL, DC_DID_EPS3_PDM_A_INST0_UPTIME_IN_SECONDS, p_new_data, sizeof(DATA_CACHE_Eps3_PDM_A_Inst0_UpTimeInSecondsType_t));
}

dc_data_status_t dc_get_eps3_pdm_a_inst0_common(DATA_CACHE_Eps3_PDM_A_Inst0_CommonMesurementsType_t * const p_data)
{
    return dc_get_raw_data(DC_DID_EPS3_PDM_A_INST0_COMMON,
                           p_data,
                           sizeof(DATA_CACHE_Eps3_PDM_A_Inst0_CommonMesurementsType_t),
                           0U,
                           sizeof(DATA_CACHE_Eps3_PDM_A_Inst0_CommonMesurementsType_t));
}

void dc_set_eps3_pdm_a_inst0_common(DATA_CACHE_Eps3_PDM_A_Inst0_CommonMesurementsType_t * const p_new_data)
{
    dc_set_raw_data(DC_DATA_INPUT_INTERNAL, DC_DID_EPS3_PDM_A_INST0_COMMON, p_new_data, sizeof(DATA_CACHE_Eps3_PDM_A_Inst0_CommonMesurementsType_t));
}

dc_data_status_t dc_get_eps3_pdm_a_inst0_hib_mode(DATA_CACHE_Eps3_PDM_A_Inst0_HibModeType_t * const p_data)
{
    return dc_get_raw_data(DC_DID_EPS3_PDM_A_INST0_HIB_MODE,
                           p_data,
                           sizeof(DATA_CACHE_Eps3_PDM_A_Inst0_HibModeType_t),
                           0U,
                           sizeof(DATA_CACHE_Eps3_PDM_A_Inst0_HibModeType_t));
}

void dc_set_eps3_pdm_a_inst0_hib_mode(DATA_CACHE_Eps3_PDM_A_Inst0_HibModeType_t * const p_new_data)
{
    dc_set_raw_data(DC_DATA_INPUT_INTERNAL, DC_DID_EPS3_PDM_A_INST0_HIB_MODE, p_new_data, sizeof(DATA_CACHE_Eps3_PDM_A_Inst0_HibModeType_t));
}

dc_data_status_t dc_get_eps3_pdm_a_inst0_general_outputs(DATA_CACHE_Eps3_PDM_A_Inst0_OutputsStatusType_t * const p_data)
{
    return dc_get_raw_data(DC_DID_EPS3_PDM_A_INST0_GENERAL_OUTPUTS,
                           p_data,
                           sizeof(DATA_CACHE_Eps3_PDM_A_Inst0_OutputsStatusType_t),
                           0U,
                           sizeof(DATA_CACHE_Eps3_PDM_A_Inst0_OutputsStatusType_t));
}

void dc_set_eps3_pdm_a_inst0_general_outputs(DATA_CACHE_Eps3_PDM_A_Inst0_OutputsStatusType_t * const p_new_data)
{
    dc_set_raw_data(DC_DATA_INPUT_INTERNAL, DC_DID_EPS3_PDM_A_INST0_GENERAL_OUTPUTS, p_new_data, sizeof(DATA_CACHE_Eps3_PDM_A_Inst0_OutputsStatusType_t));
}

dc_data_status_t dc_get_eps3_pdm_a_inst0_general_faults(DATA_CACHE_Eps3_PDM_A_Inst0_FaultsStatusType_t * const p_data)
{
    return dc_get_raw_data(DC_DID_EPS3_PDM_A_INST0_GENERAL_FAULTS,
                           p_data,
                           sizeof(DATA_CACHE_Eps3_PDM_A_Inst0_FaultsStatusType_t),
                           0U,
                           sizeof(DATA_CACHE_Eps3_PDM_A_Inst0_FaultsStatusType_t));
}

void dc_set_eps3_pdm_a_inst0_general_faults(DATA_CACHE_Eps3_PDM_A_Inst0_FaultsStatusType_t * const p_new_data)
{
    dc_set_raw_data(DC_DATA_INPUT_INTERNAL, DC_DID_EPS3_PDM_A_INST0_GENERAL_FAULTS, p_new_data, sizeof(DATA_CACHE_Eps3_PDM_A_Inst0_FaultsStatusType_t));
}

dc_data_status_t dc_get_eps3_pdm_a_inst0_all_measurements(DATA_CACHE_Eps3_PDM_A_Inst0_VoltAmpsMeasurementsType_t * const p_data)
{
    return dc_get_raw_data(DC_DID_EPS3_PDM_A_INST0_ALL_MEASUREMENTS,
                           p_data,
                           sizeof(DATA_CACHE_Eps3_PDM_A_Inst0_VoltAmpsMeasurementsType_t),
                           0U,
                           sizeof(DATA_CACHE_Eps3_PDM_A_Inst0_VoltAmpsMeasurementsType_t));
}

void dc_set_eps3_pdm_a_inst0_all_measurements(DATA_CACHE_Eps3_PDM_A_Inst0_VoltAmpsMeasurementsType_t * const p_new_data)
{
    dc_set_raw_data(DC_DATA_INPUT_INTERNAL, DC_DID_EPS3_PDM_A_INST0_ALL_MEASUREMENTS, p_new_data, sizeof(DATA_CACHE_Eps3_PDM_A_Inst0_VoltAmpsMeasurementsType_t));
}

dc_data_status_t dc_get_eps3_pdm_a_inst0_cmd_exec_status_data(DATA_CACHE_Eps3_PDM_A_Inst0_FDIR_CMD_EXEC_STATUS_type_t * const p_data)
{
    return dc_get_raw_data(DC_DID_EPS3_PDM_A_INST0_CMD_EXEC_STATUS_DATA,
                           p_data,
                           sizeof(DATA_CACHE_Eps3_PDM_A_Inst0_FDIR_CMD_EXEC_STATUS_type_t),
                           0U,
                           sizeof(DATA_CACHE_Eps3_PDM_A_Inst0_FDIR_CMD_EXEC_STATUS_type_t));
}

void dc_set_eps3_pdm_a_inst0_cmd_exec_status_data(DATA_CACHE_Eps3_PDM_A_Inst0_FDIR_CMD_EXEC_STATUS_type_t * const p_new_data)
{
    dc_set_raw_data(DC_DATA_INPUT_INTERNAL, DC_DID_EPS3_PDM_A_INST0_CMD_EXEC_STATUS_DATA, p_new_data, sizeof(DATA_CACHE_Eps3_PDM_A_Inst0_FDIR_CMD_EXEC_STATUS_type_t));
}

dc_data_status_t dc_get_eps3_pdm_b_inst0_cmd_exec_status_data(DATA_CACHE_Eps3_PDM_B_Inst0_FDIR_CMD_EXEC_STATUS_type_t * const p_data)
{
    return dc_get_raw_data(DC_DID_EPS3_PDM_B_INST0_CMD_EXEC_STATUS_DATA,
                           p_data,
                           sizeof(DATA_CACHE_Eps3_PDM_B_Inst0_FDIR_CMD_EXEC_STATUS_type_t),
                           0U,
                           sizeof(DATA_CACHE_Eps3_PDM_B_Inst0_FDIR_CMD_EXEC_STATUS_type_t));
}

void dc_set_eps3_pdm_b_inst0_cmd_exec_status_data(DATA_CACHE_Eps3_PDM_B_Inst0_FDIR_CMD_EXEC_STATUS_type_t * const p_new_data)
{
    dc_set_raw_data(DC_DATA_INPUT_INTERNAL, DC_DID_EPS3_PDM_B_INST0_CMD_EXEC_STATUS_DATA, p_new_data, sizeof(DATA_CACHE_Eps3_PDM_B_Inst0_FDIR_CMD_EXEC_STATUS_type_t));
}

dc_data_status_t dc_get_eps3_pdm_b_inst0_uptime_in_seconds(DATA_CACHE_Eps3_PDM_B_Inst0_UpTimeInSecondsType_t * const p_data)
{
    return dc_get_raw_data(DC_DID_EPS3_PDM_B_INST0_UPTIME_IN_SECONDS,
                           p_data,
                           sizeof(DATA_CACHE_Eps3_PDM_B_Inst0_UpTimeInSecondsType_t),
                           0U,
                           sizeof(DATA_CACHE_Eps3_PDM_B_Inst0_UpTimeInSecondsType_t));
}

void dc_set_eps3_pdm_b_inst0_uptime_in_seconds(DATA_CACHE_Eps3_PDM_B_Inst0_UpTimeInSecondsType_t * const p_new_data)
{
    dc_set_raw_data(DC_DATA_INPUT_INTERNAL, DC_DID_EPS3_PDM_B_INST0_UPTIME_IN_SECONDS, p_new_data, sizeof(DATA_CACHE_Eps3_PDM_B_Inst0_UpTimeInSecondsType_t));
}

dc_data_status_t dc_get_eps3_pdm_b_inst0_common(DATA_CACHE_Eps3_PDM_B_Inst0_CommonMeasurementType_t * const p_data)
{
    return dc_get_raw_data(DC_DID_EPS3_PDM_B_INST0_COMMON,
                           p_data,
                           sizeof(DATA_CACHE_Eps3_PDM_B_Inst0_CommonMeasurementType_t),
                           0U,
                           sizeof(DATA_CACHE_Eps3_PDM_B_Inst0_CommonMeasurementType_t));
}

void dc_set_eps3_pdm_b_inst0_common(DATA_CACHE_Eps3_PDM_B_Inst0_CommonMeasurementType_t * const p_new_data)
{
    dc_set_raw_data(DC_DATA_INPUT_INTERNAL, DC_DID_EPS3_PDM_B_INST0_COMMON, p_new_data, sizeof(DATA_CACHE_Eps3_PDM_B_Inst0_CommonMeasurementType_t));
}

dc_data_status_t dc_get_eps3_pdm_b_inst0_hib_mode(DATA_CACHE_Eps3_PDM_B_Inst0_hib_mode_Type_t * const p_data)
{
    return dc_get_raw_data(DC_DID_EPS3_PDM_B_INST0_HIB_MODE,
                           p_data,
                           sizeof(DATA_CACHE_Eps3_PDM_B_Inst0_hib_mode_Type_t),
                           0U,
                           sizeof(DATA_CACHE_Eps3_PDM_B_Inst0_hib_mode_Type_t));
}

void dc_set_eps3_pdm_b_inst0_hib_mode(DATA_CACHE_Eps3_PDM_B_Inst0_hib_mode_Type_t * const p_new_data)
{
    dc_set_raw_data(DC_DATA_INPUT_INTERNAL, DC_DID_EPS3_PDM_B_INST0_HIB_MODE, p_new_data, sizeof(DATA_CACHE_Eps3_PDM_B_Inst0_hib_mode_Type_t));
}

dc_data_status_t dc_get_eps3_pdm_b_inst0_general_outputs(DATA_CACHE_Eps3_PDM_B_Inst0_OutputsStatus_type_t * const p_data)
{
    return dc_get_raw_data(DC_DID_EPS3_PDM_B_INST0_GENERAL_OUTPUTS,
                           p_data,
                           sizeof(DATA_CACHE_Eps3_PDM_B_Inst0_OutputsStatus_type_t),
                           0U,
                           sizeof(DATA_CACHE_Eps3_PDM_B_Inst0_OutputsStatus_type_t));
}

void dc_set_eps3_pdm_b_inst0_general_outputs(DATA_CACHE_Eps3_PDM_B_Inst0_OutputsStatus_type_t * const p_new_data)
{
    dc_set_raw_data(DC_DATA_INPUT_INTERNAL, DC_DID_EPS3_PDM_B_INST0_GENERAL_OUTPUTS, p_new_data, sizeof(DATA_CACHE_Eps3_PDM_B_Inst0_OutputsStatus_type_t));
}

dc_data_status_t dc_get_eps3_pdm_b_inst0_channel_flag_state(DATA_CACHE_Eps3_PDM_B_Inst0_ChannelFlagState_type_t * const p_data)
{
    return dc_get_raw_data(DC_DID_EPS3_PDM_B_INST0_CHANNEL_FLAG_STATE,
                           p_data,
                           sizeof(DATA_CACHE_Eps3_PDM_B_Inst0_ChannelFlagState_type_t),
                           0U,
                           sizeof(DATA_CACHE_Eps3_PDM_B_Inst0_ChannelFlagState_type_t));
}

void dc_set_eps3_pdm_b_inst0_channel_flag_state(DATA_CACHE_Eps3_PDM_B_Inst0_ChannelFlagState_type_t * const p_new_data)
{
    dc_set_raw_data(DC_DATA_INPUT_INTERNAL, DC_DID_EPS3_PDM_B_INST0_CHANNEL_FLAG_STATE, p_new_data, sizeof(DATA_CACHE_Eps3_PDM_B_Inst0_ChannelFlagState_type_t));
}

dc_data_status_t dc_get_eps3_pdm_b_inst0_temperature(DATA_CACHE_Eps3_PDM_B_Inst0_Temps_type_t * const p_data)
{
    return dc_get_raw_data(DC_DID_EPS3_PDM_B_INST0_TEMPERATURE,
                           p_data,
                           sizeof(DATA_CACHE_Eps3_PDM_B_Inst0_Temps_type_t),
                           0U,
                           sizeof(DATA_CACHE_Eps3_PDM_B_Inst0_Temps_type_t));
}

void dc_set_eps3_pdm_b_inst0_temperature(DATA_CACHE_Eps3_PDM_B_Inst0_Temps_type_t * const p_new_data)
{
    dc_set_raw_data(DC_DATA_INPUT_INTERNAL, DC_DID_EPS3_PDM_B_INST0_TEMPERATURE, p_new_data, sizeof(DATA_CACHE_Eps3_PDM_B_Inst0_Temps_type_t));
}

dc_data_status_t dc_get_eps3_pdm_b_inst0_all_measurements(DATA_CACHE_Eps3_PDM_B_Inst0_VoltAmpsMeasurements_type_t * const p_data)
{
    return dc_get_raw_data(DC_DID_EPS3_PDM_B_INST0_ALL_MEASUREMENTS,
                           p_data,
                           sizeof(DATA_CACHE_Eps3_PDM_B_Inst0_VoltAmpsMeasurements_type_t),
                           0U,
                           sizeof(DATA_CACHE_Eps3_PDM_B_Inst0_VoltAmpsMeasurements_type_t));
}

void dc_set_eps3_pdm_b_inst0_all_measurements(DATA_CACHE_Eps3_PDM_B_Inst0_VoltAmpsMeasurements_type_t * const p_new_data)
{
    dc_set_raw_data(DC_DATA_INPUT_INTERNAL, DC_DID_EPS3_PDM_B_INST0_ALL_MEASUREMENTS, p_new_data, sizeof(DATA_CACHE_Eps3_PDM_B_Inst0_VoltAmpsMeasurements_type_t));
}

dc_data_status_t dc_get_eps3_expander_inst0_cmd_exec_status_data(DATA_CACHE_Eps3_EXPANDER_Inst0_FDIR_CMD_EXEC_STATUS_type_t * const p_data)
{
    return dc_get_raw_data(DC_DID_EPS3_EXPANDER_INST0_CMD_EXEC_STATUS_DATA,
                           p_data,
                           sizeof(DATA_CACHE_Eps3_EXPANDER_Inst0_FDIR_CMD_EXEC_STATUS_type_t),
                           0U,
                           sizeof(DATA_CACHE_Eps3_EXPANDER_Inst0_FDIR_CMD_EXEC_STATUS_type_t));
}

void dc_set_eps3_expander_inst0_cmd_exec_status_data(DATA_CACHE_Eps3_EXPANDER_Inst0_FDIR_CMD_EXEC_STATUS_type_t * const p_new_data)
{
    dc_set_raw_data(DC_DATA_INPUT_INTERNAL, DC_DID_EPS3_EXPANDER_INST0_CMD_EXEC_STATUS_DATA, p_new_data, sizeof(DATA_CACHE_Eps3_EXPANDER_Inst0_FDIR_CMD_EXEC_STATUS_type_t));
}

dc_data_status_t dc_get_eps3_expander_inst0_uptime_in_seconds(DATA_CACHE_Eps3_EXPANDER_Inst0_UpTimeInSecondsType_t * const p_data)
{
    return dc_get_raw_data(DC_DID_EPS3_EXPANDER_INST0_UPTIME_IN_SECONDS,
                           p_data,
                           sizeof(DATA_CACHE_Eps3_EXPANDER_Inst0_UpTimeInSecondsType_t),
                           0U,
                           sizeof(DATA_CACHE_Eps3_EXPANDER_Inst0_UpTimeInSecondsType_t));
}

void dc_set_eps3_expander_inst0_uptime_in_seconds(DATA_CACHE_Eps3_EXPANDER_Inst0_UpTimeInSecondsType_t * const p_new_data)
{
    dc_set_raw_data(DC_DATA_INPUT_INTERNAL, DC_DID_EPS3_EXPANDER_INST0_UPTIME_IN_SECONDS, p_new_data, sizeof(DATA_CACHE_Eps3_EXPANDER_Inst0_UpTimeInSecondsType_t));
}

dc_data_status_t dc_get_eps3_expander_inst0_common(DATA_CACHE_Eps3_EXPANDER_Inst0_CommonMeasurementType_t * const p_data)
{
    return dc_get_raw_data(DC_DID_EPS3_EXPANDER_INST0_COMMON,
                           p_data,
                           sizeof(DATA_CACHE_Eps3_EXPANDER_Inst0_CommonMeasurementType_t),
                           0U,
                           sizeof(DATA_CACHE_Eps3_EXPANDER_Inst0_CommonMeasurementType_t));
}

void dc_set_eps3_expander_inst0_common(DATA_CACHE_Eps3_EXPANDER_Inst0_CommonMeasurementType_t * const p_new_data)
{
    dc_set_raw_data(DC_DATA_INPUT_INTERNAL, DC_DID_EPS3_EXPANDER_INST0_COMMON, p_new_data, sizeof(DATA_CACHE_Eps3_EXPANDER_Inst0_CommonMeasurementType_t));
}

dc_data_status_t dc_get_eps3_expander_inst0_outputs(DATA_CACHE_Eps3_EXPANDER_Inst0_DigitalOutputsType_t * const p_data)
{
    return dc_get_raw_data(DC_DID_EPS3_EXPANDER_INST0_OUTPUTS,
                           p_data,
                           sizeof(DATA_CACHE_Eps3_EXPANDER_Inst0_DigitalOutputsType_t),
                           0U,
                           sizeof(DATA_CACHE_Eps3_EXPANDER_Inst0_DigitalOutputsType_t));
}

void dc_set_eps3_expander_inst0_outputs(DATA_CACHE_Eps3_EXPANDER_Inst0_DigitalOutputsType_t * const p_new_data)
{
    dc_set_raw_data(DC_DATA_INPUT_INTERNAL, DC_DID_EPS3_EXPANDER_INST0_OUTPUTS, p_new_data, sizeof(DATA_CACHE_Eps3_EXPANDER_Inst0_DigitalOutputsType_t));
}

dc_data_status_t dc_get_eps3_expander_inst0_general_inputs(DATA_CACHE_Eps3_EXPANDER_Inst0_GeneralInputType_t * const p_data)
{
    return dc_get_raw_data(DC_DID_EPS3_EXPANDER_INST0_GENERAL_INPUTS,
                           p_data,
                           sizeof(DATA_CACHE_Eps3_EXPANDER_Inst0_GeneralInputType_t),
                           0U,
                           sizeof(DATA_CACHE_Eps3_EXPANDER_Inst0_GeneralInputType_t));
}

void dc_set_eps3_expander_inst0_general_inputs(DATA_CACHE_Eps3_EXPANDER_Inst0_GeneralInputType_t * const p_new_data)
{
    dc_set_raw_data(DC_DATA_INPUT_INTERNAL, DC_DID_EPS3_EXPANDER_INST0_GENERAL_INPUTS, p_new_data, sizeof(DATA_CACHE_Eps3_EXPANDER_Inst0_GeneralInputType_t));
}

dc_data_status_t dc_get_eps3_expander_inst0_feedbacks(DATA_CACHE_Eps3_EXPANDER_Inst0_FeedbackType_t * const p_data)
{
    return dc_get_raw_data(DC_DID_EPS3_EXPANDER_INST0_FEEDBACKS,
                           p_data,
                           sizeof(DATA_CACHE_Eps3_EXPANDER_Inst0_FeedbackType_t),
                           0U,
                           sizeof(DATA_CACHE_Eps3_EXPANDER_Inst0_FeedbackType_t));
}

void dc_set_eps3_expander_inst0_feedbacks(DATA_CACHE_Eps3_EXPANDER_Inst0_FeedbackType_t * const p_new_data)
{
    dc_set_raw_data(DC_DATA_INPUT_INTERNAL, DC_DID_EPS3_EXPANDER_INST0_FEEDBACKS, p_new_data, sizeof(DATA_CACHE_Eps3_EXPANDER_Inst0_FeedbackType_t));
}

dc_data_status_t dc_get_eps3_expander_inst0_volt_amp_measurements(DATA_CACHE_Eps3_EXPANDER_Inst0_CurrentLimitersType_t * const p_data)
{
    return dc_get_raw_data(DC_DID_EPS3_EXPANDER_INST0_VOLT_AMP_MEASUREMENTS,
                           p_data,
                           sizeof(DATA_CACHE_Eps3_EXPANDER_Inst0_CurrentLimitersType_t),
                           0U,
                           sizeof(DATA_CACHE_Eps3_EXPANDER_Inst0_CurrentLimitersType_t));
}

void dc_set_eps3_expander_inst0_volt_amp_measurements(DATA_CACHE_Eps3_EXPANDER_Inst0_CurrentLimitersType_t * const p_new_data)
{
    dc_set_raw_data(DC_DATA_INPUT_INTERNAL, DC_DID_EPS3_EXPANDER_INST0_VOLT_AMP_MEASUREMENTS, p_new_data, sizeof(DATA_CACHE_Eps3_EXPANDER_Inst0_CurrentLimitersType_t));
}

dc_data_status_t dc_get_eps3_input_stage_inst0_uptime_in_seconds(DATA_CACHE_Eps3_INPUT_STAGE_Inst0_UpTimeInSecondsType_t * const p_data)
{
    return dc_get_raw_data(DC_DID_EPS3_INPUT_STAGE_INST0_UPTIME_IN_SECONDS,
                           p_data,
                           sizeof(DATA_CACHE_Eps3_INPUT_STAGE_Inst0_UpTimeInSecondsType_t),
                           0U,
                           sizeof(DATA_CACHE_Eps3_INPUT_STAGE_Inst0_UpTimeInSecondsType_t));
}

void dc_set_eps3_input_stage_inst0_uptime_in_seconds(DATA_CACHE_Eps3_INPUT_STAGE_Inst0_UpTimeInSecondsType_t * const p_new_data)
{
    dc_set_raw_data(DC_DATA_INPUT_INTERNAL, DC_DID_EPS3_INPUT_STAGE_INST0_UPTIME_IN_SECONDS, p_new_data, sizeof(DATA_CACHE_Eps3_INPUT_STAGE_Inst0_UpTimeInSecondsType_t));
}

dc_data_status_t dc_get_eps3_input_stage_inst0common(DATA_CACHE_Eps3_INPUT_STAGE_Inst0CommonMeasurementType_t * const p_data)
{
    return dc_get_raw_data(DC_DID_EPS3_INPUT_STAGE_INST0COMMON,
                           p_data,
                           sizeof(DATA_CACHE_Eps3_INPUT_STAGE_Inst0CommonMeasurementType_t),
                           0U,
                           sizeof(DATA_CACHE_Eps3_INPUT_STAGE_Inst0CommonMeasurementType_t));
}

void dc_set_eps3_input_stage_inst0common(DATA_CACHE_Eps3_INPUT_STAGE_Inst0CommonMeasurementType_t * const p_new_data)
{
    dc_set_raw_data(DC_DATA_INPUT_INTERNAL, DC_DID_EPS3_INPUT_STAGE_INST0COMMON, p_new_data, sizeof(DATA_CACHE_Eps3_INPUT_STAGE_Inst0CommonMeasurementType_t));
}

dc_data_status_t dc_get_eps3_input_stage_inst0hib_mode_status(DATA_CACHE_Eps3_INPUT_STAGE_Inst0hib_mode_status_type_t * const p_data)
{
    return dc_get_raw_data(DC_DID_EPS3_INPUT_STAGE_INST0HIB_MODE_STATUS,
                           p_data,
                           sizeof(DATA_CACHE_Eps3_INPUT_STAGE_Inst0hib_mode_status_type_t),
                           0U,
                           sizeof(DATA_CACHE_Eps3_INPUT_STAGE_Inst0hib_mode_status_type_t));
}

void dc_set_eps3_input_stage_inst0hib_mode_status(DATA_CACHE_Eps3_INPUT_STAGE_Inst0hib_mode_status_type_t * const p_new_data)
{
    dc_set_raw_data(DC_DATA_INPUT_INTERNAL, DC_DID_EPS3_INPUT_STAGE_INST0HIB_MODE_STATUS, p_new_data, sizeof(DATA_CACHE_Eps3_INPUT_STAGE_Inst0hib_mode_status_type_t));
}

dc_data_status_t dc_get_eps3_input_stage_inst0selflock_on(DATA_CACHE_Eps3_INPUT_STAGE_Inst0selflock_on_type_t * const p_data)
{
    return dc_get_raw_data(DC_DID_EPS3_INPUT_STAGE_INST0SELFLOCK_ON,
                           p_data,
                           sizeof(DATA_CACHE_Eps3_INPUT_STAGE_Inst0selflock_on_type_t),
                           0U,
                           sizeof(DATA_CACHE_Eps3_INPUT_STAGE_Inst0selflock_on_type_t));
}

void dc_set_eps3_input_stage_inst0selflock_on(DATA_CACHE_Eps3_INPUT_STAGE_Inst0selflock_on_type_t * const p_new_data)
{
    dc_set_raw_data(DC_DATA_INPUT_INTERNAL, DC_DID_EPS3_INPUT_STAGE_INST0SELFLOCK_ON, p_new_data, sizeof(DATA_CACHE_Eps3_INPUT_STAGE_Inst0selflock_on_type_t));
}

dc_data_status_t dc_get_eps3_input_stage_inst0sp1(DATA_CACHE_Eps3_INPUT_STAGE_Inst0Sp1InputDataType_t * const p_data)
{
    return dc_get_raw_data(DC_DID_EPS3_INPUT_STAGE_INST0SP1,
                           p_data,
                           sizeof(DATA_CACHE_Eps3_INPUT_STAGE_Inst0Sp1InputDataType_t),
                           0U,
                           sizeof(DATA_CACHE_Eps3_INPUT_STAGE_Inst0Sp1InputDataType_t));
}

void dc_set_eps3_input_stage_inst0sp1(DATA_CACHE_Eps3_INPUT_STAGE_Inst0Sp1InputDataType_t * const p_new_data)
{
    dc_set_raw_data(DC_DATA_INPUT_INTERNAL, DC_DID_EPS3_INPUT_STAGE_INST0SP1, p_new_data, sizeof(DATA_CACHE_Eps3_INPUT_STAGE_Inst0Sp1InputDataType_t));
}

dc_data_status_t dc_get_eps3_input_stage_inst0sp2(DATA_CACHE_Eps3_INPUT_STAGE_Inst0Sp2InputDataType_t * const p_data)
{
    return dc_get_raw_data(DC_DID_EPS3_INPUT_STAGE_INST0SP2,
                           p_data,
                           sizeof(DATA_CACHE_Eps3_INPUT_STAGE_Inst0Sp2InputDataType_t),
                           0U,
                           sizeof(DATA_CACHE_Eps3_INPUT_STAGE_Inst0Sp2InputDataType_t));
}

void dc_set_eps3_input_stage_inst0sp2(DATA_CACHE_Eps3_INPUT_STAGE_Inst0Sp2InputDataType_t * const p_new_data)
{
    dc_set_raw_data(DC_DATA_INPUT_INTERNAL, DC_DID_EPS3_INPUT_STAGE_INST0SP2, p_new_data, sizeof(DATA_CACHE_Eps3_INPUT_STAGE_Inst0Sp2InputDataType_t));
}

dc_data_status_t dc_get_eps3_input_stage_inst0sp3(DATA_CACHE_Eps3_INPUT_STAGE_Inst0Sp3InputDataType_t * const p_data)
{
    return dc_get_raw_data(DC_DID_EPS3_INPUT_STAGE_INST0SP3,
                           p_data,
                           sizeof(DATA_CACHE_Eps3_INPUT_STAGE_Inst0Sp3InputDataType_t),
                           0U,
                           sizeof(DATA_CACHE_Eps3_INPUT_STAGE_Inst0Sp3InputDataType_t));
}

void dc_set_eps3_input_stage_inst0sp3(DATA_CACHE_Eps3_INPUT_STAGE_Inst0Sp3InputDataType_t * const p_new_data)
{
    dc_set_raw_data(DC_DATA_INPUT_INTERNAL, DC_DID_EPS3_INPUT_STAGE_INST0SP3, p_new_data, sizeof(DATA_CACHE_Eps3_INPUT_STAGE_Inst0Sp3InputDataType_t));
}

dc_data_status_t dc_get_eps3_input_stage_inst0system_bus(DATA_CACHE_Eps3_INPUT_STAGE_Inst0SystemBusType_t * const p_data)
{
    return dc_get_raw_data(DC_DID_EPS3_INPUT_STAGE_INST0SYSTEM_BUS,
                           p_data,
                           sizeof(DATA_CACHE_Eps3_INPUT_STAGE_Inst0SystemBusType_t),
                           0U,
                           sizeof(DATA_CACHE_Eps3_INPUT_STAGE_Inst0SystemBusType_t));
}

void dc_set_eps3_input_stage_inst0system_bus(DATA_CACHE_Eps3_INPUT_STAGE_Inst0SystemBusType_t * const p_new_data)
{
    dc_set_raw_data(DC_DATA_INPUT_INTERNAL, DC_DID_EPS3_INPUT_STAGE_INST0SYSTEM_BUS, p_new_data, sizeof(DATA_CACHE_Eps3_INPUT_STAGE_Inst0SystemBusType_t));
}

dc_data_status_t dc_get_eps3_input_stage_inst0bus_7v5(DATA_CACHE_Eps3_INPUT_STAGE_Inst0Bus7v5Type_t * const p_data)
{
    return dc_get_raw_data(DC_DID_EPS3_INPUT_STAGE_INST0BUS_7V5,
                           p_data,
                           sizeof(DATA_CACHE_Eps3_INPUT_STAGE_Inst0Bus7v5Type_t),
                           0U,
                           sizeof(DATA_CACHE_Eps3_INPUT_STAGE_Inst0Bus7v5Type_t));
}

void dc_set_eps3_input_stage_inst0bus_7v5(DATA_CACHE_Eps3_INPUT_STAGE_Inst0Bus7v5Type_t * const p_new_data)
{
    dc_set_raw_data(DC_DATA_INPUT_INTERNAL, DC_DID_EPS3_INPUT_STAGE_INST0BUS_7V5, p_new_data, sizeof(DATA_CACHE_Eps3_INPUT_STAGE_Inst0Bus7v5Type_t));
}

dc_data_status_t dc_get_eps3_input_stage_inst0bus_7v5_power_good(DATA_CACHE_Eps3_INPUT_STAGE_Inst0bus_7v5_power_good_type_t * const p_data)
{
    return dc_get_raw_data(DC_DID_EPS3_INPUT_STAGE_INST0BUS_7V5_POWER_GOOD,
                           p_data,
                           sizeof(DATA_CACHE_Eps3_INPUT_STAGE_Inst0bus_7v5_power_good_type_t),
                           0U,
                           sizeof(DATA_CACHE_Eps3_INPUT_STAGE_Inst0bus_7v5_power_good_type_t));
}

void dc_set_eps3_input_stage_inst0bus_7v5_power_good(DATA_CACHE_Eps3_INPUT_STAGE_Inst0bus_7v5_power_good_type_t * const p_new_data)
{
    dc_set_raw_data(DC_DATA_INPUT_INTERNAL, DC_DID_EPS3_INPUT_STAGE_INST0BUS_7V5_POWER_GOOD, p_new_data, sizeof(DATA_CACHE_Eps3_INPUT_STAGE_Inst0bus_7v5_power_good_type_t));
}

dc_data_status_t dc_get_eps3_input_stage_inst0undervoltage_7v5(DATA_CACHE_Eps3_INPUT_STAGE_Inst0undervoltage_7V5_type_t * const p_data)
{
    return dc_get_raw_data(DC_DID_EPS3_INPUT_STAGE_INST0UNDERVOLTAGE_7V5,
                           p_data,
                           sizeof(DATA_CACHE_Eps3_INPUT_STAGE_Inst0undervoltage_7V5_type_t),
                           0U,
                           sizeof(DATA_CACHE_Eps3_INPUT_STAGE_Inst0undervoltage_7V5_type_t));
}

void dc_set_eps3_input_stage_inst0undervoltage_7v5(DATA_CACHE_Eps3_INPUT_STAGE_Inst0undervoltage_7V5_type_t * const p_new_data)
{
    dc_set_raw_data(DC_DATA_INPUT_INTERNAL, DC_DID_EPS3_INPUT_STAGE_INST0UNDERVOLTAGE_7V5, p_new_data, sizeof(DATA_CACHE_Eps3_INPUT_STAGE_Inst0undervoltage_7V5_type_t));
}

dc_data_status_t dc_get_eps3_input_stage_inst0bus_3v3(DATA_CACHE_Eps3_INPUT_STAGE_Inst0Bbus3v3Type_t * const p_data)
{
    return dc_get_raw_data(DC_DID_EPS3_INPUT_STAGE_INST0BUS_3V3,
                           p_data,
                           sizeof(DATA_CACHE_Eps3_INPUT_STAGE_Inst0Bbus3v3Type_t),
                           0U,
                           sizeof(DATA_CACHE_Eps3_INPUT_STAGE_Inst0Bbus3v3Type_t));
}

void dc_set_eps3_input_stage_inst0bus_3v3(DATA_CACHE_Eps3_INPUT_STAGE_Inst0Bbus3v3Type_t * const p_new_data)
{
    dc_set_raw_data(DC_DATA_INPUT_INTERNAL, DC_DID_EPS3_INPUT_STAGE_INST0BUS_3V3, p_new_data, sizeof(DATA_CACHE_Eps3_INPUT_STAGE_Inst0Bbus3v3Type_t));
}

dc_data_status_t dc_get_eps3_input_stage_inst0undervoltage_3v3(DATA_CACHE_Eps3_INPUT_STAGE_Inst0undervoltage_3V3_type_t * const p_data)
{
    return dc_get_raw_data(DC_DID_EPS3_INPUT_STAGE_INST0UNDERVOLTAGE_3V3,
                           p_data,
                           sizeof(DATA_CACHE_Eps3_INPUT_STAGE_Inst0undervoltage_3V3_type_t),
                           0U,
                           sizeof(DATA_CACHE_Eps3_INPUT_STAGE_Inst0undervoltage_3V3_type_t));
}

void dc_set_eps3_input_stage_inst0undervoltage_3v3(DATA_CACHE_Eps3_INPUT_STAGE_Inst0undervoltage_3V3_type_t * const p_new_data)
{
    dc_set_raw_data(DC_DATA_INPUT_INTERNAL, DC_DID_EPS3_INPUT_STAGE_INST0UNDERVOLTAGE_3V3, p_new_data, sizeof(DATA_CACHE_Eps3_INPUT_STAGE_Inst0undervoltage_3V3_type_t));
}

dc_data_status_t dc_get_eps3_input_stage_inst0_cmd_exec_status_data(DATA_CACHE_Eps3_INPUT_STAGE_Inst0_FDIR_CMD_EXEC_STATUS_type_t * const p_data)
{
    return dc_get_raw_data(DC_DID_EPS3_INPUT_STAGE_INST0_CMD_EXEC_STATUS_DATA,
                           p_data,
                           sizeof(DATA_CACHE_Eps3_INPUT_STAGE_Inst0_FDIR_CMD_EXEC_STATUS_type_t),
                           0U,
                           sizeof(DATA_CACHE_Eps3_INPUT_STAGE_Inst0_FDIR_CMD_EXEC_STATUS_type_t));
}

void dc_set_eps3_input_stage_inst0_cmd_exec_status_data(DATA_CACHE_Eps3_INPUT_STAGE_Inst0_FDIR_CMD_EXEC_STATUS_type_t * const p_new_data)
{
    dc_set_raw_data(DC_DATA_INPUT_INTERNAL, DC_DID_EPS3_INPUT_STAGE_INST0_CMD_EXEC_STATUS_DATA, p_new_data, sizeof(DATA_CACHE_Eps3_INPUT_STAGE_Inst0_FDIR_CMD_EXEC_STATUS_type_t));
}

dc_data_status_t dc_get_magdata(DATA_CACHE_CubeMag_Telemetry_t * const p_data)
{
    return dc_get_raw_data(DC_DID_MAGDATA,
                           p_data,
                           sizeof(DATA_CACHE_CubeMag_Telemetry_t),
                           0U,
                           sizeof(DATA_CACHE_CubeMag_Telemetry_t));
}

void dc_set_magdata(DATA_CACHE_CubeMag_Telemetry_t * const p_new_data)
{
    dc_set_raw_data(DC_DATA_INPUT_INTERNAL, DC_DID_MAGDATA, p_new_data, sizeof(DATA_CACHE_CubeMag_Telemetry_t));
}

dc_data_status_t dc_get_wheeldata1(DATA_CACHE_CubeWheel1_Telemetry_t * const p_data)
{
    return dc_get_raw_data(DC_DID_WHEELDATA1,
                           p_data,
                           sizeof(DATA_CACHE_CubeWheel1_Telemetry_t),
                           0U,
                           sizeof(DATA_CACHE_CubeWheel1_Telemetry_t));
}

void dc_set_wheeldata1(DATA_CACHE_CubeWheel1_Telemetry_t * const p_new_data)
{
    dc_set_raw_data(DC_DATA_INPUT_INTERNAL, DC_DID_WHEELDATA1, p_new_data, sizeof(DATA_CACHE_CubeWheel1_Telemetry_t));
}

dc_data_status_t dc_get_wheeldata2(DATA_CACHE_CubeWheel2_Telemetry_t * const p_data)
{
    return dc_get_raw_data(DC_DID_WHEELDATA2,
                           p_data,
                           sizeof(DATA_CACHE_CubeWheel2_Telemetry_t),
                           0U,
                           sizeof(DATA_CACHE_CubeWheel2_Telemetry_t));
}

void dc_set_wheeldata2(DATA_CACHE_CubeWheel2_Telemetry_t * const p_new_data)
{
    dc_set_raw_data(DC_DATA_INPUT_INTERNAL, DC_DID_WHEELDATA2, p_new_data, sizeof(DATA_CACHE_CubeWheel2_Telemetry_t));
}

dc_data_status_t dc_get_fss1_data(DATA_CACHE_FSS1_Data_type_t * const p_data)
{
    return dc_get_raw_data(DC_DID_FSS1_DATA,
                           p_data,
                           sizeof(DATA_CACHE_FSS1_Data_type_t),
                           0U,
                           sizeof(DATA_CACHE_FSS1_Data_type_t));
}

void dc_set_fss1_data(DATA_CACHE_FSS1_Data_type_t * const p_new_data)
{
    dc_set_raw_data(DC_DATA_INPUT_INTERNAL, DC_DID_FSS1_DATA, p_new_data, sizeof(DATA_CACHE_FSS1_Data_type_t));
}

dc_data_status_t dc_get_fss2_data(DATA_CACHE_FSS2_Data_type_t * const p_data)
{
    return dc_get_raw_data(DC_DID_FSS2_DATA,
                           p_data,
                           sizeof(DATA_CACHE_FSS2_Data_type_t),
                           0U,
                           sizeof(DATA_CACHE_FSS2_Data_type_t));
}

void dc_set_fss2_data(DATA_CACHE_FSS2_Data_type_t * const p_new_data)
{
    dc_set_raw_data(DC_DATA_INPUT_INTERNAL, DC_DID_FSS2_DATA, p_new_data, sizeof(DATA_CACHE_FSS2_Data_type_t));
}

dc_data_status_t dc_get_fss3_data(DATA_CACHE_FSS3_Data_type_t * const p_data)
{
    return dc_get_raw_data(DC_DID_FSS3_DATA,
                           p_data,
                           sizeof(DATA_CACHE_FSS3_Data_type_t),
                           0U,
                           sizeof(DATA_CACHE_FSS3_Data_type_t));
}

void dc_set_fss3_data(DATA_CACHE_FSS3_Data_type_t * const p_new_data)
{
    dc_set_raw_data(DC_DATA_INPUT_INTERNAL, DC_DID_FSS3_DATA, p_new_data, sizeof(DATA_CACHE_FSS3_Data_type_t));
}

dc_data_status_t dc_get_fss4_data(DATA_CACHE_FSS4_Data_type_t * const p_data)
{
    return dc_get_raw_data(DC_DID_FSS4_DATA,
                           p_data,
                           sizeof(DATA_CACHE_FSS4_Data_type_t),
                           0U,
                           sizeof(DATA_CACHE_FSS4_Data_type_t));
}

void dc_set_fss4_data(DATA_CACHE_FSS4_Data_type_t * const p_new_data)
{
    dc_set_raw_data(DC_DATA_INPUT_INTERNAL, DC_DID_FSS4_DATA, p_new_data, sizeof(DATA_CACHE_FSS4_Data_type_t));
}

dc_data_status_t dc_get_fss5_data(DATA_CACHE_FSS5_Data_type_t * const p_data)
{
    return dc_get_raw_data(DC_DID_FSS5_DATA,
                           p_data,
                           sizeof(DATA_CACHE_FSS5_Data_type_t),
                           0U,
                           sizeof(DATA_CACHE_FSS5_Data_type_t));
}

void dc_set_fss5_data(DATA_CACHE_FSS5_Data_type_t * const p_new_data)
{
    dc_set_raw_data(DC_DATA_INPUT_INTERNAL, DC_DID_FSS5_DATA, p_new_data, sizeof(DATA_CACHE_FSS5_Data_type_t));
}

dc_data_status_t dc_get_adcs_fss_data(DATA_CACHE_ADCS_FSS_t * const p_data)
{
    return dc_get_raw_data(DC_DID_ADCS_FSS_DATA,
                           p_data,
                           sizeof(DATA_CACHE_ADCS_FSS_t),
                           0U,
                           sizeof(DATA_CACHE_ADCS_FSS_t));
}

void dc_set_adcs_fss_data(DATA_CACHE_ADCS_FSS_t * const p_new_data)
{
    dc_set_raw_data(DC_DATA_INPUT_INTERNAL, DC_DID_ADCS_FSS_DATA, p_new_data, sizeof(DATA_CACHE_ADCS_FSS_t));
}

dc_data_status_t dc_get_adcs_mag_data(DATA_CACHE_ADCS_MAG_t * const p_data)
{
    return dc_get_raw_data(DC_DID_ADCS_MAG_DATA,
                           p_data,
                           sizeof(DATA_CACHE_ADCS_MAG_t),
                           0U,
                           sizeof(DATA_CACHE_ADCS_MAG_t));
}

void dc_set_adcs_mag_data(DATA_CACHE_ADCS_MAG_t * const p_new_data)
{
    dc_set_raw_data(DC_DATA_INPUT_INTERNAL, DC_DID_ADCS_MAG_DATA, p_new_data, sizeof(DATA_CACHE_ADCS_MAG_t));
}

dc_data_status_t dc_get_adcs_imu_data(DATA_CACHE_ADCS_IMU_t * const p_data)
{
    return dc_get_raw_data(DC_DID_ADCS_IMU_DATA,
                           p_data,
                           sizeof(DATA_CACHE_ADCS_IMU_t),
                           0U,
                           sizeof(DATA_CACHE_ADCS_IMU_t));
}

void dc_set_adcs_imu_data(DATA_CACHE_ADCS_IMU_t * const p_new_data)
{
    dc_set_raw_data(DC_DATA_INPUT_INTERNAL, DC_DID_ADCS_IMU_DATA, p_new_data, sizeof(DATA_CACHE_ADCS_IMU_t));
}

dc_data_status_t dc_get_adcs_rw_data(DATA_CACHE_ADCS_RW_t * const p_data)
{
    return dc_get_raw_data(DC_DID_ADCS_RW_DATA,
                           p_data,
                           sizeof(DATA_CACHE_ADCS_RW_t),
                           0U,
                           sizeof(DATA_CACHE_ADCS_RW_t));
}

void dc_set_adcs_rw_data(DATA_CACHE_ADCS_RW_t * const p_new_data)
{
    dc_set_raw_data(DC_DATA_INPUT_INTERNAL, DC_DID_ADCS_RW_DATA, p_new_data, sizeof(DATA_CACHE_ADCS_RW_t));
}

dc_data_status_t dc_get_adcs_mtq_data(DATA_CACHE_ADCS_MTQ_t * const p_data)
{
    return dc_get_raw_data(DC_DID_ADCS_MTQ_DATA,
                           p_data,
                           sizeof(DATA_CACHE_ADCS_MTQ_t),
                           0U,
                           sizeof(DATA_CACHE_ADCS_MTQ_t));
}

void dc_set_adcs_mtq_data(DATA_CACHE_ADCS_MTQ_t * const p_new_data)
{
    dc_set_raw_data(DC_DATA_INPUT_INTERNAL, DC_DID_ADCS_MTQ_DATA, p_new_data, sizeof(DATA_CACHE_ADCS_MTQ_t));
}

dc_data_status_t dc_get_eps2_bp_inst0_sbpmodechange_data(DATA_CACHE_SBpModeChangeInfo_t * const p_data)
{
    return dc_get_raw_data(DC_DID_EPS2_BP_INST0_SBPMODECHANGE_DATA,
                           p_data,
                           sizeof(DATA_CACHE_SBpModeChangeInfo_t),
                           0U,
                           sizeof(DATA_CACHE_SBpModeChangeInfo_t));
}

void dc_set_eps2_bp_inst0_sbpmodechange_data(DATA_CACHE_SBpModeChangeInfo_t * const p_new_data)
{
    dc_set_raw_data(DC_DATA_INPUT_INTERNAL, DC_DID_EPS2_BP_INST0_SBPMODECHANGE_DATA, p_new_data, sizeof(DATA_CACHE_SBpModeChangeInfo_t));
}

dc_data_status_t dc_get_eps2_bp_bpmodesmrollingtrace_data(DATA_CACHE_Eps2Inst0_BpModeSmRollingTrace_type_t * const p_data)
{
    return dc_get_raw_data(DC_DID_EPS2_BP_BPMODESMROLLINGTRACE_DATA,
                           p_data,
                           sizeof(DATA_CACHE_Eps2Inst0_BpModeSmRollingTrace_type_t),
                           0U,
                           sizeof(DATA_CACHE_Eps2Inst0_BpModeSmRollingTrace_type_t));
}

void dc_set_eps2_bp_bpmodesmrollingtrace_data(DATA_CACHE_Eps2Inst0_BpModeSmRollingTrace_type_t * const p_new_data)
{
    dc_set_raw_data(DC_DATA_INPUT_INTERNAL, DC_DID_EPS2_BP_BPMODESMROLLINGTRACE_DATA, p_new_data, sizeof(DATA_CACHE_Eps2Inst0_BpModeSmRollingTrace_type_t));
}

dc_data_status_t dc_get_eps2_pdm_sbsede_conopsmode_data(DATA_CACHE_EPSII_PDM_SBSEDE_ConopsMode_t * const p_data)
{
    return dc_get_raw_data(DC_DID_EPS2_PDM_SBSEDE_CONOPSMODE_DATA,
                           p_data,
                           sizeof(DATA_CACHE_EPSII_PDM_SBSEDE_ConopsMode_t),
                           0U,
                           sizeof(DATA_CACHE_EPSII_PDM_SBSEDE_ConopsMode_t));
}

void dc_set_eps2_pdm_sbsede_conopsmode_data(DATA_CACHE_EPSII_PDM_SBSEDE_ConopsMode_t * const p_new_data)
{
    dc_set_raw_data(DC_DATA_INPUT_INTERNAL, DC_DID_EPS2_PDM_SBSEDE_CONOPSMODE_DATA, p_new_data, sizeof(DATA_CACHE_EPSII_PDM_SBSEDE_ConopsMode_t));
}

dc_data_status_t dc_get_eps2_pdm_sbsed_bitmask_data(DATA_CACHE_EPSII_PDM_1_SBSED_Bitmask_t_t * const p_data)
{
    return dc_get_raw_data(DC_DID_EPS2_PDM_SBSED_BITMASK_DATA,
                           p_data,
                           sizeof(DATA_CACHE_EPSII_PDM_1_SBSED_Bitmask_t_t),
                           0U,
                           sizeof(DATA_CACHE_EPSII_PDM_1_SBSED_Bitmask_t_t));
}

void dc_set_eps2_pdm_sbsed_bitmask_data(DATA_CACHE_EPSII_PDM_1_SBSED_Bitmask_t_t * const p_new_data)
{
    dc_set_raw_data(DC_DATA_INPUT_INTERNAL, DC_DID_EPS2_PDM_SBSED_BITMASK_DATA, p_new_data, sizeof(DATA_CACHE_EPSII_PDM_1_SBSED_Bitmask_t_t));
}

dc_data_status_t dc_get_eps2_pdm_sbasicsettings_data(DATA_CACHE_EPSII_PDM_1_SBasicSettings_t * const p_data)
{
    return dc_get_raw_data(DC_DID_EPS2_PDM_SBASICSETTINGS_DATA,
                           p_data,
                           sizeof(DATA_CACHE_EPSII_PDM_1_SBasicSettings_t),
                           0U,
                           sizeof(DATA_CACHE_EPSII_PDM_1_SBasicSettings_t));
}

void dc_set_eps2_pdm_sbasicsettings_data(DATA_CACHE_EPSII_PDM_1_SBasicSettings_t * const p_new_data)
{
    dc_set_raw_data(DC_DATA_INPUT_INTERNAL, DC_DID_EPS2_PDM_SBASICSETTINGS_DATA, p_new_data, sizeof(DATA_CACHE_EPSII_PDM_1_SBasicSettings_t));
}

dc_data_status_t dc_get_eps2_pdm_setbasicsettings_data(DATA_CACHE_EPSII_PDM_1_SetBasicSettings_t * const p_data)
{
    return dc_get_raw_data(DC_DID_EPS2_PDM_SETBASICSETTINGS_DATA,
                           p_data,
                           sizeof(DATA_CACHE_EPSII_PDM_1_SetBasicSettings_t),
                           0U,
                           sizeof(DATA_CACHE_EPSII_PDM_1_SetBasicSettings_t));
}

void dc_set_eps2_pdm_setbasicsettings_data(DATA_CACHE_EPSII_PDM_1_SetBasicSettings_t * const p_new_data)
{
    dc_set_raw_data(DC_DATA_INPUT_INTERNAL, DC_DID_EPS2_PDM_SETBASICSETTINGS_DATA, p_new_data, sizeof(DATA_CACHE_EPSII_PDM_1_SetBasicSettings_t));
}

dc_data_status_t dc_get_eps2_pdm_sbs_geterror_data(DATA_CACHE_EPSII_PDM_1_SBS_GetError_t * const p_data)
{
    return dc_get_raw_data(DC_DID_EPS2_PDM_SBS_GETERROR_DATA,
                           p_data,
                           sizeof(DATA_CACHE_EPSII_PDM_1_SBS_GetError_t),
                           0U,
                           sizeof(DATA_CACHE_EPSII_PDM_1_SBS_GetError_t));
}

void dc_set_eps2_pdm_sbs_geterror_data(DATA_CACHE_EPSII_PDM_1_SBS_GetError_t * const p_new_data)
{
    dc_set_raw_data(DC_DATA_INPUT_INTERNAL, DC_DID_EPS2_PDM_SBS_GETERROR_DATA, p_new_data, sizeof(DATA_CACHE_EPSII_PDM_1_SBS_GetError_t));
}

dc_data_status_t dc_get_eps2inst0_pdm_sbasicsettings_data(DATA_CACHE_Eps2Inst0_SBasicSettings_type_t * const p_data)
{
    return dc_get_raw_data(DC_DID_EPS2INST0_PDM_SBASICSETTINGS_DATA,
                           p_data,
                           sizeof(DATA_CACHE_Eps2Inst0_SBasicSettings_type_t),
                           0U,
                           sizeof(DATA_CACHE_Eps2Inst0_SBasicSettings_type_t));
}

void dc_set_eps2inst0_pdm_sbasicsettings_data(DATA_CACHE_Eps2Inst0_SBasicSettings_type_t * const p_new_data)
{
    dc_set_raw_data(DC_DATA_INPUT_INTERNAL, DC_DID_EPS2INST0_PDM_SBASICSETTINGS_DATA, p_new_data, sizeof(DATA_CACHE_Eps2Inst0_SBasicSettings_type_t));
}

dc_data_status_t dc_get_vn100_data(DATA_CACHE_VN100_Data_type_t * const p_data)
{
    return dc_get_raw_data(DC_DID_VN100_DATA,
                           p_data,
                           sizeof(DATA_CACHE_VN100_Data_type_t),
                           0U,
                           sizeof(DATA_CACHE_VN100_Data_type_t));
}

void dc_set_vn100_data(DATA_CACHE_VN100_Data_type_t * const p_new_data)
{
    dc_set_raw_data(DC_DATA_INPUT_INTERNAL, DC_DID_VN100_DATA, p_new_data, sizeof(DATA_CACHE_VN100_Data_type_t));
}

dc_data_status_t dc_get_mpu6050_1_data(DATA_CACHE_MPU6050_1_Data_type_t * const p_data)
{
    return dc_get_raw_data(DC_DID_MPU6050_1_DATA,
                           p_data,
                           sizeof(DATA_CACHE_MPU6050_1_Data_type_t),
                           0U,
                           sizeof(DATA_CACHE_MPU6050_1_Data_type_t));
}

void dc_set_mpu6050_1_data(DATA_CACHE_MPU6050_1_Data_type_t * const p_new_data)
{
    dc_set_raw_data(DC_DATA_INPUT_INTERNAL, DC_DID_MPU6050_1_DATA, p_new_data, sizeof(DATA_CACHE_MPU6050_1_Data_type_t));
}

dc_data_status_t dc_get_mpu6050_2_data(DATA_CACHE_MPU6050_2_Data_type_t * const p_data)
{
    return dc_get_raw_data(DC_DID_MPU6050_2_DATA,
                           p_data,
                           sizeof(DATA_CACHE_MPU6050_2_Data_type_t),
                           0U,
                           sizeof(DATA_CACHE_MPU6050_2_Data_type_t));
}

void dc_set_mpu6050_2_data(DATA_CACHE_MPU6050_2_Data_type_t * const p_new_data)
{
    dc_set_raw_data(DC_DATA_INPUT_INTERNAL, DC_DID_MPU6050_2_DATA, p_new_data, sizeof(DATA_CACHE_MPU6050_2_Data_type_t));
}

dc_data_status_t dc_get_mtq_all_cmd_data(DATA_CACHE_MTQ_ALL_Command_Data_type_t * const p_data)
{
    return dc_get_raw_data(DC_DID_MTQ_ALL_CMD_DATA,
                           p_data,
                           sizeof(DATA_CACHE_MTQ_ALL_Command_Data_type_t),
                           0U,
                           sizeof(DATA_CACHE_MTQ_ALL_Command_Data_type_t));
}

void dc_set_mtq_all_cmd_data(DATA_CACHE_MTQ_ALL_Command_Data_type_t * const p_new_data)
{
    dc_set_raw_data(DC_DATA_INPUT_INTERNAL, DC_DID_MTQ_ALL_CMD_DATA, p_new_data, sizeof(DATA_CACHE_MTQ_ALL_Command_Data_type_t));
}

dc_data_status_t dc_get_eps2inst0_bp_sdiagerrcounter2_data(DATA_CACHE_EPSII_BP_1_SDiagErrCounter2_t * const p_data)
{
    return dc_get_raw_data(DC_DID_EPS2INST0_BP_SDIAGERRCOUNTER2_DATA,
                           p_data,
                           sizeof(DATA_CACHE_EPSII_BP_1_SDiagErrCounter2_t),
                           0U,
                           sizeof(DATA_CACHE_EPSII_BP_1_SDiagErrCounter2_t));
}

void dc_set_eps2inst0_bp_sdiagerrcounter2_data(DATA_CACHE_EPSII_BP_1_SDiagErrCounter2_t * const p_new_data)
{
    dc_set_raw_data(DC_DATA_INPUT_INTERNAL, DC_DID_EPS2INST0_BP_SDIAGERRCOUNTER2_DATA, p_new_data, sizeof(DATA_CACHE_EPSII_BP_1_SDiagErrCounter2_t));
}

dc_data_status_t dc_get_eps2inst0_bp_getmainapperrcounters2_data(DATA_CACHE_Eps2Inst0__GetMainAppErrCounters2ype_t * const p_data)
{
    return dc_get_raw_data(DC_DID_EPS2INST0_BP_GETMAINAPPERRCOUNTERS2_DATA,
                           p_data,
                           sizeof(DATA_CACHE_Eps2Inst0__GetMainAppErrCounters2ype_t),
                           0U,
                           sizeof(DATA_CACHE_Eps2Inst0__GetMainAppErrCounters2ype_t));
}

void dc_set_eps2inst0_bp_getmainapperrcounters2_data(DATA_CACHE_Eps2Inst0__GetMainAppErrCounters2ype_t * const p_new_data)
{
    dc_set_raw_data(DC_DATA_INPUT_INTERNAL, DC_DID_EPS2INST0_BP_GETMAINAPPERRCOUNTERS2_DATA, p_new_data, sizeof(DATA_CACHE_Eps2Inst0__GetMainAppErrCounters2ype_t));
}

dc_data_status_t dc_get_ina_data(DATA_CACHE_INA_Data_type_t * const p_data)
{
    return dc_get_raw_data(DC_DID_INA_DATA,
                           p_data,
                           sizeof(DATA_CACHE_INA_Data_type_t),
                           0U,
                           sizeof(DATA_CACHE_INA_Data_type_t));
}

void dc_set_ina_data(DATA_CACHE_INA_Data_type_t * const p_new_data)
{
    dc_set_raw_data(DC_DATA_INPUT_INTERNAL, DC_DID_INA_DATA, p_new_data, sizeof(DATA_CACHE_INA_Data_type_t));
}

dc_data_status_t dc_get_ang_data(DATA_CACHE_ANG_Data_type_t * const p_data)
{
    return dc_get_raw_data(DC_DID_ANG_DATA,
                           p_data,
                           sizeof(DATA_CACHE_ANG_Data_type_t),
                           0U,
                           sizeof(DATA_CACHE_ANG_Data_type_t));
}

void dc_set_ang_data(DATA_CACHE_ANG_Data_type_t * const p_new_data)
{
    dc_set_raw_data(DC_DATA_INPUT_INTERNAL, DC_DID_ANG_DATA, p_new_data, sizeof(DATA_CACHE_ANG_Data_type_t));
}

dc_data_status_t dc_get_camera_mode_data(DATA_CACHE_CAMERA_MODE_Data_type_t * const p_data)
{
    return dc_get_raw_data(DC_DID_CAMERA_MODE_DATA,
                           p_data,
                           sizeof(DATA_CACHE_CAMERA_MODE_Data_type_t),
                           0U,
                           sizeof(DATA_CACHE_CAMERA_MODE_Data_type_t));
}

void dc_set_camera_mode_data(DATA_CACHE_CAMERA_MODE_Data_type_t * const p_new_data)
{
    dc_set_raw_data(DC_DATA_INPUT_INTERNAL, DC_DID_CAMERA_MODE_DATA, p_new_data, sizeof(DATA_CACHE_CAMERA_MODE_Data_type_t));
}

dc_data_status_t dc_get_adcs_mode(DATA_CACHE_ADCS_mode_type_t * const p_data)
{
    return dc_get_raw_data(DC_DID_ADCS_MODE,
                           p_data,
                           sizeof(DATA_CACHE_ADCS_mode_type_t),
                           0U,
                           sizeof(DATA_CACHE_ADCS_mode_type_t));
}

void dc_set_adcs_mode(DATA_CACHE_ADCS_mode_type_t * const p_new_data)
{
    dc_set_raw_data(DC_DATA_INPUT_INTERNAL, DC_DID_ADCS_MODE, p_new_data, sizeof(DATA_CACHE_ADCS_mode_type_t));
}

dc_data_status_t dc_get_adcs_flag_alg(DATA_CACHE_ADCS_flag_alg_type_t * const p_data)
{
    return dc_get_raw_data(DC_DID_ADCS_FLAG_ALG,
                           p_data,
                           sizeof(DATA_CACHE_ADCS_flag_alg_type_t),
                           0U,
                           sizeof(DATA_CACHE_ADCS_flag_alg_type_t));
}

void dc_set_adcs_flag_alg(DATA_CACHE_ADCS_flag_alg_type_t * const p_new_data)
{
    dc_set_raw_data(DC_DATA_INPUT_INTERNAL, DC_DID_ADCS_FLAG_ALG, p_new_data, sizeof(DATA_CACHE_ADCS_flag_alg_type_t));
}

dc_data_status_t dc_get_adcs_result(DATA_CACHE_ADCS_result_type_t * const p_data)
{
    return dc_get_raw_data(DC_DID_ADCS_RESULT,
                           p_data,
                           sizeof(DATA_CACHE_ADCS_result_type_t),
                           0U,
                           sizeof(DATA_CACHE_ADCS_result_type_t));
}

void dc_set_adcs_result(DATA_CACHE_ADCS_result_type_t * const p_new_data)
{
    dc_set_raw_data(DC_DATA_INPUT_INTERNAL, DC_DID_ADCS_RESULT, p_new_data, sizeof(DATA_CACHE_ADCS_result_type_t));
}

dc_data_status_t dc_get_adcs_hw(DATA_CACHE_ADCS_HW_type_t * const p_data)
{
    return dc_get_raw_data(DC_DID_ADCS_HW,
                           p_data,
                           sizeof(DATA_CACHE_ADCS_HW_type_t),
                           0U,
                           sizeof(DATA_CACHE_ADCS_HW_type_t));
}

void dc_set_adcs_hw(DATA_CACHE_ADCS_HW_type_t * const p_new_data)
{
    dc_set_raw_data(DC_DATA_INPUT_INTERNAL, DC_DID_ADCS_HW, p_new_data, sizeof(DATA_CACHE_ADCS_HW_type_t));
}

dc_data_status_t dc_get_tc_flag(DATA_CACHE_CubeSpace_Telecommand_Flag_t * const p_data)
{
    return dc_get_raw_data(DC_DID_TC_FLAG,
                           p_data,
                           sizeof(DATA_CACHE_CubeSpace_Telecommand_Flag_t),
                           0U,
                           sizeof(DATA_CACHE_CubeSpace_Telecommand_Flag_t));
}

void dc_set_tc_flag(DATA_CACHE_CubeSpace_Telecommand_Flag_t * const p_new_data)
{
    dc_set_raw_data(DC_DATA_INPUT_INTERNAL, DC_DID_TC_FLAG, p_new_data, sizeof(DATA_CACHE_CubeSpace_Telecommand_Flag_t));
}

