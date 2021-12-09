/******************************************************************************
*  Module:    I2C
*  File name: I2C.h
*  Created on: Oct 31, 2021
*  Author: Abdelaziz Mohammad
*******************************************************************************/

#ifndef I2C_H_
#define I2C_H_


/*******************************************************************************
*                                                                              *
*                                  INCLUDES                                    *
*                                                                              *
********************************************************************************/
#include "std_types.h"

/*******************************************************************************
*                                                                              *
*                                  DEFINITIONS                                 *
*                                                                              *
********************************************************************************/

/*******************************************************************************
*                                                                              *
*                              Preprocessor Macros                             *
*                                                                              *
*                                                                              *
********************************************************************************/
/* I2C Status Bits in the TWSR Register */
#define TWI_START         0x08 /* start has been sent */
#define TWI_REP_START     0x10 /* repeated start */
#define TWI_MT_SLA_W_ACK  0x18 /* Master transmit ( slave address + Write request ) to slave + ACK received from slave. */
#define TWI_MT_SLA_R_ACK  0x40 /* Master transmit ( slave address + Read request ) to slave + ACK received from slave. */
#define TWI_MT_DATA_ACK   0x28 /* Master transmit data and ACK has been received from Slave. */
#define TWI_MR_DATA_ACK   0x50 /* Master received data and send ACK to slave. */
#define TWI_MR_DATA_NACK  0x58 /* Master received data but doesn't send ACK to slave. */
/*******************************************************************************
*                                                                              *
*                                  Global Variables                            *
*                                                                              *
********************************************************************************/

 /*******************************************************************************
 *                                                                              *
 *                          Interrupt Service Routine                           *
 *                                                                              *
 ********************************************************************************/


/*******************************************************************************
*                                                                              *
*                             User-Defined Data Types                          *
*                                                                              *
********************************************************************************/
/*******************************************************************************
* Name: TWI_Mode
* Type: Enumeration
* Range: Disable - Enable
* Description: Data Type for symbolic name for I2C Operation Mode
********************************************************************************/
typedef enum
{
	TWI_Disable,
	TWI_Enable
}TWI_Mode;
/*******************************************************************************
* Name: Interrupt_Mode
* Type: Enumeration
* Range: Disable - Enable
* Description: Data Type for symbolic name for I2C Interrupt Mode
********************************************************************************/
typedef enum
{
	Interrupt_Disable,
	Interrupt_Enable
}Interrupt_Mode;
/*******************************************************************************
* Name: Interrupt_Mode
* Type: Enumeration
* Range: Prescaler_1 , Prescaler_4 , Prescaler_16 , Prescaler_64
* Description: Data Type for symbolic name for I2C Prescaler Values
********************************************************************************/
typedef enum
{
	Prescaler_1,
	Prescaler_4,
	Prescaler_16,
	Prescaler_64
}Prescaler;
/*******************************************************************************
* Name: General_Call_Regection
* Type: Enumeration
* Range: Disable - Enable
* Description: Data Type for symbolic name for I2C General Call Regection
********************************************************************************/
typedef enum
{
	GCR_Disable,
    GCR_Enable
}General_Call_Regection;
/*******************************************************************************
* Name: TWI_ConfigType
* Type: Structure
* Range: Hardware dependent structure
* Description: Type of the external data structure containing the initialization
*              data for this module. This is the one that is sent to the init
*              function.
********************************************************************************/
typedef struct
{
    TWI_Mode mode;
    Interrupt_Mode interrupt_mode;
    Prescaler TWI_prescaler;
    General_Call_Regection GCR;
}TWI_ConfigType;
/*******************************************************************************
*                                                                              *
*                                  FUNCTIONS PROTOTYPE                         *
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
void TWI_init(const TWI_ConfigType * Config_Ptr );
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
void TWI_start(void);
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
void TWI_stop(void);
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
void TWI_writeByte(uint8 data);
/*******************************************************************************
* Service Name:       TWI_readByteWithACK
* Sync/Async:         Synchronous
* Reentrancy:         Non Reentrant
* Parameters (in):    data to be written
* Parameters (inout): None
* Parameters (out):   Byte read with ACK
* Return value:       None
* Description:        write byte
********************************************************************************/
uint8 TWI_readByteWithACK(void);
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
uint8 TWI_readByteWithNACK(void);
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
uint8 TWI_getStatus(void);

#endif /* I2C_H_ */
