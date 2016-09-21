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


#include "fonction.h"
#include "stdio.h"
#include <math.h>

CY_ISR_PROTO(isr_wdt);

/*
cette fonction initialise l'accéléromètre pour une range et une résolution donnée
on choisit le mode de lecture en low power !!

param : range : RANGE_2G
                RANGE_4G
                RANGE_8G
                RANGE_16G
        
        resolution :    FULL_RESOLUTION (13 bits)
                        LOW_RESOLUTION  (10 bits)

        rate :  DATA_RATE_400_Hz
                DATA_RATE_200_Hz
                DATA_RATE_100_Hz
                DATA_RATE_50_Hz
                DATA_RATE_25_Hz

*/
void accelero_init(int range, int resolution, int rate){
    
    Accelero_Start();
    // écrit la range et la resolution
    accelero_write(DATA_FORMAT_ADDR,(range | resolution)); // | : ou bit à bit
    
    // écrit le rate voulu et configure l'accéléro en Low power mode
    accelero_write(BW_RATE_ADDR, (rate | LOW_POWER));
    
    Accelero_Stop();
}


/* renvoie directement l'accélération efficace sur chacune des directions
param : les adresses des accelerations efficaces
        et le nombre d'échantillon sur lequel on calcul la valeur efficace

*/

void initialisation_projet(int8 time_sec){
 
    /* Setup ISR for interrupts at WDT counter 0 events. */
    WdtIsr_StartEx(isr_wdt);
	
	/* Setup first WDT counter to generate interrupt on match 0x4FFF */
	CySysWdtSetMode(CY_SYS_WDT_COUNTER0,CY_SYS_WDT_MODE_NONE);
	CySysWdtSetMatch(CY_SYS_WDT_COUNTER0,32000u);
	CySysWdtSetClearOnMatch(CY_SYS_WDT_COUNTER0, 1u);
	
	/* Enable WDT timers 0 and 1 cascade */
	CySysWdtSetCascade(CY_SYS_WDT_CASCADE_01);
    
	/* Set WDT reset after counter 1 reach 0x0003 */
	CySysWdtSetMatch(CY_SYS_WDT_COUNTER1,time_sec);
	CySysWdtSetMode(CY_SYS_WDT_COUNTER1,CY_SYS_WDT_MODE_INT);
    CySysWdtSetClearOnMatch(CY_SYS_WDT_COUNTER1, 1u);
	
	/* Enable WDT counters 0 and 1 */
	CySysWdtEnable(CY_SYS_WDT_COUNTER0_MASK|CY_SYS_WDT_COUNTER1_MASK);

}

/* renvoie directement l'accélération efficace sur chacune des directions
param : les adresses des accelerations efficaces
        et le nombre d'échantillon sur lequel on calcul la valeur efficace

*/
void accelero_acquisition_efficace(uint16 *a_x, uint16 *a_y, uint16 *a_z, uint8 nb_acquisition, uint16 output_data_rate){
    
    uint16 delay = 0; // en microseconde (à cause du 400 Hz)
    
    // permet de savoir tout les combien de temps on lit en fonction du output data rate de l'accelero
    if (output_data_rate == DATA_RATE_25_Hz) delay =  40000;
    if (output_data_rate == DATA_RATE_50_Hz) delay =  20000;
    if (output_data_rate == DATA_RATE_100_Hz) delay = 10000;
    if (output_data_rate == DATA_RATE_200_Hz) delay =  5000;
    if (output_data_rate == DATA_RATE_400_Hz) delay =  2500;
    
    Accelero_Start();
  
    uint8 i = 0 ;
    
    // sera les valeurs de retour
    int16 acc_x = 0 ;
    int16 acc_y = 0 ;
    int16 acc_z = 0 ;
    
    // contiendra la somme des carrés des accélérations
    uint32 sum_square_acc_x = 0;
    uint32 sum_square_acc_y = 0;
    uint32 sum_square_acc_z = 0;
    
    // memoire tampon contenant les 2 octets * 3 axes = 6 valeurs successives de l'accélération
    uint8    buff[6] = {0};

    //permet de commencer la mesure
    //le retire de son standby mode
    accelero_write(POWER_CONTROL_ADDR, MESURE_MODE);
    CyDelay(40); // datasheet : wakeup time 1.1 ms + 1/(data_rate)
    
    //on fait nb_acquisition fois :
    for ( i = 0 ; i < nb_acquisition ; i++ ) {
        
        // on écrit à l'accéléromètre l'adresse de la première donnée à lire
        uint8 wr_data[1] = {DATA_X_LSB_ADDR};
        Accelero_I2CMasterWriteBuf(ACCELERO_ADDR,wr_data,1,Accelero_I2C_MODE_COMPLETE_XFER);
    
        uint8 x; 
        do {
            //on récupère en un envoi, les 6 octets de données (ax_low, ax_high, ay_low, ay_high, az_low, az_high)
            x = Accelero_I2CMasterReadBuf(ACCELERO_ADDR,buff,6,Accelero_I2C_MODE_COMPLETE_XFER); 
        }
        while (x != Accelero_I2C_MSTR_NO_ERROR); // car écriture envoie une erreur si le write n'est pas fini
   
        //wait for data transfer to complete 
        while (!(Accelero_I2CMasterStatus() & Accelero_I2C_MSTAT_RD_CMPLT));
        
        // on reforme les accélérations
        acc_x = (int16) buff[0] | ((int8)buff[1]<<8);
        acc_y = (int16) buff[2] | ((int8)buff[3]<<8);
        acc_z = (int16) buff[4] | ((int8)buff[5]<<8);
    
        // on somme successivement les carrés
        sum_square_acc_x += acc_x * acc_x;
        sum_square_acc_y += acc_y * acc_y;
        sum_square_acc_z += acc_z * acc_z;
        
        CyDelayUs(delay); //fonction en microsecondes
        
    }
    
    //remet l'accéléro en standby mode
    accelero_write(POWER_CONTROL_ADDR, STANDBY_MODE);
    Accelero_Stop();
    
    *a_x = (uint16) sqrt(sum_square_acc_x/nb_acquisition);
    *a_y = (uint16) sqrt(sum_square_acc_y/nb_acquisition);
    *a_z = (uint16) sqrt(sum_square_acc_z/nb_acquisition);
    
}

