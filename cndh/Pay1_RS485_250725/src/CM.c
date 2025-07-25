#include "../inc/Pay1_RS485.h"
INIT_CMP_LOGGER(true, TRACE_LVL_DEBUG)

static UART_HandleTypeDef huart6 = { 0 };

static uart6_driver_pins_t U6_RS485_Driver_Pins = {
    // RS485 Interface pin: H1:34 RS-485 B, H1:36 RS-485 A
    .DE  = { GPIO_PIN_8, GPIOG },
    .nRE = { GPIO_PIN_13, GPIOG },
    .TE  = { GPIO_PIN_13, GPIOD },
    .Tx  = { GPIO_PIN_6, GPIOC },
    .Rx  = { GPIO_PIN_7, GPIOC }
};

static uint32_t baud_rates[] = { 9600, 115200, 230400, 460800, 921600, 2000000U, 3300000U };
static uart6_driver_pins_t *p_U6_RS485_driver_Pins;
static osThreadId_t RS485_TEST_Task_taskHandle;
// static osThreadId_t RS485_testing_task_taskHandle;
// static const osThreadAttr_t RS485_testing_task_attributes = {
//     .name = "RS485_testing_task",
//     .priority = (osPriority_t) osPriorityNormal,
//     .stack_size = 128 * 16
// };
static const osThreadAttr_t RS485_TEST_Task_attributes = {
    .name = "RS485_TEST_Task",
    .priority = (osPriority_t) osPriorityNormal,
    .stack_size = 128 * 16
};

static void demo_uart6_DriverEnable(void);
static void demo_uart6_DriverDisable(void);
static void demo_uart6_ReceptionEnable(void);
static void demo_uart6_ReceptionDisable(void);
static void uart6_init(uint32_t baudrate);
// static void uart6_deinit(void);

static void demo_uart6_DriverEnable(void)
{
    // RTS ACTIVE (Driver Enable)
    HAL_GPIO_WritePin(p_U6_RS485_driver_Pins->DE.port, p_U6_RS485_driver_Pins->DE.pin, GPIO_PIN_SET);
}

static void demo_uart6_DriverDisable(void)
{
    // RTS INACTIVE (Driver Disable)
    HAL_GPIO_WritePin(p_U6_RS485_driver_Pins->DE.port, p_U6_RS485_driver_Pins->DE.pin, GPIO_PIN_RESET);
}

static void demo_uart6_ReceptionEnable(void)
{
    // RE ACTIVE (Receive Enable)
    HAL_GPIO_WritePin(p_U6_RS485_driver_Pins->nRE.port, p_U6_RS485_driver_Pins->nRE.pin, GPIO_PIN_RESET);
}

static void demo_uart6_ReceptionDisable(void)
{
    // RE INACTIVE (Receive Disable)
    HAL_GPIO_WritePin(p_U6_RS485_driver_Pins->nRE.port, p_U6_RS485_driver_Pins->nRE.pin, GPIO_PIN_SET);
}

static void uart6_init(uint32_t baudrate)
{
    GPIO_InitTypeDef GPIO_InitStruct = { 0 };

    /* Peripheral clock enable */
    __HAL_RCC_USART6_CLK_ENABLE();
    __HAL_RCC_GPIOC_CLK_ENABLE();
    __HAL_RCC_GPIOD_CLK_ENABLE();
    __HAL_RCC_GPIOF_CLK_ENABLE();

    /*Configure GPIO pin : Tx_Pin */
    GPIO_InitStruct.Pin       = p_U6_RS485_driver_Pins->Tx.pin;
    GPIO_InitStruct.Mode      = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull      = GPIO_NOPULL;
    GPIO_InitStruct.Speed     = GPIO_SPEED_FREQ_VERY_HIGH;
    GPIO_InitStruct.Alternate = GPIO_AF7_USART6;
    HAL_GPIO_Init(p_U6_RS485_driver_Pins->Tx.port, &GPIO_InitStruct);

    /*Configure GPIO pin : Rx_Pin */
    GPIO_InitStruct.Pin       = p_U6_RS485_driver_Pins->Rx.pin;
    GPIO_InitStruct.Mode      = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull      = GPIO_NOPULL;
    GPIO_InitStruct.Speed     = GPIO_SPEED_FREQ_VERY_HIGH;
    GPIO_InitStruct.Alternate = GPIO_AF7_USART6;
    HAL_GPIO_Init(p_U6_RS485_driver_Pins->Rx.port, &GPIO_InitStruct);

    /*Configure GPIO pin : DE_Pin (RTS) */
    GPIO_InitStruct.Pin   = p_U6_RS485_driver_Pins->DE.pin;
    GPIO_InitStruct.Mode  = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull  = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    HAL_GPIO_Init(p_U6_RS485_driver_Pins->DE.port, &GPIO_InitStruct);

    /*Configure GPIO pin : TE_Pin */
    GPIO_InitStruct.Pin   = p_U6_RS485_driver_Pins->TE.pin;
    GPIO_InitStruct.Mode  = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull  = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    HAL_GPIO_Init(p_U6_RS485_driver_Pins->TE.port, &GPIO_InitStruct);

    /*Configure GPIO pin : nRE_Pin */
    GPIO_InitStruct.Pin   = p_U6_RS485_driver_Pins->nRE.pin;
    GPIO_InitStruct.Mode  = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull  = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    HAL_GPIO_Init(p_U6_RS485_driver_Pins->nRE.port, &GPIO_InitStruct);

    // Receive Enable ACTIVE
    demo_uart6_ReceptionEnable();

    // Termination Enable ACTIVE
    HAL_GPIO_WritePin(p_U6_RS485_driver_Pins->TE.port, p_U6_RS485_driver_Pins->TE.pin, GPIO_PIN_SET);

    // Start with a disabled communication driver...
    demo_uart6_DriverDisable();

    huart6.Instance                    = USART6;
    huart6.Init.BaudRate               = baudrate;
    huart6.Init.WordLength             = UART_WORDLENGTH_8B;
    huart6.Init.StopBits               = UART_STOPBITS_1;
    huart6.Init.Parity                 = UART_PARITY_NONE;
    huart6.Init.Mode                   = UART_MODE_TX_RX;
    huart6.Init.HwFlowCtl              = UART_HWCONTROL_NONE;
    huart6.Init.OverSampling           = UART_OVERSAMPLING_16;
    huart6.Init.OneBitSampling         = UART_ONE_BIT_SAMPLE_DISABLE;
    huart6.AdvancedInit.AdvFeatureInit = UART_ADVFEATURE_NO_INIT;

    if (HAL_UART_Init(&huart6) != HAL_OK)
    {
        Error_Handler();
    }

   /* USART6 interrupt Init */
   HAL_NVIC_SetPriority(USART6_IRQn, 5, 0);
   HAL_NVIC_EnableIRQ(USART6_IRQn);
}

