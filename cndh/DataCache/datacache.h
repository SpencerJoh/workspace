/*!
********************************************************************************************
* @file datacache.h
* @brief Data Cache public header generator
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

#ifndef DATACACHE_H
#define DATACACHE_H

#ifdef __cplusplus
extern "C" {
#endif  // #ifdef __cplusplus

#include <stdint.h>
#include <stdbool.h>
#include "datacache_cfg.h"

/**********************************************************************
 *
 *  Type definitions
 *
 **********************************************************************/

typedef enum
{
    DC_NOT_INITIALIZED = 0,       // DC has not yet been initialised, so the data provided may not be relevant
    DC_DATA_STATUS_OK = 1,        // the data has been updated by its producer in the configured time period
    DC_DATA_STATUS_INIT = 2,      // the data is initialised with ROM values by DC and has not yet been updated
    DC_DATA_STATUS_TOUT = 3       // the data expected update period has not been respected
} dc_data_status_t;

typedef enum
{
    DC_DATA_INPUT_INTERNAL,       // data is fed to the DataCache by internal components
    DC_DATA_INPUT_EXTERNAL,       // data is fed to the DataCache externally, e.g. simulation interface
    DC_DATA_INPUT_MAX
} dc_data_input_t;

// Define internal data attribute ID as specified in the FIDL file 
#define DC_ATTR_ID_OBC_0_DATA 0x00000001
#define DC_ATTR_ID_ADCS_0_DATA 0x00000002
#define DC_ATTR_ID_ADCS_1_DATA 0x00000003
#define DC_ATTR_ID_ADCS_2_DATA 0x00000004
#define DC_ATTR_ID_EPS_0_DATA 0x00000005
#define DC_ATTR_ID_SSP_0_DATA 0x00000006
#define DC_ATTR_ID_SSP_1_DATA 0x00000007
#define DC_ATTR_ID_SSP_2_DATA 0x00000008
#define DC_ATTR_ID_SSP_3_DATA 0x00000009
#define DC_ATTR_ID_AOCS_CNTRL_TLM_DATA 0x0000000A
#define DC_ATTR_ID_AOCS_CNTRL_SYS_STATE_DATA 0x0000000B
#define DC_ATTR_ID_AOCS_CNTRL_REF_PARAMS_DATA 0x0000000C
#define DC_ATTR_ID_SENSOR_GYRO_SENSOR_FRAME_DATA 0x0000000D
#define DC_ATTR_ID_SENSOR_GYRO_BODY_FRAME_DATA 0x0000000E
#define DC_ATTR_ID_SENSOR_MAG_PRIMARY_SENSOR_FRAME_DATA 0x0000000F
#define DC_ATTR_ID_SENSOR_MAG_PRIMARY_BODY_FRAME_DATA 0x00000010
#define DC_ATTR_ID_SENSOR_MAG_SECONDARY_SENSOR_FRAME_DATA 0x00000011
#define DC_ATTR_ID_SENSOR_MAG_SECONDARY_BODY_FRAME_DATA 0x00000012
#define DC_ATTR_ID_SENSOR_COARSE_SUN_SENSOR_FRAME_DATA 0x00000013
#define DC_ATTR_ID_SENSOR_COARSE_SUN_BODY_FRAME_DATA 0x00000014
#define DC_ATTR_ID_SENSOR_PANEL_TEMP_SENSOR_FRAME_DATA 0x00000015
#define DC_ATTR_ID_SENSOR_PANEL_TEMP_BODY_FRAME_DATA 0x00000016
#define DC_ATTR_ID_SENSOR_GYRO_TEMP_SENSOR_FRAME_DATA 0x00000017
#define DC_ATTR_ID_SENSOR_GYRO_TEMP_BODY_FRAME_DATA 0x00000018
#define DC_ATTR_ID_ACTUATOR_MTQ_VALUES_DATA 0x00000019
#define DC_ATTR_ID_ACTUATOR_TORQUE_VALUES_DATA 0x0000001A
#define DC_ATTR_ID_ADCS_3_DATA 0x0000001B
#define DC_ATTR_ID_ADCS_4_DATA 0x0000001C
#define DC_ATTR_ID_EPS_9_DATA 0x0000001D
#define DC_ATTR_ID_EPS_10_DATA 0x0000001E
#define DC_ATTR_ID_EPS_14_DATA 0x0000001F
#define DC_ATTR_ID_CUBEADCS_GEN2_OP_STATUS_COMMON_DATA 0x00000020
#define DC_ATTR_ID_CUBEADCS_GEN2_OP_STATUS_APP_DATA 0x00000021
#define DC_ATTR_ID_CUBEADCS_GEN2_TLM_FRAME_166_DATA 0x00000022
#define DC_ATTR_ID_CUBEADCS_GEN2_TLM_FRAME_167_DATA 0x00000023
#define DC_ATTR_ID_CUBEADCS_GEN2_TLM_FRAME_168_DATA 0x00000024
#define DC_ATTR_ID_CUBEADCS_GEN2_TLM_FRAME_169_DATA 0x00000025
#define DC_ATTR_ID_CUBEADCS_GEN2_TLM_FRAME_170_DATA 0x00000026
#define DC_ATTR_ID_CUBEADCS_GEN2_TLM_FRAME_171_DATA 0x00000027
#define DC_ATTR_ID_CUBEADCS_GEN2_TLM_FRAME_172_DATA 0x00000028
#define DC_ATTR_ID_CUBEADCS_GEN2_TLM_FRAME_173_DATA 0x00000029
#define DC_ATTR_ID_CUBEADCS_GEN2_TLM_FRAME_174_DATA 0x0000002A
#define DC_ATTR_ID_CUBEADCS_GEN2_TLM_FRAME_175_DATA 0x0000002B
#define DC_ATTR_ID_CUBEADCS_GEN2_TLM_FRAME_176_DATA 0x0000002C
#define DC_ATTR_ID_CUBEADCS_GEN2_TLM_FRAME_177_DATA 0x0000002D
#define DC_ATTR_ID_CUBEADCS_GEN2_TLM_FRAME_178_DATA 0x0000002E
#define DC_ATTR_ID_CUBEADCS_GEN2_TLM_FRAME_179_DATA 0x0000002F
#define DC_ATTR_ID_CUBEADCS_GEN2_TLM_FRAME_180_DATA 0x00000030
#define DC_ATTR_ID_CUBEADCS_GEN2_TLM_FRAME_203_DATA 0x00000031
#define DC_ATTR_ID_CUBEADCS_GEN2_TLM_FRAME_204_DATA 0x00000032
#define DC_ATTR_ID_CUBEADCS_GEN2_TLM_FRAME_205_DATA 0x00000033
#define DC_ATTR_ID_CUBEADCS_GEN2_TLM_FRAME_206_DATA 0x00000034
#define DC_ATTR_ID_CUBEADCS_GEN2_TLM_FRAME_207_DATA 0x00000035
#define DC_ATTR_ID_CUBEADCS_GEN2_TLM_FRAME_208_1_DATA 0x00000036
#define DC_ATTR_ID_CUBEADCS_GEN2_TLM_FRAME_208_2_DATA 0x00000037
#define DC_ATTR_ID_CUBEADCS_GEN2_TLM_FRAME_209_DATA 0x00000038
#define DC_ATTR_ID_CUBEADCS_GEN2_TLM_FRAME_210_DATA 0x00000039
#define DC_ATTR_ID_CUBEADCS_GEN2_TLM_FRAME_211_DATA 0x0000003A
#define DC_ATTR_ID_CUBEADCS_GEN2_TLM_FRAME_212_DATA 0x0000003B
#define DC_ATTR_ID_CUBEADCS_GEN2_TLM_FRAME_213_DATA 0x0000003C
#define DC_ATTR_ID_CUBEADCS_GEN2_TLM_FRAME_214_DATA 0x0000003D
#define DC_ATTR_ID_CUBEADCS_GEN2_TLM_FRAME_216_DATA 0x0000003E
#define DC_ATTR_ID_CUBEADCS_GEN2_TLM_FRAME_217_DATA 0x0000003F
#define DC_ATTR_ID_CUBEADCS_GEN2_TLM_FRAME_218_DATA 0x00000040
#define DC_ATTR_ID_CUBEADCS_GEN2_TLM_FRAME_225_DATA 0x00000041
#define DC_ATTR_ID_CUBEADCS_GEN2_TLM_FRAME_226_DATA 0x00000042
#define DC_ATTR_ID_CUBEADCS_GEN2_TLM_FRAME_165_DATA 0x00000043
#define DC_ATTR_ID_CUBEADCS_GEN2_TLM_FRAME_221_DATA 0x00000044
#define DC_ATTR_ID_GNSS_TIME_DATA 0x00000045
#define DC_ATTR_ID_GNSS_BESTXYZ_DATA 0x00000046
#define DC_ATTR_ID_SAT_STATE_VECTOR_FROM_PROPAGATOR_DATA 0x00000047
#define DC_ATTR_ID_SAT_MAG_FIELD_VECTOR_FROM_MODEL_DATA 0x00000048
#define DC_ATTR_ID_SAT_MAG_FIELD_VECTOR_FROM_SENSOR_DATA 0x00000049
#define DC_ATTR_ID_FDIR_EPS_I_CMD_EXEC_STATUS_DATA 0x0000004A
#define DC_ATTR_ID_FDIR_EPS_II_PDM_CMD_EXEC_STATUS_DATA 0x0000004B
#define DC_ATTR_ID_FDIR_CUBEADCS_CMD_EXEC_STATUS_DATA 0x0000004C
#define DC_ATTR_ID_FDIR_CUBEADCS_GEN2_CMD_EXEC_STATUS_DATA 0x0000004D
#define DC_ATTR_ID_FDIR_CUBEADCS_GEN2_EVENTS_DATA 0x0000004E
#define DC_ATTR_ID_FDIR_S_BAND_TMTC_CMD_EXEC_STATUS_DATA 0x0000004F
#define DC_ATTR_ID_FDIR_UHF_CMD_EXEC_STATUS_DATA 0x00000050
#define DC_ATTR_ID_FDIR_GNSS_CMD_EXEC_STATUS_DATA 0x00000051
#define DC_ATTR_ID_FDIR_SDR_CMD_EXEC_STATUS_DATA 0x00000052
#define DC_ATTR_ID_FDIR_S_X_BAND_CMD_EXEC_STATUS_DATA 0x00000053
#define DC_ATTR_ID_FDIR_THRUSTER_CMD_EXEC_STATUS_DATA 0x00000054
#define DC_ATTR_ID_XBAND_FE_DATA 0x00000055
#define DC_ATTR_ID_EPSOVERALLBATTERYINFO_DATA 0x00000056
#define DC_ATTR_ID_PPS_TELEMETRY_DATA 0x00000057
#define DC_ATTR_ID_FDIR_EPS_III_PDM_CMD_EXEC_STATUS_DATA 0x00000058
#define DC_ATTR_ID_EPS2_BP_INST0_BP_INFO_DATA 0x00000059
#define DC_ATTR_ID_EPS2_BP_INST0_DEVICE_HEALTH_INFO_DATA 0x0000005A
#define DC_ATTR_ID_EPS2_BP_INST0_INA_SENSOR1_DATA 0x0000005B
#define DC_ATTR_ID_EPS2_BP_INST0_INA_SENSOR2_DATA 0x0000005C
#define DC_ATTR_ID_EPS2_BP_INST0_BALANCER_INFO_DATA 0x0000005D
#define DC_ATTR_ID_EPS2_BP_INST0_BALANCER_STATUS_DATA 0x0000005E
#define DC_ATTR_ID_EPS2_BP_INST0_BALANCER_CELLS_INFO_DATA 0x0000005F
#define DC_ATTR_ID_EPS2_BP_INST0_CHARGER_XP_DATA 0x00000060
#define DC_ATTR_ID_EPS2_BP_INST0_CHARGER_XR_DATA 0x00000061
#define DC_ATTR_ID_EPS2_BP_INST0_CHARGER_YP_DATA 0x00000062
#define DC_ATTR_ID_EPS2_BP_INST0_CHARGER_YR_DATA 0x00000063
#define DC_ATTR_ID_EPS2_BP_INST0_CHARGER_ZP_DATA 0x00000064
#define DC_ATTR_ID_EPS2_BP_INST0_CHARGER_ZR_DATA 0x00000065
#define DC_ATTR_ID_FDIR_EPS_II_BP_INST0_CMD_EXEC_STATUS_DATA 0x00000066
#define DC_ATTR_ID_EPS3_BP_INST0_UPTIME_IN_SECONDS 0x00000067
#define DC_ATTR_ID_EPS3_BP_INST0COMMON 0x00000068
#define DC_ATTR_ID_EPS3_BP_INST0HIB_MODE_STATUS 0x00000069
#define DC_ATTR_ID_EPS3_BP_INST0MEASUREMENTS 0x0000006A
#define DC_ATTR_ID_EPS3_BP_INST0DISCHARGING_STATE 0x0000006B
#define DC_ATTR_ID_EPS3_BP_INST0CHARGE_STATUS 0x0000006C
#define DC_ATTR_ID_EPS3_BP_INST0BALANCERS_STATUS 0x0000006D
#define DC_ATTR_ID_EPS3_BP_INST0BATTERY_CELLS_STATUS 0x0000006E
#define DC_ATTR_ID_EPS3_BP_INST0HEATERS_STATUS 0x0000006F
#define DC_ATTR_ID_EPS3_BP_INST0_CMD_EXEC_STATUS_DATA 0x00000070
#define DC_ATTR_ID_DUMB_DATA 0x00000071
#define DC_ATTR_ID_DUMB_DATA1 0x00000072
#define DC_ATTR_ID_DUMB_DATA3 0x00000073
#define DC_ATTR_ID_DUMB_DATA4 0x00000074
#define DC_ATTR_ID_DUMB_DATA5 0x00000075
#define DC_ATTR_ID_DUMB_DATA6 0x00000076
#define DC_ATTR_ID_EPS3_PDM_A_INST0_UPTIME_IN_SECONDS 0x00000077
#define DC_ATTR_ID_EPS3_PDM_A_INST0_COMMON 0x00000078
#define DC_ATTR_ID_EPS3_PDM_A_INST0_HIB_MODE 0x00000079
#define DC_ATTR_ID_EPS3_PDM_A_INST0_GENERAL_OUTPUTS 0x0000007A
#define DC_ATTR_ID_EPS3_PDM_A_INST0_GENERAL_FAULTS 0x0000007B
#define DC_ATTR_ID_EPS3_PDM_A_INST0_ALL_MEASUREMENTS 0x0000007C
#define DC_ATTR_ID_EPS3_PDM_A_INST0_CMD_EXEC_STATUS_DATA 0x0000007D
#define DC_ATTR_ID_EPS3_PDM_B_INST0_CMD_EXEC_STATUS_DATA 0x0000007E
#define DC_ATTR_ID_EPS3_PDM_B_INST0_UPTIME_IN_SECONDS 0x0000007F
#define DC_ATTR_ID_EPS3_PDM_B_INST0_COMMON 0x00000080
#define DC_ATTR_ID_EPS3_PDM_B_INST0_HIB_MODE 0x00000081
#define DC_ATTR_ID_EPS3_PDM_B_INST0_GENERAL_OUTPUTS 0x00000082
#define DC_ATTR_ID_EPS3_PDM_B_INST0_CHANNEL_FLAG_STATE 0x00000083
#define DC_ATTR_ID_EPS3_PDM_B_INST0_TEMPERATURE 0x00000084
#define DC_ATTR_ID_EPS3_PDM_B_INST0_ALL_MEASUREMENTS 0x00000085
#define DC_ATTR_ID_EPS3_EXPANDER_INST0_CMD_EXEC_STATUS_DATA 0x00000086
#define DC_ATTR_ID_EPS3_EXPANDER_INST0_UPTIME_IN_SECONDS 0x00000087
#define DC_ATTR_ID_EPS3_EXPANDER_INST0_COMMON 0x00000088
#define DC_ATTR_ID_EPS3_EXPANDER_INST0_OUTPUTS 0x00000089
#define DC_ATTR_ID_EPS3_EXPANDER_INST0_GENERAL_INPUTS 0x0000008A
#define DC_ATTR_ID_EPS3_EXPANDER_INST0_FEEDBACKS 0x0000008B
#define DC_ATTR_ID_EPS3_EXPANDER_INST0_VOLT_AMP_MEASUREMENTS 0x0000008C
#define DC_ATTR_ID_EPS3_INPUT_STAGE_INST0_UPTIME_IN_SECONDS 0x0000008D
#define DC_ATTR_ID_EPS3_INPUT_STAGE_INST0COMMON 0x0000008E
#define DC_ATTR_ID_EPS3_INPUT_STAGE_INST0HIB_MODE_STATUS 0x0000008F
#define DC_ATTR_ID_EPS3_INPUT_STAGE_INST0SELFLOCK_ON 0x00000090
#define DC_ATTR_ID_EPS3_INPUT_STAGE_INST0SP1 0x00000091
#define DC_ATTR_ID_EPS3_INPUT_STAGE_INST0SP2 0x00000092
#define DC_ATTR_ID_EPS3_INPUT_STAGE_INST0SP3 0x00000093
#define DC_ATTR_ID_EPS3_INPUT_STAGE_INST0SYSTEM_BUS 0x00000094
#define DC_ATTR_ID_EPS3_INPUT_STAGE_INST0BUS_7V5 0x00000095
#define DC_ATTR_ID_EPS3_INPUT_STAGE_INST0BUS_7V5_POWER_GOOD 0x00000096
#define DC_ATTR_ID_EPS3_INPUT_STAGE_INST0UNDERVOLTAGE_7V5 0x00000097
#define DC_ATTR_ID_EPS3_INPUT_STAGE_INST0BUS_3V3 0x00000098
#define DC_ATTR_ID_EPS3_INPUT_STAGE_INST0UNDERVOLTAGE_3V3 0x00000099
#define DC_ATTR_ID_EPS3_INPUT_STAGE_INST0_CMD_EXEC_STATUS_DATA 0x0000009A
#define DC_ATTR_ID_MAGDATA 0x0000009B
#define DC_ATTR_ID_WHEELDATA1 0x0000009C
#define DC_ATTR_ID_WHEELDATA2 0x0000009D
#define DC_ATTR_ID_FSS1_DATA 0x0000009E
#define DC_ATTR_ID_FSS2_DATA 0x0000009F
#define DC_ATTR_ID_FSS3_DATA 0x000000A0
#define DC_ATTR_ID_FSS4_DATA 0x000000A1
#define DC_ATTR_ID_FSS5_DATA 0x000000A2
#define DC_ATTR_ID_ADCS_FSS_DATA 0x000000A3
#define DC_ATTR_ID_ADCS_MAG_DATA 0x000000A4
#define DC_ATTR_ID_ADCS_IMU_DATA 0x000000A5
#define DC_ATTR_ID_ADCS_RW_DATA 0x000000A6
#define DC_ATTR_ID_ADCS_MTQ_DATA 0x000000A7
#define DC_ATTR_ID_EPS2_BP_INST0_SBPMODECHANGE_DATA 0x000000A8
#define DC_ATTR_ID_EPS2_BP_BPMODESMROLLINGTRACE_DATA 0x000000A9
#define DC_ATTR_ID_EPS2_PDM_SBSEDE_CONOPSMODE_DATA 0x000000AA
#define DC_ATTR_ID_EPS2_PDM_SBSED_BITMASK_DATA 0x000000AB
#define DC_ATTR_ID_EPS2_PDM_SBASICSETTINGS_DATA 0x000000AC
#define DC_ATTR_ID_EPS2_PDM_SETBASICSETTINGS_DATA 0x000000AD
#define DC_ATTR_ID_EPS2_PDM_SBS_GETERROR_DATA 0x000000AE
#define DC_ATTR_ID_EPS2INST0_PDM_SBASICSETTINGS_DATA 0x000000AF
#define DC_ATTR_ID_VN100_DATA 0x000000B0
#define DC_ATTR_ID_MPU6050_1_DATA 0x000000B1
#define DC_ATTR_ID_MPU6050_2_DATA 0x000000B2
#define DC_ATTR_ID_MTQ_ALL_CMD_DATA 0x000000B3
#define DC_ATTR_ID_EPS2INST0_BP_SDIAGERRCOUNTER2_DATA 0x000000B4
#define DC_ATTR_ID_EPS2INST0_BP_GETMAINAPPERRCOUNTERS2_DATA 0x000000B5
#define DC_ATTR_ID_INA_DATA 0x000000B6
#define DC_ATTR_ID_ANG_DATA 0x000000B7
#define DC_ATTR_ID_CAMERA_MODE_DATA 0x000000B8
#define DC_ATTR_ID_ADCS_MODE 0x000000B9
#define DC_ATTR_ID_ADCS_FLAG_ALG 0x000000BA
#define DC_ATTR_ID_ADCS_RESULT 0x000000BB
#define DC_ATTR_ID_ADCS_HW 0x000000BC
#define DC_ATTR_ID_TC_FLAG 0x000000BD
#define DC_ATTR_ID_WHEELCOMMAND1 0x000000BE
#define DC_ATTR_ID_WHEELCOMMAND2 0x000000BF
#define DC_ATTR_ID_MAGCOMMAND 0x000000C0


typedef struct {
    uint8_t u8OpMode;
    uint32_t u32UpTime;
    uint16_t u16TotalResetCount;
    uint16_t u16ResetReasonBitField;
    uint16_t u16PayloadModesStatus;
} PACKED_STRUCT DATA_CACHE_OBC_0_t;

typedef struct {
    int16_t ai16MagFieldVec[3];
    int16_t ai16CoarseSunVec[3];
    int16_t ai16FineSunVec[3];
    int16_t ai16NadirVec[3];
    int16_t ai16AngRateVec[3];
    int16_t ai16WheelSpeedArr[3];
} PACKED_STRUCT DATA_CACHE_ADCS_0_t;

typedef struct {
    int16_t ai16EstQSet[3];
    int16_t ai16EstAngRateVec[3];
    int16_t ai16ControlledAngles[3];
    int16_t ai16RawGyroRates[3];
} PACKED_STRUCT DATA_CACHE_ADCS_1_t;

typedef struct {
    uint8_t au8AdcsState[6];
} PACKED_STRUCT DATA_CACHE_ADCS_2_t;

typedef struct {
    int64_t i64BattEnergy;
    int64_t i64BattCharge;
    int64_t i64BattChargeCapacity;
    int64_t i64BattPercent;
    int32_t i32BattVoltage;
    int32_t i32BattCurrent;
    int32_t i32BattTemperature;
} PACKED_STRUCT DATA_CACHE_EPS_0_t;

/*
    Describes the telemetry captured from the Solar Panel modules
*/
typedef struct {
    uint32_t u32Uptime;
    uint16_t u16Sun_data_main;
    uint8_t u8Sun_data_main_valid;
    uint16_t u16Sun_data_ext;
    uint8_t u8Sun_data_ext_valid;
    int16_t i16Temp_data_main;
    uint8_t u8Temp_data_main_valid;
    int16_t i16Temp_data_ext1;
    uint8_t u8Temp_data_ext1_valid;
    int16_t i16Temp_data_ext2;
    uint8_t u8Temp_data_ext2_valid;
    int16_t i16Temp_data_mcu;
    uint8_t u8Temp_data_mcu_valid;
} PACKED_STRUCT DATA_CACHE_SSP_0_Telemetry_t;

/*
    Describes the telemetry captured from the Solar Panel modules
*/
typedef struct {
    uint32_t u32Uptime;
    uint16_t u16Sun_data_main;
    uint8_t u8Sun_data_main_valid;
    uint16_t u16Sun_data_ext;
    uint8_t u8Sun_data_ext_valid;
    int16_t i16Temp_data_main;
    uint8_t u8Temp_data_main_valid;
    int16_t i16Temp_data_ext1;
    uint8_t u8Temp_data_ext1_valid;
    int16_t i16Temp_data_ext2;
    uint8_t u8Temp_data_ext2_valid;
    int16_t i16Temp_data_mcu;
    uint8_t u8Temp_data_mcu_valid;
} PACKED_STRUCT DATA_CACHE_SSP_1_Telemetry_t;

/*
    Describes the telemetry captured from the Solar Panel modules
*/
typedef struct {
    uint32_t u32Uptime;
    uint16_t u16Sun_data_main;
    uint8_t u8Sun_data_main_valid;
    uint16_t u16Sun_data_ext;
    uint8_t u8Sun_data_ext_valid;
    int16_t i16Temp_data_main;
    uint8_t u8Temp_data_main_valid;
    int16_t i16Temp_data_ext1;
    uint8_t u8Temp_data_ext1_valid;
    int16_t i16Temp_data_ext2;
    uint8_t u8Temp_data_ext2_valid;
    int16_t i16Temp_data_mcu;
    uint8_t u8Temp_data_mcu_valid;
} PACKED_STRUCT DATA_CACHE_SSP_2_Telemetry_t;

