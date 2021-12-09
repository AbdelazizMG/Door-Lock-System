/******************************************************************************
*  Module:    Operations_II
*  File name: Operations_II.h
*  Created on: Oct 26, 2021
*  Author: Abdelaziz Mohammad
*******************************************************************************/
/*******************************************************************************
*                                                                              *
*                                  INCLUDES                                    *
*                                                                              *
********************************************************************************/
#define F_CPU 8000000
#include "Operations_II.h"
#include "PWM.h"
#include "DC_Motor.h"
#include "Buzzer.h"
#include "Timers.h"
#include "UART.h"
#include "avr/io.h"
#include "I2C.h"
#include "external_eeprom.h"
#include "util/delay.h"
/*******************************************************************************
*                                                                              *
*                                  Global Variables                            *
*                                                                              *
********************************************************************************/
uint16 g_Interrupts_number = 0;

uint8 g_Password_Entry1[ARRAY_SIZE];
uint8 g_Password_Entry2[ARRAY_SIZE];
/*******************************************************************************
*                                                                              *
*                              FUNCTIONS Definitions                           *
*                                                                              *
********************************************************************************/
/*******************************************************************************
* Service Name:       OPERATION_ReceivePassword
* Sync/Async:         Synchronous
* Reentrancy:         Reentrantoopippp
* Parameters (in):    None
* Parameters (inout): None
* Parameters (out):   None
* Return value:       None
* Description:        Receive First Password from First MCU
********************************************************************************/
void OPERATION_II_ReceivePassword(void)
{
   /*Variable to hold keypadd press*/
	uint8 key1;

   /*counter for while loop*/
    uint8 counter = 0;

   while ( counter < PASSWORD_DIGITS_NUMBER )
   {
       /*Receive Digit from first MCU*/
	   key1 = UART_receiveByte();

	   if(key1 != '*')
	   {
		   /*Store Digit in the array*/
		   g_Password_Entry1[counter]=key1;

		   /*Increament counter*/
		   counter ++;
	   }
	   else if ( key1 == '*' && counter !=0)
	   {
		   counter = counter-1;
	   }


   }


}
/*******************************************************************************
* Service Name:       OPERATION_ReceiveSecondPassword
* Sync/Async:         Synchronous
* Reentrancy:         Reentrantoopippp
* Parameters (in):    None
* Parameters (inout): None
* Parameters (out):   None
* Return value:       None
* Description:        Receive First Password from First MCU
********************************************************************************/
void OPERATION_II_ReceiveSecondPassword(void)
{
	   /*Variable to hold keypadd press*/
		uint8 key1;

	   /*counter for while loop*/
	    uint8 counter = 0;

	   while ( counter < PASSWORD_DIGITS_NUMBER )
	   {
	       /*Receive Digit from first MCU*/
		   key1 = UART_receiveByte();

		   if(key1 != '*')
		   {
			   /*Store Digit in the array*/
			   g_Password_Entry2[counter]=key1;

			   /*Increament counter*/
			   counter ++;
		   }
		   else if ( key1 == '*' && counter !=0)
		   {
			   counter = counter - 1;
		   }


	   }
}
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
void OPERATION_II_checkPasswordMatch(void)
{
	   /*Variable to be used in while loop*/
	   uint8 counter = 0;

	   /*flag for matching detection - if 0 missmatch - if 1 matched*/
	   uint8 flag = 1 ;

	   /*Variable to hold number of miss matches*/
	   static uint8 missmatch_counter = 0;

	   /*Check Each Element in the Array*/
	   while (counter < PASSWORD_DIGITS_NUMBER )
	   {
	       if ( g_Password_Entry1[counter] != g_Password_Entry2[counter])
	       {
	   	    flag = 0 ;
	   	    break;
	       }
	       counter ++ ;
	   }

	   /*Resetting Counter for EEPROM LOOP*/
	   counter = 0;

     	/*Send to First MCU: 0 if dismatches , 1 if matches*/
     	UART_sendByte(flag);

	   switch (flag)
	   {
	      /*Missmatched Case*/
	      /*Repeat Step 1 */
	      case 0 :  missmatch_counter++;
	                if(missmatch_counter== MAX_WRONG_ENTRY_NUMBER)
	                {
	            		BUZZER_ON();
	            		Timer_init(&TIMER_Config_Struct);
	            		Timer2_setCallBack(OPERATIONS_II_Buzzer);
	            		g_Interrupts_number= 215;
	                	missmatch_counter = 0;
	                }
	                else
	                {
	                	OPERATION_II_ReceivePassword();
	                	OPERATION_II_ReceiveSecondPassword();
	                	OPERATION_II_checkPasswordMatch();
	                }
	    	        break;

	      /*Matched Case*/

	      /* Go to Main Options*/
	      case 1 :
	    	  while (counter < 5 )
	    	  {

	          	EEPROM_writeByte((uint16)(EEPROM_ADDRESS + counter), g_Password_Entry1[counter]);
	    		_delay_ms(10);

	    		  counter ++ ;
	    	  }

	    	        break;

	    	  /*Start Display Main Options*/
	   }


}
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
uint8 OPERATION_II_checkEEPROMMatch(void)
{
	   /*counter for while loop*/
	   uint8 counter = 0;

	   /*flag for matching detection - initially matched*/
	   uint8 flag = 1 ;

	   /*Variable to hold the value read from EEPROM*/
       uint8 value = 0;

	   while (counter < 5 )
	   {
		   /*read Byte from EEPROM*/
		   EEPROM_readByte( (uint16)(EEPROM_ADDRESS + counter), &value);


		   /*Check if any element is not matched*/
		   if(g_Password_Entry1[counter] != value)
		   {
			   flag = 0;
			   break;
		   }
		   counter ++ ;
	   }

	   return flag;
}
/*******************************************************************************
* Service Name:       OPERATIONS_II_Motor
* Sync/Async:         Synchronous
* Reentrancy:         Reentrant
* Parameters (in):    None
* Parameters (inout): None
* Parameters (out):   None
* Return value:       None
* Description:        Function to be called in the ISR
********************************************************************************/
void OPERATIONS_II_Motor (void)
{
	/*Variable To Hold interrupt number*/
	static uint16 counter = 0 ;

	/*Variable to detect which direction the motor is rotating at*
	 * 0 CW - 1 CCW */
	static uint8 flag = 0;

	counter ++ ;

	/*for 5 seconds*/
	if(counter == g_Interrupts_number && g_Interrupts_number == DOOR_OPEN_TIMER_VALUE && flag ==0)
	{
		_delay_ms(800);
		DC_MOTOR_Rotate(Stop, 0);
		counter = 0;
		/*Get ready for holding motor 3 seconds*/
		g_Interrupts_number = DOOR_HOLD_TIMER_VALUE;
		flag = 1;
	}
	else if (counter == g_Interrupts_number && g_Interrupts_number == DOOR_HOLD_TIMER_VALUE )
	{
		/*after holding motor for 3 seconds , rotate CCW for 15 seconds*/

		DC_MOTOR_Rotate(CCW, 75);
		g_Interrupts_number = DOOR_CLOSE_TIMER_VALUE;
		counter = 0;
	}
	else if (counter == g_Interrupts_number && g_Interrupts_number == DOOR_CLOSE_TIMER_VALUE && flag == 1 )
	{
		/*after 15 seconds stop the motor and display finished*/
		DC_MOTOR_Rotate(Stop, 0);
		flag = 0 ;
		counter = 0;
		Timer_Deinit(2);
		OPERATIONS_II_Main_Options();
	}
}
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
void OPERATIONS_II_Buzzer (void)
{
   static uint16 counter = 0 ;

   counter ++ ;

   if(counter == g_Interrupts_number && g_Interrupts_number == 215 )
   {
       BUZZER_OFF();
       counter = 0 ;
   }
}
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
void OPERATIONS_II_Main_Options(void)
{
	/*Variable to Hold EEPROM Check*/
	uint8 Motor_Drive_Check = 0;

	/*Variable to hold number of miss matches*/
	 static uint8 missmatch_counter = 0;

	 /*Variable to Hold user input*/
	 uint8 user_input=0;

	/*4- Take User option input from first MCU by UART*/
	user_input = UART_receiveByte();

	/* 5- Take Password for  '+' Entry and Compare with EEPROM and Send by UART Results */

	OPERATION_II_ReceivePassword();
	Motor_Drive_Check = OPERATION_II_checkEEPROMMatch();
	UART_sendByte(Motor_Drive_Check);


	while ( Motor_Drive_Check == 0)
	{
		missmatch_counter++;

		/*if Mismatches are 3 , Buzzer ON*/
		if(missmatch_counter == MAX_WRONG_ENTRY_NUMBER)
		{
			BUZZER_ON();
			Timer_init(&TIMER_Config_Struct);
			Timer2_setCallBack(OPERATIONS_II_Buzzer);
			g_Interrupts_number= BUZZER_ON_TIMER_VALUE;
			missmatch_counter = 0;
			break;
		}
		/*Re-Enter Password and Check Again until 3 tries are done*/
		OPERATION_II_ReceivePassword();
		Motor_Drive_Check = OPERATION_II_checkEEPROMMatch();
		UART_sendByte(Motor_Drive_Check);
    }

		/*Matches Case*/
	    if ( Motor_Drive_Check == 1)
		{
	    	switch( user_input)
	    	{
	    	case '+':
	    		Timer_init(&TIMER_Config_Struct);
	    		Timer2_setCallBack(OPERATIONS_II_Motor);
	    		g_Interrupts_number= DOOR_OPEN_TIMER_VALUE;
                _delay_ms(800);
	    		DC_MOTOR_Rotate(CW, 75);
	    		       break;
	    	case '-':
	    		OPERATION_II_ReceivePassword();
	    		OPERATION_II_ReceiveSecondPassword();
	    		OPERATION_II_checkPasswordMatch();
	    		OPERATIONS_II_Main_Options();
	    		       break;
	    	}

		}
}
/*******************************************************************************
* Service Name:       OPERATIONS_II_UART_HANDLE
* Sync/Async:         Synchronous
* Reentrancy:         Non-Reentrant
* Parameters (in):    Timer Config Struct
* Parameters (inout): None
* Parameters (out):   None
* Return value:       None
* Description:        Function to be called in main function to handle UART
*                     input from first MCU.
********************************************************************************/
void OPERATIONS_II_UART_HANDLE(const TIMER_ConfigType * TIMER_Config_STRUCT)
{
	/*                                             STEPS
	 * 1- Take First Password from First MCU
	 * 2- Take Second Password from second MCU
	 * 3- Check Password
	 * - if Password is not Correct: it will repeat taking and comparing Passwords until
	 *    user enter the right passoword or BUZZER will be on after 3 failures.
	 * - if Password is Correct: Receive New Passoword and Compare it with one Saved in EEPROM
	 *    and start Main Options.
	 * 4- Take User option input from first MCU by UART
	 * 5- Take Password for  '+' Entry and Compare with EEPROM and Send by UART Results:
	 * - if Matches: Start Driving the Motor Function
	 * - if Dismatches: Retake Password until it's right or after 3 times start Buzzer.
	 * 6-
	 *
	 */



	/*  1-Take First Password from First MCU */
	OPERATION_II_ReceivePassword();

	/*  2- Take Second Password from second MCU */
	OPERATION_II_ReceiveSecondPassword();

	/*  3- Check Password */
	OPERATION_II_checkPasswordMatch();

	/*  Handle Steps: 4 - 5 -6 */
	OPERATIONS_II_Main_Options();


}