void USART6_IRQHandler(void)
{
    HAL_UART_IRQHandler(&huart6);
}

// static void uart6_deinit(void)
// {
//     __HAL_RCC_USART6_CLK_DISABLE();
//     HAL_GPIO_DeInit(p_U6_RS485_driver_Pins->Tx.port, p_U6_RS485_driver_Pins->Tx.pin);
//     HAL_GPIO_DeInit(p_U6_RS485_driver_Pins->Rx.port, p_U6_RS485_driver_Pins->Rx.pin);
//     //    HAL_NVIC_DisableIRQ(USART6_IRQn);
// }

//////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////
// DATA_CACHE_CubeSpace_Telecommand_Flag_t tc_flag_copy = {0};

CubeMagConfig_t CubeMagConfig_TLM;
CubeMagConfig_t CubeMagConfig_TC;
MagnetometerMeasurement_t Primary;        // ID: 197
MagnetometerMeasurement_t Redundant;      // ID: 193
AllServiceStates_t AllServiceStates;
DeploymentStatus_t DeploymentStatus;

WheelReferenceTorque_t WheelReferenceTorque1, WheelReferenceTorque2;
WheelSpeedTelemetry_t WheelSpeed1, WheelSpeed2;
WheelReferenceSpeed_t WheelReferenceSpeed1, WheelReferenceSpeed2;
MotorPowerTelemetry_t MotorPower1, MotorPower2;

#define NODE_COUNT  13
uint8_t tx_buffer_TLM[NODE_COUNT][7] = {
    {ESC, SOM, 186, MainOBC, Magnetometer, ESC, EOM},       // CubeMag Config
    {ESC, SOM, 188, MainOBC, Magnetometer, ESC, EOM},       // All Service States
    {ESC, SOM, 190, MainOBC, Magnetometer, ESC, EOM},       // Deployment Status
    {ESC, SOM, 193, MainOBC, Magnetometer, ESC, EOM},       // Redundant Magnetometer Measurement
    {ESC, SOM, 197, MainOBC, Magnetometer, ESC, EOM},       // Primary Magnetometer Measurement

    {ESC, SOM, 186, MainOBC, ReactionWheel1, ESC, EOM},     // Wheel Reference Torque
    {ESC, SOM, 188, MainOBC, ReactionWheel1, ESC, EOM},     // Wheel Speed Measurement
    {ESC, SOM, 196, MainOBC, ReactionWheel1, ESC, EOM},     // Set momentum wheel reference speed
    {ESC, SOM, 197, MainOBC, ReactionWheel1, ESC, EOM},     // Switch motor power on/off

    {ESC, SOM, 186, MainOBC, ReactionWheel2, ESC, EOM},
    {ESC, SOM, 188, MainOBC, ReactionWheel2, ESC, EOM},
    {ESC, SOM, 196, MainOBC, ReactionWheel2, ESC, EOM},
    {ESC, SOM, 197, MainOBC, ReactionWheel2, ESC, EOM},
};





uint8_t tx_buff_CMTC[11];

CubeMagConfig_t CubeMagConfig_TC = {
    .PreferredPrimaryMagnetometer = 0, // ENUM value for preferred primary magnetometer
    .CurrentPrimaryMagnetometer   = 0, // ENUM value for current primary magnetometer
    .DeployTimeout                = 3001, // Deployment timeout in milliseconds
    .PrimaryAutoSelect            = 1, // Auto-select primary magnetometer enabled
    .Reserved                     = 0  // Reserved bits set to zero
};


void build_tx_buffer_CMTC(void);
void testing_CW_TC(void);

void build_tx_buffer_CMTC(void)
{
    tx_buff_CMTC[0] = ESC;
    tx_buff_CMTC[1] = SOM;
    tx_buff_CMTC[2] = 60; // Command ID for CubeMag Config
    tx_buff_CMTC[3] = MainOBC; // Source ID
    tx_buff_CMTC[4] = Magnetometer; // Destination ID
    memcpy(&tx_buff_CMTC[5], &CubeMagConfig_TC, sizeof(CubeMagConfig_TC));
    tx_buff_CMTC[9] = ESC; // Escape character
    tx_buff_CMTC[10] = EOM; // End of message
}




void testing_TC(void);
uint8_t rs485_rx_buffer[MAX_PACKET_LENGTH] = {0};
static volatile uint8_t rs485_TxCplt_flag = 0;
static volatile uint8_t rs485_RxCplt_flag = 0;
static uint16_t count = 0;
uint8_t node_idx = 0;
static uint16_t payload_size = 0;
static uint16_t received_size = 0;
static uint8_t write_idx = 5;
static uint8_t read_idx = 5;

