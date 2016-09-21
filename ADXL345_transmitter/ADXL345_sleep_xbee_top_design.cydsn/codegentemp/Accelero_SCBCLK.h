/*******************************************************************************
* File Name: Accelero_SCBCLK.h
* Version 2.20
*
*  Description:
*   Provides the function and constant definitions for the clock component.
*
*  Note:
*
********************************************************************************
* Copyright 2008-2012, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_CLOCK_Accelero_SCBCLK_H)
#define CY_CLOCK_Accelero_SCBCLK_H

#include <cytypes.h>
#include <cyfitter.h>


/***************************************
*        Function Prototypes
***************************************/
#if defined CYREG_PERI_DIV_CMD

void Accelero_SCBCLK_StartEx(uint32 alignClkDiv);
#define Accelero_SCBCLK_Start() \
    Accelero_SCBCLK_StartEx(Accelero_SCBCLK__PA_DIV_ID)

#else

void Accelero_SCBCLK_Start(void);

#endif/* CYREG_PERI_DIV_CMD */

void Accelero_SCBCLK_Stop(void);

void Accelero_SCBCLK_SetFractionalDividerRegister(uint16 clkDivider, uint8 clkFractional);

uint16 Accelero_SCBCLK_GetDividerRegister(void);
uint8  Accelero_SCBCLK_GetFractionalDividerRegister(void);

#define Accelero_SCBCLK_Enable()                         Accelero_SCBCLK_Start()
#define Accelero_SCBCLK_Disable()                        Accelero_SCBCLK_Stop()
#define Accelero_SCBCLK_SetDividerRegister(clkDivider, reset)  \
    Accelero_SCBCLK_SetFractionalDividerRegister((clkDivider), 0u)
#define Accelero_SCBCLK_SetDivider(clkDivider)           Accelero_SCBCLK_SetDividerRegister((clkDivider), 1u)
#define Accelero_SCBCLK_SetDividerValue(clkDivider)      Accelero_SCBCLK_SetDividerRegister((clkDivider) - 1u, 1u)


/***************************************
*             Registers
***************************************/
#if defined CYREG_PERI_DIV_CMD

#define Accelero_SCBCLK_DIV_ID     Accelero_SCBCLK__DIV_ID

#define Accelero_SCBCLK_CMD_REG    (*(reg32 *)CYREG_PERI_DIV_CMD)
#define Accelero_SCBCLK_CTRL_REG   (*(reg32 *)Accelero_SCBCLK__CTRL_REGISTER)
#define Accelero_SCBCLK_DIV_REG    (*(reg32 *)Accelero_SCBCLK__DIV_REGISTER)

#define Accelero_SCBCLK_CMD_DIV_SHIFT          (0u)
#define Accelero_SCBCLK_CMD_PA_DIV_SHIFT       (8u)
#define Accelero_SCBCLK_CMD_DISABLE_SHIFT      (30u)
#define Accelero_SCBCLK_CMD_ENABLE_SHIFT       (31u)

#define Accelero_SCBCLK_CMD_DISABLE_MASK       ((uint32)((uint32)1u << Accelero_SCBCLK_CMD_DISABLE_SHIFT))
#define Accelero_SCBCLK_CMD_ENABLE_MASK        ((uint32)((uint32)1u << Accelero_SCBCLK_CMD_ENABLE_SHIFT))

#define Accelero_SCBCLK_DIV_FRAC_MASK  (0x000000F8u)
#define Accelero_SCBCLK_DIV_FRAC_SHIFT (3u)
#define Accelero_SCBCLK_DIV_INT_MASK   (0xFFFFFF00u)
#define Accelero_SCBCLK_DIV_INT_SHIFT  (8u)

#else 

#define Accelero_SCBCLK_DIV_REG        (*(reg32 *)Accelero_SCBCLK__REGISTER)
#define Accelero_SCBCLK_ENABLE_REG     Accelero_SCBCLK_DIV_REG
#define Accelero_SCBCLK_DIV_FRAC_MASK  Accelero_SCBCLK__FRAC_MASK
#define Accelero_SCBCLK_DIV_FRAC_SHIFT (16u)
#define Accelero_SCBCLK_DIV_INT_MASK   Accelero_SCBCLK__DIVIDER_MASK
#define Accelero_SCBCLK_DIV_INT_SHIFT  (0u)

#endif/* CYREG_PERI_DIV_CMD */

#endif /* !defined(CY_CLOCK_Accelero_SCBCLK_H) */

/* [] END OF FILE */
