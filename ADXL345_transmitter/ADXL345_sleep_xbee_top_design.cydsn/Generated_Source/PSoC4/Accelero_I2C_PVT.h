/*******************************************************************************
* File Name: .h
* Version 3.0
*
* Description:
*  This private file provides constants and parameter values for the
*  SCB Component in I2C mode.
*  Please do not use this file or its content in your project.
*
* Note:
*
********************************************************************************
* Copyright 2013-2015, Cypress Semiconductor Corporation. All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_SCB_I2C_PVT_Accelero_H)
#define CY_SCB_I2C_PVT_Accelero_H

#include "Accelero_I2C.h"


/***************************************
*     Private Global Vars
***************************************/

extern volatile uint8 Accelero_state; /* Current state of I2C FSM */

#if(Accelero_I2C_SLAVE_CONST)
    extern volatile uint8 Accelero_slStatus;          /* Slave Status */

    /* Receive buffer variables */
    extern volatile uint8 * Accelero_slWrBufPtr;      /* Pointer to Receive buffer  */
    extern volatile uint32  Accelero_slWrBufSize;     /* Slave Receive buffer size  */
    extern volatile uint32  Accelero_slWrBufIndex;    /* Slave Receive buffer Index */

    /* Transmit buffer variables */
    extern volatile uint8 * Accelero_slRdBufPtr;      /* Pointer to Transmit buffer  */
    extern volatile uint32  Accelero_slRdBufSize;     /* Slave Transmit buffer size  */
    extern volatile uint32  Accelero_slRdBufIndex;    /* Slave Transmit buffer Index */
    extern volatile uint32  Accelero_slRdBufIndexTmp; /* Slave Transmit buffer Index Tmp */
    extern volatile uint8   Accelero_slOverFlowCount; /* Slave Transmit Overflow counter */
#endif /* (Accelero_I2C_SLAVE_CONST) */

#if(Accelero_I2C_MASTER_CONST)
    extern volatile uint16 Accelero_mstrStatus;      /* Master Status byte  */
    extern volatile uint8  Accelero_mstrControl;     /* Master Control byte */

    /* Receive buffer variables */
    extern volatile uint8 * Accelero_mstrRdBufPtr;   /* Pointer to Master Read buffer */
    extern volatile uint32  Accelero_mstrRdBufSize;  /* Master Read buffer size       */
    extern volatile uint32  Accelero_mstrRdBufIndex; /* Master Read buffer Index      */

    /* Transmit buffer variables */
    extern volatile uint8 * Accelero_mstrWrBufPtr;   /* Pointer to Master Write buffer */
    extern volatile uint32  Accelero_mstrWrBufSize;  /* Master Write buffer size       */
    extern volatile uint32  Accelero_mstrWrBufIndex; /* Master Write buffer Index      */
    extern volatile uint32  Accelero_mstrWrBufIndexTmp; /* Master Write buffer Index Tmp */
#endif /* (Accelero_I2C_MASTER_CONST) */

#if (Accelero_I2C_CUSTOM_ADDRESS_HANDLER_CONST)
    extern uint32 (*Accelero_customAddressHandler) (void);
#endif /* (Accelero_I2C_CUSTOM_ADDRESS_HANDLER_CONST) */

/***************************************
*     Private Function Prototypes
***************************************/

#if(Accelero_SCB_MODE_I2C_CONST_CFG)
    void Accelero_I2CInit(void);
#endif /* (Accelero_SCB_MODE_I2C_CONST_CFG) */

void Accelero_I2CStop(void);
void Accelero_I2CSaveConfig(void);
void Accelero_I2CRestoreConfig(void);

#if(Accelero_I2C_MASTER_CONST)
    void Accelero_I2CReStartGeneration(void);
#endif /* (Accelero_I2C_MASTER_CONST) */

#endif /* (CY_SCB_I2C_PVT_Accelero_H) */


/* [] END OF FILE */