/*
    Describes the telemetry captured from the Solar Panel modules
*/
typedef struct {
    uint32_t u32Uptime;
    uint16_t u16Sun_data_main;
    uint8_t u8Sun_data_main_valid;
    uint16_t u16Sun_data_ext;
    uint8_t u8Sun_data_ext_valid;
    int16_t i16Temp_data_main;
    uint8_t u8Temp_data_main_valid;
    int16_t i16Temp_data_ext1;
    uint8_t u8Temp_data_ext1_valid;
    int16_t i16Temp_data_ext2;
    uint8_t u8Temp_data_ext2_valid;
    int16_t i16Temp_data_mcu;
    uint8_t u8Temp_data_mcu_valid;
} PACKED_STRUCT DATA_CACHE_SSP_3_Telemetry_t;

typedef struct {
    uint32_t u32AdcsErrFlags;
    int32_t i32EstAngRateNorm;
    int32_t ai32EstAngRateVec[3];
    int32_t ai32EstAttAngles[3];
    int16_t ai16MeasWheelSpeed[4];
} PACKED_STRUCT DATA_CACHE_AOCS_CNTRL_TLM_t;

typedef struct {
    uint8_t u8AdcsSysState;
    uint8_t u8AdcsSysStateStatus;
} PACKED_STRUCT DATA_CACHE_AOCS_CNTRL_SYS_STATE_t;

typedef struct {
    float fRefParam1;
    float fRefParam2;
    float fRefParam3;
} PACKED_STRUCT DATA_CACHE_AOCS_CNTRL_REF_PARAMS_t;

typedef struct {
    double dGyro_1;
    double dGyro_2;
    double dGyro_3;
} PACKED_STRUCT DATA_CACHE_SENSOR_GYRO_SENSOR_FRAME_t;

typedef struct {
    double dGyro_x;
    double dGyro_y;
    double dGyro_z;
} PACKED_STRUCT DATA_CACHE_SENSOR_GYRO_BODY_FRAME_t;

typedef struct {
    double dMag_x;
    double dMag_y;
    double dMag_z;
} PACKED_STRUCT DATA_CACHE_SENSOR_MAG_PRIMARY_SENSOR_FRAME_t;

typedef struct {
    double dMag_x_current;
    double dMag_y_current;
    double dMag_z_current;
    double dMag_x_previous;
    double dMag_y_previous;
    double dMag_z_previous;
} PACKED_STRUCT DATA_CACHE_SENSOR_MAG_PRIMARY_BODY_FRAME_t;

typedef struct {
    double dMag_x;
    double dMag_y;
    double dMag_z;
} PACKED_STRUCT DATA_CACHE_SENSOR_MAG_SECONDARY_SENSOR_FRAME_t;

typedef struct {
    double dMag_x_current;
    double dMag_y_current;
    double dMag_z_current;
    double dMag_x_previous;
    double dMag_y_previous;
    double dMag_z_previous;
} PACKED_STRUCT DATA_CACHE_SENSOR_MAG_SECONDARY_BODY_FRAME_t;

typedef struct {
    int32_t i32Css_panel_1;
    int32_t i32Css_panel_2;
    int32_t i32Css_panel_3;
    int32_t i32Css_panel_4;
    int32_t i32Css_panel_5;
    int32_t i32Css_panel_6;
} PACKED_STRUCT DATA_CACHE_SENSOR_COARSE_SUN_SENSOR_FRAME_t;

typedef struct {
    int32_t i32Css_axis_x_plus;
    int32_t i32Css_axis_y_plus;
    int32_t i32Css_axis_z_plus;
    int32_t i32Css_axis_x_minus;
    int32_t i32Css_axis_y_minus;
    int32_t i32Css_axis_z_minus;
} PACKED_STRUCT DATA_CACHE_SENSOR_COARSE_SUN_BODY_FRAME_t;

/*
    Panel temperature sensors measurements in [degC] in Sensor Frame (mounting locations)
*/
typedef struct {
    double dPAN_1_TEMP;
    double dPAN_2_TEMP;
    double dPAN_3_TEMP;
    double dPAN_4_TEMP;
    double dPAN_5_TEMP;
    double dPAN_6_TEMP;
} PACKED_STRUCT DATA_CACHE_SENSOR_PANEL_TEMP_SENSOR_FRAME_t;

/*
    Panel temperature sensors measurements in [degC] in Body Frame
*/
typedef struct {
    double dPAN_X_PLUS_TEMP;
    double dPAN_Y_PLUS_TEMP;
    double dPAN_Z_PLUS_TEMP;
    double dPAN_X_MINUS_TEMP;
    double dPAN_Y_MINUS_TEMP;
    double dPAN_Z_MINUS_TEMP;
} PACKED_STRUCT DATA_CACHE_SENSOR_PANEL_TEMP_BODY_FRAME_t;

/*
    Gyroscope sensors' temperatures in the Sensor Frame
*/
typedef struct {
    double dGYRO_1_TEMP;
    double dGYRO_2_TEMP;
    double dGYRO_3_TEMP;
} PACKED_STRUCT DATA_CACHE_SENSOR_GYRO_TEMP_SENSOR_FRAME_t;

/*
    Rate sensors temperature for the three primary axes in Body Frame
*/
typedef struct {
    double dGYRO_X_TEMP;
    double dGYRO_Y_TEMP;
    double dGYRO_Z_TEMP;
} PACKED_STRUCT DATA_CACHE_SENSOR_GYRO_TEMP_BODY_FRAME_t;

/*
    Magnetorquer hardware signal control values [% PWM]
*/
typedef struct {
    int8_t i8Magnetorquer_value_x;
    int8_t i8Magnetorquer_value_y;
    int8_t i8Magnetorquer_value_z;
} PACKED_STRUCT DATA_CACHE_ACTUATOR_MTQ_VALUES_t;

/*
    Actuator desired torque in Body Frame [Nm]
*/
typedef struct {
    double dRequired_torque_x;
    double dRequired_torque_y;
    double dRequired_torque_z;
} PACKED_STRUCT DATA_CACHE_ACTUATOR_TORQUE_VALUES_t;

typedef struct {
    int16_t i16Est_roll_angle;
    int16_t i16Est_pitch_angle;
    int16_t i16Est_yaw_angle;
    int16_t i16IGRF_MagField_X;
    int16_t i16IGRF_MagField_Y;
    int16_t i16IGRF_MagField_Z;
    int16_t i16Modelled_Sun_V_X;
    int16_t i16Modelled_Sun_V_Y;
    int16_t i16Modelled_Sun_V_Z;
    int16_t i16EstGyroBias_X;
    int16_t i16EstGyroBias_Y;
    int16_t i16EstGyroBias_Z;
    int16_t i16Innovation_Vec_X;
    int16_t i16Innovation_Vec_Y;
    int16_t i16Innovation_Vec_Z;
    int16_t i16Err_Q1;
    int16_t i16Err_Q2;
    int16_t i16Err_Q3;
    int16_t i16RMS_Q1;
    int16_t i16RMS_Q2;
    int16_t i16RMS_Q3;
    int16_t i16X_AngRate_Cov;
    int16_t i16Y_AngRate_Cov;
    int16_t i16Z_AngRate_Cov;
    int16_t i16X_Rate;
    int16_t i16Y_Rate;
    int16_t i16Z_Rate;
    int16_t i16Q0;
    int16_t i16Q1;
    int16_t i16Q2;
} PACKED_STRUCT DATA_CACHE_ADCS_3_t;

typedef struct {
    uint16_t u16Cubesense1_3V3_Current;
    uint16_t u16Cubesense1_SRAM_Current;
    uint16_t u16Cubesense2_3V3_Current;
    uint16_t u16Cubesense2_SRAM_Current;
    uint16_t u16CubeControl_3V3_Current;
    uint16_t u16CubeControl_5V_Current;
    uint16_t u16CubeControl_Vbat_Current;
    uint16_t u16Wheel_1_Current;
    uint16_t u16Wheel_2_Current;
    uint16_t u16Wheel_3_Current;
    uint16_t u16CubeStar_Current;
    uint16_t u16MTQ_Current;
    int16_t i16CubeStar_MCU_Temp;
    int16_t i16ADCS_MCU_Temp;
    int16_t i16MTM_Temp;
    int16_t i16RMTM_Temp;
    int16_t i16X_Rate_Sensor_Temp;
    int16_t i16Y_Rate_Sensor_Temp;
    int16_t i16Z_Rate_Sensor_Temp;
} PACKED_STRUCT DATA_CACHE_ADCS_4_t;

/*
    GetPowerDistributionInfo from EPSII_PDM_1 interface
*/
typedef struct {
    int32_t i32In_SysBUS_Voltage;
    int32_t i32Out_BatRAW_Output_Sense_U;
    int32_t i32Out_BatRAW_Output_Sense_I;
    int32_t i32Out_BatRAW_Output_Sense_P;
    int32_t i32Out_12V_Output_Sense_U;
    int32_t i32Out_12V_Output_Sense_I;
    int32_t i32Out_12V_Output_Sense_P;
    int32_t i32Out_12V_Output_ILimit;
    int32_t i32Out_5V_Output1_Sense_U;
    int32_t i32Out_5V_Output1_Sense_I;
    int32_t i32Out_5V_Output1_Sense_P;
    int32_t i32Out_5V_Output1_ILimit;
    int32_t i32Out_5V_Output2_Sense_U;
    int32_t i32Out_5V_Output2_Sense_I;
    int32_t i32Out_5V_Output2_Sense_P;
    int32_t i32Out_5V_Output2_ILimit;
    int32_t i32Out_3V3_Output1_Sense_U;
    int32_t i32Out_3V3_Output1_Sense_I;
    int32_t i32Out_3V3_Output1_Sense_P;
    int32_t i32Out_3V3_Output1_ILimit;
    int32_t i32Out_3V3_Output2_Sense_U;
    int32_t i32Out_3V3_Output2_Sense_I;
    int32_t i32Out_3V3_Output2_Sense_P;
    int32_t i32Out_3V3_Output2_ILimit;
} PACKED_STRUCT DATA_CACHE_EPS_9_t;

/*
    GetDeviceHealthInfo from EPSII_PDM_1 interface
*/
typedef struct {
    int32_t i32ActiveCPU_RunningTime;
    int32_t i32ActiveCPU_Voltage;
    int32_t i32ActiveCPU_Temperature;
    int32_t i32PCB_Temperature_1;
    int32_t i32PCB_Temperature_2;
    int32_t i32NVM_AllocatedSize;
    int32_t i32NVM_UsedSize;
    int32_t i32Stack_AllocatedSize;
    int32_t i32Stack_UsedSize;
    uint8_t u8DPOT_MCP4562_LUP_3V3_1P;
    uint8_t u8DPOT_MCP4562_LUP_3V3_1R;
    uint8_t u8DPOT_MCP4562_LUP_3V3_2P;
    uint8_t u8DPOT_MCP4562_LUP_3V3_2R;
    uint8_t u8DPOT_MCP4562_LUP_5V_1P;
    uint8_t u8DPOT_MCP4562_LUP_5V_1R;
    uint8_t u8DPOT_MCP4562_LUP_5V_2P;
    uint8_t u8DPOT_MCP4562_LUP_5V_2R;
    uint8_t u8DPOT_MCP4562_LUP_12V_P;
    uint8_t u8DPOT_MCP4562_LUP_12V_R;
    uint8_t u8DPOT_MCP4562_OUTU_12V_P;
    uint8_t u8DPOT_MCP4562_OUTU_12V_R;
    uint8_t u8GPIO_PCA9538_U1001;
    uint8_t u8GPIO_PCA9538_U1000;
    uint8_t u8GPIO_PCA9538_U1004;
    uint8_t u8GPIO_PCA9538_U1011;
    uint8_t u8INA_LUP_IN_3V3_1P;
    uint8_t u8INA_LUP_IN_3V3_1R;
    uint8_t u8INA_LUP_IN_3V3_2P;
    uint8_t u8INA_LUP_IN_3V3_2R;
    uint8_t u8INA_LUP_IN_5V_1P;
    uint8_t u8INA_LUP_IN_5V_1R;
    uint8_t u8INA_LUP_IN_5V_2P;
    uint8_t u8INA_LUP_IN_5V_2R;
    uint8_t u8INA_LUP_IN_12V_P;
    uint8_t u8INA_LUP_IN_12V_R;
    uint8_t u8TMP117_U1014;
    uint8_t u8TMP117_U1031;
} PACKED_STRUCT DATA_CACHE_EPS_10_t;

/*
    GetRAWSensors from EPSII_PDM_1 interface (Indexes 1-54)
*/
typedef struct {
    int32_t ai32Pdm_1_54_values[54];
} PACKED_STRUCT DATA_CACHE_EPS_14_t;

/*
    CubeADCS Gen2 common operational status - TLM_137, TLM_183, TLM_230
*/
typedef struct {
    uint8_t u8State;
    uint8_t u8ResetReason;
    bool bDualBankBoot;
    bool bAppReadError;
    bool bAppEmptyError;
    bool bAppTypeError;
    bool bAppVectTblError;
    bool bConfigReadError;
    bool bConfigEmptyError;
    bool bConfigTypeError;
    bool bConfigMismatchError;
    bool bSharedParamsError;
    bool bPortValidationError;
    bool bPortDiscoveryError;
    bool bOtpSerialError;
    bool bCfgSerialError;
    bool bSerialMismatchError;
    bool bConfigUnlockError;
    bool bConfigInvalidError;
    uint8_t u8Rwl0;
    uint8_t u8Rwl1;
    uint8_t u8Rwl2;
    uint8_t u8Rwl3;
    uint8_t u8Mag0;
    uint8_t u8Mag1;
    uint8_t u8Gyro0;
    uint8_t u8Gyro1;
    uint8_t u8Fss0;
    uint8_t u8Fss1;
    uint8_t u8Fss2;
    uint8_t u8Fss3;
    uint8_t u8Hss0;
    uint8_t u8Hss1;
    uint8_t u8Str0;
    uint8_t u8Str1;
    uint8_t u8ExtSensor0;
    uint8_t u8ExtSensor1;
    uint32_t u32MasterSvc;
    uint32_t u32FramFsSvc;
    uint32_t u32EventLogSvc;
    uint32_t u32ImgLogSvc;
    uint32_t u32TlmLogSvc;
    uint32_t u32ImuSvc;
} PACKED_STRUCT DATA_CACHE_CUBEADCS_GEN2_OP_STATUS_COMMON_t;

/*
    CubeADCS Gen2 application control program operational status - TLM_185, TLM_199, TLM_200
*/
typedef struct {
    uint8_t u8Run_mode;
    uint8_t u8Control_mode;
    uint16_t u16Magnetic_control_timeout;
    uint8_t u8Estimator_main;
    uint8_t u8Estimator_backup;
    uint8_t u8Adcs_op_state;
} PACKED_STRUCT DATA_CACHE_CUBEADCS_GEN2_OP_STATUS_APP_t;

/*
    CubeADCS Gen2 TLM_166 - Health telemetry for cubenode pst3s
*/
typedef struct {
    double dStr0McuTemp;
    double dStr0McuCurrent;
    uint16_t u16Str0McuVoltage;
    double dStr0Pst3sCurrent;
    bool bStr0Pst3sOvercurrent;
    double dStr1McuTemp;
    double dStr1McuCurrent;
    uint16_t u16Str1McuVoltage;
    double dStr1Pst3sCurrent;
    bool bStr1Pst3sOvercurrent;
} PACKED_STRUCT DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_166_t;

/*
    CubeADCS Gen2 TLM_167 - Health telemetry for CubeMag magnetometer
*/
typedef struct {
    double dMag0McuTemp;
    double dMag0McuCurrent;
    uint16_t u16Mag0McuVoltage;
    double dMag0PrimaryTemp;
    double dMag0RedTemp;
    uint32_t u32Mag0BurnCurrent;
    bool bMag0DeployPinState;
    bool bMag0BurnPinState;
    bool bMag0BurnUnderCurrent;
    bool bMag0BurnOverCurrent;
    bool bMag0DeployTimeout;
    double dMag1McuTemp;
    double dMag1McuCurrent;
    uint16_t u16Mag1McuVoltage;
    double dMag1PrimaryTemp;
    double dMag1RedTemp;
    uint32_t u32Mag1BurnCurrent;
    bool bMag1DeployPinState;
    bool bMag1BurnPinState;
    bool bMag1BurnUnderCurrent;
    bool bMag1BurnOverCurrent;
    bool bMag1DeployTimeout;
} PACKED_STRUCT DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_167_t;

/*
    CubeADCS Gen2 TLM_168 - Health telemetry for CubeSense Sun
*/
typedef struct {
    double dFss0McuTemp;
    double dFss0McuCurrent;
    uint16_t u16Fss0McuVoltage;
    double dFss0CurrentCam;
    double dFss0CurrentSram;
    bool bFss0OvercurrentCam;
    bool bFss0OvercurrentSram;
    double dFss1McuTemp;
    double dFss1McuCurrent;
    uint16_t u16Fss1McuVoltage;
    double dFss1CurrentCam;
    double dFss1CurrentSram;
    bool bFss1OvercurrentCam;
    bool bFss1OvercurrentSram;
    double dFss2McuTemp;
    double dFss2McuCurrent;
    uint16_t u16Fss2McuVoltage;
    double dFss2CurrentCam;
    double dFss2CurrentSram;
    bool bFss2OvercurrentCam;
    bool bFss2OvercurrentSram;
    double dFss3McuTemp;
    double dFss3McuCurrent;
    uint16_t u16Fss3McuVoltage;
    double dFss3CurrentCam;
    double dFss3CurrentSram;
    bool bFss3OvercurrentCam;
    bool bFss3OvercurrentSram;
} PACKED_STRUCT DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_168_t;

/*
    CubeADCS Gen2 TLM_169 - Torquer Current measurements
*/
typedef struct {
    float fMtq1TotalCurrentPeakPos;
    float fMtq1TotalCurrentAveragePos;
    float fMtq1TotalCurrentPeakNeg;
    float fMtq1TotalCurrentAverageNeg;
    float fMtq2TotalCurrentPeakPos;
    float fMtq2TotalCurrentAveragePos;
    float fMtq2TotalCurrentPeakNeg;
    float fMtq2TotalCurrentAverageNeg;
    float fMtq3TotalCurrentPeakPos;
    float fMtq3TotalCurrentAveragePos;
    float fMtq3TotalCurrentPeakNeg;
    float fMtq3TotalCurrentAverageNeg;
    uint8_t u8Mtq1Polarity;
    uint8_t u8Mtq2Polarity;
    uint8_t u8Mtq3Polarity;
} PACKED_STRUCT DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_169_t;

/*
    CubeADCS Gen2 TLM_170 - Raw CubeSense Sun telemetry
*/
typedef struct {
    uint32_t u32TimeSeconds;
    uint32_t u32TimeNs;
    double dFss0Alpha;
    double dFss0Beta;
    uint8_t u8Fss0CaptureResult;
    uint8_t u8Fss0DetectionResult;
    double dFss1Alpha;
    double dFss1Beta;
    uint8_t u8Fss1CaptureResult;
    uint8_t u8Fss1DetectionResult;
    double dFss2Alpha;
    double dFss2Beta;
    uint8_t u8Fss2CaptureResult;
    uint8_t u8Fss2DetectionResult;
    double dFss3Alpha;
    double dFss3Beta;
    uint8_t u8Fss3CaptureResult;
    uint8_t u8Fss3DetectionResult;
    bool bFss0IsValid;
    bool bFss1IsValid;
    bool bFss2IsValid;
    bool bFss3IsValid;
} PACKED_STRUCT DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_170_t;

/*
    CubeADCS Gen2 TLM_171 - Raw external sensor telemetry
*/
typedef struct {
    uint32_t u32TimeSeconds;
    uint32_t u32TimeNs;
    float fExtSensor0Float0;
    float fExtSensor0Float1;
    float fExtSensor0Float2;
    float fExtSensor0Float3;
    float fExtSensor0Float4;
    float fExtSensor0Float5;
    float fExtSensor1Float0;
    float fExtSensor1Float1;
    float fExtSensor1Float2;
    float fExtSensor1Float3;
    float fExtSensor1Float4;
    float fExtSensor1Float5;
    bool bExtSensor0IsValid;
    bool bExtSensor1IsValid;
} PACKED_STRUCT DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_171_t;

/*
    CubeADCS Gen2 TLM_172 - Controller telemetry
*/
typedef struct {
    uint32_t u32TimeSeconds;
    uint32_t u32TimeNs;
    double dRpyCmdRoll;
    double dRpyCmdPitch;
    double dRpyCmdYaw;
    double dRpyErrRoll;
    double dRpyErrPitch;
    double dRpyErrYaw;
    float fTgtRefLat;
    float fTgtRefLon;
    float fTgtRefAlt;
    double dQuatErrQ0;
    double dQuatErrQ1;
    double dQuatErrQ2;
    float fRwl0CmdSpeed;
    float fRwl1CmdSpeed;
    float fRwl2CmdSpeed;
    float fRwl3CmdSpeed;
    float fRwl0CmdMom;
    float fRwl1CmdMom;
    float fRwl2CmdMom;
    float fRwl3CmdMom;
    float fRwl0CmdTorque;
    float fRwl1CmdTorque;
    float fRwl2CmdTorque;
    float fRwl3CmdTorque;
    double dMtq0CmdDip;
    double dMtq1CmdDip;
    double dMtq2CmdDip;
    float fMtq0CmdTorque;
    float fMtq1CmdTorque;
    float fMtq2CmdTorque;
    int16_t i16Mtq0CmdOnTime;
    int16_t i16Mtq1CmdOnTime;
    int16_t i16Mtq2CmdOnTime;
    uint16_t u16MagConTimeout;
    uint8_t u8ConModeActive;
    bool bRwl0ErrorFlag;
    bool bRwl1ErrorFlag;
    bool bRwl2ErrorFlag;
    bool bRwl3ErrorFlag;
    bool bRwl0ActiveFlag;
    bool bRwl1ActiveFlag;
    bool bRwl2ActiveFlag;
    bool bRwl3ActiveFlag;
    uint8_t u8FmcStage;
} PACKED_STRUCT DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_172_t;

/*
    CubeADCS Gen2 TLM_173 - Backup estimator telemetry
*/
typedef struct {
    uint32_t u32TimeSeconds;
    uint32_t u32TimeNs;
    double dEstRpyRoll;
    double dEstRpyPitch;
    double dEstRpyYaw;
    double dEstQuatQ0;
    double dEstQuatQ1;
    double dEstQuatQ2;
    double dEstQuatQ3;
    double dEstGyroBiasX;
    double dEstGyroBiasY;
    double dEstGyroBiasZ;
    double dEstRateOrcX;
    double dEstRateOrcY;
    double dEstRateOrcZ;
    double dEstRateIrcX;
    double dEstRateIrcY;
    double dEstRateIrcZ;
    float fEstGyrTorqueX;
    float fEstGyrTorqueY;
    float fEstGyrTorqueZ;
    double dEstInnovX;
    double dEstInnovY;
    double dEstInnovZ;
    double dEstStdDevRateX;
    double dEstStdDevRateY;
    double dEstStdDevRateZ;
    double dEstStdDevQ0;
    double dEstStdDevQ1;
    double dEstStdDevQ2;
    uint8_t u8EstModeActive;
} PACKED_STRUCT DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_173_t;

/*
    CubeADCS Gen2 TLM_174 - Models telemetry
*/
typedef struct {
    uint32_t u32TimeSeconds;
    uint32_t u32TimeNs;
    int32_t i32SatPosEciX;
    int32_t i32SatPosEciY;
    int32_t i32SatPosEciZ;
    int16_t i16SatVelEciX;
    int16_t i16SatVelEciY;
    int16_t i16SatVelEciZ;
    double dSatLatGeod;
    double dSatLatGeoc;
    double dSatLon;
    double dSatAlt;
    int32_t i32TgtPosEciX;
    int32_t i32TgtPosEciY;
    int32_t i32TgtPosEciZ;
    double dModelMagOrcX;
    double dModelMagOrcY;
    double dModelMagOrcZ;
    double dModelSunOrcX;
    double dModelSunOrcY;
    double dModelSunOrcZ;
    double dModelSunBetaAngle;
    double dModelHorRhoAngle;
    double dModelHorXoEastAngle;
    double dModelHorYiEastAngle;
    int32_t i32Sat2TgtGndOrcX;
    int32_t i32Sat2TgtGndOrcY;
    int32_t i32Sat2TgtGndOrcZ;
    uint16_t u16Asgp4BatchCtr;
    uint16_t u16Asgp4PosDelta;
    uint8_t u8OrbModeActive;
    bool bAsgp4Error;
    bool bEclipse;
    uint8_t u8NavSource;
} PACKED_STRUCT DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_174_t;

