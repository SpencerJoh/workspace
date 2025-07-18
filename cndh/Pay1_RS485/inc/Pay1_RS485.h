#ifndef PAY1_RS485_Magnetometer_Reactionwheel_SEUNGWON_INC_H_
#define PAY1_RS485_Magnetometer_Reactionwheel_SEUNGWON_INC_H_

#include "main.h"
#include "cmsis_os2.h"
#include <string.h>
#include "stm32h7xx.h"
#include "trace.h"
#include "es_exeh.h"
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdint.h>
#include <stddef.h>
#include <stdio.h>

#define MainOBC          240
#define Magnetometer     1
#define ReactionWheel1    2     // CubeWheel 24307
#define ReactionWheel2    3     // CubeWheel 24308

#define ESC  0x1F  // Escape
#define SOM  0x80  // Start of Message
#define SOR  0x08  // Start of Response
#define EOM  0xFF  // End of Message

#define MAX_PACKET_LENGTH 64


// typedef struct
// {
//     uint16_t      pin;
//     GPIO_TypeDef *port;
// } uart4_driver_pin;

// typedef struct
// {
//     uart4_driver_pin nRE;
//     uart4_driver_pin DE;
//     uart4_driver_pin TE;
//     uart4_driver_pin Tx;
//     uart4_driver_pin Rx;
// } uart4_driver_pins_t;

// typedef struct
// {
//     uart4_driver_pin Tx;
//     uart4_driver_pin Rx;
// } uart4_ADCS_PILS_driver_pins_t;


typedef struct {
    uint16_t pin;
    GPIO_TypeDef *port;
} uart6_driver_pin;

typedef struct {
    uart6_driver_pin nRE;
    uart6_driver_pin DE;
    uart6_driver_pin TE;
    uart6_driver_pin Tx;
    uart6_driver_pin Rx;
} uart6_driver_pins_t;

typedef enum {
    RedundantMagnetometerMeasurement_ID = 193,
    PrimaryMagnetometerMeasurement_ID = 197
} TCTLM_ID;

typedef struct {
    TCTLM_ID id;
    uint8_t data_byte;
} TCTLM_DataSize_t;

static const TCTLM_DataSize_t TCTLM_DataSizes[] = {
    { PrimaryMagnetometerMeasurement_ID,          13 }
};



/* ------------- CubeMag TCTLM ------------- */
 // CubeMag Config Telemetry Format (ID: 186)
// Frame Length: 4 bytes
typedef struct __attribute__((packed)) {
    uint8_t PreferredPrimaryMagnetometer : 4;    // bits 0-3, ENUM
    uint8_t CurrentPrimaryMagnetometer   : 4;    // bits 4-7, ENUM
    uint16_t DeployTimeout;                      // bits 8-23, UINT (Unit: [mS])
    uint8_t PrimaryAutoSelect           : 1;     // bit 24, BOOL
    uint8_t Reserved                    : 7;     // bits 25-31, unused
} CubeMagConfig_t;                              // ID: 186



typedef struct __attribute__((packed)) {    // padding 방지
    float X_axis;
    float Y_axis;
    float Z_axis;
    bool DataValid;
} MagnetometerMeasurement_t;


// Unit of measure: [mA]
// Frame Length: 5 bytes
typedef struct __attribute__((packed)) {
    uint32_t BurnCurrent;            // 32 bits (4 bytes)
    bool DeploymentPinState    : 1;  // bit 32
    bool BurnPinState          : 1;  // bit 33
    bool BurnUnderCurrent      : 1;  // bit 34
    bool BurnOverCurrent       : 1;  // bit 35
    bool DeploymentTimeout     : 1;  // bit 36
    // 나머지 3비트는 미사용
} DeploymentStatus_t;               // ID: 190


typedef enum {
    MAG_SVC_DEPLOY_ARM = 0,
    MAG_SVC_DEPLOY     = 1,
    MAG_SVC_IDLE       = 2,
    MAG_SVC_ERROR      = 3
} MagServiceState_t;