void U6_RS485_Init(void)
{
    p_U6_RS485_driver_Pins = &U6_RS485_Driver_Pins;
    uart6_init(baud_rates[4]);
    RS485_TEST_Task_taskHandle = osThreadNew(RS485_TEST_Task, NULL, &RS485_TEST_Task_attributes);
    // RS485_testing_task_taskHandle = osThreadNew(RS485_testing_task, NULL, &RS485_testing_task_attributes);
}

// void RS485_testing_task(void *argument)
// {
//     ES_TRACE_DEBUG("========= RS485 testing task START ========= \r\n");
    
//     for (;;)
//     {

//     }
// }

void RS485_TEST_Task(void *argument)
{
    ES_TRACE_DEBUG("========= RS485_TEST_Task START ========= \r\n");
    
    testing_TC();
    // RS485_TxMode();
    // build_tx_buffer_CMTC();
    // if (HAL_UART_Transmit_IT(&huart6, tx_buff_CMTC, sizeof(tx_buff_CMTC)) != HAL_OK)
    // {
    //     ES_TRACE_DEBUG("TX Failed: CubeMag TC\n");
    // }
    RS485_TxMode();
    
    if (HAL_UART_Transmit_IT(&huart6, tx_buffer_TLM[node_idx], 7) != HAL_OK)
    {
        ES_TRACE_DEBUG("TX Failed: node %d\n", node_idx);
    }
    
    for (;;)
    {
        RS485_ProcessEvents(&huart6);
    }
}

void RS485_ProcessEvents(UART_HandleTypeDef *huart)
{
    if (rs485_TxCplt_flag) 
    {
        rs485_TxCplt_flag = 0;

        RS485_RxMode();
        if (HAL_UART_Receive(&huart6, rs485_rx_buffer, MAX_PACKET_LENGTH, 50) == HAL_OK)          // goal for timeout is 50ms
        {
            ES_TRACE_DEBUG("!!!!!! RX Failed !!!!!!\n");
        }
        HAL_UART_AbortReceive(&huart6);
        rs485_RxCplt_flag = 1;
    }

    if (rs485_RxCplt_flag)
    {
        rs485_RxCplt_flag = 0;

        convert_packet_1f1f_to_1f(rs485_rx_buffer);
        DataParsing(rs485_rx_buffer);
        osDelay(10);                                // for controlling frequency
        node_idx = (node_idx + 1) % NODE_COUNT;
        if (node_idx == 0) {
            ES_TRACE_DEBUG("count: %d\r\n", ++count);
        }

        RS485_TxMode();
        if (HAL_UART_Transmit_IT(&huart6, tx_buffer_TLM[node_idx], 7) != HAL_OK)
        {
            ES_TRACE_DEBUG("!!!!!! TX Failed !!!!!!\n");
        }
        
        
        // if (check_all_flags_zero(&tc_flag_copy))
        // {
        //     ES_TRACE_DEBUG("All flags are zero, sending telemetry request\n");
        //     node_idx = (node_idx + 1) % NODE_COUNT;

        //     if (HAL_UART_Transmit_IT(&huart6, tx_buffer_TLM[node_idx], 7) != HAL_OK)
        //     {
        //         ES_TRACE_DEBUG("!!!!!! TX Failed !!!!!!\n");
        //     }
        // } else {
        //     send_telecommand(&tc_flag_copy);
        // }
    }
}