/*
    CubeADCS Gen2 TLM_175 - Calibrated GNSS sensor telemetry
*/
typedef struct {
    uint32_t u32TimeSeconds;
    uint32_t u32TimeNs;
    float fGnssSatPosEcefX;
    float fGnssSatPosEcefY;
    float fGnssSatPosEcefZ;
    float fGnssSatVelEcefX;
    float fGnssSatVelEcefY;
    float fGnssSatVelEcefZ;
    uint32_t u32GnssTimeSeconds;
    uint32_t u32GnssTimeNs;
    bool bGnssIsValid;
} PACKED_STRUCT DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_175_t;

/*
    CubeADCS Gen2 TLM_176 - Calibrated HSS sensor telemetry
*/
typedef struct {
    uint32_t u32TimeSeconds;
    uint32_t u32TimeNs;
    double dHss0CalVecX;
    double dHss0CalVecY;
    double dHss0CalVecZ;
    double dHss1CalVecX;
    double dHss1CalVecY;
    double dHss1CalVecZ;
    bool bHss0IsValid;
    bool bHss1IsValid;
} PACKED_STRUCT DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_176_t;

/*
    CubeADCS Gen2 TLM_177 - Calibrated MAG sensor telemetry
*/
typedef struct {
    uint32_t u32TimeSeconds;
    uint32_t u32TimeNs;
    double dMag0CalVecX;
    double dMag0CalVecY;
    double dMag0CalVecZ;
    double dMag1CalVecX;
    double dMag1CalVecY;
    double dMag1CalVecZ;
    bool bMag0IsValid;
    bool bMag1IsValid;
    bool bMag0IsBest;
    bool bMag1IsBest;
} PACKED_STRUCT DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_177_t;

/*
    CubeADCS Gen2 TLM_178 - Calibrated FSS sensor telemetry
*/
typedef struct {
    uint32_t u32TimeSeconds;
    uint32_t u32TimeNs;
    double dFss0CalVecX;
    double dFss0CalVecY;
    double dFss0CalVecZ;
    double dFss1CalVecX;
    double dFss1CalVecY;
    double dFss1CalVecZ;
    double dFss2CalVecX;
    double dFss2CalVecY;
    double dFss2CalVecZ;
    double dFss3CalVecX;
    double dFss3CalVecY;
    double dFss3CalVecZ;
    bool bFss0IsValid;
    bool bFss1IsValid;
    bool bFss2IsValid;
    bool bFss3IsValid;
    bool bFss0IsBest;
    bool bFss1IsBest;
    bool bFss2IsBest;
    bool bFss3IsBest;
} PACKED_STRUCT DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_178_t;

/*
    CubeADCS Gen2 TLM_179 - Raw CubeSense Earth telemetry
*/
typedef struct {
    uint32_t u32TimeSeconds;
    uint32_t u32TimeNs;
    double dHss0RawElev;
    double dHss0RawRot;
    uint8_t u8Hss0CaptureResult;
    uint8_t u8Hss0DetectionResult;
    double dHss1RawElev;
    double dHss1RawRot;
    uint8_t u8Hss1CaptureResult;
    uint8_t u8Hss1DetectionResult;
    bool bHss0IsValid;
    bool bHss1IsValid;
} PACKED_STRUCT DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_179_t;

/*
    CubeADCS Gen2 TLM_180 - Raw MAG sensor telemetry
*/
typedef struct {
    uint32_t u32TimeSeconds;
    uint32_t u32TimeNs;
    double dMag0RawVecX;
    double dMag0RawVecY;
    double dMag0RawVecZ;
    double dMag1RawVecX;
    double dMag1RawVecY;
    double dMag1RawVecZ;
    bool bMag0IsValid;
    bool bMag1IsValid;
} PACKED_STRUCT DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_180_t;

/*
    CubeADCS Gen2 TLM_203 - Raw CSS sensor telemetry
*/
typedef struct {
    uint32_t u32TimeSeconds;
    uint32_t u32TimeNs;
    uint8_t u8Css0Raw;
    uint8_t u8Css1Raw;
    uint8_t u8Css2Raw;
    uint8_t u8Css3Raw;
    uint8_t u8Css4Raw;
    uint8_t u8Css5Raw;
    uint8_t u8Css6Raw;
    uint8_t u8Css7Raw;
    uint8_t u8CsInt8Raw;
    uint8_t u8Css9Raw;
    bool bCssIsValid;
} PACKED_STRUCT DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_203_t;

/*
    CubeADCS Gen2 TLM_204 - Raw GYR sensor telemetry
*/
typedef struct {
    uint32_t u32TimeSeconds;
    uint32_t u32TimeNs;
    float fGyro0RawRateX;
    float fGyro0RawRateY;
    float fGyro0RawRateZ;
    float fGyro1RawRateX;
    float fGyro1RawRateY;
    float fGyro1RawRateZ;
    bool bGyro0IsValid;
    bool bGyro1IsValid;
} PACKED_STRUCT DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_204_t;

/*
    CubeADCS Gen2 TLM_205 - Raw RWL sensor telemetry
*/
typedef struct {
    uint32_t u32TimeSeconds;
    uint32_t u32TimeNs;
    float fRwl0MeasSpeed;
    float fRwl1MeasSpeed;
    float fRwl2MeasSpeed;
    float fRwl3MeasSpeed;
    bool bRwl0IsValid;
    bool bRwl1IsValid;
    bool bRwl2IsValid;
    bool bRwl3IsValid;
} PACKED_STRUCT DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_205_t;

/*
    CubeADCS Gen2 TLM_206 - Calibrated CSS sensor telemetry
*/
typedef struct {
    uint32_t u32TimeSeconds;
    uint32_t u32TimeNs;
    double dCssCalVecX;
    double dCssCalVecY;
    double dCssCalVecZ;
    bool bCssIsValid;
} PACKED_STRUCT DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_206_t;

/*
    CubeADCS Gen2 TLM_207 - Calibrated GYR sensor telemetry
*/
typedef struct {
    uint32_t u32TimeSeconds;
    uint32_t u32TimeNs;
    float fGyro0CalRateX;
    float fGyro0CalRateY;
    float fGyro0CalRateZ;
    float fGyro1CalRateX;
    float fGyro1CalRateY;
    float fGyro1CalRateZ;
    float fExtGyro0CalRateX;
    float fExtGyro0CalRateY;
    float fExtGyro0CalRateZ;
    float fExtGyro1CalRateX;
    float fExtGyro1CalRateY;
    float fExtGyro1CalRateZ;
    bool bGyro0IsValid;
    bool bGyro1IsValid;
    bool bExtGyro0IsValid;
    bool bExtGyro1IsValid;
} PACKED_STRUCT DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_207_t;

/*
    CubeADCS Gen2 TLM_208 - Calibrated STR sensor telemetry Part 1
*/
typedef struct {
    uint32_t u32TimeSeconds;
    uint32_t u32TimeNs;
    double dStr0MeasBodyVec0X;
    double dStr0MeasBodyVec0Y;
    double dStr0MeasBodyVec0Z;
    double dStr0MeasBodyVec1X;
    double dStr0MeasBodyVec1Y;
    double dStr0MeasBodyVec1Z;
    double dStr0MeasBodyVec2X;
    double dStr0MeasBodyVec2Y;
    double dStr0MeasBodyVec2Z;
    double dStr0ModelOrbitVec0X;
    double dStr0ModelOrbitVec0Y;
    double dStr0ModelOrbitVec0Z;
    double dStr0ModelOrbitVec1X;
    double dStr0ModelOrbitVec1Y;
    double dStr0ModelOrbitVec1Z;
    double dStr0ModelOrbitVec2X;
    double dStr0ModelOrbitVec2Y;
    double dStr0ModelOrbitVec2Z;
} PACKED_STRUCT DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_208_1_t;

/*
    CubeADCS Gen2 TLM_208 - Calibrated STR sensor telemetry part 2
*/
typedef struct {
    double dStr1MeasBodyVec0X;
    double dStr1MeasBodyVec0Y;
    double dStr1MeasBodyVec0Z;
    double dStr1MeasBodyVec1X;
    double dStr1MeasBodyVec1Y;
    double dStr1MeasBodyVec1Z;
    double dStr1MeasBodyVec2X;
    double dStr1MeasBodyVec2Y;
    double dStr1MeasBodyVec2Z;
    double dStr1ModelOrbitVec0X;
    double dStr1ModelOrbitVec0Y;
    double dStr1ModelOrbitVec0Z;
    double dStr1ModelOrbitVec1X;
    double dStr1ModelOrbitVec1Y;
    double dStr1ModelOrbitVec1Z;
    double dStr1ModelOrbitVec2X;
    double dStr1ModelOrbitVec2Y;
    double dStr1ModelOrbitVec2Z;
    bool bStr0IsValid;
    bool bStr1IsValid;
} PACKED_STRUCT DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_208_2_t;

/*
    CubeADCS Gen2 TLM_209 - Calibrated RWL sensor telemetry
*/
typedef struct {
    uint32_t u32TimeSeconds;
    uint32_t u32TimeNs;
    float fRwlTorqueVecX;
    float fRwlTorqueVecY;
    float fRwlTorqueVecZ;
    float fRwlMomVecX;
    float fRwlMomVecY;
    float fRwlMomVecZ;
    bool bRwlIsValid;
} PACKED_STRUCT DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_209_t;

/*
    CubeADCS Gen2 TLM_210 - Main estimator telemetry
*/
typedef struct {
    uint32_t u32TimeSeconds;
    uint32_t u32TimeNs;
    double dEstRpyRoll;
    double dEstRpyPitch;
    double dEstRpyYaw;
    double dEstQuatQ0;
    double dEstQuatQ1;
    double dEstQuatQ2;
    double dEstQuatQ3;
    double dEstGyroBiasX;
    double dEstGyroBiasY;
    double dEstGyroBiasZ;
    double dEstRateOrcX;
    double dEstRateOrcY;
    double dEstRateOrcZ;
    double dEstRateIrcX;
    double dEstRateIrcY;
    double dEstRateIrcZ;
    float fEstGyrTorqueX;
    float fEstGyrTorqueY;
    float fEstGyrTorqueZ;
    double dEstInnovX;
    double dEstInnovY;
    double dEstInnovZ;
    double dEstStdDevRateX;
    double dEstStdDevRateY;
    double dEstStdDevRateZ;
    double dEstStdDevQ0;
    double dEstStdDevQ1;
    double dEstStdDevQ2;
    uint8_t u8EstModeActive;
} PACKED_STRUCT DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_210_t;

/*
    CubeADCS Gen2 TLM_211 - Main estimator high-resolution telemetry
*/
typedef struct {
    uint32_t u32TimeSeconds;
    uint32_t u32TimeNs;
    float fEstQuatQ0;
    float fEstQuatQ1;
    float fEstQuatQ2;
    float fEstQuatQ3;
    float fEstRateOrcX;
    float fEstRateOrcY;
    float fEstRateOrcZ;
} PACKED_STRUCT DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_211_t;

/*
    CubeADCS Gen2 TLM_212 - Raw GNSS sensor telemetry
*/
typedef struct {
    uint32_t u32RtcTimeSeconds;
    uint32_t u32RtcTimeNs;
    int32_t i32RtcDriftNs;
    float fGnssSatPosEcefX;
    float fGnssSatPosEcefY;
    float fGnssSatPosEcefZ;
    float fGnssSatVelEcefX;
    float fGnssSatVelEcefY;
    float fGnssSatVelEcefZ;
    uint32_t u32GnssTimeSeconds;
    uint32_t u32GnssTimeNs;
    uint16_t u16GpsWeek;
    uint32_t u32Tow;
    int8_t i8UtcOffset;
    bool bGnssValidData;
    bool bGnssLock;
    bool bGnssPPSDetected;
} PACKED_STRUCT DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_212_t;

/*
    CubeADCS Gen2 TLM_213 - Raw PST3S star tracker telemetry
*/
typedef struct {
    uint32_t u32TimeSeconds;
    uint32_t u32TimeNs;
    uint8_t u8Str0Pst3sVersion;
    float fStr0Quat1;
    float fStr0Quat2;
    float fStr0Quat3;
    float fStr0Quat4;
    float fStr0AngVelX;
    float fStr0AngVelY;
    float fStr0AngVelZ;
    uint8_t u8Str0RateQuality;
    uint32_t u32Str0UnixSeconds;
    float fStr0UnixSecondsDecimal;
    int8_t i8Str0Temperature;
    uint8_t u8Str0ImageExposure;
    uint8_t u8Str0ImageThreshold;
    uint8_t u8Str0BackGroundValues;
    uint8_t u8Str0InternalProcessCode;
    uint8_t u8Str0CmosChipIdResult;
    uint8_t u8Str0FpgaMRamResult;
    uint8_t u8Str0NumberOfExtractedStars;
    uint8_t u8Str0OperatingMode;
    uint8_t u8Str0ImagingGain;
    uint8_t u8Str0MinNavigationStars;
    uint8_t u8Str0DataValid;
    uint8_t u8Str0ExtImageState;
    uint8_t u8Str0IdentifiedStars;
    uint8_t u8Str0DeviceNumber;
    uint8_t u8Str0SoftwareVersion;
    uint8_t u8Str0EdacErrorCount;
    uint32_t u32Str0ImageFrameNumber;
    uint8_t u8Str0DynamicMode;
    uint8_t u8Str0SaaMode;
    uint8_t u8Str0SaaThreshold;
    uint8_t u8Str0QuaternionFilteringState;
    uint8_t u8Str0FourStarCaptureThreshold;
    uint8_t u8Str0TrackingThreshold;
    bool bStr0EdacSwitch;
    uint8_t u8Str1Pst3sVersion;
    float fStr1Quat1;
    float fStr1Quat2;
    float fStr1Quat3;
    float fStr1Quat4;
    float fStr1AngVelX;
    float fStr1AngVelY;
    float fStr1AngVelZ;
    uint8_t u8Str1RateQuality;
    uint32_t u32Str1UnixSeconds;
    float fStr1UnixSecondsDecimal;
    int8_t i8Str1Temperature;
    uint8_t u8Str1ImageExposure;
    uint8_t u8Str1ImageThreshold;
    uint8_t u8Str1BackGroundValues;
    uint8_t u8Str1InternalProcessCode;
    uint8_t u8Str1CmosChipIdResult;
    uint8_t u8Str1FpgaMRamResult;
    uint8_t u8Str1NumberOfExtractedStars;
    uint8_t u8Str1OperatingMode;
    uint8_t u8Str1ImagingGain;
    uint8_t u8Str1MinNavigationStars;
    uint8_t u8Str1DataValid;
    uint8_t u8Str1ExtImageState;
    uint8_t u8Str1IdentifiedStars;
    uint8_t u8Str1DeviceNumber;
    uint8_t u8Str1SoftwareVersion;
    uint8_t u8Str1EdacErrorCount;
    uint32_t u32Str1ImageFrameNumber;
    uint8_t u8Str1DynamicMode;
    uint8_t u8Str1SaaMode;
    uint8_t u8Str1SaaThreshold;
    uint8_t u8Str1QuaternionFilteringState;
    uint8_t u8Str1FourStarCaptureThreshold;
    uint8_t u8Str1TrackingThreshold;
    bool bStr1EdacSwitch;
} PACKED_STRUCT DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_213_t;

/*
    CubeADCS Gen2 TLM_214 - ACP execution telemetry
*/
typedef struct {
    uint16_t u16TimeSinceLoopStart;
    uint8_t u8CurrentExecutionPoint;
    uint16_t u16ExecTimeNodeSync;
    uint16_t u16ExecTimeSensorComms;
    uint16_t u16ExecTimeSensorCal;
    uint16_t u16ExecTimeEstimators;
    uint16_t u16ExecTimeControllers;
    uint16_t u16ExecTimeWheelComms;
    uint16_t u16ExecTimeModels;
    uint16_t u16ExecTimeLoopSync;
    uint16_t u16ExecTimeHealth;
    uint16_t u16ExecTimeTlmLog;
    int16_t i16LoopRtcOffset;
    bool bLoopHasStarted;
    bool bHilSyncOk;
} PACKED_STRUCT DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_214_t;

/*
    CubeADCS Gen2 TLM_216 - CubeComputer Health
*/
typedef struct {
    double dMcuTemp;
    double dMcuCurrent;
    uint16_t u16McuVoltage;
    uint16_t u16SupplyVoltage;
    uint16_t u16V5Sense;
    uint16_t u16BatteryVoltage;
    uint16_t u16VersionVoltage;
    double dSram1Current;
    double dSram2Current;
    double dFpgaCurrent1v5;
    double dFramCurrent;
    double dAdcCurrent;
    double dFlashCurrent;
    double dRs485Current;
    double dCanCurrent;
    double dGyroCurrent;
    double dRedGyroCurrent;
    bool bGyroOverVoltage;
    bool bGyroUnderVoltage;
    bool bRedGyroOverVoltage;
    bool bRedGyroUnderVoltage;
    uint8_t au8WatchdogCount[5];
} PACKED_STRUCT DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_216_t;

/*
    CubeADCS Gen2 TLM_217 - Health telemetry for CubeSense Earth
*/
typedef struct {
    double dHss0McuTemp;
    double dHss0McuCurrent;
    uint16_t u16Hss0McuVoltage;
    double dHss0DetectorTemp;
    double dHss0DetectorCurrent;
    double dHss1McuTemp;
    double dHss1McuCurrent;
    uint16_t u16Hss1McuVoltage;
    double dHss1DetectorTemp;
    double dHss1DetectorCurrent;
} PACKED_STRUCT DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_217_t;

/*
    CubeADCS Gen2 TLM_218 - Health telemetry for Reaction Wheels
*/
typedef struct {
    double dRwl0McuTemp;
    double dRwl0McuCurrent;
    uint16_t u16Rwl0BatVoltage;
    double dRwl0BatCurrent;
    double dRwl1McuTemp;
    double dRwl1McuCurrent;
    uint16_t u16Rwl1BatVoltage;
    double dRwl1BatCurrent;
    double dRwl2McuTemp;
    double dRwl2McuCurrent;
    uint16_t u16Rwl2BatVoltage;
    double dRwl2BatCurrent;
    double dRwl3McuTemp;
    double dRwl3McuCurrent;
    uint16_t u16Rwl3BatVoltage;
    double dRwl3BatCurrent;
} PACKED_STRUCT DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_218_t;

/*
    CubeADCS Gen2 TLM_225 - Health telemetry for CubeNode NSSRWL
*/
typedef struct {
    double dRwl0McuTemp;
    double dRwl0McuCurrent;
    uint16_t u16Rwl0McuVoltage;
    double dRwl0Current5v;
    uint16_t u16Rwl0PmuCurrent;
    bool bRwl0Overcurrent5v;
    bool bRwl0PowerGood;
    bool bRwl0PmuCurrentValid;
    double dRwl1McuTemp;
    double dRwl1McuCurrent;
    uint16_t u16Rwl1McuVoltage;
    double dRwl1Current5v;
    uint16_t u16Rwl1PmuCurrent;
    bool bRwl1Overcurrent5v;
    bool bRwl1PowerGood;
    bool bRwl1PmuCurrentValid;
    double dRwl2McuTemp;
    double dRwl2McuCurrent;
    uint16_t u16Rwl2McuVoltage;
    double dRwl2Current5v;
    uint16_t u16Rwl2PmuCurrent;
    bool bRwl2Overcurrent5v;
    bool bRwl2PowerGood;
    bool bRwl2PmuCurrentValid;
    double dRwl3McuTemp;
    double dRwl3McuCurrent;
    uint16_t u16Rwl3McuVoltage;
    double dRwl3Current5v;
    uint16_t u16Rwl3PmuCurrent;
    bool bRwl3Overcurrent5v;
    bool bRwl3PowerGood;
    bool bRwl3PmuCurrentValid;
} PACKED_STRUCT DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_225_t;

/*
    CubeADCS Gen2 TLM_226 - Raw NSSRWL sensor telemetry
*/
typedef struct {
    uint32_t u32TimeSeconds;
    uint32_t u32TimeNs;
    int16_t i16Rwl0TargetValue;
    float fRwl0MeasSpeed;
    int16_t i16Rwl0MeasCurrent;
    int16_t i16Rwl0Temp;
    int16_t i16Rwl1TargetValue;
    float fRwl1MeasSpeed;
    int16_t i16Rwl1MeasCurrent;
    int16_t i16Rwl1Temp;
    int16_t i16Rwl2TargetValue;
    float fRwl2MeasSpeed;
    int16_t i16Rwl2MeasCurrent;
    int16_t i16Rwl2Temp;
    int16_t i16Rwl3TargetValue;
    float fRwl3MeasSpeed;
    int16_t i16Rwl3MeasCurrent;
    int16_t i16Rwl3Temp;
    bool bRwl0IsValid;
    bool bRwl0WheelMode;
    bool bRwl0CurentCtrlMode;
    bool bRwl0SpeedCtrlMode;
    bool bRwl0TorqueCtrlMode;
    bool bRwl0CrcError;
    bool bRwl0WrongLlCmd;
    bool bRwl0WrongHlCmd;
    bool bRwl0ToutSci1Main;
    bool bRwl1IsValid;
    bool bRwl1WheelMode;
    bool bRwl1CurentCtrlMode;
    bool bRwl1SpeedCtrlMode;
    bool bRwl1TorqueCtrlMode;
    bool bRwl1CrcError;
    bool bRwl1WrongLlCmd;
    bool bRwl1WrongHlCmd;
    bool bRwl1ToutSci1Main;
    bool bRwl2IsValid;
    bool bRwl2WheelMode;
    bool bRwl2CurentCtrlMode;
    bool bRwl2SpeedCtrlMode;
    bool bRwl2TorqueCtrlMode;
    bool bRwl2CrcError;
    bool bRwl2WrongLlCmd;
    bool bRwl2WrongHlCmd;
    bool bRwl2ToutSci1Main;
    bool bRwl3IsValid;
    bool bRwl3WheelMode;
    bool bRwl3CurentCtrlMode;
    bool bRwl3SpeedCtrlMode;
    bool bRwl3TorqueCtrlMode;
    bool bRwl3CrcError;
    bool bRwl3WrongLlCmd;
    bool bRwl3WrongHlCmd;
    bool bRwl3ToutSci1Main;
} PACKED_STRUCT DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_226_t;

/*
    CubeADCS Gen2 TLM_165 - Health telemetry for CubeStar
*/
typedef struct {
    double dStr0McuTemp;
    double dStr0McuCurrent;
    uint16_t u16Str0McuVoltage;
    double dStr0Current;
    double dStr0CurrentPk;
    double dStr0DetectorPcbTemp;
    bool bStr0SensorInitOk;
    bool bStr0SensorConfigOk;
    uint32_t u32Str0ErrorCode;
    double dStr1McuTemp;
    double dStr1McuCurrent;
    uint16_t u16Str1McuVoltage;
    double dStr1Current;
    double dStr1CurrentPk;
    double dStr1DetectorPcbTemp;
    bool bStr1SensorInitOk;
    bool bStr1SensorConfigOk;
    uint32_t u32Str1ErrorCode;
} PACKED_STRUCT DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_165_t;

/*
    CubeADCS Gen2 TLM_221 - Health telemetry for CubeStar
*/
typedef struct {
    uint8_t u8Mag0SensingElement;
    uint8_t u8Mag1SensingElement;
} PACKED_STRUCT DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_221_t;

typedef struct {
    uint8_t u8Sync;
    uint8_t au8Message[25];
    uint8_t au8Port[8];
    int32_t i32Sequence;
    float fIdle_time;
    uint32_t u32Time_status;
    uint32_t u32Week;
    float fSeconds;
    uint32_t u32Receiver_status;
    uint32_t u32Reserved;
    uint32_t u32Receiver_sw_version;
    uint8_t u8End1;
    uint32_t u32Clock_status;
    double dOffset;
    double dOffset_std;
    double dUtc_offset;
    uint32_t u32Utc_year;
    uint8_t u8Utc_month;
    uint8_t u8Utc_day;
    uint8_t u8Utc_hour;
    uint8_t u8Utc_min;
    uint32_t u32Utc_ms;
    uint32_t u32Utc_status;
    uint32_t u32Crc32;
    uint8_t au8End2[2];
} PACKED_STRUCT DATA_CACHE_GNSS_TIME_t;

