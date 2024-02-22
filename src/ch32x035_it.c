/********************************** (C) COPYRIGHT *******************************
 * File Name          : ch32x035_it.c
 * Author             : WCH
 * Version            : V1.0.0
 * Date               : 2023/04/06
 * Description        : Main Interrupt Service Routines.
*********************************************************************************
* Copyright (c) 2021 Nanjing Qinheng Microelectronics Co., Ltd.
* Attention: This software (modified or not) and binary are used for 
* microcontroller manufactured by Nanjing Qinheng Microelectronics.
*******************************************************************************/
#include "ch32x035_it.h"
#include "cdc_UART.h"

void NMI_Handler(void) __attribute__((interrupt("WCH-Interrupt-fast")));
void HardFault_Handler(void) __attribute__((interrupt("WCH-Interrupt-fast")));
void TIM3_IRQHandler( void )__attribute__((interrupt("WCH-Interrupt-fast")));

/*********************************************************************
 * @fn      TIM3_IRQHandler
 *
 * @brief   This function handles TIM3 exception.
 *
 * @return  none
 */
void TIM3_IRQHandler( void )
{

    if( TIM_GetITStatus( TIM3, TIM_IT_Update ) != RESET )
    {
        /* Clear interrupt flag */
        TIM_ClearITPendingBit( TIM3, TIM_IT_Update );

        /* uart timeout counts */
        Uart.Rx_TimeOut++;
        Uart.USB_Up_TimeOut++;
    }

}
