/*Methode qui permet de genrer une onde pwm de facon materielle
 *IN: le pourcentage qui represente le rapport a/b
 */

#include "PWM_roues_.h"

void ajustementPWM ( uint8_t pourcentage ) {

  // mise à un des sorties OC1A et OC1B sur comparaison

  // réussie en mode PWM 8 bits, phase correcte

  // et valeur de TOP fixe à 0xFF (mode #1 de la table 17-6

  // page 177 de la description technique du ATmega324PA)

  OCR1A = pourcentage ;

  OCR1B = pourcentage ;


  // division d'horloge par 8 - implique une frequence de PWM fixe


  //TCCR1A |= (1 << COM1A1) | (1 << COM1B1)| (1 << WGM10); //Table 16-4.
    TCCR1A |= (1 << WGM10);
    TCCR1A |= (1 << COM1A1);
    TCCR1A |= (1 << COM1B1);

    TCCR1B |= (1 << CS11);

  TCCR1B |= (1 << CS11);

  TCCR1C = 0;

}
