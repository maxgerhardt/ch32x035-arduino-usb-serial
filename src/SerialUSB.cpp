#include <SerialUSB.h>

SerialUSBBase SerialUSB;

#include <ch32x035_usbfs_device.h>
#include <ch32x035_it.h>
#include <usb_desc.h>

PWR_VDD PWR_VDD_SupplyVoltage(void)
{

    PWR_VDD VDD_Voltage = PWR_VDD_3V3;
    //Delay_Init();
    RCC_APB1PeriphClockCmd( RCC_APB1Periph_PWR, ENABLE);
    PWR_PVDLevelConfig(PWR_PVDLevel_4V0);
    delayMicroseconds(10);
    if( PWR_GetFlagStatus(PWR_FLAG_PVDO) == (uint32_t)RESET)
    {
        VDD_Voltage = PWR_VDD_5V;
    }
    PWR_PVDLevelConfig(PWR_PVDLevel_2V1);

    return VDD_Voltage;
}


void SerialUSBBase::begin(int baud) {
    RCC_Configuration( );

    /* Tim3 init */
    TIM3_Init( );

    UART2_Init( 1, DEF_UARTx_BAUDRATE, DEF_UARTx_STOPBIT, DEF_UARTx_PARITY );

    /* Usb Init */
    USBFS_RCC_Init( );
    USBFS_Device_Init( ENABLE , PWR_VDD_SupplyVoltage());
}

void SerialUSBBase::maintain() {
    UART2_DataRx_Deal( );
    UART2_DataTx_Deal( );
}

extern uint8_t  UART2_Rx_Buf[DEF_UARTx_RX_BUF_LEN];
size_t SerialUSBBase::write(const uint8_t *buffer, size_t size) {
    size_t remaining_buf = DEF_UARTx_RX_BUF_LEN - Uart.Rx_RemainLen;
    if (remaining_buf < size) {
        /* FAIL */
        return 0;
    }
    if (Uart.Rx_RemainLen == 0) {
        Uart.Rx_DealPtr = 0;
    }
    memcpy(UART2_Rx_Buf + Uart.Rx_DealPtr + Uart.Rx_RemainLen, buffer, size);
    Uart.Rx_RemainLen += size;
    Uart.Rx_TimeOut = 0x00;
    return size;
}