void testing_TC(void)
{
    /* =========================================== 1 =========================================== */
    /* for testing CM TC */
    RS485_TxMode();
    build_tx_buffer_CMTC();
    if (HAL_UART_Transmit_IT(&huart6, tx_buff_CMTC, sizeof(tx_buff_CMTC)) != HAL_OK)
    {
        ES_TRACE_DEBUG("TX Failed: CubeMag TC\n");
    }
    while (!rs485_TxCplt_flag) { }
    rs485_TxCplt_flag = 0;

    RS485_RxMode();
    if (HAL_UART_Receive(&huart6, rs485_rx_buffer, MAX_PACKET_LENGTH, 50) == HAL_OK)          // goal for timeout is 50ms
    {
        ES_TRACE_DEBUG("!!!!!! RX Failed !!!!!!\n");
    }
    HAL_UART_AbortReceive(&huart6);
    osDelay(10);



    char debug_str[3 * MAX_PACKET_LENGTH + 1];  // "FF " 형태로 출력할 수 있는 크기 확보
    int len = MAX_PACKET_LENGTH;                // 수신한 데이터 길이
    int pos = 0;

    for (int i = 0; i < len; i++)
    {
        pos += snprintf(&debug_str[pos], sizeof(debug_str) - pos, "%02X ", rs485_rx_buffer[i]);
    }
    ES_TRACE_DEBUG("RX Data: %s\n", debug_str);



    if (rs485_rx_buffer[0] == ESC && rs485_rx_buffer[1] == SOR && rs485_rx_buffer[2] == 60 && 
        rs485_rx_buffer[3] == Magnetometer && rs485_rx_buffer[4] == MainOBC && rs485_rx_buffer[5] == 0x00 &&
        rs485_rx_buffer[6] == ESC && rs485_rx_buffer[7] == EOM) {
        ES_TRACE_DEBUG("CubeMag Config Command(ID: 60) Successful\r\n");
    } else {
        ES_TRACE_DEBUG("CubeMag Config Command(ID: 60) Failed with error code: %d\r\n", rs485_rx_buffer[5]);
    }



    // uint8_t power_on_CW1[] = {ESC, SOM, 60, MainOBC, ReactionWheel1, 0x01, ESC, EOM};
    // uint8_t power_off_CW1[] = {ESC, SOM, 60, MainOBC, ReactionWheel1, 0x00, ESC, EOM};
    // uint8_t power_on_CW2[] = {ESC, SOM, 60, MainOBC, ReactionWheel2, 0x01, ESC, EOM};
    // uint8_t power_off_CW2[] = {ESC, SOM, 60, MainOBC, ReactionWheel2, 0x00, ESC, EOM};
    // // uint8_t tx_buff_CW1_TC[11] = {
    // //     0x1F, 0x80, 64, 0xF0, 0x02, 0x00, 0x00, 0xFA, 0x43, 0x1F, 0xFF
    // // };
    // // uint8_t tx_buff_CW2_TC[11] = {
    // //     0x1F, 0x80, 64, 0xF0, 0x03, 0x00, 0x00, 0xFA, 0x43, 0x1F, 0xFF
    // // };

    // float rpm = 100.0f;
    // uint8_t tx_buff_CW1_TC64[11] = {0x1F, 0x80, 64, 0xF0, 0x02};
    // memcpy(&tx_buff_CW1_TC64[5], &rpm, sizeof(rpm));  // 5~8에 rpm 삽입
    // tx_buff_CW1_TC64[9] = 0x1F;
    // tx_buff_CW1_TC64[10] = 0xFF;
    
    // uint8_t tx_buff_CW2_TC64[11] = {0x1F, 0x80, 64, 0xF0, 0x03};
    // memcpy(&tx_buff_CW2_TC64[5], &rpm, sizeof(rpm));  // 5~8에 rpm 삽입
    // tx_buff_CW2_TC64[9] = 0x1F;
    // tx_buff_CW2_TC64[10] = 0xFF;

    // /* =========================================== 2 =========================================== */
    // osDelay(500);
    // RS485_TxMode();
    // if (HAL_UART_Transmit_IT(&huart6, power_on_CW1, sizeof(power_on_CW1)) != HAL_OK)
    // {
    //     ES_TRACE_DEBUG("TX Failed: CubeWheel1 TC\n");
    // }

    // RS485_RxMode();
    // if (HAL_UART_Receive(&huart6, rs485_rx_buffer, MAX_PACKET_LENGTH, 50) == HAL_OK)          // goal for timeout is 50ms
    // {
    //     ES_TRACE_DEBUG("!!!!!! RX Failed !!!!!!\n");
    // }
    // HAL_UART_AbortReceive(&huart6);
    // if (rs485_rx_buffer[0] == ESC && rs485_rx_buffer[1] == SOR && rs485_rx_buffer[2] == 60 && 
    //     rs485_rx_buffer[3] == ReactionWheel1 && rs485_rx_buffer[4] == MainOBC && rs485_rx_buffer[5] == 0x00 &&
    //     rs485_rx_buffer[6] == ESC && rs485_rx_buffer[7] == EOM) {
    //     ES_TRACE_DEBUG("CubeWheel1 TC Command(ID: 60) Successful\r\n");
    // } else {
    //     ES_TRACE_DEBUG("CubeWheel1 TC Command(ID: 60) Failed with error code: %d\r\n", rs485_rx_buffer[5]);
    // }



    // /* =========================================== 3 =========================================== */
    // osDelay(500);
    // RS485_TxMode();
    // if (HAL_UART_Transmit_IT(&huart6, power_on_CW2, sizeof(power_on_CW2)) != HAL_OK)
    // {
    //     ES_TRACE_DEBUG("TX Failed: CubeWheel2 TC\n");
    // }

    // RS485_RxMode();
    // if (HAL_UART_Receive(&huart6, rs485_rx_buffer, MAX_PACKET_LENGTH, 50) == HAL_OK)          // goal for timeout is 50ms
    // {
    //     ES_TRACE_DEBUG("!!!!!! RX Failed !!!!!!\n");
    // }
    // HAL_UART_AbortReceive(&huart6);
    // if (rs485_rx_buffer[0] == ESC && rs485_rx_buffer[1] == SOR && rs485_rx_buffer[2] == 60 && 
    //     rs485_rx_buffer[3] == ReactionWheel2 && rs485_rx_buffer[4] == MainOBC && rs485_rx_buffer[5] == 0x00 &&
    //     rs485_rx_buffer[6] == ESC && rs485_rx_buffer[7] == EOM) {
    //     ES_TRACE_DEBUG("CubeWheel2 TC Command(ID: 60) Successful\r\n");
    // } else {
    //     ES_TRACE_DEBUG("CubeWheel2 TC Command(ID: 60) Failed with error code: %d\r\n", rs485_rx_buffer[5]);
    // }


    // /* =========================================== 4 =========================================== */
    // osDelay(500);
    // RS485_TxMode();
    // if (HAL_UART_Transmit_IT(&huart6, tx_buff_CW1_TC64, sizeof(tx_buff_CW1_TC64)) != HAL_OK)
    // {
    //     ES_TRACE_DEBUG("TX Failed: CubeWheel1 TC for 100RPM\n");
    // }
    // RS485_RxMode();
    // if (HAL_UART_Receive(&huart6, rs485_rx_buffer, MAX_PACKET_LENGTH, 50) == HAL_OK)          // goal for timeout is 50ms
    // {
    //     ES_TRACE_DEBUG("!!!!!! RX Failed !!!!!!\n");
    // }
    // HAL_UART_AbortReceive(&huart6);
    // if (rs485_rx_buffer[0] == ESC && rs485_rx_buffer[1] == SOR && rs485_rx_buffer[2] == 64 && 
    //     rs485_rx_buffer[3] == ReactionWheel1 && rs485_rx_buffer[4] == MainOBC && rs485_rx_buffer[5] == 0x00 &&
    //     rs485_rx_buffer[6] == ESC && rs485_rx_buffer[7] == EOM) {
    //     ES_TRACE_DEBUG("CubeWheel1 TC Command(ID: 64) Successful\r\n");
    // } else if (rs485_rx_buffer[5] == 0x01) {
    //     ES_TRACE_DEBUG("CubeWheel1 TC Command(ID: 64) Failed with error code: %d\r\n", rs485_rx_buffer[5]);
    // } else {
    //     ES_TRACE_DEBUG("CubeWheel1 TC Command(ID: 64) Unknown response code: %d\r\n", rs485_rx_buffer[5]);
    // }


    // /* =========================================== 5 =========================================== */
    // osDelay(500);
    // RS485_TxMode();
    // if (HAL_UART_Transmit_IT(&huart6, tx_buff_CW2_TC64, sizeof(tx_buff_CW2_TC64)) != HAL_OK)
    // {
    //     ES_TRACE_DEBUG("TX Failed: CubeWheel2 TC for 100RPM\n");
    // }
    // RS485_RxMode();
    // if (HAL_UART_Receive(&huart6, rs485_rx_buffer, MAX_PACKET_LENGTH, 50) == HAL_OK)          // goal for timeout is 50ms
    // {
    //     ES_TRACE_DEBUG("!!!!!! RX Failed !!!!!!\n");
    // }
    // HAL_UART_AbortReceive(&huart6);
    // if (rs485_rx_buffer[0] == ESC && rs485_rx_buffer[1] == SOR && rs485_rx_buffer[2] == 64 && 
    //     rs485_rx_buffer[3] == ReactionWheel2 && rs485_rx_buffer[4] == MainOBC && rs485_rx_buffer[5] == 0x00 &&
    //     rs485_rx_buffer[6] == ESC && rs485_rx_buffer[7] == EOM) {
    //     ES_TRACE_DEBUG("CubeWheel2 TC Command(ID: 64) Successful\r\n");
    // } else if (rs485_rx_buffer[5] == 0x01) {
    //     ES_TRACE_DEBUG("CubeWheel2 TC Command(ID: 64) Failed with error code: %d\r\n", rs485_rx_buffer[5]);
    // } else {
    //     ES_TRACE_DEBUG("CubeWheel2 TC Command(ID: 64) Unknown response code: %d\r\n", rs485_rx_buffer[5]);
    // }
    

    // /* =========================================== 6 =========================================== */
    // for (int i = 0; i < 10; i++) {
    //     osDelay(1000);
    //     ES_TRACE_DEBUG("Waiting for 1 second... %d\r\n", i + 1);
    // }
    // rpm = 0.0f; // Reset RPM for next test
    // memcpy(&tx_buff_CW1_TC64[5], &rpm, sizeof(rpm));  // 5~8에 rpm 삽입
    // memcpy(&tx_buff_CW2_TC64[5], &rpm, sizeof(rpm));  // 5~8에 rpm 삽입


    // /* =========================================== 7 =========================================== */
    // osDelay(500);
    // RS485_TxMode();
    // if (HAL_UART_Transmit_IT(&huart6, tx_buff_CW1_TC64, sizeof(tx_buff_CW1_TC64)) != HAL_OK)
    // {
    //     ES_TRACE_DEBUG("TX Failed: CubeWheel1 TC for 0 RPM\n");
    // }
    // RS485_RxMode();
    // if (HAL_UART_Receive(&huart6, rs485_rx_buffer, MAX_PACKET_LENGTH, 50) == HAL_OK)          // goal for timeout is 50ms
    // {
    //     ES_TRACE_DEBUG("!!!!!! RX Failed !!!!!!\n");
    // }
    // HAL_UART_AbortReceive(&huart6);
    // if (rs485_rx_buffer[0] == ESC && rs485_rx_buffer[1] == SOR && rs485_rx_buffer[2] == 64 && 
    //     rs485_rx_buffer[3] == ReactionWheel1 && rs485_rx_buffer[4] == MainOBC && rs485_rx_buffer[5] == 0x00 &&
    //     rs485_rx_buffer[6] == ESC && rs485_rx_buffer[7] == EOM) {
    //     ES_TRACE_DEBUG("CubeWheel1 TC Command(ID: 64) Successful\r\n");
    // } else if (rs485_rx_buffer[5] == 0x01) {
    //     ES_TRACE_DEBUG("CubeWheel1 TC Command(ID: 64) Failed with error code: %d\r\n", rs485_rx_buffer[5]);
    // } else {
    //     ES_TRACE_DEBUG("CubeWheel1 TC Command(ID: 64) Unknown response code: %d\r\n", rs485_rx_buffer[5]);
    // }

    
    // /* =========================================== 8 =========================================== */
    // osDelay(500);
    // RS485_TxMode();
    // if (HAL_UART_Transmit_IT(&huart6, tx_buff_CW2_TC64, sizeof(tx_buff_CW2_TC64)) != HAL_OK)
    // {
    //     ES_TRACE_DEBUG("TX Failed: CubeWheel2 TC for 0 RPM\n");
    // }
    // RS485_RxMode();
    // if (HAL_UART_Receive(&huart6, rs485_rx_buffer, MAX_PACKET_LENGTH, 50) == HAL_OK)          // goal for timeout is 50ms
    // {
    //     ES_TRACE_DEBUG("!!!!!! RX Failed !!!!!!\n");
    // }
    // HAL_UART_AbortReceive(&huart6);
    // if (rs485_rx_buffer[0] == ESC && rs485_rx_buffer[1] == SOR && rs485_rx_buffer[2] == 64 && 
    //     rs485_rx_buffer[3] == ReactionWheel2 && rs485_rx_buffer[4] == MainOBC && rs485_rx_buffer[5] == 0x00 &&
    //     rs485_rx_buffer[6] == ESC && rs485_rx_buffer[7] == EOM) {
    //     ES_TRACE_DEBUG("CubeWheel2 TC Command(ID: 64) Successful\r\n");
    // } else if (rs485_rx_buffer[5] == 0x01) {
    //     ES_TRACE_DEBUG("CubeWheel2 TC Command(ID: 64) Failed with error code: %d\r\n", rs485_rx_buffer[5]);
    // } else {
    //     ES_TRACE_DEBUG("CubeWheel2 TC Command(ID: 64) Unknown response code: %d\r\n", rs485_rx_buffer[5]);
    // }


    // /* =========================================== 9 =========================================== */
    // osDelay(500);
    // RS485_TxMode();
    // if (HAL_UART_Transmit_IT(&huart6, power_off_CW1, sizeof(power_off_CW1)) != HAL_OK)
    // {
    //     ES_TRACE_DEBUG("TX Failed: CubeWheel1 TC\n");
    // }

    // RS485_RxMode();
    // if (HAL_UART_Receive(&huart6, rs485_rx_buffer, MAX_PACKET_LENGTH, 50) == HAL_OK)          // goal for timeout is 50ms
    // {
    //     ES_TRACE_DEBUG("!!!!!! RX Failed !!!!!!\n");
    // }
    // HAL_UART_AbortReceive(&huart6);
    // if (rs485_rx_buffer[0] == ESC && rs485_rx_buffer[1] == SOR && rs485_rx_buffer[2] == 60 && 
    //     rs485_rx_buffer[3] == ReactionWheel1 && rs485_rx_buffer[4] == MainOBC && rs485_rx_buffer[5] == 0x00 &&
    //     rs485_rx_buffer[6] == ESC && rs485_rx_buffer[7] == EOM) {
    //     ES_TRACE_DEBUG("CubeWheel1 TC Command(ID: 60) Successful\r\n");
    // } else {
    //     ES_TRACE_DEBUG("CubeWheel1 TC Command(ID: 60) Failed with error code: %d\r\n", rs485_rx_buffer[5]);
    // }


    // /* =========================================== 10 =========================================== */
    // osDelay(500);
    // RS485_TxMode();
    // if (HAL_UART_Transmit_IT(&huart6, power_off_CW2, sizeof(power_off_CW2)) != HAL_OK)
    // {
    //     ES_TRACE_DEBUG("TX Failed: CubeWheel2 TC\n");
    // }

    // RS485_RxMode();
    // if (HAL_UART_Receive(&huart6, rs485_rx_buffer, MAX_PACKET_LENGTH, 50) == HAL_OK)          // goal for timeout is 50ms
    // {
    //     ES_TRACE_DEBUG("!!!!!! RX Failed !!!!!!\n");
    // }
    // HAL_UART_AbortReceive(&huart6);
    // if (rs485_rx_buffer[0] == ESC && rs485_rx_buffer[1] == SOR && rs485_rx_buffer[2] == 60 && 
    //     rs485_rx_buffer[3] == ReactionWheel1 && rs485_rx_buffer[4] == MainOBC && rs485_rx_buffer[5] == 0x00 &&
    //     rs485_rx_buffer[6] == ESC && rs485_rx_buffer[7] == EOM) {
    //     ES_TRACE_DEBUG("CubeWheel2 TC Command(ID: 60) Successful\r\n");
    // } else {
    //     ES_TRACE_DEBUG("CubeWheel2 TC Command(ID: 60) Failed with error code: %d\r\n", rs485_rx_buffer[5]);
    // }
    // osDelay(500);


    // if ((rs485_rx_buffer[5] == 0x00) || (rs485_rx_buffer[5] == 0x01)) {
    //     memcpy(&MotorPower1, &rs485_rx_buffer[5], sizeof(MotorPower1));
    //     ES_TRACE_DEBUG(
    //         "Reaction Wheel 1 Motor Power => Switch: %s\r\n",
    //         MotorPower1.MotorPowerSwitch ? "ON" : "OFF"
    //     );
    // } else {
    //     ES_TRACE_DEBUG("CubeWheel1 TC Command(ID: 64) Unknown response code: %d\r\n", rs485_rx_buffer[5]);
    // }
}











