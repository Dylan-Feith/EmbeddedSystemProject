/* ========================================
 *
 * Copyright YOUR COMPANY, THE YEAR
 * All Rights Reserved
 * UNPUBLISHED, LICENSED SOFTWARE.
 *
 * CONFIDENTIAL AND PROPRIETARY INFORMATION
 * WHICH IS THE PROPERTY OF your company.
 *
 * ========================================
*/
#include <project.h>
#include "fonction.h"
#include <stdio.h>
#include <math.h>

#define WANTED_DATA_RATE DATA_RATE_50_Hz

CY_ISR(isr_wdt){
    
    // clear l'interrupt   
    CySysWdtClearInterrupt(CY_SYS_WDT_COUNTER1_INT);
    WdtIsr_ClearPending();
}

int main()
{
    // ces trois commandes étaient faites initialement pour que 
    // le xbee ait le temps de s'apparier avec le récepteur au démarrage. 
    // La valeur est surement exagéré.
    
    Pin_gestion_sleep_xbee_Write(0u);
    CyDelay(400);
    Pin_gestion_sleep_xbee_Write(1u);
    
    // INITALISATION DES VARIABLES
    uint16 acc_eff_x = 0 ;
    uint16 acc_eff_y = 0 ;
    uint16 acc_eff_z = 0 ;
    
    uint16 norme_acc_efficace = 0 ;

    /* Enabling global interrupts. */
    CyGlobalIntEnable;
    
    accelero_init(RANGE_2G,FULL_RESOLUTION, WANTED_DATA_RATE);
    
    // param : le temps pendant lequel le PSoC reste en veille
    initialisation_projet(10);
    
    for(;;){
        
        
        accelero_acquisition_efficace(&acc_eff_x, &acc_eff_y, &acc_eff_z, 10, WANTED_DATA_RATE);
        //norme_acc_efficace = accelero_calcul_norme_acc_efficace(acc_eff_x,acc_eff_y,acc_eff_z);
        accelero_transmission(acc_eff_x,acc_eff_y,acc_eff_z,norme_acc_efficace);
        
        // met le PSoC en Deep Sleep
        CySysPmDeepSleep();
        }
}

/* [] END OF FILE */

