/*******************************************************************************
* File Name: zigbee_IntClock.h
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

#if !defined(CY_CLOCK_zigbee_IntClock_H)
#define CY_CLOCK_zigbee_IntClock_H

#include <cytypes.h>
#include <cyfitter.h>


/***************************************
*        Function Prototypes
***************************************/
#if defined CYREG_PERI_DIV_CMD

void zigbee_IntClock_StartEx(uint32 alignClkDiv);
#define zigbee_IntClock_Start() \
    zigbee_IntClock_StartEx(zigbee_IntClock__PA_DIV_ID)

#else

void zigbee_IntClock_Start(void);

#endif/* CYREG_PERI_DIV_CMD */

void zigbee_IntClock_Stop(void);

void zigbee_IntClock_SetFractionalDividerRegister(uint16 clkDivider, uint8 clkFractional);

uint16 zigbee_IntClock_GetDividerRegister(void);
uint8  zigbee_IntClock_GetFractionalDividerRegister(void);

#define zigbee_IntClock_Enable()                         zigbee_IntClock_Start()
#define zigbee_IntClock_Disable()                        zigbee_IntClock_Stop()
#define zigbee_IntClock_SetDividerRegister(clkDivider, reset)  \
    zigbee_IntClock_SetFractionalDividerRegister((clkDivider), 0u)
#define zigbee_IntClock_SetDivider(clkDivider)           zigbee_IntClock_SetDividerRegister((clkDivider), 1u)
#define zigbee_IntClock_SetDividerValue(clkDivider)      zigbee_IntClock_SetDividerRegister((clkDivider) - 1u, 1u)


/***************************************
*             Registers
***************************************/
#if defined CYREG_PERI_DIV_CMD

#define zigbee_IntClock_DIV_ID     zigbee_IntClock__DIV_ID

#define zigbee_IntClock_CMD_REG    (*(reg32 *)CYREG_PERI_DIV_CMD)
#define zigbee_IntClock_CTRL_REG   (*(reg32 *)zigbee_IntClock__CTRL_REGISTER)
#define zigbee_IntClock_DIV_REG    (*(reg32 *)zigbee_IntClock__DIV_REGISTER)

#define zigbee_IntClock_CMD_DIV_SHIFT          (0u)
#define zigbee_IntClock_CMD_PA_DIV_SHIFT       (8u)
#define zigbee_IntClock_CMD_DISABLE_SHIFT      (30u)
#define zigbee_IntClock_CMD_ENABLE_SHIFT       (31u)

#define zigbee_IntClock_CMD_DISABLE_MASK       ((uint32)((uint32)1u << zigbee_IntClock_CMD_DISABLE_SHIFT))
#define zigbee_IntClock_CMD_ENABLE_MASK        ((uint32)((uint32)1u << zigbee_IntClock_CMD_ENABLE_SHIFT))

#define zigbee_IntClock_DIV_FRAC_MASK  (0x000000F8u)
#define zigbee_IntClock_DIV_FRAC_SHIFT (3u)
#define zigbee_IntClock_DIV_INT_MASK   (0xFFFFFF00u)
#define zigbee_IntClock_DIV_INT_SHIFT  (8u)

#else 

#define zigbee_IntClock_DIV_REG        (*(reg32 *)zigbee_IntClock__REGISTER)
#define zigbee_IntClock_ENABLE_REG     zigbee_IntClock_DIV_REG
#define zigbee_IntClock_DIV_FRAC_MASK  zigbee_IntClock__FRAC_MASK
#define zigbee_IntClock_DIV_FRAC_SHIFT (16u)
#define zigbee_IntClock_DIV_INT_MASK   zigbee_IntClock__DIVIDER_MASK
#define zigbee_IntClock_DIV_INT_SHIFT  (0u)

#endif/* CYREG_PERI_DIV_CMD */

#endif /* !defined(CY_CLOCK_zigbee_IntClock_H) */

/* [] END OF FILE */