typedef struct {
    uint8_t u8Sync;
    uint8_t au8Message[25];
    uint8_t au8Port[8];
    int32_t i32Sequence;
    float fIdle_time;
    uint32_t u32Time_status;
    uint32_t u32Week;
    float fSeconds;
    uint32_t u32Receiver_status;
    uint32_t u32Reserved1;
    uint32_t u32Receiver_sw_version;
    uint8_t u8End1;
    uint32_t u32P_sol_status;
    uint32_t u32Pos_type;
    double dPx;
    double dPy;
    double dPz;
    float fPxo;
    float fPyo;
    float fPzo;
    uint32_t u32V_sol_status;
    uint32_t u32Vel_type;
    double dVx;
    double dVy;
    double dVz;
    float fVxo;
    float fVyo;
    float fVzo;
    uint8_t au8Stn_id[4];
    float fV_latency;
    float fDiff_age;
    float fSol_age;
    uint8_t u8Svs;
    uint8_t u8Solnsvs;
    uint8_t u8Ggl1;
    uint8_t u8Solnmultisvs;
    uint8_t u8Reserved2;
    uint8_t u8Ext_sol_stat;
    uint8_t u8Galileo_and_beidou_sig_mask;
    uint8_t u8Gps_and_glonass_sig_mask;
    uint32_t u32Crc32;
    uint8_t au8End2[2];
} PACKED_STRUCT DATA_CACHE_GNSS_BESTXYZ_t;

/*
    Satellite state vector obtained from an onboard propagator
*/
typedef struct {
    double dPx;
    double dPy;
    double dPz;
    double dVx;
    double dVy;
    double dVz;
} PACKED_STRUCT DATA_CACHE_SAT_STATE_VECTOR_FROM_PROPAGATOR_t;

/*
    Modelled magnetic field on satellite in ECI reference frame
*/
typedef struct {
    double dMag_field_x;
    double dMag_field_y;
    double dMag_field_z;
} PACKED_STRUCT DATA_CACHE_SAT_MAG_FIELD_VECTOR_FROM_MODEL_t;

/*
    Measured magnetic field on satellite in Body Frame
*/
typedef struct {
    double dMag_field_x_current;
    double dMag_field_y_current;
    double dMag_field_z_current;
    double dMag_field_x_previous;
    double dMag_field_y_previous;
    double dMag_field_z_previous;
} PACKED_STRUCT DATA_CACHE_SAT_MAG_FIELD_VECTOR_FROM_SENSOR_t;

/*
    Input determening the thruster command execution status
*/
typedef struct {
    bool bError_occured;
} PACKED_STRUCT DATA_CACHE_FDIR_EPS_I_CMD_EXEC_STATUS_t;

/*
    Input determening the thruster command execution status
*/
typedef struct {
    uint8_t u8EPSII_PDM_1_GetPowerDistributionInfo_ErrorCode;
    uint8_t u8EPSII_PDM_1_GetDeviceHealthInfo_ErrorCode;
    uint8_t u8EPSII_PDM_1_GetRAWSensors_PDM1_ErrorCode;
    uint8_t u8EPSII_PDM_1_GetRAWSensors_PDM2_ErrorCode;
    uint8_t u8EPSII_PDM_1_GetBasicSettings_ErrorCode;
    uint8_t u8EPSII_PDM_1_SetBasicSettings_ErrorCode;
} PACKED_STRUCT DATA_CACHE_FDIR_EPS_II_PDM_CMD_EXEC_STATUS_t;

/*
    Input determening the thruster command execution status
*/
typedef struct {
    uint8_t u8Error_code;
} PACKED_STRUCT DATA_CACHE_FDIR_CUBEADCS_CMD_EXEC_STATUS_t;

/*
    Input determening the thruster command execution status
*/
typedef struct {
    bool bError_occured;
} PACKED_STRUCT DATA_CACHE_FDIR_CUBEADCS_GEN2_CMD_EXEC_STATUS_t;

/*
    The sum of all events that are in the FDIR agent logic for CubeADCS Gen2 (on OBC side)
*/
typedef struct {
    bool abNode_comm_error[7];
    bool abNode_failure[7];
    bool abNode_setup_error[7];
    bool abNode_discovery_error[7];
    bool abNode_port_validation_error[7];
    bool abGyro_voltage_error[2];
    bool abGyro_critical_error[2];
    bool bControl_loop_failure;
    bool bControl_loop_critical_error;
    bool bConfiguration_validation_error;
    bool bConfiguration_persist_error;
    bool bVirtual_watchdog_error;
} PACKED_STRUCT DATA_CACHE_FDIR_CUBEADCS_GEN2_EVENTS_t;

/*
    Input determening the S-Band telemetry/telecontrol execution status
*/
typedef struct {
    uint8_t u8Error_code;
} PACKED_STRUCT DATA_CACHE_FDIR_S_BAND_TMTC_CMD_EXEC_STATUS_t;

/*
    Input determening the UHF command execution status
*/
typedef struct {
    bool bError_occured;
} PACKED_STRUCT DATA_CACHE_FDIR_UHF_CMD_EXEC_STATUS_t;

/*
    Input determening the GNSS command execution status
*/
typedef struct {
    bool bError_occured;
} PACKED_STRUCT DATA_CACHE_FDIR_GNSS_CMD_EXEC_STATUS_t;

/*
    Input determening the SDR command execution status
*/
typedef struct {
    bool bError_occured;
} PACKED_STRUCT DATA_CACHE_FDIR_SDR_CMD_EXEC_STATUS_t;

/*
    Input determening the S/X-Band command execution status
*/
typedef struct {
    uint16_t u16Error_code;
} PACKED_STRUCT DATA_CACHE_FDIR_S_X_BAND_CMD_EXEC_STATUS_t;

/*
    Input determening the thruster command execution status
*/
typedef struct {
    bool bError_occured;
} PACKED_STRUCT DATA_CACHE_FDIR_THRUSTER_CMD_EXEC_STATUS_t;

/*
    Describes the telemetry captured from the XBand FE module
*/
typedef struct {
    uint8_t u8System_state;
    uint8_t u8Status_flags;
    int16_t i16Pa_temperature;
    int16_t i16Pa_pwr_det;
    uint16_t u16Powsup_5v_rf_drv;
    uint16_t u16Pa_idd;
    uint16_t u16Pa_vdd;
    uint16_t u16Powsup_5v_vco_drv;
    uint16_t u16Powsup_3v3_pll;
    uint16_t u16Powsup_5v_if_amp;
    uint16_t u16Powsup_5v_att;
    int16_t i16Pa_vgg;
    uint16_t u16Cpu_vdd;
    int16_t i16Cpu_temperature;
    uint16_t u16Adc_vref_internal;
} PACKED_STRUCT DATA_CACHE_XBandFeTelemetry_t;

/*
    GetBatteryInfo from EPSII_BP_1 interface
*/
typedef struct {
    uint32_t u32Capacity;
    uint16_t u16Voltage;
} PACKED_STRUCT DATA_CACHE_EpsOverallBatteryInfoType_t;

/*
    PPS driver telemetry
*/
typedef struct {
    uint32_t u32Pps_detect_cnt;
    uint32_t u32Last_pps_uptime;
    uint8_t u8Current_drv_status;
    uint8_t u8Latest_rtc_sync_status;
    uint32_t u32Rtc_sync_success_cnt;
    uint32_t u32Rtc_sync_fail_cnt;
    uint32_t u32Pps_timeout_cnt;
} PACKED_STRUCT DATA_CACHE_PPS_Telemetry_t;

/*
    Input determening the thruster command execution status
*/
typedef struct {
    uint8_t u8Eps_iii_pdm_a_get_telemetry_ErrorCode;
} PACKED_STRUCT DATA_CACHE_FDIR_EPS_III_PDM_CMD_EXEC_STATUS_t;

/*
    GetBatteryInfo from EPSII_BP_1 interface
*/
typedef struct {
    uint32_t u32Capacity;
    uint16_t u16Voltage;
    int16_t i16Current;
    int32_t i32Temperature;
    uint8_t u8Bp_mode;
} PACKED_STRUCT DATA_CACHE_Eps2Inst0BatteryInfoType_t;

/*
    GetDeviceHealthInfo from EPSII_BP_1 interface
*/
typedef struct {
    int32_t i32ActiveCPU_RunningTime;
    int32_t i32ActiveCPU_Voltage;
    int32_t i32ActiveCPU_Temperature;
    int32_t i32PCB_Temperature_1;
    int32_t i32PCB_Temperature_2;
    uint8_t u8BALANCER_CHIP_1;
    uint8_t u8LT8491_IC_XP;
    uint8_t u8LT8491_IC_XR;
    uint8_t u8LT8491_IC_YP;
    uint8_t u8LT8491_IC_YR;
    uint8_t u8LT8491_IC_ZP;
    uint8_t u8LT8491_IC_ZR;
    uint8_t u8INA_BAT_OUT_1;
    uint8_t u8INA_BAT_OUT_2;
    uint8_t u8TMP117_U810;
    uint8_t u8TMP117_U811;
    uint8_t u8GPIO_PCA9538_U2001;
    uint8_t u8GPIO_PCA9538_U2002;
} PACKED_STRUCT DATA_CACHE_Eps2Inst0DeviceHealthInfoType_t;

/*
    Information provided by INA sensor 1
*/
typedef struct {
    uint16_t u16Voltage;
    int16_t i16Current;
    int16_t i16Energy;
    int16_t i16Temperature;
} PACKED_STRUCT DATA_CACHE_Eps2Inst0InaSensors1Type_t;

/*
    Information provided by INA sensor 2
*/
typedef struct {
    uint16_t u16Voltage;
    int16_t i16Current;
    int16_t i16Energy;
    int16_t i16Temperature;
} PACKED_STRUCT DATA_CACHE_Eps2Inst0InaSensors2Type_t;

/*
    Telemetry provided by the Balancer
*/
typedef struct {
    uint16_t u16Voltage;
    int16_t i16Current;
    int16_t i16Internal_Temperature;
} PACKED_STRUCT DATA_CACHE_Eps2Inst0BalancerInfoType_t;

/*
    Status provided by the Balancer
*/
typedef struct {
    uint8_t u8COM_STATE;
    uint8_t u8Status_register_0;
    uint8_t u8Status_register_1;
    uint8_t u8Status_register_2;
    uint8_t u8Status_register_3;
} PACKED_STRUCT DATA_CACHE_Eps2Inst0BalancerStatusType_t;

/*
    Balancer Cells info
*/
typedef struct {
    uint16_t u16Cell_1;
    uint16_t u16Cell_2;
    uint16_t u16Cell_3;
    uint16_t u16Cell_4;
    uint16_t u16Cell_5;
    uint16_t u16Cell_6;
    uint16_t u16Cell_7;
    uint16_t u16Cell_8;
} PACKED_STRUCT DATA_CACHE_Eps2Inst0BalancerCellsInfoType_t;

/*
    Charger info
*/
typedef struct {
    uint8_t u8COM_STATE;
    uint16_t u16STAT_SUPPLY;
    uint16_t u16TELE_POUT;
    uint16_t u16TELE_PIN;
    uint16_t u16TELE_IOUT;
    uint16_t u16TELE_IIN;
    uint16_t u16TELE_VBAT;
    uint16_t u16TELE_VINR;
} PACKED_STRUCT DATA_CACHE_Eps2Inst0ChargerXpType_t;

/*
    Charger info
*/
typedef struct {
    uint8_t u8COM_STATE;
    uint16_t u16STAT_SUPPLY;
    uint16_t u16TELE_POUT;
    uint16_t u16TELE_PIN;
    uint16_t u16TELE_IOUT;
    uint16_t u16TELE_IIN;
    uint16_t u16TELE_VBAT;
    uint16_t u16TELE_VINR;
} PACKED_STRUCT DATA_CACHE_Eps2Inst0ChargerXrType_t;

/*
    Charger info
*/
typedef struct {
    uint8_t u8COM_STATE;
    uint16_t u16STAT_SUPPLY;
    uint16_t u16TELE_POUT;
    uint16_t u16TELE_PIN;
    uint16_t u16TELE_IOUT;
    uint16_t u16TELE_IIN;
    uint16_t u16TELE_VBAT;
    uint16_t u16TELE_VINR;
} PACKED_STRUCT DATA_CACHE_Eps2Inst0ChargerYpType_t;

/*
    Charger info
*/
typedef struct {
    uint8_t u8COM_STATE;
    uint16_t u16STAT_SUPPLY;
    uint16_t u16TELE_POUT;
    uint16_t u16TELE_PIN;
    uint16_t u16TELE_IOUT;
    uint16_t u16TELE_IIN;
    uint16_t u16TELE_VBAT;
    uint16_t u16TELE_VINR;
} PACKED_STRUCT DATA_CACHE_Eps2Inst0ChargerYrType_t;

/*
    Charger info
*/
typedef struct {
    uint8_t u8COM_STATE;
    uint16_t u16STAT_SUPPLY;
    uint16_t u16TELE_POUT;
    uint16_t u16TELE_PIN;
    uint16_t u16TELE_IOUT;
    uint16_t u16TELE_IIN;
    uint16_t u16TELE_VBAT;
    uint16_t u16TELE_VINR;
} PACKED_STRUCT DATA_CACHE_Eps2Inst0ChargerZpType_t;

/*
    Charger info
*/
typedef struct {
    uint8_t u8COM_STATE;
    uint16_t u16STAT_SUPPLY;
    uint16_t u16TELE_POUT;
    uint16_t u16TELE_PIN;
    uint16_t u16TELE_IOUT;
    uint16_t u16TELE_IIN;
    uint16_t u16TELE_VBAT;
    uint16_t u16TELE_VINR;
} PACKED_STRUCT DATA_CACHE_Eps2Inst0ChargerZrType_t;

/*
    Input determening the thruster command execution status
*/
typedef struct {
    uint8_t u8EPSII_BP_1_GetBatteryInfo_ErrorCode;
    uint8_t u8EPSII_BP_1_GetDeviceHealthInfo_ErrorCode;
    uint8_t u8EPSII_BP_1_GetRAWSensors_1_ErrorCode;
    uint8_t u8EPSII_BP_1_GetRAWSensors_2_ErrorCode;
    uint8_t u8EPSII_BP_1_GetRAWSensors_3_ErrorCode;
} PACKED_STRUCT DATA_CACHE_Eps2Inst0_FDIR_CMD_EXEC_STATUS_type_t;

/*
    Number of seconds since last power up
*/
typedef struct {
    uint32_t u32Seconds;
} PACKED_STRUCT DATA_CACHE_Eps3Inst0_UpTimeInSecondsType_t;

/*
    Common measurements
*/
typedef struct {
    uint16_t u16Mcu_volt;
    int32_t i32Mcu_temp;
    uint16_t u16Sys_bus_volt;
} PACKED_STRUCT DATA_CACHE_Eps3Inst0CommonMeasurementType_t;

/*
    all states concerning the algorithms of HIB mode
*/
typedef struct {
    uint8_t u8Hib_mode_en;
    uint8_t u8Battery_dead;
    uint8_t u8Battery_low;
    uint8_t u8Battery_temp_low;
} PACKED_STRUCT DATA_CACHE_Eps3Inst0HIBModeStatusType_t;

/*
    Exact measured values like voltages, currents, temperatures
*/
typedef struct {
    uint16_t u16V_batt;
    int16_t i16I_batt;
    uint8_t u8Soc_batt;
    uint16_t u16V_batt_cell_1;
    uint16_t u16V_batt_cell_2;
    uint16_t u16V_batt_cell_3;
    uint16_t u16V_batt_cell_4;
    int32_t i32T_batt;
    int32_t i32P_heater_1;
    int32_t i32P_heater_2;
    uint16_t u16V_buss_7_5V;
    uint16_t u16V_buss_3_3V;
} PACKED_STRUCT DATA_CACHE_Eps3Inst0MeasurementsType_t;

/*
    all states concerning the discharging algorithms
*/
typedef struct {
    uint8_t u8Discharge;
    uint8_t u8Battery_low;
    uint8_t u8Battery_dead;
    uint8_t u8Battery_ocp_charge;
    uint8_t u8Battery_ocp_discharge;
    uint8_t u8Discharge_switch_over_heat_prot;
    int32_t i32Discharge_switch_over_heat_temp;
    uint8_t u8Battery_overheat;
    int32_t i32T_batt;
    uint8_t u8V_buss_7_5v_error_flag;
    uint8_t u8Charge_mode_en;
    uint8_t u8Charging_current_flow;
    uint8_t u8Charging_voltage_ok;
} PACKED_STRUCT DATA_CACHE_Eps3Inst0DischargeStateType_t;

/*
    all states concerning the charging algorithms
*/
typedef struct {
    uint8_t u8Battery_charging_on;
    uint8_t u8Charging_voltage_ok;
    uint8_t u8Battery_dead;
    uint8_t u8Battery_over_voltage_prot;
    uint8_t u8Battery_slow_charging;
    uint8_t u8Charging_current_flow;
    uint16_t u16Charge_current;
    uint8_t u8Valid_input_voltage;
} PACKED_STRUCT DATA_CACHE_Eps3Inst0ChargeOnStatusType_t;

/*
    all states concerning the balancers
*/
typedef struct {
    uint8_t u8Balancer_on;
    uint8_t u8Balancer_voltage_ok;
    uint8_t u8Charging_current_flow;
} PACKED_STRUCT DATA_CACHE_Eps3Inst0BalancersStatusType_t;

/*
    all states concerning the battery cells
*/
typedef struct {
    uint8_t u8Balance_cell_1_en;
    uint8_t u8Balance_cell_2_en;
    uint8_t u8Balance_cell_3_en;
    uint8_t u8Balance_cell_4_en;
} PACKED_STRUCT DATA_CACHE_Eps3Inst0BatteryCellsStatusType_t;

/*
    all states concerning the heaters
*/
typedef struct {
    uint8_t u8Heater_en;
    uint8_t u8Heater_under_5_deg_c;
    uint8_t u8Battery_dead;
    uint8_t u8Battery_alert;
} PACKED_STRUCT DATA_CACHE_Eps3Inst0HeatersStatusType_t;

/*
    Input determening the thruster command execution status
*/
typedef struct {
    uint8_t u8Eps_iii_batt_pack_get_telemetry_ErrorCode;
} PACKED_STRUCT DATA_CACHE_Eps3Inst0_FDIR_CMD_EXEC_STATUS_type_t;

/*
    Voltage and Current measurements
*/
typedef struct {
    uint16_t u16Voltage;
    int16_t i16Current;
} PACKED_STRUCT DATA_CACHE_VoltAmps_t;

/*
    Voltage and Current measurements
*/
typedef struct {
    uint16_t u16Ch_voltage;
    int16_t i16In_current;
    int16_t i16Out_current;
} PACKED_STRUCT DATA_CACHE_VoltAllAmps_t;

/*
    state of the mppt
*/
typedef struct {
    uint16_t u16Status;
    uint16_t u16Faults;
    uint16_t u16Mode;
} PACKED_STRUCT DATA_CACHE_MpptState_str_t;

/*
    Read status
*/
typedef struct {
    uint8_t u8Status;
} PACKED_STRUCT DATA_CACHE_ReadEnDftStatus_t;

/*
    Current status of the channel. OFF, ON or unknown
*/
typedef struct {
    uint8_t u8Status;
} PACKED_STRUCT DATA_CACHE_OnOffStatus_t;

typedef struct {
    uint8_t u8Status;
} PACKED_STRUCT DATA_CACHE_ReadLvlState_t;

/*
    Number of seconds since last power up
*/
typedef struct {
    uint32_t u32Seconds;
} PACKED_STRUCT DATA_CACHE_Eps3_PDM_A_Inst0_UpTimeInSecondsType_t;

/*
    Common measurements
*/
typedef struct {
    uint16_t u16Mcu_volt;
    int32_t i32Mcu_temp;
    uint16_t u16Sys_bus_volt;
} PACKED_STRUCT DATA_CACHE_Eps3_PDM_A_Inst0_CommonMesurementsType_t;

/*
    HIB mode status
*/
typedef struct {
    DATA_CACHE_OnOffStatus_t sStatus;
} PACKED_STRUCT DATA_CACHE_Eps3_PDM_A_Inst0_HibModeType_t;

/*
    Outputs status for 3.3V 5V 12V and external system bus channels
*/
typedef struct {
    DATA_CACHE_ReadEnDftStatus_t sEn_ext_sys_bus;
    DATA_CACHE_ReadEnDftStatus_t sEn_3v3_bus_in;
    DATA_CACHE_ReadEnDftStatus_t sEn_3v3_bus_out;
    DATA_CACHE_ReadEnDftStatus_t sEn_5v_bus_in;
    DATA_CACHE_ReadEnDftStatus_t sEn_5v_bus_out;
    DATA_CACHE_ReadEnDftStatus_t sEn_12v_bus_in;
    DATA_CACHE_ReadEnDftStatus_t sEn_12v_bus_out;
} PACKED_STRUCT DATA_CACHE_Eps3_PDM_A_Inst0_OutputsStatusType_t;

/*
    All IN and OUT Faults status
*/
typedef struct {
    DATA_CACHE_OnOffStatus_t sFlt_ext_sys_bus;
    DATA_CACHE_OnOffStatus_t sFlt_in_3v3_bus;
    DATA_CACHE_OnOffStatus_t sFlt_out_3v3_bus;
    DATA_CACHE_OnOffStatus_t sFlt_in_5v_bus;
    DATA_CACHE_OnOffStatus_t sFlt_out_5v_bus;
    DATA_CACHE_OnOffStatus_t sFlt_in_12v_bus;
    DATA_CACHE_OnOffStatus_t sFlt_out_12v_bus;
} PACKED_STRUCT DATA_CACHE_Eps3_PDM_A_Inst0_FaultsStatusType_t;

/*
    Voltage and Current measurements
*/
typedef struct {
    DATA_CACHE_VoltAmps_t sSystem_bus;
    DATA_CACHE_VoltAmps_t sExt_sys_bus;
    DATA_CACHE_VoltAllAmps_t sBus_3v3;
    DATA_CACHE_VoltAllAmps_t sBus_5v;
    DATA_CACHE_VoltAllAmps_t sBus_12v;
} PACKED_STRUCT DATA_CACHE_Eps3_PDM_A_Inst0_VoltAmpsMeasurementsType_t;

/*
    Input determining the thruster command execution status
*/
typedef struct {
    uint8_t u8Eps_iii_pdm_a_get_telemetry_ErrorCode;
    uint8_t u8Eps_iii_pdm_a_low_volt_control_ErrorCode;
    uint8_t u8Eps_iii_pdm_a_external_system_bus_control_ErrorCode;
} PACKED_STRUCT DATA_CACHE_Eps3_PDM_A_Inst0_FDIR_CMD_EXEC_STATUS_type_t;

/*
    Input determining the thruster command execution status
*/
typedef struct {
    uint8_t u8Eps_iii_pdm_b_get_telemetry_ErrorCode;
    uint8_t u8Eps_iii_pdm_b_a_b_control_ErrorCode;
} PACKED_STRUCT DATA_CACHE_Eps3_PDM_B_Inst0_FDIR_CMD_EXEC_STATUS_type_t;

/*
    Number of seconds since last power up
*/
typedef struct {
    uint32_t u32Seconds;
} PACKED_STRUCT DATA_CACHE_Eps3_PDM_B_Inst0_UpTimeInSecondsType_t;

/*
    Common measurements
*/
typedef struct {
    uint16_t u16Mcu_volt;
    int32_t i32Mcu_temp;
    uint16_t u16Sys_bus_volt;
} PACKED_STRUCT DATA_CACHE_Eps3_PDM_B_Inst0_CommonMeasurementType_t;

/*
    HibMode status type
*/
typedef struct {
    DATA_CACHE_OnOffStatus_t sStatus;
} PACKED_STRUCT DATA_CACHE_Eps3_PDM_B_Inst0_hib_mode_Type_t;

/*
    Status of A and B Outputs
*/
typedef struct {
    DATA_CACHE_ReadEnDftStatus_t sEn_a_in_bus;
    DATA_CACHE_ReadEnDftStatus_t sEn_a_out_bus;
    DATA_CACHE_ReadEnDftStatus_t sEn_b_in_bus;
    DATA_CACHE_ReadEnDftStatus_t sEn_b_out_bus;
} PACKED_STRUCT DATA_CACHE_Eps3_PDM_B_Inst0_OutputsStatus_type_t;

/*
    All Input and Output channel flag state
*/
typedef struct {
    DATA_CACHE_OnOffStatus_t sA_input_current_state;
    DATA_CACHE_OnOffStatus_t sA_output_current_state;
    DATA_CACHE_OnOffStatus_t sA_input_voltage_state;
    DATA_CACHE_OnOffStatus_t sA_output_voltage_state;
    DATA_CACHE_OnOffStatus_t sB_input_current_state;
    DATA_CACHE_OnOffStatus_t sB_output_current_state;
    DATA_CACHE_OnOffStatus_t sB_input_voltage_state;
    DATA_CACHE_OnOffStatus_t sB_output_voltage_state;
} PACKED_STRUCT DATA_CACHE_Eps3_PDM_B_Inst0_ChannelFlagState_type_t;

