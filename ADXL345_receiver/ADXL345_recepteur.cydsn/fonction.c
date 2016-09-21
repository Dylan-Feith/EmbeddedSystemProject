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
#include <fonction.h>
#include <project.h>

#include <string.h>
#include <stdio.h>


uint16 reception(int8 *voie){
    
    	    char remote_char_low = 0;
            char remote_char_high = 0;
    
            // on attend un octet avec le flag 1 (pour le high)
            do{
                    while(XBee_SpiUartGetRxBufferSize() == 0);
                    remote_char_high = XBee_UartGetChar();
                }
            while((remote_char_high & 0x80) != 0x80);
            
            
            switch (remote_char_high & 0xC0)
            {
                case 0xC0 ://si on recoit a_x, on le sait (c'est le seul a avoir le flag 11
                {
                    remote_char_high -= 0xC0;
                    *voie = 1 ;
                    break;    
                }
                
                case 0x80 :// si on a le flag 10 c'est qu'on a bien eu la valeur suivante
                {
                    remote_char_high -= 0x80;
                    *voie = *voie + 1 ;
                    break;
                }
                default :
                {
                 *voie = 0 ;   
                }   
            }
            
            //le prochain c'est le low :
            while (XBee_SpiUartGetRxBufferSize()==0); // on attends.  
            remote_char_low = XBee_UartGetChar();
            
            // si ce n'est pas normal (on n'a pas le flag )
            if ( !((remote_char_low & 0x80) == 0x00)){
                *voie = 0 ;
            }
                
            // On reforme l'uint16.
            uint16 numeric_acc = (remote_char_high & 0x3F) ;
            numeric_acc <<=7; //decallage de 7 bits vers la gauche et affecte à numeric_acc
            numeric_acc += remote_char_low & 0x7F;
            CyDelay(10);
            
            return numeric_acc;
               
}


/* [] END OF FILE */
