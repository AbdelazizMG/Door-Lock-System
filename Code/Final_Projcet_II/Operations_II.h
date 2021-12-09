/******************************************************************************
*  Module:    Operations_II
*  File name: Operations_II.h
*  Created on: Oct 26, 2021
*  Author: Abdelaziz Mohammad
*******************************************************************************/

#ifndef OPERATIONS_II_H_
#define OPERATIONS_II_H_

/*******************************************************************************
*                                                                              *
*                                  INCLUDES                                    *
*                                                                              *
********************************************************************************/
#include "std_types.h"
#include "common_macros.h"
#include "Timers.h"
extern TIMER_ConfigType TIMER_Config_Struct;

/*******************************************************************************
*                                                                              *
*                                  Definitions                                 *
*                                                                              *
********************************************************************************/
#define ARRAY_SIZE 5
#define DOOR_OPEN_TIMER_VALUE  461
#define DOOR_CLOSE_TIMER_VALUE 461
#define DOOR_HOLD_TIMER_VALUE  92
#define BUZZER_ON_TIMER_VALUE  1845
#define PASSWORD_DIGITS_NUMBER 5
#define MAX_WRONG_ENTRY_NUMBER 3
/*******************************************************************************
*                                                                              *
*                              FUNCTIONS PROTOTYPE                             *
*                                                                              *
********************************************************************************/
/*******************************************************************************
* Service Name:       OPERATION_II_ReceivePassword
* Sync/Async:         Synchronous
* Reentrancy:         Reentrant
* Parameters (in):    None
* Parameters (inout): None
* Parameters (out):   None
* Return value:       None
* Description:        Receive First Password from First MCU
********************************************************************************/
void OPERATION_II_ReceivePassword(void);
/*******************************************************************************
* Service Name:       OPERATION_II_ReceiveSecondPassword
* Sync/Async:         Synchronous
* Reentrancy:         Reentrant
* Parameters (in):    None
* Parameters (inout): None
* Parameters (out):   None
* Return value:       None
* Description:        Receive First Password from First MCU
********************************************************************************/
void OPERATION_II_ReceiveSecondPassword(void);
/*******************************************************************************
* Service Name:       OPERATION_II_checkPasswordMatch
* Sync/Async:         Synchronous
* Reentrancy:         Reentrant
* Parameters (in):    None
* Parameters (inout): None
* Parameters (out):   None
* Return value:       None
* Description:        Check Password Match between different entries
********************************************************************************/
void OPERATION_II_checkPasswordMatch(void);
/*******************************************************************************
* Service Name:       OPERATION_checkEEPROMMatch
* Sync/Async:         Synchronous
* Reentrancy:         Reentrant
* Parameters (in):    None
* Parameters (inout): None
* Parameters (out):   None
* Return value:       None
* Description:        Check Password Match EEPROM and Entry
********************************************************************************/
uint8 OPERATION_II_checkEEPROMMatch(void);
/*******************************************************************************
* Service Name:       Motor
* Sync/Async:         Synchronous
* Reentrancy:         Reentrant
* Parameters (in):    None
* Parameters (inout): None
* Parameters (out):   None
* Return value:       None
* Description:        Function to be called in the ISR
********************************************************************************/
void OPERATIONS_II_Motor (void);
/*******************************************************************************
* Service Name:       OPERATIONS_II_Buzzer
* Sync/Async:         Synchronous
* Reentrancy:         Reentrant
* Parameters (in):    None
* Parameters (inout): None
* Parameters (out):   None
* Return value:       None
* Description:        Function to be called in the ISR
********************************************************************************/
void OPERATIONS_II_Buzzer (void);
/*******************************************************************************
* Service Name:       OPERATIONS_II_Main_Options
* Sync/Async:         Synchronous
* Reentrancy:         Reentrant
* Parameters (in):    None
* Parameters (inout): None
* Parameters (out):   None
* Return value:       None
* Description:        Function to Handle User Main Option from First MCU
********************************************************************************/
void OPERATIONS_II_Main_Options(void);
/*******************************************************************************
* Service Name:       OPERATIONS_II_UART_HANDLE
* Sync/Async:         Synchronous
* Reentrancy:         Non-Reentrant
* Parameters (in):    None
* Parameters (inout): None
* Parameters (out):   None
* Return value:       None
* Description:        Function to be called in main function to handle UART
*                     input from first MCU.
********************************************************************************/
void OPERATIONS_II_UART_HANDLE (const TIMER_ConfigType * TIMER_Config_STRUCT);







#endif /* OPERATIONS_II_H_ */
