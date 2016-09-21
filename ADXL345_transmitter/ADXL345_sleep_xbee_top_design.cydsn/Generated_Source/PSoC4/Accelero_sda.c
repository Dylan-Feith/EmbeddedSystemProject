/*******************************************************************************
* File Name: Accelero_sda.c  
* Version 2.10
*
* Description:
*  This file contains API to enable firmware control of a Pins component.
*
* Note:
*
********************************************************************************
* Copyright 2008-2014, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#include "cytypes.h"
#include "Accelero_sda.h"

#define SetP4PinDriveMode(shift, mode)  \
    do { \
        Accelero_sda_PC =   (Accelero_sda_PC & \
                                (uint32)(~(uint32)(Accelero_sda_DRIVE_MODE_IND_MASK << (Accelero_sda_DRIVE_MODE_BITS * (shift))))) | \
                                (uint32)((uint32)(mode) << (Accelero_sda_DRIVE_MODE_BITS * (shift))); \
    } while (0)


/*******************************************************************************
* Function Name: Accelero_sda_Write
********************************************************************************
*
* Summary:
*  Assign a new value to the digital port's data output register.  
*
* Parameters:  
*  prtValue:  The value to be assigned to the Digital Port. 
*
* Return: 
*  None 
*  
*******************************************************************************/
void Accelero_sda_Write(uint8 value) 
{
    uint8 drVal = (uint8)(Accelero_sda_DR & (uint8)(~Accelero_sda_MASK));
    drVal = (drVal | ((uint8)(value << Accelero_sda_SHIFT) & Accelero_sda_MASK));
    Accelero_sda_DR = (uint32)drVal;
}


/*******************************************************************************
* Function Name: Accelero_sda_SetDriveMode
********************************************************************************
*
* Summary:
*  Change the drive mode on the pins of the port.
* 
* Parameters:  
*  mode:  Change the pins to one of the following drive modes.
*
*  Accelero_sda_DM_STRONG     Strong Drive 
*  Accelero_sda_DM_OD_HI      Open Drain, Drives High 
*  Accelero_sda_DM_OD_LO      Open Drain, Drives Low 
*  Accelero_sda_DM_RES_UP     Resistive Pull Up 
*  Accelero_sda_DM_RES_DWN    Resistive Pull Down 
*  Accelero_sda_DM_RES_UPDWN  Resistive Pull Up/Down 
*  Accelero_sda_DM_DIG_HIZ    High Impedance Digital 
*  Accelero_sda_DM_ALG_HIZ    High Impedance Analog 
*
* Return: 
*  None
*
*******************************************************************************/
void Accelero_sda_SetDriveMode(uint8 mode) 
{
	SetP4PinDriveMode(Accelero_sda__0__SHIFT, mode);
}


/*******************************************************************************
* Function Name: Accelero_sda_Read
********************************************************************************
*
* Summary:
*  Read the current value on the pins of the Digital Port in right justified 
*  form.
*
* Parameters:  
*  None 
*
* Return: 
*  Returns the current value of the Digital Port as a right justified number
*  
* Note:
*  Macro Accelero_sda_ReadPS calls this function. 
*  
*******************************************************************************/
uint8 Accelero_sda_Read(void) 
{
    return (uint8)((Accelero_sda_PS & Accelero_sda_MASK) >> Accelero_sda_SHIFT);
}


/*******************************************************************************
* Function Name: Accelero_sda_ReadDataReg
********************************************************************************
*
* Summary:
*  Read the current value assigned to a Digital Port's data output register
*
* Parameters:  
*  None 
*
* Return: 
*  Returns the current value assigned to the Digital Port's data output register
*  
*******************************************************************************/
uint8 Accelero_sda_ReadDataReg(void) 
{
    return (uint8)((Accelero_sda_DR & Accelero_sda_MASK) >> Accelero_sda_SHIFT);
}


/* If Interrupts Are Enabled for this Pins component */ 
#if defined(Accelero_sda_INTSTAT) 

    /*******************************************************************************
    * Function Name: Accelero_sda_ClearInterrupt
    ********************************************************************************
    *
    * Summary:
    *  Clears any active interrupts attached to port and returns the value of the 
    *  interrupt status register.
    *
    * Parameters:  
    *  None 
    *
    * Return: 
    *  Returns the value of the interrupt status register
    *  
    *******************************************************************************/
    uint8 Accelero_sda_ClearInterrupt(void) 
    {
		uint8 maskedStatus = (uint8)(Accelero_sda_INTSTAT & Accelero_sda_MASK);
		Accelero_sda_INTSTAT = maskedStatus;
        return maskedStatus >> Accelero_sda_SHIFT;
    }

#endif /* If Interrupts Are Enabled for this Pins component */ 


/* [] END OF FILE */
