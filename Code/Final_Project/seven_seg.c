/******************************************************************************
*  Module:    7segment
*  File name: seven_seg.c
*  Created on: Oct 9, 2021
*  Author: Abdelaziz Mohammad
*******************************************************************************/
/*******************************************************************************
*                                                                              *
*                                  INCLUDES                                    *
*                                                                              *
********************************************************************************/
#include "seven_seg.h"
#include "gpio.h"
#include "avr/io.h"

/*******************************************************************************
*                                                                              *
*                              Global Variables                                *
*                                                                              *
********************************************************************************/
/*This Global Variable is to save the 7seg port to use it in the second function*/
uint8 g_7seg_port;

/*******************************************************************************
*                                                                              *
*                              FUNCTIONS Definitions                           *
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
* Description:        Setup 7seg port pins as output pins starting from PIN0 : PIN3
********************************************************************************/
void _7seg_Setup(uint8 port , uint8 first_pin)
{
	 g_7seg_port = port;
	switch(port)
	{
	 /*Setting up the 7447 decoder 4 pins as output pins starting from PIN0:PIN3*/
 	 case PORTA_ID:
		           GPIO_setupPinDirection(PORTA_ID,first_pin,PIN_OUTPUT);
		           GPIO_setupPinDirection(PORTA_ID,first_pin+1,PIN_OUTPUT);
		           GPIO_setupPinDirection(PORTA_ID,first_pin+2,PIN_OUTPUT);
		           GPIO_setupPinDirection(PORTA_ID,first_pin+3,PIN_OUTPUT);
		           break;
 	 case PORTB_ID:
 			       GPIO_setupPinDirection(PORTB_ID,first_pin,PIN_OUTPUT);
 			       GPIO_setupPinDirection(PORTB_ID,first_pin+1,PIN_OUTPUT);
 			       GPIO_setupPinDirection(PORTB_ID,first_pin+2,PIN_OUTPUT);
 			       GPIO_setupPinDirection(PORTB_ID,first_pin+3,PIN_OUTPUT);
 			       break;
 	 case PORTC_ID:
 			       GPIO_setupPinDirection(PORTC_ID,first_pin,PIN_OUTPUT);
 			       GPIO_setupPinDirection(PORTC_ID,first_pin+1,PIN_OUTPUT);
 			       GPIO_setupPinDirection(PORTC_ID,first_pin+2,PIN_OUTPUT);
 			       GPIO_setupPinDirection(PORTC_ID,first_pin+3,PIN_OUTPUT);
 			           break;
 	 case PORTD_ID:
 			       GPIO_setupPinDirection(PORTD_ID,first_pin,PIN_OUTPUT);
 			       GPIO_setupPinDirection(PORTD_ID,first_pin+1,PIN_OUTPUT);
 			       GPIO_setupPinDirection(PORTD_ID,first_pin+2,PIN_OUTPUT);
 			       GPIO_setupPinDirection(PORTD_ID,first_pin+3,PIN_OUTPUT);
 			           break;
 	/*For wrong port entry , do nothing*/
 	 default: break;
	}
}
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
void _7seg_Write(uint8 value)
{
	 /*Check if the required value is from 0:9 , otherwise do nothing*/
	 if(value >=0 && value <= 9 )
	 {
         switch(value)
         {
         case 0 :   		 GPIO_writePin( g_7seg_port, 3, LOGIC_LOW);
                             GPIO_writePin( g_7seg_port, 4, LOGIC_LOW);
                             GPIO_writePin( g_7seg_port, 5, LOGIC_LOW);
                             GPIO_writePin( g_7seg_port, 6, LOGIC_LOW);
        	        break;
         case 1 :   		 GPIO_writePin( g_7seg_port, 3, LOGIC_HIGH);
                             GPIO_writePin( g_7seg_port, 4, LOGIC_LOW);
                             GPIO_writePin( g_7seg_port, 5, LOGIC_LOW);
                             GPIO_writePin( g_7seg_port, 6, LOGIC_LOW);
        	        break;
         case 2 :   		 GPIO_writePin( g_7seg_port, 3, LOGIC_LOW);
                             GPIO_writePin( g_7seg_port, 4, LOGIC_HIGH);
                             GPIO_writePin( g_7seg_port, 5, LOGIC_LOW);
                             GPIO_writePin( g_7seg_port, 6, LOGIC_LOW);
        	        break;
         case 3 :   		 GPIO_writePin( g_7seg_port, 3, LOGIC_HIGH);
                             GPIO_writePin( g_7seg_port, 4, LOGIC_HIGH);
                             GPIO_writePin( g_7seg_port, 5, LOGIC_LOW);
                             GPIO_writePin( g_7seg_port, 6, LOGIC_LOW);
        	        break;
         }


	 }


}