// renvoie la norme du vecteur acceleration efficace (Pythagore)
uint16 accelero_calcul_norme_acc_efficace(uint16 a_x, uint16 a_y, uint16 a_z){

    return sqrt( a_x * a_x + a_y * a_y + a_z * a_z );

}

// envoie les données au xbee afin qu'il les transmettre 
// ce programme également gère les flags d'envoi.
// en pratique, on ne transmet plus a_globale qui correspondant à la norme du vecteur acceleration efficace
// en effet, c'est une information redondante car le recepteur peut calculer cette valeur directement
void accelero_transmission(uint16 a_x, uint16 a_y, uint16 a_z, uint16 a_globale){
     // pour ce faire, on va envoyer au Xbee un tableau contenant les données à transmettre
    
    //tableau de stockage
    uint8 data[6] = {0};
    
    // formation du tableau en fonction des flags définis 
    data[0] = (uint8)( ((a_x >>7) & 0x3F) + FLAG_TRANSMISSION_X);
    data[1] = a_x & 0x7F ;
    data[2] = (uint8)( ((a_y >>7) & 0x3F) + FLAG_TRANSMISSION_Y_Z);
    data[3] = a_y &  0x7F ;
    data[4] = (uint8)( ((a_z >>7) & 0x3F) + FLAG_TRANSMISSION_Y_Z);
    data[5] = a_z & 0x7F;
    
    // reveille le Xbee
    Pin_gestion_sleep_xbee_SetDriveMode(Pin_gestion_sleep_xbee_DM_STRONG);         
    Pin_gestion_sleep_xbee_Write(0u);
    CyDelay(10); // temps de réveil du xbee
    
    // place la pin tx en mode strong drive
    Pin_tx_SetDriveMode(Pin_tx_DM_STRONG);
    
    zigbee_Start();
    
    // envoi au Xbee des données
    zigbee_PutArray(data,6);
    CyDelay(50); // delay car il supprime la fin des données, à tester plus court
    while ( !(zigbee_GetTxBufferSize()==0));
    
    zigbee_Sleep();
    CyDelay(5); //surement plus utile
    
    // on remet les pins en mode haute impédance
    Pin_tx_SetDriveMode(Pin_tx_DM_DIG_HIZ);
    Pin_gestion_sleep_xbee_SetDriveMode(Pin_gestion_sleep_xbee_DM_DIG_HIZ);
    
    // on éteinds le Xbee
    Pin_gestion_sleep_xbee_Write(1u);
    
}

/* // cette fonction n'est plus utilisé car j'envoie désormais toutes les données en bloc au Xbee
void accelero_transmission_une_voie(uint16 a, int16 flag){
    
    int8 a_LSB = 0 ;
    int8 a_MSB = 0 ;
    
    // Pour la transmission le bit de poids le plus fort de a_LSB est un zéro 
    // Les 7 autres bits sont de la donnée
    a_LSB = (int8)(a & 0x7F); 
    
    // les deux bits de poids le plus fort de a_MSB sont un 11 pour a_x et 10 pour a_y et a_z
    // les 6 autres bits sont de la donnée
    a_MSB = (int8)( (a>>7) & 0x3F);
    a_MSB+= flag;
    
    
    XBee_UartPutChar(a_MSB);
    XBee_UartPutChar(a_LSB);
    
    //on attend d'être sur d'avoir tout transmis.
    while ( !(XBee_SpiUartGetTxBufferSize()==0));
    
}*/

/*
 *
 * GESTION DES REGISTRES
 *
*/

// renvoie la valeur dans l'adresse du registre de l'accelerometre



uint8 accelero_read(uint8 register_adress){

    uint8 x;
    uint8 rd_data = 123;
    
    do {
        uint8 wr_data[1] = {register_adress};
        x = Accelero_I2CMasterWriteBuf(ACCELERO_ADDR,wr_data,1,Accelero_I2C_MODE_COMPLETE_XFER);
    }
    while (0); //x != Accelero_I2C_MSTR_NO_ERROR
    
    do {
        x = Accelero_I2CMasterReadBuf(ACCELERO_ADDR,&rd_data,1,Accelero_I2C_MODE_COMPLETE_XFER); 
    }
    while (x != Accelero_I2C_MSTR_NO_ERROR); // car écriture envoie une erreur si le write n'est pas fini
    
   
    //wait for data transfer to complete 
    while (!(Accelero_I2CMasterStatus() & Accelero_I2C_MSTAT_RD_CMPLT));
    
    return rd_data;
}

// ecrit dans l'adresse du registre la valeur wr_data
void accelero_write( uint8 register_adress, uint8 wr_data){
    
    uint8  buffer[2];

    /* Initialize buffer with packet */
    buffer[0] = register_adress;
    buffer[1] = wr_data;
  
    Accelero_I2CMasterWriteBuf(ACCELERO_ADDR, buffer, 2 ,Accelero_I2C_MODE_COMPLETE_XFER);

    /* Waits until master completes write transfer */
    while (0u == (Accelero_I2CMasterStatus() & Accelero_I2C_MSTAT_WR_CMPLT));  

}

    
/* [] END OF FILE */
