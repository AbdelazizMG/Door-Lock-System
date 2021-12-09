/******************************************************************************
*  Module:    Timers
*  File name: Timers.c
*  Created on: Oct 25, 2021
*  Author: Abdelaziz Mohammad
*******************************************************************************/
/*******************************************************************************
*                                                                              *
*                                  INCLUDES                                    *
*                                                                              *
********************************************************************************/
#include "Timers.h"
#include "avr/io.h"
#include "avr/interrupt.h"
#include "gpio.h"
#include "common_macros.h"
/*******************************************************************************
*                                                                              *
*                                  Global Variables                            *
*                                                                              *
********************************************************************************/
/* Global variables to hold the address of the call back function in the application */
static volatile void (*g_Timer0_callBackPtr)(void)=NULL_PTR;
static volatile void (*g_Timer1_callBackPtr)(void)=NULL_PTR;
static volatile void (*g_Timer2_callBackPtr)(void)=NULL_PTR;

/*******************************************************************************
*                                                                              *
*                              Interrupt Service Routines                      *
*                                                                              *
********************************************************************************/
ISR(TIMER0_OVF_vect)
{
    if ( g_Timer0_callBackPtr != NULL_PTR)
    {
    	(*g_Timer0_callBackPtr)();
    }
}
ISR(TIMER0_COMP_vect)
{
    if ( g_Timer0_callBackPtr != NULL_PTR)
    {
    	(*g_Timer0_callBackPtr)();
    }
}
ISR(TIMER1_COMPA_vect)
{
    if ( g_Timer1_callBackPtr != NULL_PTR)
    {
    	(*g_Timer1_callBackPtr)();
    }
}
ISR(TIMER1_COMPB_vect)
{
    if ( g_Timer1_callBackPtr != NULL_PTR)
    {
    	(*g_Timer1_callBackPtr)();
    }
}
ISR(TIMER2_OVF_vect)
{
    if ( g_Timer2_callBackPtr != NULL_PTR)
    {
    	(*g_Timer2_callBackPtr)();
    }
}
ISR(TIMER2_COMP_vect)
{
    if ( g_Timer2_callBackPtr != NULL_PTR)
    {
    	(*g_Timer2_callBackPtr)();
    }
}