typedef enum {
    MNT_SVC_OFF     = 0,
    MNT_SVC_INIT    = 1,
    MNT_SVC_IDLE    = 2,
    MNT_SVC_AUTO    = 3,
    MNT_SVC_SAMPLE  = 4,
    MNT_SVC_ERROR   = 5
} MagnetometerState_t;

typedef struct __attribute__((packed)) {
    MagServiceState_t MagSvcState;
    MagnetometerState_t PrimaryMagState;
    MagnetometerState_t RedundantMagState;
} AllServiceStates_t;                  // ID: 188


/* ------------- CubeMag TCTLM ------------- */

/* ------------- CubeWheel TCTLM ------------- */
// typedef struct {
//     float Kp;
//     float Ki;
//     float Kd;
// } MainGain_t; // ID: 193


// Table 52: Wheel Reference Torque Telemetry Format (ID: 186)
// Frame Length: 4 bytes
typedef struct __attribute__((packed)) {
    float ReferenceTorque;              // 32 bits, FLOAT, Unit: [mNm]
} WheelReferenceTorque_t;              // ID: 186

// Table 55: Wheel Speed Telemetry Format (ID: 188)  
// Frame Length: 5 bytes
typedef struct __attribute__((packed)) {
    float WheelSpeed;                   // bits 0-31, FLOAT, Unit: [RPM]
    uint8_t WheelErrorState;            // bits 32-39, ENUM (Table 48)
} WheelSpeedTelemetry_t;               // ID: 188

// Table 63: Wheel Reference Speed Telemetry Format (ID: 196)
// Frame Length: 4 bytes
typedef struct __attribute__((packed)) {
    float ReferenceSpeed;               // 32 bits, FLOAT, Unit: [RPM]
} WheelReferenceSpeed_t;               // ID: 196

// Table 64: Motor Power Telemetry Format (ID: 197)
// Frame Length: 1 byte
typedef struct __attribute__((packed)) {
    bool MotorPowerSwitch : 1;          // bit 0, BOOL
    uint8_t Reserved      : 7;          // bits 1-7, unused
} MotorPowerTelemetry_t;               // ID: 197

/* ------------- CubeWheel TCTLM ------------- */
extern CubeMagConfig_t CubeMagConfig_TLM;
extern CubeMagConfig_t CubeMagConfig_TC;
extern MagnetometerMeasurement_t Primary;        // ID: 197
extern MagnetometerMeasurement_t Redundant;      // ID: 193
extern AllServiceStates_t AllServiceStates;
extern DeploymentStatus_t DeploymentStatus;

extern WheelReferenceTorque_t WheelReferenceTorque1, WheelReferenceTorque2;
extern WheelSpeedTelemetry_t WheelSpeed1, WheelSpeed2;
extern WheelReferenceSpeed_t WheelReferenceSpeed1, WheelReferenceSpeed2;
extern MotorPowerTelemetry_t MotorPower1, MotorPower2;



/* ================ function prototypes ================ */

/**
* \brief STM32 UART6 Interrupt handler callback
*/
void USART6_IRQHandler(void);
void convert_packet_1f1f_to_1f(uint8_t *data);

void U6_RS485_Init(void);
void RS485_TEST_Task(void *arg);
void RS485_ProcessEvents(UART_HandleTypeDef *huart);
void RS485_TxMode(void);
void RS485_RxMode(void);

void RS485_TCTLM(uint8_t ID, uint32_t DATA);
void resend_TCTLM(void);
void HAL_UART_TxCpltCallback(UART_HandleTypeDef *huart);
// void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart);
void NACK_handler(void);
void HAL_UART_IDLE_Callback(UART_HandleTypeDef *huart);
void RS485_ProcessEvents(UART_HandleTypeDef *huart);
void DataParsing(uint8_t *data);
void flush_buffer(uint8_t *buffer);
uint8_t getDataLengthById(TCTLM_ID id);


#endif /* PAY1_RS485_Magnetometer_Reactionwheel_SEUNGWON_INC_H_*/