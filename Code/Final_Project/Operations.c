/******************************************************************************
*  Module:    Operations
*  File name: Operations.h
*  Created on: Oct 25, 2021
*  Author: Abdelaziz Mohammad
*******************************************************************************/
/*******************************************************************************
*                                                                              *
*                                  INCLUDES                                    *
*                                                                              *
********************************************************************************/
#define F_CPU 8000000
#include "LCD.h"
#include "keypad.h"
#include "util/delay.h"
#include "Operations.h"
#include "Timers.h"
#include "UART.h"
#include "avr/io.h"
#include "seven_seg.h"
/*******************************************************************************
*                                                                              *
*                              Global Variables                                *
*                                                                              *
********************************************************************************/
/*Variable used in call back functions*/
uint16 g_Interrupt_Number=0;

/*Timer Configuration Structure*/
extern const TIMER_ConfigType Config_Struct;

/*******************************************************************************
*                                                                              *
*                              FUNCTIONS Definitions                           *
*                                                                              *
********************************************************************************/
/*******************************************************************************
* Service Name:       OPERATION_EnterPassword
* Sync/Async:         Synchronous
* Reentrancy:         Reentrantoopippp
* Parameters (in):    None
* Parameters (inout): None
* Parameters (out):   None
* Return value:       None
* Description:        Ask user to enter the password , with option to delete wrong
*                     Click.
********************************************************************************/
void OPERATION_EnterPassword(void)
{
	/*Clear Screen from prvious operation*/
	LCD_clearScreen();

   /*Variable to hold keypadd press*/
	uint8 key1;

   /*counter for while loop*/
    uint8 counter = 0;

   /*Actual Operation*/
   LCD_displayString("Enter Password:");
   LCD_moveCursor(1, 0);

   while ( counter < PASSWORD_DIGITS_NUMBER)
   {
	   /*Get Keypress from the user*/
	   key1 = KEYPAD_getPressedKey();

	   UART_sendByte(key1);

	   /*Option to delete wrong Click*/
	   if(key1 == '*' && counter !=0)
	   {

		   LCD_moveCursor(1, counter-1);
		   LCD_displayCharacter(' ');
		   LCD_moveCursor(1, counter-1);
		   counter= counter - 1 ;
		   _delay_ms(800);

	   }
	   else if (key1 != '*')
	   {
		   /*Display Key Press on LCD */
		   LCD_displayCharacter('*');

		   _delay_ms(800);



		   /*Increament counter*/
		   counter ++;
	   }


   }


}
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
void OPERATION_reEnterPassword(void)
{
    /*Clear screen from previous operation*/
	LCD_clearScreen();

   /*Variable to hold keypad press*/
	uint8 key;

   /*counter for while loop*/
    uint8 counter = 0;

   /*Actual Operation*/
   LCD_displayString("Re Enter Pass:");
   LCD_moveCursor(1, 0);

   /*Take 5 digits from the user*/
   while ( counter < PASSWORD_DIGITS_NUMBER )
   {
	   /*Get Key press from the user*/
	   key = KEYPAD_getPressedKey();


	   /*Option to delete wrong Click*/
	   if(key == '*' && counter !=0)
	   {
		   UART_sendByte(key);
		   LCD_moveCursor(1, counter-1);
		   LCD_displayCharacter(' ');
		   LCD_moveCursor(1, counter-1);
		   counter= counter - 1 ;
		   _delay_ms(800);

	   }
	   else if ( key != '*')
	   {
		   /*Display Key Press on LCD*/

		   LCD_displayCharacter('*');
		   _delay_ms(800);

		   /*Send First Digit by UART*/
		   UART_sendByte(key);

		   /*Increament counter*/
		   counter ++;
	   }

   }


}
/*******************************************************************************
* Service Name:       OPERATION_checkMatch
* Sync/Async:         Synchronous
* Reentrancy:         Reentrant
* Parameters (in):    None
* Parameters (inout): None
* Parameters (out):   None
* Return value:       None
* Description:        Receive Password Match Check from Second MCU and start
*                     Taking action on displaing depending on the value received
********************************************************************************/
void OPERATION_ReceivecheckPasswordMatch(void)
{
   /*flag for matching detection - if 0 missmatch - if 1 matched*/
   uint8 flag = 5 ;

   /*Variable to hold number of miss matches*/
   static uint8 missmatch_counter = 0;

   /*Take Response from Second MCU - if 0 missmatch - if 1 matched */
   flag = UART_receiveByte();

   switch (flag)
   {
      /*Missmatched Case*/
      /*Repeat Step 1 */
      case 0 :  missmatch_counter++;

               _7seg_Write(missmatch_counter);
                if(missmatch_counter== MAX_WRONG_ENTRY_NUMBER)
                {

                	LCD_clearScreen();
                	LCD_displayString("Error");
                	missmatch_counter = 0;
                }
                else
                {
                	OPERATION_EnterPassword();
                	OPERATION_reEnterPassword();
                	OPERATION_ReceivecheckPasswordMatch();
                }
    	        break;

      /* Go to Main Options*/
      case 1 :

    	        _7seg_Write(0);

    	        /*Go to Main Options*/
    	        OPERATION_MainOptions();
    	        break;
   }
}
/*******************************************************************************
* Service Name:       OPERATION_MainOptions
* Sync/Async:         Synchronous
* Reentrancy:         Reentrant
* Parameters (in):    None
* Parameters (inout): None
* Parameters (out):   None
* Return value:       None
* Description:        Display Main Options for user
********************************************************************************/
void OPERATION_MainOptions(void)
{
    /*Clear screen from previous operation*/
	LCD_clearScreen();

	/*variable to hold keypad press*/
	uint8 key;

	/*Variable to check Driving Motor*/
	uint8 Motor_Drive_Check = 0;

	/*Variable to hold number of miss matches*/
	 static uint8 missmatch_counter = 0;

	/*Actual Operation*/
	LCD_displayString("+: Open Door");
	LCD_moveCursor(1, 0);
	LCD_displayString("-: Change Pass");

	/*Get Key Press */
	key = KEYPAD_getPressedKey();

	_delay_ms(800);

	/*Send User option input by UART*/
	 UART_sendByte(key);


	 /*Enter Password*/
	 OPERATION_EnterPassword();

	 /*IF matched with password saved in EEPROM - Drive Motor*/
	 Motor_Drive_Check = UART_receiveByte();

	 /*Miss Matched Case*/

	 while ( Motor_Drive_Check == 0 )
	 {
		 missmatch_counter++;

		 _7seg_Write(missmatch_counter);

		 if(missmatch_counter == MAX_WRONG_ENTRY_NUMBER)
		 {
			 LCD_clearScreen();
			 LCD_displayString("Error");
			 missmatch_counter = 0;
			 break;
		 }

		 /*Enter Password*/
		 OPERATION_EnterPassword();
		 Motor_Drive_Check = UART_receiveByte();

	 }

	 /*Matched Case*/
	 if(Motor_Drive_Check == 1)
	 {
		 switch (key)
		 {
		 case '+':

		 LCD_clearScreen();
		 LCD_displayString("Opening Door");

		 _7seg_Write(0);


		 /*Init Timer*/
		 Timer_init(&Config_Struct);

		 /*I-Bit*/
		 SET_BIT(SREG,7);

		 /*Setting Time for 15 seconds*/
		 g_Interrupt_Number=DOOR_OPEN_TIMER_VALUE;

		 /*Start Taking ACTION in ISR*/
		 Timer0_setCallBack(OPERATION_LCD_Control);
		 break;


		 /*Change Password Case*/
		 case '-' :
			 /*repeat step 1*/
			 OPERATION_EnterPassword();
			 OPERATION_reEnterPassword();
			 OPERATION_ReceivecheckPasswordMatch();
			 break;

		 default:
			 break;

		 }

     }

}
/*******************************************************************************
* Service Name:       OPERATION_LCD_Control
* Sync/Async:         Synchronous
* Reentrancy:         Reentrant
* Parameters (in):    None
* Parameters (inout): None
* Parameters (out):   None
* Return value:       uint8
* Description:        Function to be called when ISR happens
********************************************************************************/
void OPERATION_LCD_Control(void)
{
	/*Variable to hold interrupt counts*/
	static uint16 counter = 0;

	/*Variable to detect which direction the motor is rotating*
	 * 0 indicated CW , 1 indicates CCW
	 */

	static uint8 flag = 0;

	counter ++ ;

	/*Holdind Motor for three seconds perparing for second rotation*/
	if(counter ==  g_Interrupt_Number && g_Interrupt_Number == DOOR_OPEN_TIMER_VALUE && flag ==0)
	{
		LCD_clearScreen();
		LCD_displayString("Holding Door");

   	    g_Interrupt_Number= DOOR_HOLD_TIMER_VALUE;
		counter=0;
		flag = 1;
	}
	/*Rotating Motor in CCW Direction*/
	else if (counter ==  g_Interrupt_Number && g_Interrupt_Number == DOOR_HOLD_TIMER_VALUE)
	{
   	      LCD_clearScreen();
   	      LCD_displayString("Closing Door");

   	      g_Interrupt_Number= DOOR_CLOSE_TIMER_VALUE;
   	      counter = 0;
	}
	/*after 15 seconds stop the timer*/
	else if(counter ==  g_Interrupt_Number && g_Interrupt_Number == DOOR_CLOSE_TIMER_VALUE && flag ==1)
	{
        counter=0;
        flag=0;
        Timer_Deinit(0);
        OPERATION_MainOptions();


	}

}

