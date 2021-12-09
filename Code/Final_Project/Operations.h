/******************************************************************************
*  Module:    Operations
*  File name: Operations.h
*  Created on: Oct 25, 2021
*  Author: Abdelaziz Mohammad
*******************************************************************************/

#ifndef OPERATIONS_H_
#define OPERATIONS_H_

/*******************************************************************************
*                                                                              *
*                                  INCLUDES                                    *
*                                                                              *
********************************************************************************/
#include "std_types.h"
#include "common_macros.h"

/*******************************************************************************
*                                                                              *
*                                  Definitions                                 *
*                                                                              *
********************************************************************************/
#define ARRAY_SIZE 5
#define DOOR_OPEN_TIMER_VALUE  461
#define DOOR_CLOSE_TIMER_VALUE 461
#define DOOR_HOLD_TIMER_VALUE  92
#define PASSWORD_DIGITS_NUMBER 5
#define MAX_WRONG_ENTRY_NUMBER 3
/*******************************************************************************
*                                                                              *
*                                  FUNCTIONS PROTOTYPE                         *
*                                                                              *
********************************************************************************/
/*******************************************************************************
* Service Name:       PERATION_EnterPassword
* Sync/Async:         Synchronous
* Reentrancy:         Reentrant
* Parameters (in):    None
* Parameters (inout): None
* Parameters (out):   None
* Return value:       None
* Description:        Ask user to enter the password
********************************************************************************/
void OPERATION_EnterPassword(void);
/*******************************************************************************
* Service Name:       OPERATION_reEnterPassword
* Sync/Async:         Synchronous
* Reentrancy:         Reentrant
* Parameters (in):    None
* Parameters (inout): None
* Parameters (out):   None
* Return value:       None
* Description:        Ask user to re-enter the password
********************************************************************************/
void OPERATION_reEnterPassword(void);
/*******************************************************************************
* Service Name:       OPERATION_checkMatch
* Sync/Async:         Synchronous
* Reentrancy:         Reentrant
* Parameters (in):    None
* Parameters (inout): None
* Parameters (out):   None
* Return value:       None
* Description:       Receive Password Match Check from Second MCU and start
*                    Taking action on displaing depending on the value received
********************************************************************************/
void OPERATION_ReceivecheckPasswordMatch(void);
/*******************************************************************************
* Service Name:       OPERATION_MainOptions
* Sync/Async:         Synchronous
* Reentrancy:         Reentrant
* Parameters (in):    None
* Parameters (inout): None
* Parameters (out):   None
* Return value:       uint8
* Description:        Display Main Options for user
********************************************************************************/
void OPERATION_MainOptions(void);

/*******************************************************************************
* Service Name:       OPERATION_
* Sync/Async:         Synchronous
* Reentrancy:         Reentrant
* Parameters (in):    None
* Parameters (inout): None
* Parameters (out):   None
* Return value:       uint8
* Description:        Function to be called when ISR happens
********************************************************************************/
void OPERATION_LCD_Control(void);



#endif /* OPERATIONS_H_ */