/*
    Temperature data
*/
typedef struct {
    int32_t i32Temp_bus_a;
    int32_t i32Temp_bus_b;
} PACKED_STRUCT DATA_CACHE_Eps3_PDM_B_Inst0_Temps_type_t;

/*
    Voltage and Current measurements
*/
typedef struct {
    DATA_CACHE_VoltAmps_t sSystem_bus;
    DATA_CACHE_VoltAllAmps_t sBus_a;
    DATA_CACHE_VoltAllAmps_t sBus_b;
} PACKED_STRUCT DATA_CACHE_Eps3_PDM_B_Inst0_VoltAmpsMeasurements_type_t;

/*
    Input determining the thruster command execution status
*/
typedef struct {
    uint8_t u8Eps_iii_expander_get_telemetry_ErrorCode;
    uint8_t u8Eps_iii_expander_h1_channels_control_ErrorCode;
    uint8_t u8Eps_iii_expander_gpio_control_ErrorCode;
    uint8_t u8Eps_iii_expander_interconnect_control_ErrorCode;
    uint8_t u8Eps_iii_expander_release_control_ErrorCode;
    uint8_t u8Eps_iii_expander_release_5v_ErrorCode;
} PACKED_STRUCT DATA_CACHE_Eps3_EXPANDER_Inst0_FDIR_CMD_EXEC_STATUS_type_t;

/*
    Number of seconds since last power up
*/
typedef struct {
    uint32_t u32Seconds;
} PACKED_STRUCT DATA_CACHE_Eps3_EXPANDER_Inst0_UpTimeInSecondsType_t;

/*
    Common measurements
*/
typedef struct {
    uint16_t u16Mcu_volt;
    int32_t i32Mcu_temp;
    uint16_t u16Sys_bus_volt;
} PACKED_STRUCT DATA_CACHE_Eps3_EXPANDER_Inst0_CommonMeasurementType_t;

/*
    The status of All Feedback channels
*/
typedef struct {
    DATA_CACHE_ReadEnDftStatus_t sLv_h1_47_48;
    DATA_CACHE_ReadEnDftStatus_t sHv_h1_47_48;
    DATA_CACHE_ReadEnDftStatus_t sLv_h1_49_50;
    DATA_CACHE_ReadEnDftStatus_t sHv_h1_49_50;
    DATA_CACHE_ReadEnDftStatus_t sLv_h1_51_52;
    DATA_CACHE_ReadEnDftStatus_t sHv_h1_51_52;
    DATA_CACHE_ReadEnDftStatus_t sInterconnect_battery;
    DATA_CACHE_ReadEnDftStatus_t sInterconnect_3v3;
    DATA_CACHE_ReadEnDftStatus_t sInterconnect_5v;
    DATA_CACHE_ReadEnDftStatus_t sInterconnect_12v;
    DATA_CACHE_ReadEnDftStatus_t sGeneral_output_1;
    DATA_CACHE_ReadEnDftStatus_t sGeneral_output_2;
    DATA_CACHE_ReadEnDftStatus_t sGeneral_output_3;
    DATA_CACHE_ReadEnDftStatus_t sGeneral_output_4;
    DATA_CACHE_ReadEnDftStatus_t sGeneral_output_5;
    DATA_CACHE_ReadEnDftStatus_t sGeneral_output_6;
    DATA_CACHE_ReadEnDftStatus_t sGeneral_output_7;
    DATA_CACHE_ReadEnDftStatus_t sGeneral_output_8;
    DATA_CACHE_ReadEnDftStatus_t sRelease_1;
    DATA_CACHE_ReadEnDftStatus_t sRelease_2;
    DATA_CACHE_ReadEnDftStatus_t sRelease_3;
    DATA_CACHE_ReadEnDftStatus_t sRelease_4;
    DATA_CACHE_ReadEnDftStatus_t sRelease_a1;
    DATA_CACHE_ReadEnDftStatus_t sRelease_b1;
    DATA_CACHE_ReadEnDftStatus_t sRelease_a2;
    DATA_CACHE_ReadEnDftStatus_t sRelease_b2;
    DATA_CACHE_ReadEnDftStatus_t sRelease_a3;
    DATA_CACHE_ReadEnDftStatus_t sRelease_b3;
    DATA_CACHE_ReadEnDftStatus_t sRelease_a4;
    DATA_CACHE_ReadEnDftStatus_t sRelease_b4;
} PACKED_STRUCT DATA_CACHE_Eps3_EXPANDER_Inst0_DigitalOutputsType_t;

/*
    The level state of all General inputs
*/
typedef struct {
    DATA_CACHE_ReadLvlState_t sGeneral_input_1;
    DATA_CACHE_ReadLvlState_t sGeneral_input_2;
    DATA_CACHE_ReadLvlState_t sGeneral_input_3;
    DATA_CACHE_ReadLvlState_t sGeneral_input_4;
    DATA_CACHE_ReadLvlState_t sGeneral_input_5;
    DATA_CACHE_ReadLvlState_t sGeneral_input_6;
    DATA_CACHE_ReadLvlState_t sGeneral_input_7;
    DATA_CACHE_ReadLvlState_t sGeneral_input_8;
} PACKED_STRUCT DATA_CACHE_Eps3_EXPANDER_Inst0_GeneralInputType_t;

/*
    The level state of all Feedbacks
*/
typedef struct {
    DATA_CACHE_ReadLvlState_t sFeedback_1_1;
    DATA_CACHE_ReadLvlState_t sFeedback_1_2;
    DATA_CACHE_ReadLvlState_t sFeedback_2_1;
    DATA_CACHE_ReadLvlState_t sFeedback_2_2;
    DATA_CACHE_ReadLvlState_t sFeedback_3_1;
    DATA_CACHE_ReadLvlState_t sFeedback_3_2;
    DATA_CACHE_ReadLvlState_t sFeedback_4_1;
    DATA_CACHE_ReadLvlState_t sFeedback_4_2;
} PACKED_STRUCT DATA_CACHE_Eps3_EXPANDER_Inst0_FeedbackType_t;

/*
    Voltage and Current measurements
*/
typedef struct {
    DATA_CACHE_VoltAmps_t sH_h1_47_48;
    DATA_CACHE_VoltAmps_t sL_h1_47_48;
    DATA_CACHE_VoltAmps_t sH_h1_49_50;
    DATA_CACHE_VoltAmps_t sL_h1_49_50;
    DATA_CACHE_VoltAmps_t sH_h1_51_52;
    DATA_CACHE_VoltAmps_t sL_h1_51_52;
    DATA_CACHE_VoltAmps_t sRelease1;
    DATA_CACHE_VoltAmps_t sRelease2;
    DATA_CACHE_VoltAmps_t sRelease3;
    DATA_CACHE_VoltAmps_t sRelease4;
    DATA_CACHE_VoltAmps_t sInterc_3v3;
    DATA_CACHE_VoltAmps_t sInterc_5v;
    DATA_CACHE_VoltAmps_t sInterc_12v;
    DATA_CACHE_VoltAmps_t sInterc_battery;
} PACKED_STRUCT DATA_CACHE_Eps3_EXPANDER_Inst0_CurrentLimitersType_t;

/*
    Number of seconds since last power up
*/
typedef struct {
    uint32_t u32Seconds;
} PACKED_STRUCT DATA_CACHE_Eps3_INPUT_STAGE_Inst0_UpTimeInSecondsType_t;

/*
    Common measurements
*/
typedef struct {
    uint16_t u16Mcu_volt;
    int32_t i32Mcu_temp;
    uint16_t u16Sys_bus_volt;
} PACKED_STRUCT DATA_CACHE_Eps3_INPUT_STAGE_Inst0CommonMeasurementType_t;

/*
    Current status of the channel. OFF, ON or unknown
*/
typedef struct {
    uint8_t u8Status;
} PACKED_STRUCT DATA_CACHE_Eps3_INPUT_STAGE_Inst0hib_mode_status_type_t;

/*
    Current status of the channel. OFF, ON or unknown
*/
typedef struct {
    uint8_t u8Status;
} PACKED_STRUCT DATA_CACHE_Eps3_INPUT_STAGE_Inst0selflock_on_type_t;

/*
    Solar panel (SP1) input data
*/
typedef struct {
    DATA_CACHE_VoltAllAmps_t sSp_measurements;
    uint8_t u8Input_current_state;
    uint8_t u8Output_current_state;
    uint8_t u8Input_voltage_state;
    uint8_t u8Output_voltage_state;
    DATA_CACHE_MpptState_str_t sState_mppt;
} PACKED_STRUCT DATA_CACHE_Eps3_INPUT_STAGE_Inst0Sp1InputDataType_t;

/*
    Solar panel (SP2) input data
*/
typedef struct {
    DATA_CACHE_VoltAllAmps_t sSp_measurements;
    uint8_t u8Input_current_state;
    uint8_t u8Output_current_state;
    uint8_t u8Input_voltage_state;
    uint8_t u8Output_voltage_state;
    DATA_CACHE_MpptState_str_t sState_mppt;
} PACKED_STRUCT DATA_CACHE_Eps3_INPUT_STAGE_Inst0Sp2InputDataType_t;

/*
    Solar panel (SP3) input data
*/
typedef struct {
    DATA_CACHE_VoltAllAmps_t sSp_measurements;
    uint8_t u8Input_current_state;
    uint8_t u8Output_current_state;
    uint8_t u8Input_voltage_state;
    uint8_t u8Output_voltage_state;
    DATA_CACHE_MpptState_str_t sState_mppt;
} PACKED_STRUCT DATA_CACHE_Eps3_INPUT_STAGE_Inst0Sp3InputDataType_t;

/*
    Voltage and Current measurements
*/
typedef struct {
    uint16_t u16Voltage;
    int16_t i16Current;
} PACKED_STRUCT DATA_CACHE_Eps3_INPUT_STAGE_Inst0SystemBusType_t;

/*
    Voltage and Current measurements
*/
typedef struct {
    uint16_t u16Voltage;
    int16_t i16Current;
} PACKED_STRUCT DATA_CACHE_Eps3_INPUT_STAGE_Inst0Bus7v5Type_t;

/*
    Current status of the channel. OFF, ON or unknown
*/
typedef struct {
    uint8_t u8Status;
} PACKED_STRUCT DATA_CACHE_Eps3_INPUT_STAGE_Inst0bus_7v5_power_good_type_t;

/*
    Current status of the channel. OFF, ON or unknown
*/
typedef struct {
    uint8_t u8Status;
} PACKED_STRUCT DATA_CACHE_Eps3_INPUT_STAGE_Inst0undervoltage_7V5_type_t;

/*
    Voltage and Current measurements
*/
typedef struct {
    uint16_t u16Voltage;
    int16_t i16Current;
} PACKED_STRUCT DATA_CACHE_Eps3_INPUT_STAGE_Inst0Bbus3v3Type_t;

/*
    Current status of the channel. OFF, ON or unknown
*/
typedef struct {
    uint8_t u8Status;
} PACKED_STRUCT DATA_CACHE_Eps3_INPUT_STAGE_Inst0undervoltage_3V3_type_t;

/*
    Command execution statuses
*/
typedef struct {
    uint8_t u8Eps_iii_pdm_a_get_telemetry_ErrorCode;
} PACKED_STRUCT DATA_CACHE_Eps3_INPUT_STAGE_Inst0_FDIR_CMD_EXEC_STATUS_type_t;

/*
    Magnetometer
*/
typedef struct {
    float fX_axis;
    float fY_axis;
    float fZ_axis;
    bool bDataValid;
    float fX_axis_red;
    float fY_axis_red;
    float fZ_axis_red;
    bool bDataValid_red;
    uint32_t u32BurnCurrent;
    bool bDeploymentPinState;
    bool bBurnPinState;
    bool bBurnUnderCurrent;
    bool bBurnOverCurrent;
    bool bDeploymentTimeout;
    uint8_t u8MagSvcState;
    uint8_t u8PrimaryMagState;
    uint8_t u8RedundantMagState;
} PACKED_STRUCT DATA_CACHE_CubeMag_Telemetry_t;

/*
    Reaction Wheel 1
*/
typedef struct {
    float fWheelSpeed_1;
    uint8_t u8WheelErrorState_1;
    float fReferenceSpeed_1;
    bool bMotorPowerSwitch_1;
} PACKED_STRUCT DATA_CACHE_CubeWheel1_Telemetry_t;

/*
    Reaction Wheel 2
*/
typedef struct {
    float fWheelSpeed_2;
    uint8_t u8WheelErrorState_2;
    float fReferenceSpeed_2;
    bool bMotorPowerSwitch_2;
} PACKED_STRUCT DATA_CACHE_CubeWheel2_Telemetry_t;

typedef struct {
    float fAlpha;
    float fBeta;
    uint8_t u8Sampling_mode;
} PACKED_STRUCT DATA_CACHE_FSS1_Data_type_t;

typedef struct {
    float fAlpha;
    float fBeta;
    uint8_t u8Sampling_mode;
} PACKED_STRUCT DATA_CACHE_FSS2_Data_type_t;

typedef struct {
    float fAlpha;
    float fBeta;
    uint8_t u8Sampling_mode;
} PACKED_STRUCT DATA_CACHE_FSS3_Data_type_t;

typedef struct {
    float fAlpha;
    float fBeta;
    uint8_t u8Sampling_mode;
} PACKED_STRUCT DATA_CACHE_FSS4_Data_type_t;

typedef struct {
    float fAlpha;
    float fBeta;
    uint8_t u8Sampling_mode;
} PACKED_STRUCT DATA_CACHE_FSS5_Data_type_t;

typedef struct {
    float afFSS1[2];
    float afFSS2[2];
    float afFSS3[2];
    float afFSS4[2];
    float afFSS5[2];
} PACKED_STRUCT DATA_CACHE_ADCS_FSS_t;

typedef struct {
    float afMAG_pri_fieldVec[3];
} PACKED_STRUCT DATA_CACHE_ADCS_MAG_t;

typedef struct {
    float afIMU_angRate[3];
} PACKED_STRUCT DATA_CACHE_ADCS_IMU_t;

typedef struct {
    float afRW_speed[2];
} PACKED_STRUCT DATA_CACHE_ADCS_RW_t;

typedef struct {
    float afMTQ_command[3];
} PACKED_STRUCT DATA_CACHE_ADCS_MTQ_t;

typedef struct {
    uint32_t u32Time_stamp;
    uint8_t u8ETarget_mode;
} PACKED_STRUCT DATA_CACHE_SBpModeChangeInfo_t;

typedef struct {
    uint8_t u8Current_index;
    DATA_CACHE_SBpModeChangeInfo_t asChange_info[7];
} PACKED_STRUCT DATA_CACHE_Eps2Inst0_BpModeSmRollingTrace_type_t;

typedef struct {
    uint8_t u8EPSII_PDM_SBSEDE_ConopsMode;
} PACKED_STRUCT DATA_CACHE_EPSII_PDM_SBSEDE_ConopsMode_t;

typedef struct {
    uint8_t u8EPSII_PDM_1_SBSED_Bitmask_t;
} PACKED_STRUCT DATA_CACHE_EPSII_PDM_1_SBSED_Bitmask_t_t;

typedef struct {
    DATA_CACHE_EPSII_PDM_SBSEDE_ConopsMode_t sENConOpsStartMode;
    DATA_CACHE_EPSII_PDM_1_SBSED_Bitmask_t_t sENBBUS_RAWOutputEnable;
    int32_t i32I32N12V_Voltage;
    int32_t i32I32N12V_CurrentLimit;
    DATA_CACHE_EPSII_PDM_1_SBSED_Bitmask_t_t sEN12V_MasterEnable;
    DATA_CACHE_EPSII_PDM_1_SBSED_Bitmask_t_t sEN12V_SP1_3_Enable;
    DATA_CACHE_EPSII_PDM_1_SBSED_Bitmask_t_t sEN12V_SP1_4_Enable;
    DATA_CACHE_EPSII_PDM_1_SBSED_Bitmask_t_t sEN12V_SP1_5_Enable;
    int32_t i32I32N5V_Ch1_CurrentLimit;
    DATA_CACHE_EPSII_PDM_1_SBSED_Bitmask_t_t sEN5V_Ch1_MasterEnable;
    DATA_CACHE_EPSII_PDM_1_SBSED_Bitmask_t_t sEN5V_Ch1_SP2_3_Enable;
    DATA_CACHE_EPSII_PDM_1_SBSED_Bitmask_t_t sEN5V_Ch1_SP2_4_Enable;
    int32_t i32I32N5V_Ch2_CurrentLimit;
    DATA_CACHE_EPSII_PDM_1_SBSED_Bitmask_t_t sEN5V_Ch2_MasterEnable;
    DATA_CACHE_EPSII_PDM_1_SBSED_Bitmask_t_t sEN5V_Ch2_SP1_6_Enable;
    DATA_CACHE_EPSII_PDM_1_SBSED_Bitmask_t_t sEN5V_Ch2_SP1_7_Enable;
    int32_t i32I32N3V3_Ch1_CurrentLimit;
    DATA_CACHE_EPSII_PDM_1_SBSED_Bitmask_t_t sEN3V3_Ch1_MasterEnable;
    DATA_CACHE_EPSII_PDM_1_SBSED_Bitmask_t_t sEN3V3_Ch1_SP2_5_Enable;
    DATA_CACHE_EPSII_PDM_1_SBSED_Bitmask_t_t sEN3V3_Ch1_SP2_6_Enable;
    DATA_CACHE_EPSII_PDM_1_SBSED_Bitmask_t_t sEN3V3_Ch1_SP2_7_Enable;
    int32_t i32I32N3V3_Ch2_CurrentLimit;
    DATA_CACHE_EPSII_PDM_1_SBSED_Bitmask_t_t sEN3V3_Ch2_MasterEnable;
    uint16_t u16U16NPC104_GPIO_InversedBitmask;
    uint16_t u16U16NPC104_GPIO_NormalModeValueBitmask;
    uint16_t u16U16NPC104_GPIO_PhoenixModeValueBitmask;
    uint16_t u16U16NPC104_GPIO_OvhModeValueBitmask;
} PACKED_STRUCT DATA_CACHE_EPSII_PDM_1_SBasicSettings_t;

typedef struct {
    DATA_CACHE_EPSII_PDM_1_SBasicSettings_t sSBasicSettings;
} PACKED_STRUCT DATA_CACHE_EPSII_PDM_1_SetBasicSettings_t;

typedef struct {
    uint8_t u8EPSII_PDM_1_SBS_GetError;
} PACKED_STRUCT DATA_CACHE_EPSII_PDM_1_SBS_GetError_t;

typedef struct {
    DATA_CACHE_EPSII_PDM_1_SBS_GetError_t sEErr;
    DATA_CACHE_EPSII_PDM_1_SBasicSettings_t sSBasicSettings;
} PACKED_STRUCT DATA_CACHE_Eps2Inst0_SBasicSettings_type_t;

/*
    VN100 Sensor Data
*/
typedef struct {
    uint64_t u64TimeStartup;
    float fMag_X;
    float fMag_Y;
    float fMag_Z;
    float fACC_X;
    float fACC_Y;
    float fACC_Z;
    float fGyro_X;
    float fGyro_Y;
    float fGyro_Z;
    float fYaw;
    float fPitch;
    float fRoll;
    float fQuaternion_X;
    float fQuaternion_Y;
    float fQuaternion_Z;
    float fQuaternion_S;
} PACKED_STRUCT DATA_CACHE_VN100_Data_type_t;

/*
    MPU6050 Sensor 1 Data
*/
typedef struct {
    float fGyro_X;
    float fGyro_Y;
    float fGyro_Z;
    float fTemp;
    float fAcc_X;
    float fAcc_Y;
    float fAcc_Z;
} PACKED_STRUCT DATA_CACHE_MPU6050_1_Data_type_t;

/*
    MPU6050 Sensor 2 Data
*/
typedef struct {
    float fGyro_X;
    float fGyro_Y;
    float fGyro_Z;
    float fTemp;
    float fAcc_X;
    float fAcc_Y;
    float fAcc_Z;
} PACKED_STRUCT DATA_CACHE_MPU6050_2_Data_type_t;

/*
    Magnetorquer ALL Command Data
*/
typedef struct {
    bool bMTQ_1_Select;
    int8_t i8MTQ_1_DutyCycle;
    bool bMTQ_1_Direction;
    bool bMTQ_2_Select;
    int8_t i8MTQ_2_DutyCycle;
    bool bMTQ_2_Direction;
    bool bMTQ_3_Select;
    int8_t i8MTQ_3_DutyCycle;
    bool bMTQ_3_Direction;
} PACKED_STRUCT DATA_CACHE_MTQ_ALL_Command_Data_type_t;

typedef struct {
    uint16_t u16EDC_CONOPS_ENTER_IN_PANEL_COUNTER;
    uint16_t u16EDC_CONOPS_ENTER_IN_HIB_COUNTER;
} PACKED_STRUCT DATA_CACHE_EPSII_BP_1_SDiagErrCounter2_t;

typedef struct {
    DATA_CACHE_EPSII_BP_1_SDiagErrCounter2_t sErrorCounters2;
} PACKED_STRUCT DATA_CACHE_Eps2Inst0__GetMainAppErrCounters2ype_t;

/*
    INA Data
*/
typedef struct {
    float fShunt_Voltage;
    float fBus_Voltage;
    float fPower;
    float fCurrent;
} PACKED_STRUCT DATA_CACHE_INA_Data_type_t;

/*
    Analog Data
*/
typedef struct {
    float fIOBC_Temp;
    uint16_t u16RSD_1_Temp_raw;
    uint16_t u16EHD_1_Temp_raw;
    uint16_t u16PD_1_raw;
    uint16_t u16PD_2_raw;
    uint16_t u16PD_3_raw;
    uint16_t u16RSD_2_Temp_raw;
    uint16_t u16EHD_2_Temp_raw;
    uint16_t u16PD_4_raw;
    uint16_t u16PD_5_raw;
    uint16_t u16PD_6_raw;
} PACKED_STRUCT DATA_CACHE_ANG_Data_type_t;

/*
    CAMERA_MODE Data
*/
typedef struct {
    uint16_t u16NONE;
} PACKED_STRUCT DATA_CACHE_CAMERA_MODE_Data_type_t;

/*
    ADCS Mode
*/
typedef struct {
    uint8_t u8Mode;
    uint8_t u8ModeAD;
    uint8_t u8ModeAC;
} PACKED_STRUCT DATA_CACHE_ADCS_mode_type_t;

/*
    Flag about ADCS algorithms
*/
typedef struct {
    bool bFlag_RD;
    uint8_t u8Flag_sun;
    bool bFlag_traid;
    bool bFlag_traidgyro;
    uint8_t u8Flag_ekf;
} PACKED_STRUCT DATA_CACHE_ADCS_flag_alg_type_t;

/*
    Result of ADCS algorithms
*/
typedef struct {
    float afC_I2B[9];
    float fSp_err;
} PACKED_STRUCT DATA_CACHE_ADCS_result_type_t;

/*
    Data related to ADCS HW
*/
typedef struct {
    uint8_t au8HW_status[6];
    uint8_t u8RW_powerCmd;
    float afFSS_ang[10];
    float afS_BRF[3];
    float afB_BRF[3];
    float afIMU_w[3];
    float afW_BRF[3];
    float afM_cmd[3];
    float afTau_RWN[2];
} PACKED_STRUCT DATA_CACHE_ADCS_HW_type_t;

/*
    CubeSpace Telecommand Flag
*/
typedef struct {
    uint8_t u8CM_TC_1;
    uint8_t u8CM_TC_3;
    uint8_t u8CM_TC_4;
    uint8_t u8CM_TC_5;
    uint8_t u8CM_TC_6;
    uint8_t u8CM_TC_60;
    uint8_t u8CM_TC_63;
    uint8_t u8CM_TC_66;
    uint8_t u8CW1_TC_1;
    uint8_t u8CW1_TC_3;
    uint8_t u8CW1_TC_4;
    uint8_t u8CW1_TC_5;
    uint8_t u8CW1_TC_6;
    uint8_t u8CW1_TC_60;
    uint8_t u8CW1_TC_62;
    uint8_t u8CW1_TC_64;
    uint8_t u8CW2_TC_1;
    uint8_t u8CW2_TC_3;
    uint8_t u8CW2_TC_4;
    uint8_t u8CW2_TC_5;
    uint8_t u8CW2_TC_6;
    uint8_t u8CW2_TC_60;
    uint8_t u8CW2_TC_62;
    uint8_t u8CW2_TC_64;
} PACKED_STRUCT DATA_CACHE_CubeSpace_Telecommand_Flag_t;

