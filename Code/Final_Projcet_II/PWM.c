/******************************************************************************
*  Module: PWM
*  File name: PWM.C
*  Created on: Oct 9, 2021
*  Author: Abdelaziz Mohammad
*******************************************************************************/

/*******************************************************************************
*                                                                              *
*                                  INCLUDES                                    *
*                                                                              *
********************************************************************************/
#include "PWM.h"
#include <avr/io.h>
#include "common_macros.h"
#include "gpio.h"
/*******************************************************************************
*                                                                              *
*                              FUNCTIONS Definitions                           *
*                                                                              *
********************************************************************************/
/*******************************************************************************
* Service Name:       PWM_Timer0_Start
* Sync/Async:         Synchronous
* Reentrancy:         Reentrant
* Parameters (in):    Duty Cycle
* Parameters (inout): None
* Parameters (out):   None
* Return value:       None
* Description:        Initialize Timer0 and Rotating DC Motor with a defined speed
********************************************************************************/
void PWM_Timer0_Start(uint8 duty_cycle)
{
    /*Fast PWM Mode*/
	SET_BIT(TCCR0,WGM00);
	SET_BIT(TCCR0,WGM01);

	/*Non Inverting*/
	SET_BIT(TCCR0,COM01);

	/*Prescaler = 8*/
	CLEAR_BIT(TCCR0,CS00);
    SET_BIT(TCCR0,CS01);
    CLEAR_BIT(TCCR0,CS02);

    /*Setting OC0 as Output PIN*/
    GPIO_setupPinDirection(PORTB_ID,PIN3_ID,PIN_OUTPUT);

    /*Initialize TCNT*/
    TCNT0 = 0;

    /*Setting  OCR0 Value*/
    OCR0 = duty_cycle;

}
