/**************************************************************************
* Module:    DC Motor
* File name: DC_Motor.h
* Created on: Oct 9, 2021
* Author: Abdelaziz Mohammad
***************************************************************************/

#ifndef DC_MOTOR_H_
#define DC_MOTOR_H_

/*******************************************************************************
*                                                                              *
*                                  INCLUDES                                    *
*                                                                              *
********************************************************************************/
#include "std_types.h"
/*******************************************************************************
*                                                                              *
*                                  DEFINTIONS                                  *
*                                                                              *
********************************************************************************/
#define DC_Motor_PORT 3   //PORTD
#define DC_Motor_PINA 2
#define DC_Motor_PINB 3
/*******************************************************************************
*                                                                              *
*                             User-Defined Data Types                          *
*                                                                              *
********************************************************************************/
/*******************************************************************************
* Name: DC_Motor_State
* Type: Enumeration
* Range: Stop - CW - CCW
* Description: Data Type for symbolic name for DC Motor States
********************************************************************************/
typedef enum
{
	Stop,
	CW,
	CCW
}DC_Motor_State;
/*******************************************************************************
*                                                                              *
*                             FUNCTIONS PROTOTYPE                              *
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
void DC_MOTOR_Init(void);
/*******************************************************************************
* Service Name:       DC_MOTOR_Rotate
* Sync/Async:         Synchronous
* Reentrancy:         Reentrant
* Parameters (in):    DC Motor State - DC Motor Speed
* Parameters (inout): None
* Parameters (out):   None
* Return value:       None
* Description:        Rotate the DC Depending on the Motor State
*                     Send the required PWM Duty Cycle based on the required
*                     speed Value.
********************************************************************************/
void DC_MOTOR_Rotate(DC_Motor_State state , uint8 speed);


#endif /* DC_MOTOR_H_ */