/*
    Reaction Wheel 1
*/
typedef struct {
    uint8_t u8Reset_type_1;
    uint8_t u8ErrorLog_IndexReference_1;
    uint8_t u8ErrorLog_IndexValue_1;
    uint8_t u8ErrorLog_Entries_1;
    uint32_t u32ErrorLog_EntryTimestamp_1;
    uint32_t u32ErrorLog_EntryErrorCode_1;
    uint8_t u8ErrorLogSettings_1;
    bool bMotorPowerSwitch_1;
    float fReferenceSpeed_1;
} PACKED_STRUCT DATA_CACHE_CubeWheel1_Telecommand_t;

/*
    Reaction Wheel 2
*/
typedef struct {
    uint8_t u8Reset_type_2;
    uint8_t u8ErrorLog_IndexReference_2;
    uint8_t u8ErrorLog_IndexValue_2;
    uint8_t u8ErrorLog_Entries_2;
    uint32_t u32ErrorLog_EntryTimestamp_2;
    uint32_t u32ErrorLog_EntryErrorCode_2;
    uint8_t u8ErrorLogSettings_2;
    bool bMotorPowerSwitch_2;
    float fReferenceSpeed_2;
} PACKED_STRUCT DATA_CACHE_CubeWheel2_Telecommand_t;

/*
    Magnetometer
*/
typedef struct {
    uint8_t u8Reset_type_2;
    uint8_t u8ErrorLog_IndexReference_2;
    uint8_t u8ErrorLog_IndexValue_2;
    uint8_t u8ErrorLog_Entries_2;
    uint32_t u32ErrorLog_EntryTimestamp_2;
    uint32_t u32ErrorLog_EntryErrorCode_2;
    uint8_t u8ErrorLogSettings_2;
    uint8_t u8CubeMagConfigItems;
    uint16_t u16DeployTimeout;
    uint8_t u8Primary_AutoSelect;
    float fReferenceSpeed_2;
} PACKED_STRUCT DATA_CACHE_CubeMag_Telecommand_t;


// Enum type to access the datacache structure with the index
typedef enum
{
    DC_DID_OBC_0_DATA,
    DC_DID_ADCS_0_DATA,
    DC_DID_ADCS_1_DATA,
    DC_DID_ADCS_2_DATA,
    DC_DID_EPS_0_DATA,
    DC_DID_SSP_0_DATA,
    DC_DID_SSP_1_DATA,
    DC_DID_SSP_2_DATA,
    DC_DID_SSP_3_DATA,
    DC_DID_AOCS_CNTRL_TLM_DATA,
    DC_DID_AOCS_CNTRL_SYS_STATE_DATA,
    DC_DID_AOCS_CNTRL_REF_PARAMS_DATA,
    DC_DID_SENSOR_GYRO_SENSOR_FRAME_DATA,
    DC_DID_SENSOR_GYRO_BODY_FRAME_DATA,
    DC_DID_SENSOR_MAG_PRIMARY_SENSOR_FRAME_DATA,
    DC_DID_SENSOR_MAG_PRIMARY_BODY_FRAME_DATA,
    DC_DID_SENSOR_MAG_SECONDARY_SENSOR_FRAME_DATA,
    DC_DID_SENSOR_MAG_SECONDARY_BODY_FRAME_DATA,
    DC_DID_SENSOR_COARSE_SUN_SENSOR_FRAME_DATA,
    DC_DID_SENSOR_COARSE_SUN_BODY_FRAME_DATA,
    DC_DID_SENSOR_PANEL_TEMP_SENSOR_FRAME_DATA,
    DC_DID_SENSOR_PANEL_TEMP_BODY_FRAME_DATA,
    DC_DID_SENSOR_GYRO_TEMP_SENSOR_FRAME_DATA,
    DC_DID_SENSOR_GYRO_TEMP_BODY_FRAME_DATA,
    DC_DID_ACTUATOR_MTQ_VALUES_DATA,
    DC_DID_ACTUATOR_TORQUE_VALUES_DATA,
    DC_DID_ADCS_3_DATA,
    DC_DID_ADCS_4_DATA,
    DC_DID_EPS_9_DATA,
    DC_DID_EPS_10_DATA,
    DC_DID_EPS_14_DATA,
    DC_DID_CUBEADCS_GEN2_OP_STATUS_COMMON_DATA,
    DC_DID_CUBEADCS_GEN2_OP_STATUS_APP_DATA,
    DC_DID_CUBEADCS_GEN2_TLM_FRAME_166_DATA,
    DC_DID_CUBEADCS_GEN2_TLM_FRAME_167_DATA,
    DC_DID_CUBEADCS_GEN2_TLM_FRAME_168_DATA,
    DC_DID_CUBEADCS_GEN2_TLM_FRAME_169_DATA,
    DC_DID_CUBEADCS_GEN2_TLM_FRAME_170_DATA,
    DC_DID_CUBEADCS_GEN2_TLM_FRAME_171_DATA,
    DC_DID_CUBEADCS_GEN2_TLM_FRAME_172_DATA,
    DC_DID_CUBEADCS_GEN2_TLM_FRAME_173_DATA,
    DC_DID_CUBEADCS_GEN2_TLM_FRAME_174_DATA,
    DC_DID_CUBEADCS_GEN2_TLM_FRAME_175_DATA,
    DC_DID_CUBEADCS_GEN2_TLM_FRAME_176_DATA,
    DC_DID_CUBEADCS_GEN2_TLM_FRAME_177_DATA,
    DC_DID_CUBEADCS_GEN2_TLM_FRAME_178_DATA,
    DC_DID_CUBEADCS_GEN2_TLM_FRAME_179_DATA,
    DC_DID_CUBEADCS_GEN2_TLM_FRAME_180_DATA,
    DC_DID_CUBEADCS_GEN2_TLM_FRAME_203_DATA,
    DC_DID_CUBEADCS_GEN2_TLM_FRAME_204_DATA,
    DC_DID_CUBEADCS_GEN2_TLM_FRAME_205_DATA,
    DC_DID_CUBEADCS_GEN2_TLM_FRAME_206_DATA,
    DC_DID_CUBEADCS_GEN2_TLM_FRAME_207_DATA,
    DC_DID_CUBEADCS_GEN2_TLM_FRAME_208_1_DATA,
    DC_DID_CUBEADCS_GEN2_TLM_FRAME_208_2_DATA,
    DC_DID_CUBEADCS_GEN2_TLM_FRAME_209_DATA,
    DC_DID_CUBEADCS_GEN2_TLM_FRAME_210_DATA,
    DC_DID_CUBEADCS_GEN2_TLM_FRAME_211_DATA,
    DC_DID_CUBEADCS_GEN2_TLM_FRAME_212_DATA,
    DC_DID_CUBEADCS_GEN2_TLM_FRAME_213_DATA,
    DC_DID_CUBEADCS_GEN2_TLM_FRAME_214_DATA,
    DC_DID_CUBEADCS_GEN2_TLM_FRAME_216_DATA,
    DC_DID_CUBEADCS_GEN2_TLM_FRAME_217_DATA,
    DC_DID_CUBEADCS_GEN2_TLM_FRAME_218_DATA,
    DC_DID_CUBEADCS_GEN2_TLM_FRAME_225_DATA,
    DC_DID_CUBEADCS_GEN2_TLM_FRAME_226_DATA,
    DC_DID_CUBEADCS_GEN2_TLM_FRAME_165_DATA,
    DC_DID_CUBEADCS_GEN2_TLM_FRAME_221_DATA,
    DC_DID_GNSS_TIME_DATA,
    DC_DID_GNSS_BESTXYZ_DATA,
    DC_DID_SAT_STATE_VECTOR_FROM_PROPAGATOR_DATA,
    DC_DID_SAT_MAG_FIELD_VECTOR_FROM_MODEL_DATA,
    DC_DID_SAT_MAG_FIELD_VECTOR_FROM_SENSOR_DATA,
    DC_DID_FDIR_EPS_I_CMD_EXEC_STATUS_DATA,
    DC_DID_FDIR_EPS_II_PDM_CMD_EXEC_STATUS_DATA,
    DC_DID_FDIR_CUBEADCS_CMD_EXEC_STATUS_DATA,
    DC_DID_FDIR_CUBEADCS_GEN2_CMD_EXEC_STATUS_DATA,
    DC_DID_FDIR_CUBEADCS_GEN2_EVENTS_DATA,
    DC_DID_FDIR_S_BAND_TMTC_CMD_EXEC_STATUS_DATA,
    DC_DID_FDIR_UHF_CMD_EXEC_STATUS_DATA,
    DC_DID_FDIR_GNSS_CMD_EXEC_STATUS_DATA,
    DC_DID_FDIR_SDR_CMD_EXEC_STATUS_DATA,
    DC_DID_FDIR_S_X_BAND_CMD_EXEC_STATUS_DATA,
    DC_DID_FDIR_THRUSTER_CMD_EXEC_STATUS_DATA,
    DC_DID_XBAND_FE_DATA,
    DC_DID_EPSOVERALLBATTERYINFO_DATA,
    DC_DID_PPS_TELEMETRY_DATA,
    DC_DID_FDIR_EPS_III_PDM_CMD_EXEC_STATUS_DATA,
    DC_DID_EPS2_BP_INST0_BP_INFO_DATA,
    DC_DID_EPS2_BP_INST0_DEVICE_HEALTH_INFO_DATA,
    DC_DID_EPS2_BP_INST0_INA_SENSOR1_DATA,
    DC_DID_EPS2_BP_INST0_INA_SENSOR2_DATA,
    DC_DID_EPS2_BP_INST0_BALANCER_INFO_DATA,
    DC_DID_EPS2_BP_INST0_BALANCER_STATUS_DATA,
    DC_DID_EPS2_BP_INST0_BALANCER_CELLS_INFO_DATA,
    DC_DID_EPS2_BP_INST0_CHARGER_XP_DATA,
    DC_DID_EPS2_BP_INST0_CHARGER_XR_DATA,
    DC_DID_EPS2_BP_INST0_CHARGER_YP_DATA,
    DC_DID_EPS2_BP_INST0_CHARGER_YR_DATA,
    DC_DID_EPS2_BP_INST0_CHARGER_ZP_DATA,
    DC_DID_EPS2_BP_INST0_CHARGER_ZR_DATA,
    DC_DID_FDIR_EPS_II_BP_INST0_CMD_EXEC_STATUS_DATA,
    DC_DID_EPS3_BP_INST0_UPTIME_IN_SECONDS,
    DC_DID_EPS3_BP_INST0COMMON,
    DC_DID_EPS3_BP_INST0HIB_MODE_STATUS,
    DC_DID_EPS3_BP_INST0MEASUREMENTS,
    DC_DID_EPS3_BP_INST0DISCHARGING_STATE,
    DC_DID_EPS3_BP_INST0CHARGE_STATUS,
    DC_DID_EPS3_BP_INST0BALANCERS_STATUS,
    DC_DID_EPS3_BP_INST0BATTERY_CELLS_STATUS,
    DC_DID_EPS3_BP_INST0HEATERS_STATUS,
    DC_DID_EPS3_BP_INST0_CMD_EXEC_STATUS_DATA,
    DC_DID_DUMB_DATA,
    DC_DID_DUMB_DATA1,
    DC_DID_DUMB_DATA3,
    DC_DID_DUMB_DATA4,
    DC_DID_DUMB_DATA5,
    DC_DID_DUMB_DATA6,
    DC_DID_EPS3_PDM_A_INST0_UPTIME_IN_SECONDS,
    DC_DID_EPS3_PDM_A_INST0_COMMON,
    DC_DID_EPS3_PDM_A_INST0_HIB_MODE,
    DC_DID_EPS3_PDM_A_INST0_GENERAL_OUTPUTS,
    DC_DID_EPS3_PDM_A_INST0_GENERAL_FAULTS,
    DC_DID_EPS3_PDM_A_INST0_ALL_MEASUREMENTS,
    DC_DID_EPS3_PDM_A_INST0_CMD_EXEC_STATUS_DATA,
    DC_DID_EPS3_PDM_B_INST0_CMD_EXEC_STATUS_DATA,
    DC_DID_EPS3_PDM_B_INST0_UPTIME_IN_SECONDS,
    DC_DID_EPS3_PDM_B_INST0_COMMON,
    DC_DID_EPS3_PDM_B_INST0_HIB_MODE,
    DC_DID_EPS3_PDM_B_INST0_GENERAL_OUTPUTS,
    DC_DID_EPS3_PDM_B_INST0_CHANNEL_FLAG_STATE,
    DC_DID_EPS3_PDM_B_INST0_TEMPERATURE,
    DC_DID_EPS3_PDM_B_INST0_ALL_MEASUREMENTS,
    DC_DID_EPS3_EXPANDER_INST0_CMD_EXEC_STATUS_DATA,
    DC_DID_EPS3_EXPANDER_INST0_UPTIME_IN_SECONDS,
    DC_DID_EPS3_EXPANDER_INST0_COMMON,
    DC_DID_EPS3_EXPANDER_INST0_OUTPUTS,
    DC_DID_EPS3_EXPANDER_INST0_GENERAL_INPUTS,
    DC_DID_EPS3_EXPANDER_INST0_FEEDBACKS,
    DC_DID_EPS3_EXPANDER_INST0_VOLT_AMP_MEASUREMENTS,
    DC_DID_EPS3_INPUT_STAGE_INST0_UPTIME_IN_SECONDS,
    DC_DID_EPS3_INPUT_STAGE_INST0COMMON,
    DC_DID_EPS3_INPUT_STAGE_INST0HIB_MODE_STATUS,
    DC_DID_EPS3_INPUT_STAGE_INST0SELFLOCK_ON,
    DC_DID_EPS3_INPUT_STAGE_INST0SP1,
    DC_DID_EPS3_INPUT_STAGE_INST0SP2,
    DC_DID_EPS3_INPUT_STAGE_INST0SP3,
    DC_DID_EPS3_INPUT_STAGE_INST0SYSTEM_BUS,
    DC_DID_EPS3_INPUT_STAGE_INST0BUS_7V5,
    DC_DID_EPS3_INPUT_STAGE_INST0BUS_7V5_POWER_GOOD,
    DC_DID_EPS3_INPUT_STAGE_INST0UNDERVOLTAGE_7V5,
    DC_DID_EPS3_INPUT_STAGE_INST0BUS_3V3,
    DC_DID_EPS3_INPUT_STAGE_INST0UNDERVOLTAGE_3V3,
    DC_DID_EPS3_INPUT_STAGE_INST0_CMD_EXEC_STATUS_DATA,
    DC_DID_MAGDATA,
    DC_DID_WHEELDATA1,
    DC_DID_WHEELDATA2,
    DC_DID_FSS1_DATA,
    DC_DID_FSS2_DATA,
    DC_DID_FSS3_DATA,
    DC_DID_FSS4_DATA,
    DC_DID_FSS5_DATA,
    DC_DID_ADCS_FSS_DATA,
    DC_DID_ADCS_MAG_DATA,
    DC_DID_ADCS_IMU_DATA,
    DC_DID_ADCS_RW_DATA,
    DC_DID_ADCS_MTQ_DATA,
    DC_DID_EPS2_BP_INST0_SBPMODECHANGE_DATA,
    DC_DID_EPS2_BP_BPMODESMROLLINGTRACE_DATA,
    DC_DID_EPS2_PDM_SBSEDE_CONOPSMODE_DATA,
    DC_DID_EPS2_PDM_SBSED_BITMASK_DATA,
    DC_DID_EPS2_PDM_SBASICSETTINGS_DATA,
    DC_DID_EPS2_PDM_SETBASICSETTINGS_DATA,
    DC_DID_EPS2_PDM_SBS_GETERROR_DATA,
    DC_DID_EPS2INST0_PDM_SBASICSETTINGS_DATA,
    DC_DID_VN100_DATA,
    DC_DID_MPU6050_1_DATA,
    DC_DID_MPU6050_2_DATA,
    DC_DID_MTQ_ALL_CMD_DATA,
    DC_DID_EPS2INST0_BP_SDIAGERRCOUNTER2_DATA,
    DC_DID_EPS2INST0_BP_GETMAINAPPERRCOUNTERS2_DATA,
    DC_DID_INA_DATA,
    DC_DID_ANG_DATA,
    DC_DID_CAMERA_MODE_DATA,
    DC_DID_ADCS_MODE,
    DC_DID_ADCS_FLAG_ALG,
    DC_DID_ADCS_RESULT,
    DC_DID_ADCS_HW,
    DC_DID_TC_FLAG,
    DC_DID_WHEELCOMMAND1,
    DC_DID_WHEELCOMMAND2,
    DC_DID_MAGCOMMAND,
    DC_DID_MAX
} dc_did_id;


/**********************************************************************
 *
 *  DataCache function prototypes
 *
 **********************************************************************/

/*!
* @brief Init routine for the DataCache component
*/
void dc_init(void);
/*!
* @brief Main Data Cache task function
* @warning Should not be called too often because it locks the data in order to modify it and
*          could interfere with the set/get operations called by DC clients.
*/
void dc_task(void);

dc_data_status_t dc_get_obc_0_data(DATA_CACHE_OBC_0_t * const p_data);
void dc_set_obc_0_data(DATA_CACHE_OBC_0_t * const p_new_data);

dc_data_status_t dc_get_adcs_0_data(DATA_CACHE_ADCS_0_t * const p_data);
void dc_set_adcs_0_data(DATA_CACHE_ADCS_0_t * const p_new_data);

dc_data_status_t dc_get_adcs_1_data(DATA_CACHE_ADCS_1_t * const p_data);
void dc_set_adcs_1_data(DATA_CACHE_ADCS_1_t * const p_new_data);

dc_data_status_t dc_get_adcs_2_data(DATA_CACHE_ADCS_2_t * const p_data);
void dc_set_adcs_2_data(DATA_CACHE_ADCS_2_t * const p_new_data);

dc_data_status_t dc_get_eps_0_data(DATA_CACHE_EPS_0_t * const p_data);
void dc_set_eps_0_data(DATA_CACHE_EPS_0_t * const p_new_data);

dc_data_status_t dc_get_ssp_0_data(DATA_CACHE_SSP_0_Telemetry_t * const p_data);
void dc_set_ssp_0_data(DATA_CACHE_SSP_0_Telemetry_t * const p_new_data);

dc_data_status_t dc_get_ssp_1_data(DATA_CACHE_SSP_1_Telemetry_t * const p_data);
void dc_set_ssp_1_data(DATA_CACHE_SSP_1_Telemetry_t * const p_new_data);

dc_data_status_t dc_get_ssp_2_data(DATA_CACHE_SSP_2_Telemetry_t * const p_data);
void dc_set_ssp_2_data(DATA_CACHE_SSP_2_Telemetry_t * const p_new_data);

dc_data_status_t dc_get_ssp_3_data(DATA_CACHE_SSP_3_Telemetry_t * const p_data);
void dc_set_ssp_3_data(DATA_CACHE_SSP_3_Telemetry_t * const p_new_data);

dc_data_status_t dc_get_aocs_cntrl_tlm_data(DATA_CACHE_AOCS_CNTRL_TLM_t * const p_data);
void dc_set_aocs_cntrl_tlm_data(DATA_CACHE_AOCS_CNTRL_TLM_t * const p_new_data);

dc_data_status_t dc_get_aocs_cntrl_sys_state_data(DATA_CACHE_AOCS_CNTRL_SYS_STATE_t * const p_data);
void dc_set_aocs_cntrl_sys_state_data(DATA_CACHE_AOCS_CNTRL_SYS_STATE_t * const p_new_data);

dc_data_status_t dc_get_aocs_cntrl_ref_params_data(DATA_CACHE_AOCS_CNTRL_REF_PARAMS_t * const p_data);
void dc_set_aocs_cntrl_ref_params_data(DATA_CACHE_AOCS_CNTRL_REF_PARAMS_t * const p_new_data);

dc_data_status_t dc_get_sensor_gyro_sensor_frame_data(DATA_CACHE_SENSOR_GYRO_SENSOR_FRAME_t * const p_data);
void dc_set_sensor_gyro_sensor_frame_data(DATA_CACHE_SENSOR_GYRO_SENSOR_FRAME_t * const p_new_data);

dc_data_status_t dc_get_sensor_gyro_body_frame_data(DATA_CACHE_SENSOR_GYRO_BODY_FRAME_t * const p_data);
void dc_set_sensor_gyro_body_frame_data(DATA_CACHE_SENSOR_GYRO_BODY_FRAME_t * const p_new_data);

dc_data_status_t dc_get_sensor_mag_primary_sensor_frame_data(DATA_CACHE_SENSOR_MAG_PRIMARY_SENSOR_FRAME_t * const p_data);
void dc_set_sensor_mag_primary_sensor_frame_data(DATA_CACHE_SENSOR_MAG_PRIMARY_SENSOR_FRAME_t * const p_new_data);

dc_data_status_t dc_get_sensor_mag_primary_body_frame_data(DATA_CACHE_SENSOR_MAG_PRIMARY_BODY_FRAME_t * const p_data);
void dc_set_sensor_mag_primary_body_frame_data(DATA_CACHE_SENSOR_MAG_PRIMARY_BODY_FRAME_t * const p_new_data);

dc_data_status_t dc_get_sensor_mag_secondary_sensor_frame_data(DATA_CACHE_SENSOR_MAG_SECONDARY_SENSOR_FRAME_t * const p_data);
void dc_set_sensor_mag_secondary_sensor_frame_data(DATA_CACHE_SENSOR_MAG_SECONDARY_SENSOR_FRAME_t * const p_new_data);

dc_data_status_t dc_get_sensor_mag_secondary_body_frame_data(DATA_CACHE_SENSOR_MAG_SECONDARY_BODY_FRAME_t * const p_data);
void dc_set_sensor_mag_secondary_body_frame_data(DATA_CACHE_SENSOR_MAG_SECONDARY_BODY_FRAME_t * const p_new_data);

dc_data_status_t dc_get_sensor_coarse_sun_sensor_frame_data(DATA_CACHE_SENSOR_COARSE_SUN_SENSOR_FRAME_t * const p_data);
void dc_set_sensor_coarse_sun_sensor_frame_data(DATA_CACHE_SENSOR_COARSE_SUN_SENSOR_FRAME_t * const p_new_data);

dc_data_status_t dc_get_sensor_coarse_sun_body_frame_data(DATA_CACHE_SENSOR_COARSE_SUN_BODY_FRAME_t * const p_data);
void dc_set_sensor_coarse_sun_body_frame_data(DATA_CACHE_SENSOR_COARSE_SUN_BODY_FRAME_t * const p_new_data);

dc_data_status_t dc_get_sensor_panel_temp_sensor_frame_data(DATA_CACHE_SENSOR_PANEL_TEMP_SENSOR_FRAME_t * const p_data);
void dc_set_sensor_panel_temp_sensor_frame_data(DATA_CACHE_SENSOR_PANEL_TEMP_SENSOR_FRAME_t * const p_new_data);

dc_data_status_t dc_get_sensor_panel_temp_body_frame_data(DATA_CACHE_SENSOR_PANEL_TEMP_BODY_FRAME_t * const p_data);
void dc_set_sensor_panel_temp_body_frame_data(DATA_CACHE_SENSOR_PANEL_TEMP_BODY_FRAME_t * const p_new_data);

dc_data_status_t dc_get_sensor_gyro_temp_sensor_frame_data(DATA_CACHE_SENSOR_GYRO_TEMP_SENSOR_FRAME_t * const p_data);
void dc_set_sensor_gyro_temp_sensor_frame_data(DATA_CACHE_SENSOR_GYRO_TEMP_SENSOR_FRAME_t * const p_new_data);

dc_data_status_t dc_get_sensor_gyro_temp_body_frame_data(DATA_CACHE_SENSOR_GYRO_TEMP_BODY_FRAME_t * const p_data);
void dc_set_sensor_gyro_temp_body_frame_data(DATA_CACHE_SENSOR_GYRO_TEMP_BODY_FRAME_t * const p_new_data);

dc_data_status_t dc_get_actuator_mtq_values_data(DATA_CACHE_ACTUATOR_MTQ_VALUES_t * const p_data);
void dc_set_actuator_mtq_values_data(DATA_CACHE_ACTUATOR_MTQ_VALUES_t * const p_new_data);

dc_data_status_t dc_get_actuator_torque_values_data(DATA_CACHE_ACTUATOR_TORQUE_VALUES_t * const p_data);
void dc_set_actuator_torque_values_data(DATA_CACHE_ACTUATOR_TORQUE_VALUES_t * const p_new_data);

dc_data_status_t dc_get_adcs_3_data(DATA_CACHE_ADCS_3_t * const p_data);
void dc_set_adcs_3_data(DATA_CACHE_ADCS_3_t * const p_new_data);

dc_data_status_t dc_get_adcs_4_data(DATA_CACHE_ADCS_4_t * const p_data);
void dc_set_adcs_4_data(DATA_CACHE_ADCS_4_t * const p_new_data);

dc_data_status_t dc_get_eps_9_data(DATA_CACHE_EPS_9_t * const p_data);
void dc_set_eps_9_data(DATA_CACHE_EPS_9_t * const p_new_data);

