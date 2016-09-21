/*******************************************************************************
* File Name: XBee_SCBCLK.h
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

#if !defined(CY_CLOCK_XBee_SCBCLK_H)
#define CY_CLOCK_XBee_SCBCLK_H

#include <cytypes.h>
#include <cyfitter.h>


/***************************************
*        Function Prototypes
***************************************/
#if defined CYREG_PERI_DIV_CMD

void XBee_SCBCLK_StartEx(uint32 alignClkDiv);
#define XBee_SCBCLK_Start() \
    XBee_SCBCLK_StartEx(XBee_SCBCLK__PA_DIV_ID)

#else

void XBee_SCBCLK_Start(void);

#endif/* CYREG_PERI_DIV_CMD */

void XBee_SCBCLK_Stop(void);

void XBee_SCBCLK_SetFractionalDividerRegister(uint16 clkDivider, uint8 clkFractional);

uint16 XBee_SCBCLK_GetDividerRegister(void);
uint8  XBee_SCBCLK_GetFractionalDividerRegister(void);

#define XBee_SCBCLK_Enable()                         XBee_SCBCLK_Start()
#define XBee_SCBCLK_Disable()                        XBee_SCBCLK_Stop()
#define XBee_SCBCLK_SetDividerRegister(clkDivider, reset)  \
    XBee_SCBCLK_SetFractionalDividerRegister((clkDivider), 0u)
#define XBee_SCBCLK_SetDivider(clkDivider)           XBee_SCBCLK_SetDividerRegister((clkDivider), 1u)
#define XBee_SCBCLK_SetDividerValue(clkDivider)      XBee_SCBCLK_SetDividerRegister((clkDivider) - 1u, 1u)


/***************************************
*             Registers
***************************************/
#if defined CYREG_PERI_DIV_CMD

#define XBee_SCBCLK_DIV_ID     XBee_SCBCLK__DIV_ID

#define XBee_SCBCLK_CMD_REG    (*(reg32 *)CYREG_PERI_DIV_CMD)
#define XBee_SCBCLK_CTRL_REG   (*(reg32 *)XBee_SCBCLK__CTRL_REGISTER)
#define XBee_SCBCLK_DIV_REG    (*(reg32 *)XBee_SCBCLK__DIV_REGISTER)

#define XBee_SCBCLK_CMD_DIV_SHIFT          (0u)
#define XBee_SCBCLK_CMD_PA_DIV_SHIFT       (8u)
#define XBee_SCBCLK_CMD_DISABLE_SHIFT      (30u)
#define XBee_SCBCLK_CMD_ENABLE_SHIFT       (31u)

#define XBee_SCBCLK_CMD_DISABLE_MASK       ((uint32)((uint32)1u << XBee_SCBCLK_CMD_DISABLE_SHIFT))
#define XBee_SCBCLK_CMD_ENABLE_MASK        ((uint32)((uint32)1u << XBee_SCBCLK_CMD_ENABLE_SHIFT))

#define XBee_SCBCLK_DIV_FRAC_MASK  (0x000000F8u)
#define XBee_SCBCLK_DIV_FRAC_SHIFT (3u)
#define XBee_SCBCLK_DIV_INT_MASK   (0xFFFFFF00u)
#define XBee_SCBCLK_DIV_INT_SHIFT  (8u)

#else 

#define XBee_SCBCLK_DIV_REG        (*(reg32 *)XBee_SCBCLK__REGISTER)
#define XBee_SCBCLK_ENABLE_REG     XBee_SCBCLK_DIV_REG
#define XBee_SCBCLK_DIV_FRAC_MASK  XBee_SCBCLK__FRAC_MASK
#define XBee_SCBCLK_DIV_FRAC_SHIFT (16u)
#define XBee_SCBCLK_DIV_INT_MASK   XBee_SCBCLK__DIVIDER_MASK
#define XBee_SCBCLK_DIV_INT_SHIFT  (0u)

#endif/* CYREG_PERI_DIV_CMD */

#endif /* !defined(CY_CLOCK_XBee_SCBCLK_H) */

/* [] END OF FILE */
