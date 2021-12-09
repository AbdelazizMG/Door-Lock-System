/******************************************************************************
*  Module:    Buzzer
*  File name: Buzzer.h
*  Created on: Oct 25, 2021
*  Author: Abdelaziz Mohammad
*******************************************************************************/

#ifndef BUZZER_H_
#define BUZZER_H_

/*******************************************************************************
*                                                                              *
*                                  INCLUDES                                    *
*                                                                              *
********************************************************************************/
#include "std_types.h"

/*******************************************************************************
*                                                                              *
*                              FUNCTIONS PROTOTYPE                             *
*                                                                              *
********************************************************************************/
/*******************************************************************************
* Service Name:       BUZZER_init
* Sync/Async:         Synchronous
* Reentrancy:         Reentrant
* Parameters (in):    PORT - PIN Number
* Parameters (inout): None
* Parameters (out):   None
* Return value:       None
* Description:        Define buzzer pin as output pin
*                     Saves port and pin in global variables defined above
********************************************************************************/
void BUZZER_init(uint8 port , uint8 pin);
/*******************************************************************************
* Service Name:       BUZZER_ON
* Sync/Async:         Synchronous
* Reentrancy:         Reentrant
* Parameters (in):    None
* Parameters (inout): None
* Parameters (out):   None
* Return value:       None
* Description:        Make The Buzzer Beebs
********************************************************************************/
void BUZZER_ON(void);
/*******************************************************************************
* Service Name:       BUZZER_OFF
* Sync/Async:         Synchronous
* Reentrancy:         Reentrant
* Parameters (in):    None
* Parameters (inout): None
* Parameters (out):   None
* Return value:       None
* Description:        Make The Buzzer Stop
********************************************************************************/
void BUZZER_OFF(void);

#endif /* BUZZER_H_ */
