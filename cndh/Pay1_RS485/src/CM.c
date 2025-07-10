#include "../inc/RS485_Jisoo.h"
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

#define NODE_COUNT  3
uint8_t tx_buffer[NODE_COUNT][7] = {
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
uint8_t rs485_rx_buffer[MAX_PACKET_LENGTH] = {0};
static volatile uint8_t rs485_TxCplt_flag = 0;
static volatile uint8_t rs485_RxCplt_flag = 0;
//static uint16_t count = 0;
uint8_t node_idx = 0;
Primary primary;
gain1 gain_CW1;
gain2 gain_CW2;


void U6_RS485_Init(void)
{
    p_U6_RS485_driver_Pins = &U6_RS485_Driver_Pins;
    uart6_init(baud_rates[4]);
    RS485_TEST_Task_taskHandle = osThreadNew(RS485_TEST_Task, NULL, &RS485_TEST_Task_attributes);
}

void RS485_TEST_Task(void *argument)
{
    ES_TRACE_DEBUG("========= RS485_TEST_Task START ========= \r\n");
    RS485_TxMode();
    if (HAL_UART_Transmit_IT(&huart6, tx_buffer[node_idx], 7) != HAL_OK)
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
    //       ES_TRACE_DEBUG("!!!!!! RX Failed !!!!!!\n");
   //        ES_TRACE_DEBUG("UART RxState: %d, gState: %d\n", huart6.RxState, huart6.gState);
        }
        HAL_UART_AbortReceive(&huart6);
        rs485_RxCplt_flag = 1;
    }

    if (rs485_RxCplt_flag)
    {
        rs485_RxCplt_flag = 0;


        DataParsing(rs485_rx_buffer);
        osDelay(50);                                // for controlling frequency
        node_idx = (node_idx++) % NODE_COUNT;


        RS485_TxMode();
        if (HAL_UART_Transmit_IT(&huart6, tx_buffer[node_idx], 7) != HAL_OK)
        {
     //       ES_TRACE_DEBUG("!!!!!! TX Failed !!!!!!\n");
        }

    }
}

void DataParsing(uint8_t *data)
{
    static uint16_t payload_size = 0;
    static uint16_t received_size = 0;
    static uint8_t write_idx = 5;
    static uint8_t read_idx = 5;


    received_size =  MAX_PACKET_LENGTH - huart6.RxXferCount;
    payload_size = received_size - 7;                           // 7: ESC, SOR, TLM ID, SRC, DST, ESC, EOM

    ES_TRACE_DEBUG("count: %d\r\n", ++count);

    if (node_idx == 0)
    {
        /* ================ printing for debug ================ */
        char debug_str[3 * received_size + 1];
        memset(debug_str, 0, sizeof(debug_str));
        for (int i = 0; i < received_size; i++) {
            sprintf(&debug_str[i * 3], "%02X ", rs485_rx_buffer[i]);
        }
    //    ES_TRACE_DEBUG("rs485_rx_buffer: %s\r\n", debug_str);


        /* ================ 0x1F1F -> 0x1F decoding ================ */
        if (payload_size > sizeof(primary)) {
            write_idx = 5;
            read_idx = 5;
            while (read_idx < payload_size + 5) {
                if (data[read_idx] == ESC && data[read_idx + 1] == ESC) {
                    data[write_idx++] = ESC;
                    read_idx += 2;
                } else {
                    data[write_idx++] = data[read_idx++];
                }
            }
        }

        memcpy(&primary, &data[5], sizeof(primary));
        ES_TRACE_DEBUG(
            "Primary Data [Magnetometer] => X: %.4f, Y: %.4f, Z: %.4f, Valid: %s\r\n",
            primary.X_axis,
            primary.Y_axis,
            primary.Z_axis,
            primary.DataValid ? "true" : "false"
        );
    }
    else if (node_idx == 1)
    {
        // ReactionWheel1
        memcpy(&gain_CW1, &data[5], sizeof(gain_CW1));
        ES_TRACE_DEBUG(
            "Main Gain Data [ReactionWheel 1] => Kp: %.4f, Ki: %.4f, Kd: %.4f\r\n",
            gain_CW1.Kp,
            gain_CW1.Ki,
            gain_CW1.Kd
        );
    }
    else if (node_idx == 2)
    {
        // ReactionWheel2
        memcpy(&gain_CW2, &data[5], sizeof(gain_CW2));
        ES_TRACE_DEBUG(
            "Main Gain Data [ReactionWheel 2] => Kp: %.4f, Ki: %.4f, Kd: %.4f\r\n",
            gain_CW2.Kp,
            gain_CW2.Ki,
            gain_CW2.Kd
        );
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
