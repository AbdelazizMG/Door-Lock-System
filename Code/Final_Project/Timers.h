/******************************************************************************
*  Module:    Timers
*  File name: Timers.h
*  Created on: Oct 25, 2021
*  Author: Abdelaziz Mohammad
*******************************************************************************/

#ifndef TIMERS_H_
#define TIMERS_H_

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


/*******************************************************************************
*                                                                              *
*                       External   Global Variables                            *
*                                                                              *
********************************************************************************/

/*******************************************************************************
*                                                                              *
*                             User-Defined Data Types                          *
*                                                                              *
********************************************************************************/
/*******************************************************************************
* Name: Timer_Number
* Type: Enumeration
* Range: Timer_0 - Timer_1 - Timer_2
* Description: Data Type for symbolic name for Timer Number
********************************************************************************/
typedef enum
{
  Timer_0,
  Timer_1,
  Timer_2
}Timer_Number;
/*******************************************************************************
* Name: Timer_Mode
* Type: Enumeration
* Range: Normal - PWM_PhaseCorrect - CTC - PWM_Fast
* Description: Data Type for symbolic name for Timer Mode
********************************************************************************/
typedef enum
{
  Normal,
  PWM_PhaseCorrect,
  CTC,
  PWM_Fast
}Timer_Mode;
/*******************************************************************************
* Name: Timer_Prescaler
* Type: Enumeration
* Range: No_Clock - No_Prescaler - FCPU_8 - FCPU_64 - FCPU_256 - FCPU_1024
*        External_Falling - External_Rising
* Description: Data Type for symbolic name for Timer Prescaler
********************************************************************************/
typedef enum
{
   /*Timer 0 and Timer 1 Values*/
   No_Clock=0,
   No_Prescaler=1,
   FCPU_8=2,
   FCPU_64=3,
   FCPU_256=4,
   FCPU_1024=5,
   External_Falling=6,
   External_Rising=7,

   /*Timer 2 Values*/
   Timer2_FCPU_8=2,
   Timer2_FCPU_32=3,
   Timer2_FCPU_64=4,
   Timer2_FCPU_128=5,
   Timer2_FCPU_256=6,
   Timer2_FCPU_1024=7
}Timer_Prescaler;
/*******************************************************************************
* Name: Timer_overFlowInterrupt
* Type: Enumeration
* Range: OF_Interrupt_Disable - OF_Interrupt_Enable
* Description: Data Type for symbolic name for Timer Overflow Interrupt
********************************************************************************/
typedef enum
{
  OF_Interrupt_Disable,
  OF_Interrupt_Enable
}Timer_overFlowInterrupt;
/*******************************************************************************
* Name: Timer_outputCompareMatchInterrupt
* Type: Enumeration
* Range: OTC_Interrupt_Disable - OTC_Interrupt_Enable
* Description: Data Type for symbolic name for Timer Output Compare Match Interrupt
********************************************************************************/
typedef enum
{
  OTC_Interrupt_Disable,
  OTC_Interrupt_Enable
}Timer_outputCompareMatchInterrupt;
/*******************************************************************************
* Name: Timer_OCPin_Mode
* Type: Enumeration
* Range:Disconnected - Toggle - NinInverting - Inverting
* Description: Data Type for symbolic name for Timer OC Pin Mode
********************************************************************************/
typedef	enum
{
	OCPin_Disconnected,
	OCPin_Toggle,
	OCPin_NinInverting,
	OCPin_Inverting
}Timer_OCPin_Mode;
/*******************************************************************************
* Name: Timer_ConfigType
* Type: Structure
* Range: Hardware dependent structure
* Description: Type of the external data structure containing the initialization
*              data for this module. This is the one that is sent to the init
*              function.
********************************************************************************/
typedef struct
{
	Timer_Number timer_number;
	Timer_Mode timer_mode;
	Timer_Prescaler timer_prescaler;
	Timer_overFlowInterrupt timer_overflowinterrupt;
	Timer_outputCompareMatchInterrupt timer_OTCInterrupt;
	Timer_OCPin_Mode timer_OCPin_mode;
	uint16 TCNT_value;
	uint8 OCR_Value;
}TIMER_ConfigType;
/*******************************************************************************
*                                                                              *
*                                  FUNCTIONS PROTOTYPE                         *
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
void Timer_init(const TIMER_ConfigType * Config_Ptr );
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
void Timer_Deinit(uint8 Timer_Number);
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
void Timer0_setCallBack(void(*a_ptr)(void));
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
void Timer1_setCallBack(void(*a_ptr)(void));
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
void Timer2_setCallBack(void(*a_ptr)(void));


#endif /* TIMERS_H_ */