dc_data_status_t dc_get_eps_10_data(DATA_CACHE_EPS_10_t * const p_data);
void dc_set_eps_10_data(DATA_CACHE_EPS_10_t * const p_new_data);

dc_data_status_t dc_get_eps_14_data(DATA_CACHE_EPS_14_t * const p_data);
void dc_set_eps_14_data(DATA_CACHE_EPS_14_t * const p_new_data);

dc_data_status_t dc_get_cubeadcs_gen2_op_status_common_data(DATA_CACHE_CUBEADCS_GEN2_OP_STATUS_COMMON_t * const p_data);
void dc_set_cubeadcs_gen2_op_status_common_data(DATA_CACHE_CUBEADCS_GEN2_OP_STATUS_COMMON_t * const p_new_data);

dc_data_status_t dc_get_cubeadcs_gen2_op_status_app_data(DATA_CACHE_CUBEADCS_GEN2_OP_STATUS_APP_t * const p_data);
void dc_set_cubeadcs_gen2_op_status_app_data(DATA_CACHE_CUBEADCS_GEN2_OP_STATUS_APP_t * const p_new_data);

dc_data_status_t dc_get_cubeadcs_gen2_tlm_frame_166_data(DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_166_t * const p_data);
void dc_set_cubeadcs_gen2_tlm_frame_166_data(DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_166_t * const p_new_data);

dc_data_status_t dc_get_cubeadcs_gen2_tlm_frame_167_data(DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_167_t * const p_data);
void dc_set_cubeadcs_gen2_tlm_frame_167_data(DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_167_t * const p_new_data);

dc_data_status_t dc_get_cubeadcs_gen2_tlm_frame_168_data(DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_168_t * const p_data);
void dc_set_cubeadcs_gen2_tlm_frame_168_data(DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_168_t * const p_new_data);

dc_data_status_t dc_get_cubeadcs_gen2_tlm_frame_169_data(DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_169_t * const p_data);
void dc_set_cubeadcs_gen2_tlm_frame_169_data(DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_169_t * const p_new_data);

dc_data_status_t dc_get_cubeadcs_gen2_tlm_frame_170_data(DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_170_t * const p_data);
void dc_set_cubeadcs_gen2_tlm_frame_170_data(DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_170_t * const p_new_data);

dc_data_status_t dc_get_cubeadcs_gen2_tlm_frame_171_data(DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_171_t * const p_data);
void dc_set_cubeadcs_gen2_tlm_frame_171_data(DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_171_t * const p_new_data);

dc_data_status_t dc_get_cubeadcs_gen2_tlm_frame_172_data(DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_172_t * const p_data);
void dc_set_cubeadcs_gen2_tlm_frame_172_data(DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_172_t * const p_new_data);

dc_data_status_t dc_get_cubeadcs_gen2_tlm_frame_173_data(DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_173_t * const p_data);
void dc_set_cubeadcs_gen2_tlm_frame_173_data(DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_173_t * const p_new_data);

dc_data_status_t dc_get_cubeadcs_gen2_tlm_frame_174_data(DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_174_t * const p_data);
void dc_set_cubeadcs_gen2_tlm_frame_174_data(DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_174_t * const p_new_data);

dc_data_status_t dc_get_cubeadcs_gen2_tlm_frame_175_data(DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_175_t * const p_data);
void dc_set_cubeadcs_gen2_tlm_frame_175_data(DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_175_t * const p_new_data);

dc_data_status_t dc_get_cubeadcs_gen2_tlm_frame_176_data(DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_176_t * const p_data);
void dc_set_cubeadcs_gen2_tlm_frame_176_data(DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_176_t * const p_new_data);

dc_data_status_t dc_get_cubeadcs_gen2_tlm_frame_177_data(DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_177_t * const p_data);
void dc_set_cubeadcs_gen2_tlm_frame_177_data(DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_177_t * const p_new_data);

dc_data_status_t dc_get_cubeadcs_gen2_tlm_frame_178_data(DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_178_t * const p_data);
void dc_set_cubeadcs_gen2_tlm_frame_178_data(DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_178_t * const p_new_data);

dc_data_status_t dc_get_cubeadcs_gen2_tlm_frame_179_data(DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_179_t * const p_data);
void dc_set_cubeadcs_gen2_tlm_frame_179_data(DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_179_t * const p_new_data);

dc_data_status_t dc_get_cubeadcs_gen2_tlm_frame_180_data(DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_180_t * const p_data);
void dc_set_cubeadcs_gen2_tlm_frame_180_data(DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_180_t * const p_new_data);

dc_data_status_t dc_get_cubeadcs_gen2_tlm_frame_203_data(DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_203_t * const p_data);
void dc_set_cubeadcs_gen2_tlm_frame_203_data(DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_203_t * const p_new_data);

dc_data_status_t dc_get_cubeadcs_gen2_tlm_frame_204_data(DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_204_t * const p_data);
void dc_set_cubeadcs_gen2_tlm_frame_204_data(DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_204_t * const p_new_data);

dc_data_status_t dc_get_cubeadcs_gen2_tlm_frame_205_data(DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_205_t * const p_data);
void dc_set_cubeadcs_gen2_tlm_frame_205_data(DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_205_t * const p_new_data);

dc_data_status_t dc_get_cubeadcs_gen2_tlm_frame_206_data(DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_206_t * const p_data);
void dc_set_cubeadcs_gen2_tlm_frame_206_data(DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_206_t * const p_new_data);

dc_data_status_t dc_get_cubeadcs_gen2_tlm_frame_207_data(DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_207_t * const p_data);
void dc_set_cubeadcs_gen2_tlm_frame_207_data(DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_207_t * const p_new_data);

dc_data_status_t dc_get_cubeadcs_gen2_tlm_frame_208_1_data(DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_208_1_t * const p_data);
void dc_set_cubeadcs_gen2_tlm_frame_208_1_data(DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_208_1_t * const p_new_data);

dc_data_status_t dc_get_cubeadcs_gen2_tlm_frame_208_2_data(DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_208_2_t * const p_data);
void dc_set_cubeadcs_gen2_tlm_frame_208_2_data(DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_208_2_t * const p_new_data);

dc_data_status_t dc_get_cubeadcs_gen2_tlm_frame_209_data(DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_209_t * const p_data);
void dc_set_cubeadcs_gen2_tlm_frame_209_data(DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_209_t * const p_new_data);

dc_data_status_t dc_get_cubeadcs_gen2_tlm_frame_210_data(DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_210_t * const p_data);
void dc_set_cubeadcs_gen2_tlm_frame_210_data(DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_210_t * const p_new_data);

dc_data_status_t dc_get_cubeadcs_gen2_tlm_frame_211_data(DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_211_t * const p_data);
void dc_set_cubeadcs_gen2_tlm_frame_211_data(DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_211_t * const p_new_data);

dc_data_status_t dc_get_cubeadcs_gen2_tlm_frame_212_data(DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_212_t * const p_data);
void dc_set_cubeadcs_gen2_tlm_frame_212_data(DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_212_t * const p_new_data);

dc_data_status_t dc_get_cubeadcs_gen2_tlm_frame_213_data(DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_213_t * const p_data);
void dc_set_cubeadcs_gen2_tlm_frame_213_data(DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_213_t * const p_new_data);

dc_data_status_t dc_get_cubeadcs_gen2_tlm_frame_214_data(DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_214_t * const p_data);
void dc_set_cubeadcs_gen2_tlm_frame_214_data(DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_214_t * const p_new_data);

dc_data_status_t dc_get_cubeadcs_gen2_tlm_frame_216_data(DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_216_t * const p_data);
void dc_set_cubeadcs_gen2_tlm_frame_216_data(DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_216_t * const p_new_data);

dc_data_status_t dc_get_cubeadcs_gen2_tlm_frame_217_data(DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_217_t * const p_data);
void dc_set_cubeadcs_gen2_tlm_frame_217_data(DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_217_t * const p_new_data);

dc_data_status_t dc_get_cubeadcs_gen2_tlm_frame_218_data(DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_218_t * const p_data);
void dc_set_cubeadcs_gen2_tlm_frame_218_data(DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_218_t * const p_new_data);

dc_data_status_t dc_get_cubeadcs_gen2_tlm_frame_225_data(DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_225_t * const p_data);
void dc_set_cubeadcs_gen2_tlm_frame_225_data(DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_225_t * const p_new_data);

dc_data_status_t dc_get_cubeadcs_gen2_tlm_frame_226_data(DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_226_t * const p_data);
void dc_set_cubeadcs_gen2_tlm_frame_226_data(DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_226_t * const p_new_data);

dc_data_status_t dc_get_cubeadcs_gen2_tlm_frame_165_data(DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_165_t * const p_data);
void dc_set_cubeadcs_gen2_tlm_frame_165_data(DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_165_t * const p_new_data);

dc_data_status_t dc_get_cubeadcs_gen2_tlm_frame_221_data(DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_221_t * const p_data);
void dc_set_cubeadcs_gen2_tlm_frame_221_data(DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_221_t * const p_new_data);

dc_data_status_t dc_get_gnss_time_data(DATA_CACHE_GNSS_TIME_t * const p_data);
void dc_set_gnss_time_data(DATA_CACHE_GNSS_TIME_t * const p_new_data);

dc_data_status_t dc_get_gnss_bestxyz_data(DATA_CACHE_GNSS_BESTXYZ_t * const p_data);
void dc_set_gnss_bestxyz_data(DATA_CACHE_GNSS_BESTXYZ_t * const p_new_data);

dc_data_status_t dc_get_sat_state_vector_from_propagator_data(DATA_CACHE_SAT_STATE_VECTOR_FROM_PROPAGATOR_t * const p_data);
void dc_set_sat_state_vector_from_propagator_data(DATA_CACHE_SAT_STATE_VECTOR_FROM_PROPAGATOR_t * const p_new_data);

dc_data_status_t dc_get_sat_mag_field_vector_from_model_data(DATA_CACHE_SAT_MAG_FIELD_VECTOR_FROM_MODEL_t * const p_data);
void dc_set_sat_mag_field_vector_from_model_data(DATA_CACHE_SAT_MAG_FIELD_VECTOR_FROM_MODEL_t * const p_new_data);

dc_data_status_t dc_get_sat_mag_field_vector_from_sensor_data(DATA_CACHE_SAT_MAG_FIELD_VECTOR_FROM_SENSOR_t * const p_data);
void dc_set_sat_mag_field_vector_from_sensor_data(DATA_CACHE_SAT_MAG_FIELD_VECTOR_FROM_SENSOR_t * const p_new_data);

dc_data_status_t dc_get_fdir_eps_i_cmd_exec_status_data(DATA_CACHE_FDIR_EPS_I_CMD_EXEC_STATUS_t * const p_data);
void dc_set_fdir_eps_i_cmd_exec_status_data(DATA_CACHE_FDIR_EPS_I_CMD_EXEC_STATUS_t * const p_new_data);

dc_data_status_t dc_get_fdir_eps_ii_pdm_cmd_exec_status_data(DATA_CACHE_FDIR_EPS_II_PDM_CMD_EXEC_STATUS_t * const p_data);
void dc_set_fdir_eps_ii_pdm_cmd_exec_status_data(DATA_CACHE_FDIR_EPS_II_PDM_CMD_EXEC_STATUS_t * const p_new_data);

dc_data_status_t dc_get_fdir_cubeadcs_cmd_exec_status_data(DATA_CACHE_FDIR_CUBEADCS_CMD_EXEC_STATUS_t * const p_data);
void dc_set_fdir_cubeadcs_cmd_exec_status_data(DATA_CACHE_FDIR_CUBEADCS_CMD_EXEC_STATUS_t * const p_new_data);

dc_data_status_t dc_get_fdir_cubeadcs_gen2_cmd_exec_status_data(DATA_CACHE_FDIR_CUBEADCS_GEN2_CMD_EXEC_STATUS_t * const p_data);
void dc_set_fdir_cubeadcs_gen2_cmd_exec_status_data(DATA_CACHE_FDIR_CUBEADCS_GEN2_CMD_EXEC_STATUS_t * const p_new_data);

dc_data_status_t dc_get_fdir_cubeadcs_gen2_events_data(DATA_CACHE_FDIR_CUBEADCS_GEN2_EVENTS_t * const p_data);
void dc_set_fdir_cubeadcs_gen2_events_data(DATA_CACHE_FDIR_CUBEADCS_GEN2_EVENTS_t * const p_new_data);

dc_data_status_t dc_get_fdir_s_band_tmtc_cmd_exec_status_data(DATA_CACHE_FDIR_S_BAND_TMTC_CMD_EXEC_STATUS_t * const p_data);
void dc_set_fdir_s_band_tmtc_cmd_exec_status_data(DATA_CACHE_FDIR_S_BAND_TMTC_CMD_EXEC_STATUS_t * const p_new_data);

dc_data_status_t dc_get_fdir_uhf_cmd_exec_status_data(DATA_CACHE_FDIR_UHF_CMD_EXEC_STATUS_t * const p_data);
void dc_set_fdir_uhf_cmd_exec_status_data(DATA_CACHE_FDIR_UHF_CMD_EXEC_STATUS_t * const p_new_data);

dc_data_status_t dc_get_fdir_gnss_cmd_exec_status_data(DATA_CACHE_FDIR_GNSS_CMD_EXEC_STATUS_t * const p_data);
void dc_set_fdir_gnss_cmd_exec_status_data(DATA_CACHE_FDIR_GNSS_CMD_EXEC_STATUS_t * const p_new_data);

dc_data_status_t dc_get_fdir_sdr_cmd_exec_status_data(DATA_CACHE_FDIR_SDR_CMD_EXEC_STATUS_t * const p_data);
void dc_set_fdir_sdr_cmd_exec_status_data(DATA_CACHE_FDIR_SDR_CMD_EXEC_STATUS_t * const p_new_data);

dc_data_status_t dc_get_fdir_s_x_band_cmd_exec_status_data(DATA_CACHE_FDIR_S_X_BAND_CMD_EXEC_STATUS_t * const p_data);
void dc_set_fdir_s_x_band_cmd_exec_status_data(DATA_CACHE_FDIR_S_X_BAND_CMD_EXEC_STATUS_t * const p_new_data);

dc_data_status_t dc_get_fdir_thruster_cmd_exec_status_data(DATA_CACHE_FDIR_THRUSTER_CMD_EXEC_STATUS_t * const p_data);
void dc_set_fdir_thruster_cmd_exec_status_data(DATA_CACHE_FDIR_THRUSTER_CMD_EXEC_STATUS_t * const p_new_data);

dc_data_status_t dc_get_xband_fe_data(DATA_CACHE_XBandFeTelemetry_t * const p_data);
void dc_set_xband_fe_data(DATA_CACHE_XBandFeTelemetry_t * const p_new_data);

dc_data_status_t dc_get_epsoverallbatteryinfo_data(DATA_CACHE_EpsOverallBatteryInfoType_t * const p_data);
void dc_set_epsoverallbatteryinfo_data(DATA_CACHE_EpsOverallBatteryInfoType_t * const p_new_data);

dc_data_status_t dc_get_pps_telemetry_data(DATA_CACHE_PPS_Telemetry_t * const p_data);
void dc_set_pps_telemetry_data(DATA_CACHE_PPS_Telemetry_t * const p_new_data);

dc_data_status_t dc_get_fdir_eps_iii_pdm_cmd_exec_status_data(DATA_CACHE_FDIR_EPS_III_PDM_CMD_EXEC_STATUS_t * const p_data);
void dc_set_fdir_eps_iii_pdm_cmd_exec_status_data(DATA_CACHE_FDIR_EPS_III_PDM_CMD_EXEC_STATUS_t * const p_new_data);

dc_data_status_t dc_get_eps2_bp_inst0_bp_info_data(DATA_CACHE_Eps2Inst0BatteryInfoType_t * const p_data);
void dc_set_eps2_bp_inst0_bp_info_data(DATA_CACHE_Eps2Inst0BatteryInfoType_t * const p_new_data);

dc_data_status_t dc_get_eps2_bp_inst0_device_health_info_data(DATA_CACHE_Eps2Inst0DeviceHealthInfoType_t * const p_data);
void dc_set_eps2_bp_inst0_device_health_info_data(DATA_CACHE_Eps2Inst0DeviceHealthInfoType_t * const p_new_data);

dc_data_status_t dc_get_eps2_bp_inst0_ina_sensor1_data(DATA_CACHE_Eps2Inst0InaSensors1Type_t * const p_data);
void dc_set_eps2_bp_inst0_ina_sensor1_data(DATA_CACHE_Eps2Inst0InaSensors1Type_t * const p_new_data);

dc_data_status_t dc_get_eps2_bp_inst0_ina_sensor2_data(DATA_CACHE_Eps2Inst0InaSensors2Type_t * const p_data);
void dc_set_eps2_bp_inst0_ina_sensor2_data(DATA_CACHE_Eps2Inst0InaSensors2Type_t * const p_new_data);

dc_data_status_t dc_get_eps2_bp_inst0_balancer_info_data(DATA_CACHE_Eps2Inst0BalancerInfoType_t * const p_data);
void dc_set_eps2_bp_inst0_balancer_info_data(DATA_CACHE_Eps2Inst0BalancerInfoType_t * const p_new_data);

dc_data_status_t dc_get_eps2_bp_inst0_balancer_status_data(DATA_CACHE_Eps2Inst0BalancerStatusType_t * const p_data);
void dc_set_eps2_bp_inst0_balancer_status_data(DATA_CACHE_Eps2Inst0BalancerStatusType_t * const p_new_data);

dc_data_status_t dc_get_eps2_bp_inst0_balancer_cells_info_data(DATA_CACHE_Eps2Inst0BalancerCellsInfoType_t * const p_data);
void dc_set_eps2_bp_inst0_balancer_cells_info_data(DATA_CACHE_Eps2Inst0BalancerCellsInfoType_t * const p_new_data);

dc_data_status_t dc_get_eps2_bp_inst0_charger_xp_data(DATA_CACHE_Eps2Inst0ChargerXpType_t * const p_data);
void dc_set_eps2_bp_inst0_charger_xp_data(DATA_CACHE_Eps2Inst0ChargerXpType_t * const p_new_data);

dc_data_status_t dc_get_eps2_bp_inst0_charger_xr_data(DATA_CACHE_Eps2Inst0ChargerXrType_t * const p_data);
void dc_set_eps2_bp_inst0_charger_xr_data(DATA_CACHE_Eps2Inst0ChargerXrType_t * const p_new_data);

dc_data_status_t dc_get_eps2_bp_inst0_charger_yp_data(DATA_CACHE_Eps2Inst0ChargerYpType_t * const p_data);
void dc_set_eps2_bp_inst0_charger_yp_data(DATA_CACHE_Eps2Inst0ChargerYpType_t * const p_new_data);

dc_data_status_t dc_get_eps2_bp_inst0_charger_yr_data(DATA_CACHE_Eps2Inst0ChargerYrType_t * const p_data);
void dc_set_eps2_bp_inst0_charger_yr_data(DATA_CACHE_Eps2Inst0ChargerYrType_t * const p_new_data);

dc_data_status_t dc_get_eps2_bp_inst0_charger_zp_data(DATA_CACHE_Eps2Inst0ChargerZpType_t * const p_data);
void dc_set_eps2_bp_inst0_charger_zp_data(DATA_CACHE_Eps2Inst0ChargerZpType_t * const p_new_data);

dc_data_status_t dc_get_eps2_bp_inst0_charger_zr_data(DATA_CACHE_Eps2Inst0ChargerZrType_t * const p_data);
void dc_set_eps2_bp_inst0_charger_zr_data(DATA_CACHE_Eps2Inst0ChargerZrType_t * const p_new_data);

dc_data_status_t dc_get_fdir_eps_ii_bp_inst0_cmd_exec_status_data(DATA_CACHE_Eps2Inst0_FDIR_CMD_EXEC_STATUS_type_t * const p_data);
void dc_set_fdir_eps_ii_bp_inst0_cmd_exec_status_data(DATA_CACHE_Eps2Inst0_FDIR_CMD_EXEC_STATUS_type_t * const p_new_data);

dc_data_status_t dc_get_eps3_bp_inst0_uptime_in_seconds(DATA_CACHE_Eps3Inst0_UpTimeInSecondsType_t * const p_data);
void dc_set_eps3_bp_inst0_uptime_in_seconds(DATA_CACHE_Eps3Inst0_UpTimeInSecondsType_t * const p_new_data);

dc_data_status_t dc_get_eps3_bp_inst0common(DATA_CACHE_Eps3Inst0CommonMeasurementType_t * const p_data);
void dc_set_eps3_bp_inst0common(DATA_CACHE_Eps3Inst0CommonMeasurementType_t * const p_new_data);

dc_data_status_t dc_get_eps3_bp_inst0hib_mode_status(DATA_CACHE_Eps3Inst0HIBModeStatusType_t * const p_data);
void dc_set_eps3_bp_inst0hib_mode_status(DATA_CACHE_Eps3Inst0HIBModeStatusType_t * const p_new_data);

dc_data_status_t dc_get_eps3_bp_inst0measurements(DATA_CACHE_Eps3Inst0MeasurementsType_t * const p_data);
void dc_set_eps3_bp_inst0measurements(DATA_CACHE_Eps3Inst0MeasurementsType_t * const p_new_data);

dc_data_status_t dc_get_eps3_bp_inst0discharging_state(DATA_CACHE_Eps3Inst0DischargeStateType_t * const p_data);
void dc_set_eps3_bp_inst0discharging_state(DATA_CACHE_Eps3Inst0DischargeStateType_t * const p_new_data);

dc_data_status_t dc_get_eps3_bp_inst0charge_status(DATA_CACHE_Eps3Inst0ChargeOnStatusType_t * const p_data);
void dc_set_eps3_bp_inst0charge_status(DATA_CACHE_Eps3Inst0ChargeOnStatusType_t * const p_new_data);

dc_data_status_t dc_get_eps3_bp_inst0balancers_status(DATA_CACHE_Eps3Inst0BalancersStatusType_t * const p_data);
void dc_set_eps3_bp_inst0balancers_status(DATA_CACHE_Eps3Inst0BalancersStatusType_t * const p_new_data);

dc_data_status_t dc_get_eps3_bp_inst0battery_cells_status(DATA_CACHE_Eps3Inst0BatteryCellsStatusType_t * const p_data);
void dc_set_eps3_bp_inst0battery_cells_status(DATA_CACHE_Eps3Inst0BatteryCellsStatusType_t * const p_new_data);

dc_data_status_t dc_get_eps3_bp_inst0heaters_status(DATA_CACHE_Eps3Inst0HeatersStatusType_t * const p_data);
void dc_set_eps3_bp_inst0heaters_status(DATA_CACHE_Eps3Inst0HeatersStatusType_t * const p_new_data);

dc_data_status_t dc_get_eps3_bp_inst0_cmd_exec_status_data(DATA_CACHE_Eps3Inst0_FDIR_CMD_EXEC_STATUS_type_t * const p_data);
void dc_set_eps3_bp_inst0_cmd_exec_status_data(DATA_CACHE_Eps3Inst0_FDIR_CMD_EXEC_STATUS_type_t * const p_new_data);

dc_data_status_t dc_get_dumb_data(DATA_CACHE_VoltAmps_t * const p_data);
void dc_set_dumb_data(DATA_CACHE_VoltAmps_t * const p_new_data);

dc_data_status_t dc_get_dumb_data1(DATA_CACHE_VoltAllAmps_t * const p_data);
void dc_set_dumb_data1(DATA_CACHE_VoltAllAmps_t * const p_new_data);

dc_data_status_t dc_get_dumb_data3(DATA_CACHE_MpptState_str_t * const p_data);
void dc_set_dumb_data3(DATA_CACHE_MpptState_str_t * const p_new_data);

dc_data_status_t dc_get_dumb_data4(DATA_CACHE_ReadEnDftStatus_t * const p_data);
void dc_set_dumb_data4(DATA_CACHE_ReadEnDftStatus_t * const p_new_data);

dc_data_status_t dc_get_dumb_data5(DATA_CACHE_OnOffStatus_t * const p_data);
void dc_set_dumb_data5(DATA_CACHE_OnOffStatus_t * const p_new_data);

dc_data_status_t dc_get_dumb_data6(DATA_CACHE_ReadLvlState_t * const p_data);
void dc_set_dumb_data6(DATA_CACHE_ReadLvlState_t * const p_new_data);

dc_data_status_t dc_get_eps3_pdm_a_inst0_uptime_in_seconds(DATA_CACHE_Eps3_PDM_A_Inst0_UpTimeInSecondsType_t * const p_data);
void dc_set_eps3_pdm_a_inst0_uptime_in_seconds(DATA_CACHE_Eps3_PDM_A_Inst0_UpTimeInSecondsType_t * const p_new_data);

