#include "led.h"


/*Mehtode qui fait clignoter une led pendant un certain temps a l'aide d'une minueterie
 *IN: la couleur laquelle on veut afficher la led (VERT, ROUGE), le nombre de fois que l'on veut faire
 *  clignoter la led, le volatile bool sert pour l'interruption pour l'interuption
*/
void clignoterLed(uint8_t couleur, uint16_t duree, uint8_t repeterXFois, volatile bool& minuterieExpiree)
{
    for (uint8_t i = 0; i < repeterXFois; i++)
    {
        PORTB = couleur;
        partirMinuterie( duree); 
        while (minuterieExpiree == 0) {} 

        minuterieExpiree = 0;
        PORTB = 0;
        partirMinuterie( duree);
        while (minuterieExpiree == 0) {}

        minuterieExpiree = 0;
    } 
} 


/*Methode qui affiche la led d'une couleur ambre en changeant rapidement entre vert et ROUGE
 * Le main appelera cette fonction avec sa propre boucle determinant la periode d'affichage
 */
void ambre (void)
{
    PORTB = 1;
    partirMinuterie(8);
    PORTB = 2;
    partirMinuterie(8);
    
}
