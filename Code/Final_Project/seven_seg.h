/******************************************************************************
*  Module:    7segment
*  File name: seven_seg.h
*  Created on: Oct 9, 2021
*  Author: Abdelaziz Mohammad
*******************************************************************************/

#ifndef SEVEN_SEG_H_
#define SEVEN_SEG_H_

/*******************************************************************************
*                                                                              *
*                                  INCLUDES                                    *
*                                                                              *
********************************************************************************/
#include "std_types.h"

/*******************************************************************************
*                                                                              *
*                                  Definitions                                 *
*                                                                              *
********************************************************************************/


/*******************************************************************************
*                                                                              *
*                                  FUNCTIONS PROTOTYPE                         *
*                                                                              *
********************************************************************************/
/*******************************************************************************
* Service Name:       _7seg_Setup
* Sync/Async:         Synchronous
* Reentrancy:         Reentrant
* Parameters (in):    Port Number
* Parameters (inout): None
* Parameters (out):   None
* Return value:       None
* Description:        Setup 7seg port pins as output pins
********************************************************************************/
void _7seg_Setup(uint8 port , uint8 first_pin);
/*******************************************************************************
* Service Name:       _7seg_Write
* Sync/Async:         Synchronous
* Reentrancy:         Reentrant
* Parameters (in):    Value to be Displayed
* Parameters (inout): None
* Parameters (out):   None
* Return value:       None
* Description:        Display the required value on the 7segment
********************************************************************************/
void _7seg_Write(uint8 value);

#endif /* SEVEN_SEG_H_ */
