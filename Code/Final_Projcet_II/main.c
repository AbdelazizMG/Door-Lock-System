/******************************************************************************
*  Module:    main
*  File name: main.c
*  Created on: Oct 25, 2021
*  Author: Abdelaziz Mohammad
*******************************************************************************/
/*******************************************************************************
*                                                                              *
*                                  INCLUDES                                    *
*                                                                              *
********************************************************************************/
#include "UART.h"
#include "DC_Motor.h"
#include "Buzzer.h"
#include "gpio.h"
#include "Timers.h"
#include "common_macros.h"
#include "avr/io.h"
#include "Operations_II.h"
#define F_CPU 8000000

extern uint16 g_Interrupts_number;


int main (void)
{

	  /*Configuration Structure*/
	 UART_ConfigType UART_Config_Struct =
	 {
			 Transmitter_Receiver,
			 Double_Speed,
			 Asynchronous,
			 Parity_Disabled,
			 StopBit_1,
			 DataFrame_8Bits,
			 BaudRate_9600,
			 RX_InterruptDisable,
			 TX_InterruptDisable
	 };

	    /*Init Buzzer*/
	    BUZZER_init(PORTC_ID, PIN2_ID);

	    /*DC - Motor Init*/
	    DC_MOTOR_Init();

	    /*UART Init*/
	    UART_Init(&UART_Config_Struct);


	    /*Enable I-Bit*/
	    SET_BIT(SREG,7);


	while (1)
	{

		OPERATIONS_II_UART_HANDLE(&TIMER_Config_Struct);


	}

}


