/*******************************************************************************
* File Name: Accelero_scl.h  
* Version 2.10
*
* Description:
*  This file containts Control Register function prototypes and register defines
*
* Note:
*
********************************************************************************
* Copyright 2008-2014, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_PINS_Accelero_scl_H) /* Pins Accelero_scl_H */
#define CY_PINS_Accelero_scl_H

#include "cytypes.h"
#include "cyfitter.h"
#include "Accelero_scl_aliases.h"


/***************************************
*        Function Prototypes             
***************************************/    

void    Accelero_scl_Write(uint8 value) ;
void    Accelero_scl_SetDriveMode(uint8 mode) ;
uint8   Accelero_scl_ReadDataReg(void) ;
uint8   Accelero_scl_Read(void) ;
uint8   Accelero_scl_ClearInterrupt(void) ;


/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define Accelero_scl_DRIVE_MODE_BITS        (3)
#define Accelero_scl_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - Accelero_scl_DRIVE_MODE_BITS))

#define Accelero_scl_DM_ALG_HIZ         (0x00u)
#define Accelero_scl_DM_DIG_HIZ         (0x01u)
#define Accelero_scl_DM_RES_UP          (0x02u)
#define Accelero_scl_DM_RES_DWN         (0x03u)
#define Accelero_scl_DM_OD_LO           (0x04u)
#define Accelero_scl_DM_OD_HI           (0x05u)
#define Accelero_scl_DM_STRONG          (0x06u)
#define Accelero_scl_DM_RES_UPDWN       (0x07u)

/* Digital Port Constants */
#define Accelero_scl_MASK               Accelero_scl__MASK
#define Accelero_scl_SHIFT              Accelero_scl__SHIFT
#define Accelero_scl_WIDTH              1u


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define Accelero_scl_PS                     (* (reg32 *) Accelero_scl__PS)
/* Port Configuration */
#define Accelero_scl_PC                     (* (reg32 *) Accelero_scl__PC)
/* Data Register */
#define Accelero_scl_DR                     (* (reg32 *) Accelero_scl__DR)
/* Input Buffer Disable Override */
#define Accelero_scl_INP_DIS                (* (reg32 *) Accelero_scl__PC2)


#if defined(Accelero_scl__INTSTAT)  /* Interrupt Registers */

    #define Accelero_scl_INTSTAT                (* (reg32 *) Accelero_scl__INTSTAT)

#endif /* Interrupt Registers */


/***************************************
* The following code is DEPRECATED and 
* must not be used.
***************************************/

#define Accelero_scl_DRIVE_MODE_SHIFT       (0x00u)
#define Accelero_scl_DRIVE_MODE_MASK        (0x07u << Accelero_scl_DRIVE_MODE_SHIFT)


#endif /* End Pins Accelero_scl_H */


/* [] END OF FILE */
