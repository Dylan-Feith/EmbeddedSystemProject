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

#include "project.h"
#include <math.h>

#define ACCELERO_ADDR           0x1D

/* 
 *
 *DEFINITION DES CONSTANTES DU PROJET
 * 
*/


#define RANGE_2G                0x00
#define RANGE_4G                0x01
#define RANGE_8G                0x02
#define RANGE_16G               0x03

#define FULL_RESOLUTION         0x08 // 13 bits
#define LOW_RESOLUTION          0x00 // 10 bits

#define LOW_POWER               0x10
#define HIGH_POWER              0x00

#define DATA_RATE_400_Hz        0x0C
#define DATA_RATE_200_Hz        0x0B
#define DATA_RATE_100_Hz        0x0A
#define DATA_RATE_50_Hz         0x09
#define DATA_RATE_25_Hz         0x08

#define MESURE_MODE             0x08
#define STANDBY_MODE            0X00

#define DATA_FORMAT_ADDR        0x31
#define POWER_CONTROL_ADDR      0x2D
#define BW_RATE_ADDR            0x2C

#define DATA_X_LSB_ADDR         0x32 // finalement seule cette adresse est utilisée 
                                     //car on lit 6 fois dans la mémoire à partir de 0x32

#define DATA_X_MSB_ADDR         0x33
#define DATA_Y_LSB_ADDR         0x34
#define DATA_Y_MSB_ADDR         0x35
#define DATA_Z_LSB_ADDR         0x36
#define DATA_Z_MSB_ADDR         0x37

#define FLAG_TRANSMISSION_X     0xC0 // 11 00 0000     
#define FLAG_TRANSMISSION_Y_Z   0x80 // 10 00 0000

/*
 *
 * INITIALISATIONS
 *
*/

// initialise l'accelerometre
void accelero_init(int range, int resolution, int rate);

// initialise le WDT : param le temps de veille en secondes
void initialisation_projet(int8 time_sec); 


/*
 *
 * GESTION GLOBALE DE L'ACCELEROMETRE
 *
*/

// lis nb_acquision données sur chaque axe à la vitesse output_data_rate de l'accelerometre
// et calcule dynamiquement la valeur des accelerations efficaces sur les trois axes
// on passe en parametre des pointeurs pour les trois axes afin de récupérer les valeurs 
void accelero_acquisition_efficace(uint16 *a_x, uint16 *a_y, uint16 *a_z, uint8 nb_acquisition, uint16 output_data_rate);

// renvoie la norme du vecteur acceleration efficace (Pythagore)
uint16 accelero_calcul_norme_acc_efficace(uint16 a_x, uint16 a_y, uint16 a_z);

// envoie les données au xbee afin qu'il les transmettre 
// ce programme également gère les flags d'envoi.
// en pratique, on ne transmet plus a_globale qui correspondant à la norme du vecteur acceleration efficace
// en effet, c'est une information redondante car le recepteur peut calculer cette valeur directement
void accelero_transmission(uint16 a_x, uint16 a_y, uint16 a_z, uint16 a_globale);

// cette fonction n'est plus utilisé car j'envoie désormais toutes les données en bloc au Xbee
void accelero_transmission_une_voie(uint16 a, int16 flag); // n'est pas utilisé

/*
 *
 * GESTION DES REGISTRES
 *
*/

// renvoie la valeur dans l'adresse du registre de l'accelerometre
uint8 accelero_read(uint8 register_adress);

// ecrit dans l'adresse du registre la valeur wr_data
void accelero_write( uint8 register_adress, uint8 wr_data);


/* [] END OF FILE */
