/******************************************************************************
*  Module:    UART
*  File name: UART.h
*  Created on: Oct 10, 2021
*  Author: Abdelaziz Mohammad
*******************************************************************************/
/*******************************************************************************
*                                                                              *
*                                  INCLUDES                                    *
*                                                                              *
********************************************************************************/
#include "UART.h"
#include "std_types.h"
#include "avr/io.h"
#include "avr/interrupt.h"
#include "common_macros.h"
/*******************************************************************************
*                                                                              *
*                                  Global Variables                            *
*                                                                              *
********************************************************************************/
 uint16 g_UBRR_value = 0;
 uint8  g_speed_mode_division_factor = 0;
 /*******************************************************************************
 *                                                                              *
 *                          Interrupt Service Routine                           *
 *                                                                              *
 ********************************************************************************/
ISR(USART_RXC_vect)
 {

 }

ISR(USART_TXC_vect)
 {

 }
/*******************************************************************************
*                                                                              *
*                              FUNCTIONS Definitions                           *
*                                                                              *
********************************************************************************/
/*******************************************************************************
* Service Name:       UART_Init
* Sync/Async:         Synchronous
* Reentrancy:         Non Reentrant
* Parameters (in):    configurations - Pointer to post-build configuration data
* Parameters (inout): None
* Parameters (out):   None
* Return value:       None
* Description:        Initialize the UART module.
********************************************************************************/
void UART_Init(const UART_ConfigType * Config_Ptr)
{
	/*Config Operation Mode*/
    switch( Config_Ptr ->operation_mode)
    {
      case Receiver:                SET_BIT(UCSRB,RXEN);
    	                            break;
      case Transmitter:             SET_BIT(UCSRB,TXEN);
    	                            break;
      case Transmitter_Receiver:    SET_BIT(UCSRB,RXEN);
                                    SET_BIT(UCSRB,TXEN);
    	                            break;
    }
	/*Config Transmission Speed*/
	switch( Config_Ptr ->speed)
	{
	  case Normal_Speed:   CLEAR_BIT(UCSRA,U2X);
	                       g_speed_mode_division_factor = 16;
	 	                   break;
	  case Double_Speed:   SET_BIT(UCSRA,U2X);
                           g_speed_mode_division_factor = 8;
	  		               break;
	}

	/*Config Synchronization of UART*/
	switch ( Config_Ptr->synchronization)
	{
	 case Asynchronous: SET_BIT(UCSRC,URSEL);
	                    CLEAR_BIT(UCSRC,UMSEL);
		                break;
	 case Synchronous:  SET_BIT(UCSRC,URSEL);
	                    SET_BIT(UCSRC,UMSEL);
	 		            break;
	}

	/*Config Parity Bit of UART*/
	switch ( Config_Ptr ->parity)
	{
	  case Parity_Disabled: SET_BIT(UCSRC,URSEL);
		                    CLEAR_BIT(UCSRC,UPM0);
	                        CLEAR_BIT(UCSRC,UPM1);
	                        break;
	  case Parity_Odd:      SET_BIT(UCSRC,URSEL);
		                    SET_BIT(UCSRC,UPM0);
                            SET_BIT(UCSRC,UPM1);
                            break;
	  case Parity_Even:     SET_BIT(UCSRC,URSEL);
		                    CLEAR_BIT(UCSRC,UPM0);
                            SET_BIT(UCSRC,UPM1);
                            break;
	}

	/*Config Number of Stop Bits of UART*/
    switch( Config_Ptr ->stop_bit)
    {
    case StopBit_1:  CLEAR_BIT(UCSRC,USBS);
    	             break;
    case StopBit_2:  SET_BIT(UCSRC,USBS);
    	             break;
    }

    /*Config Number of Data Frame Bits*/
    switch ( Config_Ptr ->dataframe_bits )
    {
    case DataFrame_5Bits:  CLEAR_BIT(UCSRC,UCSZ0);
                           CLEAR_BIT(UCSRC,UCSZ1);
                           CLEAR_BIT(UCSRB,UCSZ2);
    	                   break;
    case DataFrame_6Bits:  SET_BIT(UCSRC,UCSZ0);
                           CLEAR_BIT(UCSRC,UCSZ1);
                           CLEAR_BIT(UCSRB,UCSZ2);
    	                   break;
    case DataFrame_7Bits:  CLEAR_BIT(UCSRC,UCSZ0);
                           SET_BIT(UCSRC,UCSZ1);
                           CLEAR_BIT(UCSRB,UCSZ2);
    	                   break;
    case DataFrame_8Bits:  SET_BIT(UCSRC,UCSZ0);
                           SET_BIT(UCSRC,UCSZ1);
                           CLEAR_BIT(UCSRB,UCSZ2);
    	                   break;
    case DataFrame_9Bits:  SET_BIT(UCSRC,UCSZ0);
                           SET_BIT(UCSRC,UCSZ1);
                           SET_BIT(UCSRB,UCSZ2);
    	                   break;
    }


    switch( Config_Ptr ->baud_rate)
    {
    case BaudRate_9600:   /*For 1 MHz  value = 12 , For 8MHz value = 103*/
    	                  UBRRH = 103>>8;
                           UBRRL = 103;
    	                  break;
    	                  /*There is a bug in the equation shown blow */
    case BaudRate_14400:  g_UBRR_value= (uint16)(((F_CPU / (g_speed_mode_division_factor * 14400 )))-1);
    	                  break;
    case BaudRate_19200:  g_UBRR_value= (uint16)(((F_CPU / (g_speed_mode_division_factor * 19200 )))-1);
    	                  break;
    case BaudRate_115200: g_UBRR_value= (uint16)(((F_CPU / (g_speed_mode_division_factor * 115200)))-1);
    	                  break;
    }


    /*Config RX Interrupt*/
    switch(Config_Ptr ->rx_interrupt)
    {
    case RX_InterruptDisable: CLEAR_BIT(UCSRB,RXCIE);
                              break;
    case RX_InterruptEnable:  SET_BIT(UCSRB,RXCIE);
                              break;

    }

    /*Config TX Interrupt*/
    switch(Config_Ptr ->tx_interrupt)
    {
    case TX_InterruptDisable: CLEAR_BIT(UCSRB,TXCIE);
                              break;
    case TX_InterruptEnable:  SET_BIT(UCSRB,TXCIE);
                              break;

    }

}
/*******************************************************************************
* Service Name:       UART_sendByte
* Sync/Async:         Synchronous
* Reentrancy:         Reentrant
* Parameters (in):    Data to be sent
* Parameters (inout): None
* Parameters (out):   None
* Return value:       None
* Description:        Send a Byte to other devices.
********************************************************************************/
void UART_sendByte( const uint8 data )
{
   /*Wait until Flag = 1 , etc: UDR is empty and ready to be loaded with data*/
   while (BIT_IS_CLEAR(UCSRA,UDRE));
   UDR = data;
}
/*******************************************************************************
* Service Name:       UART_receiveByte
* Sync/Async:         Synchronous
* Reentrancy:         Reentrant
* Parameters (in):    None
* Parameters (inout): None
* Parameters (out):   None
* Return value:       uint8
* Description:        receive a Byte from other devices
********************************************************************************/
uint8 UART_receiveByte (void)
{
	 /*Wait until Flag = 1 , etc: UDR is Loaded with received Data then return UDR*/
	  while (BIT_IS_CLEAR(UCSRA,RXC));
      return UDR;
}
/*******************************************************************************
* Service Name:       UART_sendString
* Sync/Async:         Synchronous
* Reentrancy:         Reentrant
* Parameters (in):    String to be sent
* Parameters (inout): None
* Parameters (out):   None
* Return value:       None
* Description:        Send a String to other devices.
********************************************************************************/
void UART_sendString( const uint8 * Str)
{
	uint8 i = 0;

		/* Send the whole string */
		while(Str[i] != '\0')
		{
			UART_sendByte(Str[i]);
			i++;
		}
}
/*******************************************************************************
* Service Name:       UART_receiveString
* Sync/Async:         Synchronous
* Reentrancy:         Reentrant
* Parameters (in):    None
* Parameters (inout): None
* Parameters (out):   None
* Return value:       uint8
* Description:        receive a stringfrom other devices
********************************************************************************/
void UART_receiveString (uint8 *Str)
{
	uint8 i = 0;

	/* Receive the first byte */
	Str[i] = UART_receiveByte();

	/* Receive the whole string until the '#' */
	while(Str[i] != '#')
	{
		i++;
		Str[i] = UART_receiveByte();
	}

	/* After receiving the whole string plus the '#', replace the '#' with '\0' */
	Str[i] = '\0';
}
