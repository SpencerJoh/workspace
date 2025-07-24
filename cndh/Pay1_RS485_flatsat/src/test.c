
void testing_TC(void)
{


    /* for testing CM TC */
    build_tx_buffer_CMTC();
    if (HAL_UART_Transmit_IT(&huart6, tx_buff_CMTC, sizeof(tx_buff_CMTC)) != HAL_OK)
    {
        ES_TRACE_DEBUG("TX Failed: CubeMag TC\n");
    }



    uint8_t power_on_CW1[] = {ESC, SOM, 60, MainOBC, ReactionWheel1, 0x01, ESC, EOM};
    uint8_t power_off_CW1[] = {ESC, SOM, 60, MainOBC, ReactionWheel1, 0x00, ESC, EOM};
    uint8_t power_on_CW2[] = {ESC, SOM, 60, MainOBC, ReactionWheel2, 0x01, ESC, EOM};
    uint8_t power_off_CW2[] = {ESC, SOM, 60, MainOBC, ReactionWheel2, 0x00, ESC, EOM};
    
    float rpm = 100.0f;
    uint8_t tx_buff_CW_TC64[11] = {0x1F, 0x80, 64, 0xF0, 0x02};
    memcpy(&tx_buff_CW_TC64[5], &rpm, sizeof(float));  // 5~8에 rpm 삽입
    tx_buff_CW_TC64[9] = 0x1F;
    tx_buff_CW_TC64[10] = 0xFF;
    

    if (HAL_UART_Transmit_IT(&huart6, power_on_CW1, sizeof(power_on_CW1)) != HAL_OK)
    {
        ES_TRACE_DEBUG("TX Failed: CubeWheel1 TC\n");
    }

    RS485_RxMode();
    if (HAL_UART_Receive(&huart6, rs485_rx_buffer, MAX_PACKET_LENGTH, 50) == HAL_OK)          // goal for timeout is 50ms
    {
        ES_TRACE_DEBUG("!!!!!! RX Failed !!!!!!\n");
    }
    HAL_UART_AbortReceive(&huart6);
    




    if ((rs485_rx_buffer[5] == 0x00) || (rs485_rx_buffer[5] == 0x01)) {
        memcpy(&MotorPower1, &rs485_rx_buffer[5], sizeof(MotorPower1));
        ES_TRACE_DEBUG(
            "Reaction Wheel 1 Motor Power => Switch: %s\r\n",
            MotorPower1.MotorPowerSwitch ? "ON" : "OFF"
        );
    } else {
        ES_TRACE_DEBUG("CubeWheel1 TC Command(ID: 64) Unknown response code: %d\r\n", rs485_rx_buffer[5]);
    }






    
    RS485_TxMode();

    rpm = 200.0f;  // Change RPM for testing
    memcpy(&tx_buff_CWTC[5], &rpm, sizeof(float));  // 5~8에 rpm 삽입

    if (HAL_UART_Transmit_IT(&huart6, power_on_CW2, sizeof(power_on_CW2)) != HAL_OK)
    {
        ES_TRACE_DEBUG("TX Failed: CubeWheel2 TC\n");
    }

    RS485_RxMode();

    if (HAL_UART_Receive(&huart6, rs485_rx_buffer, MAX_PACKET_LENGTH, 50) == HAL_OK)          // goal for timeout is 50ms
    {
        ES_TRACE_DEBUG("!!!!!! RX Failed !!!!!!\n");
    }


}



// uint8_t tx_buff_CWTC[11] = {
//     0x1F, 0x80, 64, 0xF0, 0x02, 0x00, 0x00, 0xFA, 0x43, 0x1F, 0xFF
// };