// void send_telecommand(DATA_CACHE_CubeSpace_Telecommand_Flag_t* flags) {

//     if (flags->u8CW1_TC_60)
//     {
//         if (HAL_UART_Transmit_IT(&huart6, power_on_CW1, sizeof(power_on_CW1)) != HAL_OK)
//         {
//             ES_TRACE_DEBUG("TX Failed: CubeWheel1 TC\n");
//         }
//         flags->u8CW1_TC_60 = 0;
//     } else if (flags->u8CW1_TC_64)
//     {

        
//         /* this code would be replaced by getting value from datacache */
//         float rpm = 100.0f; // Example RPM value
//         uint8_t tx_buff_CW_TC64[11] = {ESC, SOM, 64, MainOBC, ReactionWheel1, 0xF0, 0x02};
//         memcpy(&tx_buff_CW_TC64[5], &rpm, sizeof(float));
//         tx_buff_CW_TC64[9] = ESC;
//         tx_buff_CW_TC64[10] = EOM;
//         if (HAL_UART_Transmit_IT(&huart6, tx_buff_CW_TC64, sizeof(tx_buff_CW_TC64)) != HAL_OK)
//         {
//             ES_TRACE_DEBUG("TX Failed: CubeWheel1 TC for RPM\n");
//         }
//         flags->u8CW1_TC_64 = 0;
//     } else if (flags->u8CW2_TC_60)
//     {
//         if (HAL_UART_Transmit_IT(&huart6, power_on_CW2, sizeof(power_on_CW2)) != HAL_OK)
//         {
//             ES_TRACE_DEBUG("TX Failed: CubeWheel2 TC\n");
//         }
//         flags->u8CW2_TC_60 = 0;
//     } else if (flags->u8CW2_TC_64)
//     {
//         /* this code would be replaced by getting value from datacache */
//         float rpm = 100.0f; // Example RPM value
//         uint8_t tx_buff_CW_TC64[11] = {ESC, SOM, 64, MainOBC, ReactionWheel2, 0xF0, 0x02};
//         memcpy(&tx_buff_CW_TC64[5], &rpm, sizeof(float));
//         tx_buff_CW_TC64[9] = ESC;
//         tx_buff_CW_TC64[10] = EOM;
//         if (HAL_UART_Transmit_IT(&huart6, tx_buff_CW_TC64, sizeof(tx_buff_CW_TC64)) != HAL_OK)
//         {
//             ES_TRACE_DEBUG("TX Failed: CubeWheel1 TC for RPM\n");
//         }
//         flags->u8CW2_TC_64 = 0;
//     } else if (flags->u8CM_TC_60)
//     {
//         build_tx_buffer_CMTC();
//         if (HAL_UART_Transmit_IT(&huart6, tx_buff_CMTC, sizeof(tx_buff_CMTC)) != HAL_OK)
//         {
//             ES_TRACE_DEBUG("TX Failed: CubeMag TC\n");
//         }
//         flags->u8CM_TC_60 = 0;
//     } else {
//         ES_TRACE_DEBUG("No telecommand flags set.\n");
//     }
//     dc_set_tc_flag(&tc_flag_copy);
// }

