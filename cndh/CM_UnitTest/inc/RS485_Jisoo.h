#ifndef ESPF_ARCH_STM32H753IIT_DRIVERS_RS485_JISOO_INC_RS485_JISOO_H_
#define ESPF_ARCH_STM32H753IIT_DRIVERS_RS485_JISOO_INC_RS485_JISOO_H_

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
#define ReactionWheel    1
#define Magnetometer     1

#define ESC  0x1F  // Escape
#define SOM  0x80  // Start of Message
#define SOR  0x08  // Start of Response
#define EOM  0xFF  // End of Message

#define MAX_PACKET_LENGTH 64


typedef struct
{
    uint16_t      pin;
    GPIO_TypeDef *port;
} uart4_driver_pin;

typedef struct
{
    uart4_driver_pin nRE;
    uart4_driver_pin DE;
    uart4_driver_pin TE;
    uart4_driver_pin Tx;
    uart4_driver_pin Rx;
} uart4_driver_pins_t;

typedef struct
{
    uart4_driver_pin Tx;
    uart4_driver_pin Rx;
} uart4_ADCS_PILS_driver_pins_t;


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

// Unit of measure: [nT]
// Frame Length: 13 bytes
// {32bits, 32bits, 32bits, 1bit}

/*
typedef struct __attribute__((packed)) {    // padding 방지
    float X_axis;
    float Y_axis;
    float Z_axis;
    bool DataValid;
} PrimaryMagnetometerMeasurement;   // ID: 197

typedef struct __attribute__((packed)) {    // padding 방지
    float X_axis;
    float Y_axis;
    float Z_axis;
    bool DataValid;
} RedundantMagnetometerMeasurement;  // ID: 193
*/

typedef struct __attribute__((packed)) {    // padding 방지
    float X_axis;
    float Y_axis;
    float Z_axis;
    bool DataValid;
} MagnetometerMeasurement_t;

typedef MagnetometerMeasurement_t Primary;        // ID: 197
typedef MagnetometerMeasurement_t Redundant;      // ID: 193



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
typedef struct {
    float Kp;
    float Ki;
    float Kd;
} MainGain; // ID: 193

/* ------------- CubeWheel TCTLM ------------- */




/* ================ function prototypes ================ */

/**
* \brief STM32 UART6 Interrupt handler callback
*/
void USART6_IRQHandler(void);
// 굳이 헤더파일에 선언 안해도 되는 것 같음, 만약 내가 이 함수를 직접 호출해서 사용하면 선언필요.


void U6_RS485_Init(void);
void RS485_TEST_Task(void *arg);
void RS485_ProcessEvents(UART_HandleTypeDef *huart);


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


#endif /* ESPF_ARCH_STM32H753IIT_DRIVERS_RS485_JISOO_INC_RS485_JISOO_H_ */
