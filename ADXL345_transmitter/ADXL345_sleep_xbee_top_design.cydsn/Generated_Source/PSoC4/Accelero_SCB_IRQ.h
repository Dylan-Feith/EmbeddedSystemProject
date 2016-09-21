/*******************************************************************************
* File Name: Accelero_SCB_IRQ.h
* Version 1.70
*
*  Description:
*   Provides the function definitions for the Interrupt Controller.
*
*
********************************************************************************
* Copyright 2008-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/
#if !defined(CY_ISR_Accelero_SCB_IRQ_H)
#define CY_ISR_Accelero_SCB_IRQ_H


#include <cytypes.h>
#include <cyfitter.h>

/* Interrupt Controller API. */
void Accelero_SCB_IRQ_Start(void);
void Accelero_SCB_IRQ_StartEx(cyisraddress address);
void Accelero_SCB_IRQ_Stop(void);

CY_ISR_PROTO(Accelero_SCB_IRQ_Interrupt);

void Accelero_SCB_IRQ_SetVector(cyisraddress address);
cyisraddress Accelero_SCB_IRQ_GetVector(void);

void Accelero_SCB_IRQ_SetPriority(uint8 priority);
uint8 Accelero_SCB_IRQ_GetPriority(void);

void Accelero_SCB_IRQ_Enable(void);
uint8 Accelero_SCB_IRQ_GetState(void);
void Accelero_SCB_IRQ_Disable(void);

void Accelero_SCB_IRQ_SetPending(void);
void Accelero_SCB_IRQ_ClearPending(void);


/* Interrupt Controller Constants */

/* Address of the INTC.VECT[x] register that contains the Address of the Accelero_SCB_IRQ ISR. */
#define Accelero_SCB_IRQ_INTC_VECTOR            ((reg32 *) Accelero_SCB_IRQ__INTC_VECT)

/* Address of the Accelero_SCB_IRQ ISR priority. */
#define Accelero_SCB_IRQ_INTC_PRIOR             ((reg32 *) Accelero_SCB_IRQ__INTC_PRIOR_REG)

/* Priority of the Accelero_SCB_IRQ interrupt. */
#define Accelero_SCB_IRQ_INTC_PRIOR_NUMBER      Accelero_SCB_IRQ__INTC_PRIOR_NUM

/* Address of the INTC.SET_EN[x] byte to bit enable Accelero_SCB_IRQ interrupt. */
#define Accelero_SCB_IRQ_INTC_SET_EN            ((reg32 *) Accelero_SCB_IRQ__INTC_SET_EN_REG)

/* Address of the INTC.CLR_EN[x] register to bit clear the Accelero_SCB_IRQ interrupt. */
#define Accelero_SCB_IRQ_INTC_CLR_EN            ((reg32 *) Accelero_SCB_IRQ__INTC_CLR_EN_REG)

/* Address of the INTC.SET_PD[x] register to set the Accelero_SCB_IRQ interrupt state to pending. */
#define Accelero_SCB_IRQ_INTC_SET_PD            ((reg32 *) Accelero_SCB_IRQ__INTC_SET_PD_REG)

/* Address of the INTC.CLR_PD[x] register to clear the Accelero_SCB_IRQ interrupt. */
#define Accelero_SCB_IRQ_INTC_CLR_PD            ((reg32 *) Accelero_SCB_IRQ__INTC_CLR_PD_REG)



#endif /* CY_ISR_Accelero_SCB_IRQ_H */


/* [] END OF FILE */
