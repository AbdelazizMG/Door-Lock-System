/**************************************************************************
* Module:    DC Motor
* File name: DC_Motor.c
* Created on: Oct 9, 2021
* Author: Abdelaziz Mohammad
***************************************************************************/

/*******************************************************************************
*                                                                              *
*                                  INCLUDES                                    *
*                                                                              *
********************************************************************************/
#include "DC_Motor.h"
#include "gpio.h"
#include "PWM.h"
/*******************************************************************************
*                                                                              *
*                              FUNCTIONS Definitions                           *
*                                                                              *
********************************************************************************/
/*******************************************************************************
* Service Name:       DC_MOTOR_Init
* Sync/Async:         Synchronous
* Reentrancy:         Reentrant
* Parameters (in):    None
* Parameters (inout): None
* Parameters (out):   None
* Return value:       None
* Description:        Initialize the DC Motor
********************************************************************************/
void DC_MOTOR_Init(void)
{
	/*Set DC Motors Pins as Output PINS*/
	GPIO_setupPinDirection(DC_Motor_PORT, DC_Motor_PINA, PIN_OUTPUT);
	GPIO_setupPinDirection(DC_Motor_PORT, DC_Motor_PINB, PIN_OUTPUT);

	/*Stop DC Motor at the beginning*/
	GPIO_writePin(DC_Motor_PORT,DC_Motor_PINA,LOGIC_LOW);
	GPIO_writePin(DC_Motor_PORT,DC_Motor_PINB,LOGIC_LOW);
}
/*******************************************************************************
* Service Name:       DC_MOTOR_Rotate
* Sync/Async:         Synchronous
* Reentrancy:         Reentrant
* Parameters (in):    DC Motor State - DC Motor Speed Precentage
* Parameters (inout): None
* Parameters (out):   None
* Return value:       None
* Description:        Rotate the DC Depending on the Motor State
*                     Send the required PWM Duty Cycle based on the required
*                     speed precentage needed.
********************************************************************************/
void DC_MOTOR_Rotate(DC_Motor_State state , uint8 speed)
{
	/*Variable to convert the speed precentage into a duty cycle*/
	uint8 temp_duty_cycle;
    switch ( state )
    {
       case Stop : GPIO_writePin(DC_Motor_PORT,DC_Motor_PINA,LOGIC_LOW);
                   GPIO_writePin(DC_Motor_PORT,DC_Motor_PINB,LOGIC_LOW);
                   break;
       case CW:
    	           GPIO_writePin(DC_Motor_PORT,DC_Motor_PINA,LOGIC_HIGH);
    	           GPIO_writePin(DC_Motor_PORT,DC_Motor_PINB,LOGIC_LOW);
    	           break;
       case CCW:
    	           GPIO_writePin(DC_Motor_PORT,DC_Motor_PINA,LOGIC_LOW);
    	           GPIO_writePin(DC_Motor_PORT,DC_Motor_PINB,LOGIC_HIGH);
    	           break;
    }
    temp_duty_cycle = (speed * 255) / 100 ;
    PWM_Timer0_Start(temp_duty_cycle);
}