/*******************************************************************************
*                                                                              *
*                              FUNCTIONS Definitions                           *
*                                                                              *
********************************************************************************/
/*******************************************************************************
* Service Name:       Timer_Init
* Sync/Async:         Synchronous
* Reentrancy:         Non Reentrant
* Parameters (in):    configurations - Pointer to post-build configuration data
* Parameters (inout): None
* Parameters (out):   None
* Return value:       None
* Description:        Initialize the Selected Timer module.
********************************************************************************/
void Timer_init(const TIMER_ConfigType * Config_Ptr )
{
	/*Check Timer Number*/
    switch(Config_Ptr->timer_number)
    {
        case Timer_0:
        	           /*Check Timer Mode*/
        	          switch(Config_Ptr->timer_mode)
        	           {
        	                case Normal:           CLEAR_BIT(TCCR0,WGM00);
        	                                       CLEAR_BIT(TCCR0,WGM01);
                                                   /*Non-PWM Mode*/
                                                   SET_BIT(TCCR0,FOC0);
        	                	                   break;

        	                case PWM_PhaseCorrect: SET_BIT(TCCR0,WGM00);
                                                   CLEAR_BIT(TCCR0,WGM01);
        	                	                   break;

        	                case CTC:              CLEAR_BIT(TCCR0,WGM00);
                                                   SET_BIT(TCCR0,WGM01);
                                                   /*Non-PWM Mode*/
                                                   SET_BIT(TCCR0,FOC0);
        	                	                   break;

        	                case PWM_Fast:         SET_BIT(TCCR0,WGM00);
                                                   SET_BIT(TCCR0,WGM01);
        	                	                   break;
        	           }

        	           /*Check OC Pin Mode*/
        	           TCCR0 = (TCCR0 & 0xCF ) | (Config_Ptr->timer_OCPin_mode << 4 ) ;

                       /*Check Prescaler*/
                       TCCR0 = (TCCR0 & 0xF8)  | (Config_Ptr->timer_prescaler );

                       /*TCNT inital Value*/
                       TCNT0 = Config_Ptr->TCNT_value;

                       /*OCR Value*/
                       OCR0 = Config_Ptr->OCR_Value;

                       /*Over Flow interrupt*/
                       TIMSK = (TIMSK & 0xFE) | Config_Ptr->timer_overflowinterrupt;

                       /*Output compare  interrupt*/
                       TIMSK = (TIMSK & 0xFD) | Config_Ptr->timer_OTCInterrupt;

        	           break;


        case Timer_1:

        	           break;


        case Timer_2:
        	          /*Check Timer Mode*/
	                  switch(Config_Ptr->timer_mode)
	                  {
	                         case Normal:           CLEAR_BIT(TCCR2,WGM20);
	                                                CLEAR_BIT(TCCR2,WGM21);
	                                                /*Non-PWM Mode*/
	                                                SET_BIT(TCCR2,FOC2);
	                                                /*Interrupt Enable*/
	                                                CLEAR_BIT(TIMSK,OCIE2);
	                	                            break;
	                         case PWM_PhaseCorrect: SET_BIT(TCCR2,WGM20);
                                                    CLEAR_BIT(TCCR2,WGM21);
	                	                            break;
	                         case CTC:              CLEAR_BIT(TCCR2,WGM20);
                                                    SET_BIT(TCCR2,WGM21);
                                                    /*Non-PWM Mode*/
                                                    SET_BIT(TCCR2,FOC2);
                                                    /*Interrupt Enable*/
                                                    SET_BIT(TIMSK,OCIE2);
	                	                            break;
	                         case PWM_Fast:         SET_BIT(TCCR2,WGM20);
                                                    SET_BIT(TCCR2,WGM21);
	                	                            break;
	                 }
       	              /*Check OC Pin Mode*/
       	              TCCR2 = (TCCR2 & 0xCF ) | (Config_Ptr->timer_OCPin_mode << 4 ) ;

                      /*Check Prescaler*/
                      TCCR2 = (TCCR2 & 0xF8) | Config_Ptr->timer_prescaler ;

                      /*TCNT inital Value*/
                      TCNT2 = Config_Ptr->TCNT_value;

                      /*OCR Value*/
                      OCR2 = Config_Ptr->OCR_Value;

                      /*Over Flow interrupt*/
                      TIMSK = (TIMSK & 0xBF) | Config_Ptr->timer_overflowinterrupt;

    	             break;
    }
}
/*******************************************************************************
* Service Name:       Timer_deInit
* Sync/Async:         Synchronous
* Reentrancy:         Reentrant
* Parameters (in):    Timer Number
* Parameters (inout): None
* Parameters (out):   None
* Return value:       None
* Description:        Disable the Selected Timer module.
********************************************************************************/
void Timer_Deinit(uint8 Timer_Number)
{
	/*Check Timer Number, Then we disable the clock of prescaler*/
	switch (Timer_Number)
	{
	   case Timer_0:   CLEAR_BIT(TCCR0,CS00);
	                   CLEAR_BIT(TCCR0,CS01);
	                   CLEAR_BIT(TCCR0,CS02);
		               break;
	   case Timer_1:   CLEAR_BIT(TCCR1B,CS10);
                       CLEAR_BIT(TCCR1B,CS11);
                       CLEAR_BIT(TCCR1B,CS12);
		               break;
	   case Timer_2:   CLEAR_BIT(TCCR2,CS20);
                       CLEAR_BIT(TCCR2,CS21);
                       CLEAR_BIT(TCCR2,CS22);
		               break;
	}
}
/*******************************************************************************
* Service Name:       Timer0_setCallBack
* Sync/Async:         Synchronous
* Reentrancy:         Non Reentrant
* Parameters (in):    Timer Number
* Parameters (inout): None
* Parameters (out):   None
* Return value:       None
* Description:        Call Back TIMER0 Function.
********************************************************************************/
void Timer0_setCallBack(void(*a_ptr)(void))
{
   g_Timer0_callBackPtr = a_ptr;
}
/*******************************************************************************
* Service Name:       Timer1_setCallBack
* Sync/Async:         Synchronous
* Reentrancy:         Non Reentrant
* Parameters (in):    Timer Number
* Parameters (inout): None
* Parameters (out):   None
* Return value:       None
* Description:        Call Back TIMER1 Function.
********************************************************************************/
void Timer1_setCallBack(void(*a_ptr)(void))
{
	g_Timer1_callBackPtr = a_ptr;
}
/*******************************************************************************
* Service Name:       Timer2_setCallBack
* Sync/Async:         Synchronous
* Reentrancy:         Non Reentrant
* Parameters (in):    Timer Number
* Parameters (inout): None
* Parameters (out):   None
* Return value:       None
* Description:        Call Back TIMER2 Function.
********************************************************************************/
void Timer2_setCallBack(void(*a_ptr)(void))
{
	g_Timer2_callBackPtr = a_ptr;
}