// // tc_flags.CW2_TC_3 = 1;     // test 용 

// bool check_all_flags_zero(const DATA_CACHE_CubeSpace_Telecommand_Flag_t* flags) {
//     static const DATA_CACHE_CubeSpace_Telecommand_Flag_t zero_flags = {0};
//     dc_get_tc_flag(&tc_flag_copy);
//     return (memcmp(flags, &zero_flags, sizeof(DATA_CACHE_CubeSpace_Telecommand_Flag_t)) == 0);
// }


void DataParsing(uint8_t *data)
{
    if (data[0] != ESC || data[1] != SOR)
    {
        ES_TRACE_DEBUG("Invalid packet received.\r\n");
        return; // Exit if the packet is invalid
    }

    if (data[3] == Magnetometer) {
        switch (data[2]) {
            case 60:
                if (data[5] == 0x00) {
                    ES_TRACE_DEBUG("CubeMag Config Command(ID: 60) Successful\r\n");
                } else {
                    ES_TRACE_DEBUG("CubeMag Config Command(ID: 60) Failed with error code: %d\r\n", data[5]);
                }
                break;

            case 186:  // CubeMag Config
                memcpy(&CubeMagConfig_TLM, &data[5], sizeof(CubeMagConfig_TLM));
                ES_TRACE_DEBUG(
                    "CubeMag Config => Preferred Primary Mag: %d, Current Primary Mag: %d, "
                    "Deploy Timeout: %d mS, Primary Auto-Select: %s\r\n",
                    CubeMagConfig_TLM.PreferredPrimaryMagnetometer,
                    CubeMagConfig_TLM.CurrentPrimaryMagnetometer,
                    CubeMagConfig_TLM.DeployTimeout,
                    CubeMagConfig_TLM.PrimaryAutoSelect ? "true" : "false"
                );
                break;
                
            case 188:  // All Service States
                memcpy(&AllServiceStates, &data[5], sizeof(AllServiceStates));
                ES_TRACE_DEBUG(
                    "All Service States => CubeMag: %d, Primary Magnetometer: %d, Redundant Magnetometer: %d\r\n",
                    AllServiceStates.MagSvcState,
                    AllServiceStates.PrimaryMagState,
                    AllServiceStates.RedundantMagState
                );
                break;
                
            case 190:  // Deployment Status
                memcpy(&DeploymentStatus, &data[5], sizeof(DeploymentStatus));
                ES_TRACE_DEBUG(
                    "Deployment Status => BurnCurrent: %u mA, DeploymentPinState: %d, BurnPinState: %d, "
                    "BurnUnderCurrent: %d, BurnOverCurrent: %d, DeploymentTimeout: %d\r\n",
                    DeploymentStatus.BurnCurrent,
                    DeploymentStatus.DeploymentPinState,
                    DeploymentStatus.BurnPinState,
                    DeploymentStatus.BurnUnderCurrent,
                    DeploymentStatus.BurnOverCurrent,
                    DeploymentStatus.DeploymentTimeout
                );
                break;
                
            case 193:  // Redundant Magnetometer Measurement
                memcpy(&Redundant, &data[5], sizeof(Redundant));
                ES_TRACE_DEBUG(
                    "Redundant Data [Magnetometer] => X: %.4f, Y: %.4f, Z: %.4f, Valid: %s\r\n",
                    Redundant.X_axis,
                    Redundant.Y_axis,
                    Redundant.Z_axis,
                    Redundant.DataValid ? "true" : "false"
                );
                break;
                
            case 197:  // Primary Magnetometer Measurement
                memcpy(&Primary, &data[5], sizeof(Primary));
                ES_TRACE_DEBUG(
                    "Primary Data [Magnetometer] => X: %.4f, Y: %.4f, Z: %.4f, Valid: %s\r\n",
                    Primary.X_axis,
                    Primary.Y_axis,
                    Primary.Z_axis,
                    Primary.DataValid ? "true" : "false"
                );
                break;

            default:
                ES_TRACE_DEBUG("Unknown Node ID: %d\r\n", data[2]);
                return;
        }
    }
    else if (data[3] == ReactionWheel1) {
        switch (data[2]) {
            case 186:  // Wheel Reference Torque
                memcpy(&WheelReferenceTorque1, &data[5], sizeof(WheelReferenceTorque1));
                ES_TRACE_DEBUG(
                    "Reaction Wheel 1 Reference Torque => %.4f mNm\r\n",
                    WheelReferenceTorque1.ReferenceTorque
                );
                break;
                
            case 188:  // Wheel Speed
                memcpy(&WheelSpeed1, &data[5], sizeof(WheelSpeed1));
                ES_TRACE_DEBUG(
                    "Reaction Wheel 1 Speed => Speed: %.2f RPM, Error State: %d\r\n",
                    WheelSpeed1.WheelSpeed,
                    WheelSpeed1.WheelErrorState
                );
                break;
                
            case 196:  // Wheel Reference Speed
                memcpy(&WheelReferenceSpeed1, &data[5], sizeof(WheelReferenceSpeed1));
                ES_TRACE_DEBUG(
                    "Reaction Wheel 1 Reference Speed => %.2f RPM\r\n",
                    WheelReferenceSpeed1.ReferenceSpeed
                );
                break;
                
            case 197:  // Motor Power
                memcpy(&MotorPower1, &data[5], sizeof(MotorPower1));
                ES_TRACE_DEBUG(
                    "Reaction Wheel 1 Motor Power => Switch: %s\r\n",
                    MotorPower1.MotorPowerSwitch ? "ON" : "OFF"
                );
                break;
                
            default:
                ES_TRACE_DEBUG("Unknown Reaction Wheel 1 Message ID: %d\r\n", data[2]);
                break;
        }
    }
    else if (data[3] == ReactionWheel2) {
        switch (data[2]) {
            case 186:  // Wheel Reference Torque
                memcpy(&WheelReferenceTorque2, &data[5], sizeof(WheelReferenceTorque2));
                ES_TRACE_DEBUG(
                    "Reaction Wheel 2 Reference Torque => %.4f mNm\r\n",
                    WheelReferenceTorque2.ReferenceTorque
                );
                break;
                
            case 188:  // Wheel Speed
                memcpy(&WheelSpeed2, &data[5], sizeof(WheelSpeed2));
                ES_TRACE_DEBUG(
                    "Reaction Wheel 2 Speed => Speed: %.2f RPM, Error State: %d\r\n",
                    WheelSpeed2.WheelSpeed,
                    WheelSpeed2.WheelErrorState
                );
                break;
                
            case 196:  // Wheel Reference Speed
                memcpy(&WheelReferenceSpeed2, &data[5], sizeof(WheelReferenceSpeed2));
                ES_TRACE_DEBUG(
                    "Reaction Wheel 2 Reference Speed => %.2f RPM\r\n",
                    WheelReferenceSpeed2.ReferenceSpeed
                );
                break;
                
            case 197:  // Motor Power
                memcpy(&MotorPower2, &data[5], sizeof(MotorPower2));
                ES_TRACE_DEBUG(
                    "Reaction Wheel 2 Motor Power => Switch: %s\r\n",
                    MotorPower2.MotorPowerSwitch ? "ON" : "OFF"
                );
                break;
                
            default:
                ES_TRACE_DEBUG("Unknown Reaction Wheel 2 Message ID: %d\r\n", data[2]);
                break;
        }
    }
    else {
        ES_TRACE_DEBUG("Unknown address: %d\r\n", data[3]);
        return; 
    }
}

