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

/*
Lors des envois, de temps en temps, certains se passe mal et le système se désynchronise.
Pour resynchroniser, on utilise derniere_voie_recu
On sait que l'on envoit a_x, a_y puis a_z
ces grandeurs sont codées sur 13 bits. On envoie donc deux octets.
On envoie d'abord a_x_MSB qui a pour valeur 11 puis 6 bits de données
puis a_x_LSB qui a pour valeur 0 puis 7 bits de données

Ensuite vient a_y puis a_z avec la même logique sauf que le flag du MSB n'est plus 11 mais 10

derniere_voie_recu devient 1 si on vient de lire a_x
il s'incrémente de 1 si on lit une valeur ayant le flag 10

S'il y a une erreur, derniere_voie_recu vaut 0

*/
#include <project.h>
#include <string.h>
#include <stdio.h>
#include <fonction.h>


const char startup_header[] = "\n\rPsoc en mode reception\r\n";
const char command_prompt[] = "reception : ";

int main()
{
    uint16 nb_erreur = 0 ;
    int8 derniere_voie_recu = 0 ;
    
    char str[20] = {'\0'};
    
    XBee_Start(); //Enable com between micro and XBee
	PC_Start(); //Enable com between micro and PC
    
    PC_UartPutString(startup_header);
	PC_UartPutString("\n\r");
	PC_UartPutString(command_prompt);
    
    for(;;)
    {

        uint16 acc_received = reception(&derniere_voie_recu);

        switch(derniere_voie_recu)
        {
            case 1:
            {    
                sprintf(str, "a_x :%d\n\r",acc_received);
                PC_UartPutString(str); // Print received characters in local terminal
                break;
            }
        
        
            case 2: 
            {
                sprintf(str, "a_y :%d\n\r",acc_received);
                PC_UartPutString(str); // Print received characters in local terminal
                break;
            }
            case 3 :
            {
                sprintf(str, "a_z :%d\n\r",acc_received);
                PC_UartPutString(str); // Print received characters in local terminal
                PC_UartPutString("\n\r");
                break;
            }
            default :
            {
                nb_erreur++;
                sprintf(str, "erreur numero : %d\n\r",nb_erreur);
                PC_UartPutString(str); 
            }
        }
            
            
           
        }
    
}

/* [] END OF FILE */
