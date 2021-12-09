/******************************************************************************
*  Module:    I2C
*  File name: I2C.C
*  Created on: Oct 31, 2021
*  Author: Abdelaziz Mohammad
*******************************************************************************/
/*******************************************************************************
*                                                                              *
*                                  INCLUDES                                    *
*                                                                              *
********************************************************************************/
#include "I2C.h"
#include "common_macros.h"
#include "avr/io.h"
/*******************************************************************************
*                                                                              *
*                                  Global Variables                            *
*                                                                              *
********************************************************************************/

/*******************************************************************************
*                                                                              *
*                              FUNCTIONS Definitions                           *
*                                                                              *
********************************************************************************/
/*******************************************************************************
* Service Name:       TWI_Init
* Sync/Async:         Synchronous
* Reentrancy:         Non Reentrant
* Parameters (in):    configurations - Pointer to post-build configuration data
* Parameters (inout): None
* Parameters (out):   None
* Return value:       None
* Description:        Initialize the I2C module.
********************************************************************************/
void TWI_init(const TWI_ConfigType * Config_Ptr)
{
    /*Enable or Disable the TWI Module*/
   switch ( Config_Ptr -> mode )
   {
      case TWI_Disable: CLEAR_BIT(TWCR,TWEN);
    	            break;
      case TWI_Enable:  SET_BIT(TWCR,TWEN);
    	            break;
   }

   /*Enable or Disable Interrupt for I2C*/
   switch( Config_Ptr ->interrupt_mode)
   {
     case Interrupt_Disable:   CLEAR_BIT(TWCR,TWIE);
    	                       break;
     case Interrupt_Enable:    SET_BIT(TWCR,TWIE);
    	                       break;
   }

   /*Setting Prescaler*/
   TWSR = ( TWSR & 0xFC ) | Config_Ptr -> TWI_prescaler ;

   /*General Call Recognition Enable Bit*/
   switch ( Config_Ptr ->GCR)
   {
       case GCR_Disable : CLEAR_BIT(TWAR,TWGCE);
    	         break;
       case GCR_Enable :  SET_BIT(TWAR,TWGCE);
    	         break;
   }

   TWBR = 0x02;
   TWAR = 0b00000010; // my address = 0x01 :)
}
/*******************************************************************************
* Service Name:       TWI_start
* Sync/Async:         Synchronous
* Reentrancy:         Non Reentrant
* Parameters (in):    None
* Parameters (inout): None
* Parameters (out):   None
* Return value:       None
* Description:        Send the start BIT
********************************************************************************/
void TWI_start(void)
{
    /*
	 * Clear the TWINT flag before sending the start bit TWINT=1
	 * send the start bit by TWSTA=1
	 * Enable TWI Module TWEN=1
	 */
    TWCR = (1 << TWINT) | (1 << TWSTA) | (1 << TWEN);

    /* Wait for TWINT flag set in TWCR Register (start bit is send successfully) */
    while(BIT_IS_CLEAR(TWCR,TWINT));
}
/*******************************************************************************
* Service Name:       TWI_stop
* Sync/Async:         Synchronous
* Reentrancy:         Non Reentrant
* Parameters (in):    None
* Parameters (inout): None
* Parameters (out):   None
* Return value:       None
* Description:        Send the stop BIT
********************************************************************************/
void TWI_stop(void)
{
    /*
	 * Clear the TWINT flag before sending the stop bit TWINT=1
	 * send the stop bit by TWSTO=1
	 * Enable TWI Module TWEN=1
	 */
    TWCR = (1 << TWINT) | (1 << TWSTO) | (1 << TWEN);
}
/*******************************************************************************
* Service Name:       TWI_writeByte
* Sync/Async:         Synchronous
* Reentrancy:         Non Reentrant
* Parameters (in):    data to be written
* Parameters (inout): None
* Parameters (out):   None
* Return value:       None
* Description:        write byte
********************************************************************************/
void TWI_writeByte(uint8 data)
{
    /* Put data On TWI data Register */
    TWDR = data;
    /*
	 * Clear the TWINT flag before sending the data TWINT=1
	 * Enable TWI Module TWEN=1
	 */
    TWCR = (1 << TWINT) | (1 << TWEN);
    /* Wait for TWINT flag set in TWCR Register(data is send successfully) */
    while(BIT_IS_CLEAR(TWCR,TWINT));
}
/*******************************************************************************
* Service Name:       TWI_readByteWithACK
* Sync/Async:         Synchronous
* Reentrancy:         Non Reentrant
* Parameters (in):    None
* Parameters (inout): None
* Parameters (out):   Byte read with ack
* Return value:       None
* Description:        write byte
********************************************************************************/
uint8 TWI_readByteWithACK(void)
{
	/*
	 * Clear the TWINT flag before reading the data TWINT=1
	 * Enable sending ACK after reading or receiving data TWEA=1
	 * Enable TWI Module TWEN=1
	 */
    TWCR = (1 << TWINT) | (1 << TWEN) | (1 << TWEA);
    /* Wait for TWINT flag set in TWCR Register (data received successfully) */
    while(BIT_IS_CLEAR(TWCR,TWINT));
    /* Read Data */
    return TWDR;
}
/*******************************************************************************
* Service Name:       TWI_readByteWithNACK
* Sync/Async:         Synchronous
* Reentrancy:         Non Reentrant
* Parameters (in):    None
* Parameters (inout): None
* Parameters (out):   Byte read with NACK
* Return value:       uint8
* Description:        write byte with NACK
********************************************************************************/
uint8 TWI_readByteWithNACK(void)
{
	/*
	 * Clear the TWINT flag before reading the data TWINT=1
	 * Enable TWI Module TWEN=1
	 */
    TWCR = (1 << TWINT) | (1 << TWEN);
    /* Wait for TWINT flag set in TWCR Register (data received successfully) */
    while(BIT_IS_CLEAR(TWCR,TWINT));
    /* Read Data */
    return TWDR;
}
/*******************************************************************************
* Service Name:       TWI_getStatus
* Sync/Async:         Synchronous
* Reentrancy:         Non Reentrant
* Parameters (in):    None
* Parameters (inout): None
* Parameters (out):   None
* Return value:       uint8
* Description:        get the status
********************************************************************************/
uint8 TWI_getStatus(void)
{
    uint8 status;
    /* masking to eliminate first 3 bits and get the last 5 bits (status bits) */
    status = TWSR & 0xF8;
    return status;
}