dc_data_status_t dc_get_eps3_pdm_a_inst0_common(DATA_CACHE_Eps3_PDM_A_Inst0_CommonMesurementsType_t * const p_data);
void dc_set_eps3_pdm_a_inst0_common(DATA_CACHE_Eps3_PDM_A_Inst0_CommonMesurementsType_t * const p_new_data);

dc_data_status_t dc_get_eps3_pdm_a_inst0_hib_mode(DATA_CACHE_Eps3_PDM_A_Inst0_HibModeType_t * const p_data);
void dc_set_eps3_pdm_a_inst0_hib_mode(DATA_CACHE_Eps3_PDM_A_Inst0_HibModeType_t * const p_new_data);

dc_data_status_t dc_get_eps3_pdm_a_inst0_general_outputs(DATA_CACHE_Eps3_PDM_A_Inst0_OutputsStatusType_t * const p_data);
void dc_set_eps3_pdm_a_inst0_general_outputs(DATA_CACHE_Eps3_PDM_A_Inst0_OutputsStatusType_t * const p_new_data);

dc_data_status_t dc_get_eps3_pdm_a_inst0_general_faults(DATA_CACHE_Eps3_PDM_A_Inst0_FaultsStatusType_t * const p_data);
void dc_set_eps3_pdm_a_inst0_general_faults(DATA_CACHE_Eps3_PDM_A_Inst0_FaultsStatusType_t * const p_new_data);

dc_data_status_t dc_get_eps3_pdm_a_inst0_all_measurements(DATA_CACHE_Eps3_PDM_A_Inst0_VoltAmpsMeasurementsType_t * const p_data);
void dc_set_eps3_pdm_a_inst0_all_measurements(DATA_CACHE_Eps3_PDM_A_Inst0_VoltAmpsMeasurementsType_t * const p_new_data);

dc_data_status_t dc_get_eps3_pdm_a_inst0_cmd_exec_status_data(DATA_CACHE_Eps3_PDM_A_Inst0_FDIR_CMD_EXEC_STATUS_type_t * const p_data);
void dc_set_eps3_pdm_a_inst0_cmd_exec_status_data(DATA_CACHE_Eps3_PDM_A_Inst0_FDIR_CMD_EXEC_STATUS_type_t * const p_new_data);

dc_data_status_t dc_get_eps3_pdm_b_inst0_cmd_exec_status_data(DATA_CACHE_Eps3_PDM_B_Inst0_FDIR_CMD_EXEC_STATUS_type_t * const p_data);
void dc_set_eps3_pdm_b_inst0_cmd_exec_status_data(DATA_CACHE_Eps3_PDM_B_Inst0_FDIR_CMD_EXEC_STATUS_type_t * const p_new_data);

dc_data_status_t dc_get_eps3_pdm_b_inst0_uptime_in_seconds(DATA_CACHE_Eps3_PDM_B_Inst0_UpTimeInSecondsType_t * const p_data);
void dc_set_eps3_pdm_b_inst0_uptime_in_seconds(DATA_CACHE_Eps3_PDM_B_Inst0_UpTimeInSecondsType_t * const p_new_data);

dc_data_status_t dc_get_eps3_pdm_b_inst0_common(DATA_CACHE_Eps3_PDM_B_Inst0_CommonMeasurementType_t * const p_data);
void dc_set_eps3_pdm_b_inst0_common(DATA_CACHE_Eps3_PDM_B_Inst0_CommonMeasurementType_t * const p_new_data);

dc_data_status_t dc_get_eps3_pdm_b_inst0_hib_mode(DATA_CACHE_Eps3_PDM_B_Inst0_hib_mode_Type_t * const p_data);
void dc_set_eps3_pdm_b_inst0_hib_mode(DATA_CACHE_Eps3_PDM_B_Inst0_hib_mode_Type_t * const p_new_data);

dc_data_status_t dc_get_eps3_pdm_b_inst0_general_outputs(DATA_CACHE_Eps3_PDM_B_Inst0_OutputsStatus_type_t * const p_data);
void dc_set_eps3_pdm_b_inst0_general_outputs(DATA_CACHE_Eps3_PDM_B_Inst0_OutputsStatus_type_t * const p_new_data);

dc_data_status_t dc_get_eps3_pdm_b_inst0_channel_flag_state(DATA_CACHE_Eps3_PDM_B_Inst0_ChannelFlagState_type_t * const p_data);
void dc_set_eps3_pdm_b_inst0_channel_flag_state(DATA_CACHE_Eps3_PDM_B_Inst0_ChannelFlagState_type_t * const p_new_data);

dc_data_status_t dc_get_eps3_pdm_b_inst0_temperature(DATA_CACHE_Eps3_PDM_B_Inst0_Temps_type_t * const p_data);
void dc_set_eps3_pdm_b_inst0_temperature(DATA_CACHE_Eps3_PDM_B_Inst0_Temps_type_t * const p_new_data);

dc_data_status_t dc_get_eps3_pdm_b_inst0_all_measurements(DATA_CACHE_Eps3_PDM_B_Inst0_VoltAmpsMeasurements_type_t * const p_data);
void dc_set_eps3_pdm_b_inst0_all_measurements(DATA_CACHE_Eps3_PDM_B_Inst0_VoltAmpsMeasurements_type_t * const p_new_data);

dc_data_status_t dc_get_eps3_expander_inst0_cmd_exec_status_data(DATA_CACHE_Eps3_EXPANDER_Inst0_FDIR_CMD_EXEC_STATUS_type_t * const p_data);
void dc_set_eps3_expander_inst0_cmd_exec_status_data(DATA_CACHE_Eps3_EXPANDER_Inst0_FDIR_CMD_EXEC_STATUS_type_t * const p_new_data);

dc_data_status_t dc_get_eps3_expander_inst0_uptime_in_seconds(DATA_CACHE_Eps3_EXPANDER_Inst0_UpTimeInSecondsType_t * const p_data);
void dc_set_eps3_expander_inst0_uptime_in_seconds(DATA_CACHE_Eps3_EXPANDER_Inst0_UpTimeInSecondsType_t * const p_new_data);

dc_data_status_t dc_get_eps3_expander_inst0_common(DATA_CACHE_Eps3_EXPANDER_Inst0_CommonMeasurementType_t * const p_data);
void dc_set_eps3_expander_inst0_common(DATA_CACHE_Eps3_EXPANDER_Inst0_CommonMeasurementType_t * const p_new_data);

dc_data_status_t dc_get_eps3_expander_inst0_outputs(DATA_CACHE_Eps3_EXPANDER_Inst0_DigitalOutputsType_t * const p_data);
void dc_set_eps3_expander_inst0_outputs(DATA_CACHE_Eps3_EXPANDER_Inst0_DigitalOutputsType_t * const p_new_data);

dc_data_status_t dc_get_eps3_expander_inst0_general_inputs(DATA_CACHE_Eps3_EXPANDER_Inst0_GeneralInputType_t * const p_data);
void dc_set_eps3_expander_inst0_general_inputs(DATA_CACHE_Eps3_EXPANDER_Inst0_GeneralInputType_t * const p_new_data);

dc_data_status_t dc_get_eps3_expander_inst0_feedbacks(DATA_CACHE_Eps3_EXPANDER_Inst0_FeedbackType_t * const p_data);
void dc_set_eps3_expander_inst0_feedbacks(DATA_CACHE_Eps3_EXPANDER_Inst0_FeedbackType_t * const p_new_data);

dc_data_status_t dc_get_eps3_expander_inst0_volt_amp_measurements(DATA_CACHE_Eps3_EXPANDER_Inst0_CurrentLimitersType_t * const p_data);
void dc_set_eps3_expander_inst0_volt_amp_measurements(DATA_CACHE_Eps3_EXPANDER_Inst0_CurrentLimitersType_t * const p_new_data);

dc_data_status_t dc_get_eps3_input_stage_inst0_uptime_in_seconds(DATA_CACHE_Eps3_INPUT_STAGE_Inst0_UpTimeInSecondsType_t * const p_data);
void dc_set_eps3_input_stage_inst0_uptime_in_seconds(DATA_CACHE_Eps3_INPUT_STAGE_Inst0_UpTimeInSecondsType_t * const p_new_data);

dc_data_status_t dc_get_eps3_input_stage_inst0common(DATA_CACHE_Eps3_INPUT_STAGE_Inst0CommonMeasurementType_t * const p_data);
void dc_set_eps3_input_stage_inst0common(DATA_CACHE_Eps3_INPUT_STAGE_Inst0CommonMeasurementType_t * const p_new_data);

dc_data_status_t dc_get_eps3_input_stage_inst0hib_mode_status(DATA_CACHE_Eps3_INPUT_STAGE_Inst0hib_mode_status_type_t * const p_data);
void dc_set_eps3_input_stage_inst0hib_mode_status(DATA_CACHE_Eps3_INPUT_STAGE_Inst0hib_mode_status_type_t * const p_new_data);

dc_data_status_t dc_get_eps3_input_stage_inst0selflock_on(DATA_CACHE_Eps3_INPUT_STAGE_Inst0selflock_on_type_t * const p_data);
void dc_set_eps3_input_stage_inst0selflock_on(DATA_CACHE_Eps3_INPUT_STAGE_Inst0selflock_on_type_t * const p_new_data);

dc_data_status_t dc_get_eps3_input_stage_inst0sp1(DATA_CACHE_Eps3_INPUT_STAGE_Inst0Sp1InputDataType_t * const p_data);
void dc_set_eps3_input_stage_inst0sp1(DATA_CACHE_Eps3_INPUT_STAGE_Inst0Sp1InputDataType_t * const p_new_data);

dc_data_status_t dc_get_eps3_input_stage_inst0sp2(DATA_CACHE_Eps3_INPUT_STAGE_Inst0Sp2InputDataType_t * const p_data);
void dc_set_eps3_input_stage_inst0sp2(DATA_CACHE_Eps3_INPUT_STAGE_Inst0Sp2InputDataType_t * const p_new_data);

dc_data_status_t dc_get_eps3_input_stage_inst0sp3(DATA_CACHE_Eps3_INPUT_STAGE_Inst0Sp3InputDataType_t * const p_data);
void dc_set_eps3_input_stage_inst0sp3(DATA_CACHE_Eps3_INPUT_STAGE_Inst0Sp3InputDataType_t * const p_new_data);

dc_data_status_t dc_get_eps3_input_stage_inst0system_bus(DATA_CACHE_Eps3_INPUT_STAGE_Inst0SystemBusType_t * const p_data);
void dc_set_eps3_input_stage_inst0system_bus(DATA_CACHE_Eps3_INPUT_STAGE_Inst0SystemBusType_t * const p_new_data);

dc_data_status_t dc_get_eps3_input_stage_inst0bus_7v5(DATA_CACHE_Eps3_INPUT_STAGE_Inst0Bus7v5Type_t * const p_data);
void dc_set_eps3_input_stage_inst0bus_7v5(DATA_CACHE_Eps3_INPUT_STAGE_Inst0Bus7v5Type_t * const p_new_data);

dc_data_status_t dc_get_eps3_input_stage_inst0bus_7v5_power_good(DATA_CACHE_Eps3_INPUT_STAGE_Inst0bus_7v5_power_good_type_t * const p_data);
void dc_set_eps3_input_stage_inst0bus_7v5_power_good(DATA_CACHE_Eps3_INPUT_STAGE_Inst0bus_7v5_power_good_type_t * const p_new_data);

dc_data_status_t dc_get_eps3_input_stage_inst0undervoltage_7v5(DATA_CACHE_Eps3_INPUT_STAGE_Inst0undervoltage_7V5_type_t * const p_data);
void dc_set_eps3_input_stage_inst0undervoltage_7v5(DATA_CACHE_Eps3_INPUT_STAGE_Inst0undervoltage_7V5_type_t * const p_new_data);

dc_data_status_t dc_get_eps3_input_stage_inst0bus_3v3(DATA_CACHE_Eps3_INPUT_STAGE_Inst0Bbus3v3Type_t * const p_data);
void dc_set_eps3_input_stage_inst0bus_3v3(DATA_CACHE_Eps3_INPUT_STAGE_Inst0Bbus3v3Type_t * const p_new_data);

dc_data_status_t dc_get_eps3_input_stage_inst0undervoltage_3v3(DATA_CACHE_Eps3_INPUT_STAGE_Inst0undervoltage_3V3_type_t * const p_data);
void dc_set_eps3_input_stage_inst0undervoltage_3v3(DATA_CACHE_Eps3_INPUT_STAGE_Inst0undervoltage_3V3_type_t * const p_new_data);

dc_data_status_t dc_get_eps3_input_stage_inst0_cmd_exec_status_data(DATA_CACHE_Eps3_INPUT_STAGE_Inst0_FDIR_CMD_EXEC_STATUS_type_t * const p_data);
void dc_set_eps3_input_stage_inst0_cmd_exec_status_data(DATA_CACHE_Eps3_INPUT_STAGE_Inst0_FDIR_CMD_EXEC_STATUS_type_t * const p_new_data);

dc_data_status_t dc_get_magdata(DATA_CACHE_CubeMag_Telemetry_t * const p_data);
void dc_set_magdata(DATA_CACHE_CubeMag_Telemetry_t * const p_new_data);

dc_data_status_t dc_get_wheeldata1(DATA_CACHE_CubeWheel1_Telemetry_t * const p_data);
void dc_set_wheeldata1(DATA_CACHE_CubeWheel1_Telemetry_t * const p_new_data);

dc_data_status_t dc_get_wheeldata2(DATA_CACHE_CubeWheel2_Telemetry_t * const p_data);
void dc_set_wheeldata2(DATA_CACHE_CubeWheel2_Telemetry_t * const p_new_data);

dc_data_status_t dc_get_fss1_data(DATA_CACHE_FSS1_Data_type_t * const p_data);
void dc_set_fss1_data(DATA_CACHE_FSS1_Data_type_t * const p_new_data);

dc_data_status_t dc_get_fss2_data(DATA_CACHE_FSS2_Data_type_t * const p_data);
void dc_set_fss2_data(DATA_CACHE_FSS2_Data_type_t * const p_new_data);

dc_data_status_t dc_get_fss3_data(DATA_CACHE_FSS3_Data_type_t * const p_data);
void dc_set_fss3_data(DATA_CACHE_FSS3_Data_type_t * const p_new_data);

dc_data_status_t dc_get_fss4_data(DATA_CACHE_FSS4_Data_type_t * const p_data);
void dc_set_fss4_data(DATA_CACHE_FSS4_Data_type_t * const p_new_data);

dc_data_status_t dc_get_fss5_data(DATA_CACHE_FSS5_Data_type_t * const p_data);
void dc_set_fss5_data(DATA_CACHE_FSS5_Data_type_t * const p_new_data);

dc_data_status_t dc_get_adcs_fss_data(DATA_CACHE_ADCS_FSS_t * const p_data);
void dc_set_adcs_fss_data(DATA_CACHE_ADCS_FSS_t * const p_new_data);

dc_data_status_t dc_get_adcs_mag_data(DATA_CACHE_ADCS_MAG_t * const p_data);
void dc_set_adcs_mag_data(DATA_CACHE_ADCS_MAG_t * const p_new_data);

dc_data_status_t dc_get_adcs_imu_data(DATA_CACHE_ADCS_IMU_t * const p_data);
void dc_set_adcs_imu_data(DATA_CACHE_ADCS_IMU_t * const p_new_data);

dc_data_status_t dc_get_adcs_rw_data(DATA_CACHE_ADCS_RW_t * const p_data);
void dc_set_adcs_rw_data(DATA_CACHE_ADCS_RW_t * const p_new_data);

dc_data_status_t dc_get_adcs_mtq_data(DATA_CACHE_ADCS_MTQ_t * const p_data);
void dc_set_adcs_mtq_data(DATA_CACHE_ADCS_MTQ_t * const p_new_data);

dc_data_status_t dc_get_eps2_bp_inst0_sbpmodechange_data(DATA_CACHE_SBpModeChangeInfo_t * const p_data);
void dc_set_eps2_bp_inst0_sbpmodechange_data(DATA_CACHE_SBpModeChangeInfo_t * const p_new_data);

dc_data_status_t dc_get_eps2_bp_bpmodesmrollingtrace_data(DATA_CACHE_Eps2Inst0_BpModeSmRollingTrace_type_t * const p_data);
void dc_set_eps2_bp_bpmodesmrollingtrace_data(DATA_CACHE_Eps2Inst0_BpModeSmRollingTrace_type_t * const p_new_data);

dc_data_status_t dc_get_eps2_pdm_sbsede_conopsmode_data(DATA_CACHE_EPSII_PDM_SBSEDE_ConopsMode_t * const p_data);
void dc_set_eps2_pdm_sbsede_conopsmode_data(DATA_CACHE_EPSII_PDM_SBSEDE_ConopsMode_t * const p_new_data);

dc_data_status_t dc_get_eps2_pdm_sbsed_bitmask_data(DATA_CACHE_EPSII_PDM_1_SBSED_Bitmask_t_t * const p_data);
void dc_set_eps2_pdm_sbsed_bitmask_data(DATA_CACHE_EPSII_PDM_1_SBSED_Bitmask_t_t * const p_new_data);

dc_data_status_t dc_get_eps2_pdm_sbasicsettings_data(DATA_CACHE_EPSII_PDM_1_SBasicSettings_t * const p_data);
void dc_set_eps2_pdm_sbasicsettings_data(DATA_CACHE_EPSII_PDM_1_SBasicSettings_t * const p_new_data);

dc_data_status_t dc_get_eps2_pdm_setbasicsettings_data(DATA_CACHE_EPSII_PDM_1_SetBasicSettings_t * const p_data);
void dc_set_eps2_pdm_setbasicsettings_data(DATA_CACHE_EPSII_PDM_1_SetBasicSettings_t * const p_new_data);

dc_data_status_t dc_get_eps2_pdm_sbs_geterror_data(DATA_CACHE_EPSII_PDM_1_SBS_GetError_t * const p_data);
void dc_set_eps2_pdm_sbs_geterror_data(DATA_CACHE_EPSII_PDM_1_SBS_GetError_t * const p_new_data);

dc_data_status_t dc_get_eps2inst0_pdm_sbasicsettings_data(DATA_CACHE_Eps2Inst0_SBasicSettings_type_t * const p_data);
void dc_set_eps2inst0_pdm_sbasicsettings_data(DATA_CACHE_Eps2Inst0_SBasicSettings_type_t * const p_new_data);

dc_data_status_t dc_get_vn100_data(DATA_CACHE_VN100_Data_type_t * const p_data);
void dc_set_vn100_data(DATA_CACHE_VN100_Data_type_t * const p_new_data);

dc_data_status_t dc_get_mpu6050_1_data(DATA_CACHE_MPU6050_1_Data_type_t * const p_data);
void dc_set_mpu6050_1_data(DATA_CACHE_MPU6050_1_Data_type_t * const p_new_data);

dc_data_status_t dc_get_mpu6050_2_data(DATA_CACHE_MPU6050_2_Data_type_t * const p_data);
void dc_set_mpu6050_2_data(DATA_CACHE_MPU6050_2_Data_type_t * const p_new_data);

dc_data_status_t dc_get_mtq_all_cmd_data(DATA_CACHE_MTQ_ALL_Command_Data_type_t * const p_data);
void dc_set_mtq_all_cmd_data(DATA_CACHE_MTQ_ALL_Command_Data_type_t * const p_new_data);

dc_data_status_t dc_get_eps2inst0_bp_sdiagerrcounter2_data(DATA_CACHE_EPSII_BP_1_SDiagErrCounter2_t * const p_data);
void dc_set_eps2inst0_bp_sdiagerrcounter2_data(DATA_CACHE_EPSII_BP_1_SDiagErrCounter2_t * const p_new_data);

dc_data_status_t dc_get_eps2inst0_bp_getmainapperrcounters2_data(DATA_CACHE_Eps2Inst0__GetMainAppErrCounters2ype_t * const p_data);
void dc_set_eps2inst0_bp_getmainapperrcounters2_data(DATA_CACHE_Eps2Inst0__GetMainAppErrCounters2ype_t * const p_new_data);

dc_data_status_t dc_get_ina_data(DATA_CACHE_INA_Data_type_t * const p_data);
void dc_set_ina_data(DATA_CACHE_INA_Data_type_t * const p_new_data);

dc_data_status_t dc_get_ang_data(DATA_CACHE_ANG_Data_type_t * const p_data);
void dc_set_ang_data(DATA_CACHE_ANG_Data_type_t * const p_new_data);

dc_data_status_t dc_get_camera_mode_data(DATA_CACHE_CAMERA_MODE_Data_type_t * const p_data);
void dc_set_camera_mode_data(DATA_CACHE_CAMERA_MODE_Data_type_t * const p_new_data);

dc_data_status_t dc_get_adcs_mode(DATA_CACHE_ADCS_mode_type_t * const p_data);
void dc_set_adcs_mode(DATA_CACHE_ADCS_mode_type_t * const p_new_data);

dc_data_status_t dc_get_adcs_flag_alg(DATA_CACHE_ADCS_flag_alg_type_t * const p_data);
void dc_set_adcs_flag_alg(DATA_CACHE_ADCS_flag_alg_type_t * const p_new_data);

dc_data_status_t dc_get_adcs_result(DATA_CACHE_ADCS_result_type_t * const p_data);
void dc_set_adcs_result(DATA_CACHE_ADCS_result_type_t * const p_new_data);

dc_data_status_t dc_get_adcs_hw(DATA_CACHE_ADCS_HW_type_t * const p_data);
void dc_set_adcs_hw(DATA_CACHE_ADCS_HW_type_t * const p_new_data);

dc_data_status_t dc_get_tc_flag(DATA_CACHE_CubeSpace_Telecommand_Flag_t * const p_data);
void dc_set_tc_flag(DATA_CACHE_CubeSpace_Telecommand_Flag_t * const p_new_data);

dc_data_status_t dc_get_wheelcommand1(DATA_CACHE_CubeWheel1_Telecommand_t * const p_data);
void dc_set_wheelcommand1(DATA_CACHE_CubeWheel1_Telecommand_t * const p_new_data);

dc_data_status_t dc_get_wheelcommand2(DATA_CACHE_CubeWheel2_Telecommand_t * const p_data);
void dc_set_wheelcommand2(DATA_CACHE_CubeWheel2_Telecommand_t * const p_new_data);

dc_data_status_t dc_get_magcommand(DATA_CACHE_CubeMag_Telecommand_t * const p_data);
void dc_set_magcommand(DATA_CACHE_CubeMag_Telecommand_t * const p_new_data);


/*!
* @brief Provides raw data access to individual data cache entries.
* @param id identifier of the DC entry to access
* @param p_data a pointer to the buffer where the DC entry bytes shall be written
* @param user_buf_size size in bytes of the user-provided buffer
* @param start_offset initial offset where to copy from
* @param bytes_to_read number of bytes to read starting from start_offset position
*
* @return DC entry data status
*
* @note Users have to provide a buffer >= to the size of the DC entry, otherwise the
*       operation will assert if debugging is turned on.
*/
dc_data_status_t dc_get_raw_data(const dc_did_id id,
                                 void * const p_data,
                                 const uint32_t user_buf_size,
                                 const uint32_t start_offset,
                                 const uint32_t bytes_to_read);

/*!
* @brief Used to update a DC entry as a binary blob.
* @param input_type identifies how data is fed to the DataCache (e.g. internally by the system or through a simulation interface)
* @param id identifier of the DC entry to update
* @param p_new_data a pointer to the buffer where the new DC entry data shall be copied from
* @param data_size size in bytes of the user-provided buffer
*/
void dc_set_raw_data(const dc_data_input_t input_type, const dc_did_id id, const void * const p_new_data, const uint32_t data_size);

/*!
* @brief Provides the size in bytes of a DC entry given its unique id
* @param id identifier of the requested DC entry
*
* @return size in bytes of the DC binary block
*/
uint32_t dc_get_data_size(const dc_did_id id);

/*!
* @brief Provides the internal item index based on the data attribute idenitifier defined in your FIDL file
* @param type_id ID from FIDL file for the corresponding DataCache attribute entry
*
* @return internal ID which can directly be used with DataCache APIs
*/
dc_did_id dc_get_index_by_data_id(const uint16_t attr_id);

/*!
* @brief Sets the input mode for one or all DataCache entries.
* @param id ID from FIDL file for the corresponding DataCache attribute entry
*           (if DC_DID_MAX specified, all entries get updated)
* @param input_type specifies the input type to use for the specified entry
*/
void dc_set_input_mode(const dc_did_id id, dc_data_input_t input_type);

/**********************************************************************
 *
 *  Shared defines
 *
 **********************************************************************/

#ifdef __cplusplus
}
#endif  // #ifdef __cplusplus

#endif  // #ifndef DATACACHE_H