void HAL_UART_TxCpltCallback(UART_HandleTypeDef *huart)
{
    if (huart->Instance != USART6) return;
    rs485_TxCplt_flag = 1;
}

void RS485_TxMode(void)
{
    demo_uart6_DriverEnable();
    demo_uart6_ReceptionDisable();
    while ((((U6_RS485_Driver_Pins.DE.port->ODR >> 8) & 0x1) == 0) ||
           (((U6_RS485_Driver_Pins.nRE.port->ODR >> 13) & 0x1) == 0))
    {
        osDelay(1);
    }
}

void RS485_RxMode(void)
{
    demo_uart6_DriverDisable();
    demo_uart6_ReceptionEnable();
    while ((((U6_RS485_Driver_Pins.DE.port->ODR >> 8) & 0x1) == 1) ||
           (((U6_RS485_Driver_Pins.nRE.port->ODR >> 13) & 0x1) == 1))
    {
        osDelay(1);
    }
}


void convert_packet_1f1f_to_1f(uint8_t *data)
{
    payload_size = 0;
    received_size = 0;
    write_idx = 5;
    read_idx = 5;
    received_size =  MAX_PACKET_LENGTH - huart6.RxXferCount;
    payload_size = received_size - 7;                           // 7: ESC, SOR, TLM ID, SRC, DST, ESC, EOM
    
    /* ================ printing for debug ================ */
    // char debug_str[3 * received_size + 1];
    // memset(debug_str, 0, sizeof(debug_str));
    // for (int i = 0; i < received_size; i++) {
    //     sprintf(&debug_str[i * 3], "%02X ", rs485_rx_buffer[i]);
    // }


    while (read_idx < payload_size + 5) {
        if (data[read_idx] == ESC && data[read_idx + 1] == ESC) {
            data[write_idx++] = ESC;
            read_idx += 2;
        } else {
            data[write_idx++] = data[read_idx++];
        }
    }

}
