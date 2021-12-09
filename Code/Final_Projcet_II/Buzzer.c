/******************************************************************************
*  Module:    Buzzer
*  File name: Buzzer.h
*  Created on: Oct 25, 2021
*  Author: Abdelaziz Mohammad
*******************************************************************************/
/*******************************************************************************
*                                                                              *
*                                  INCLUDES                                    *
*                                                                              *
********************************************************************************/
#include "std_types.h"
#include "Buzzer.h"
#include "gpio.h"

/*******************************************************************************
*                                                                              *
*                                  Global Variables                            *
*                                                                              *
********************************************************************************/
static uint8 g_buzzer_port ;
static uint8 g_buzzer_pin;

/*******************************************************************************
*                                                                              *
*                              FUNCTIONS Definitions                           *
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
void BUZZER_init(uint8 port , uint8 pin)
{
	/*User Error*/
    if( port > 3 || pin > 7 )
    {

    }
    else
    {
       /*Setup Pin direction as output pin*/
       GPIO_setupPinDirection(port, pin, PIN_OUTPUT);

       /*Saves the port and pin in global variables to be used in functions below*/
       g_buzzer_port = port;
       g_buzzer_pin = pin;
    }
}
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
void BUZZER_ON(void)
{
   /*Make the Buzzer Beebs*/
   GPIO_writePin(g_buzzer_port, g_buzzer_pin, LOGIC_HIGH);
}
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
void BUZZER_OFF(void)
{
	/*Make the Buzzer Stops*/
	 GPIO_writePin(g_buzzer_port, g_buzzer_pin, LOGIC_LOW);
}

