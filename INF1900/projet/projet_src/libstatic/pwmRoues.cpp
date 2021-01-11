/*
Projet final 4081 pwmRoues.cpp
Auteurs: Maximiliano Falicoff -2013658
        Philippe Desilets -2020566
		Guillaume Nadeau
		Alexis Thibeault

Permet de generer des ondes pwm sur ls pins D4 et D5
*/

#include "pwmRoues.h"



/**
 * @brief Fonction qui permet de generer un onde PWM materielle
 * on a besoin des int car on veut passer un nombre signe, on lui passe un pourcentage et apres la methode le met sur 255 pour fini le bon pourcentage a/b
 * En dependance du signe des param, on aura les led qui s'allumeront 
 * 
 * @param pourcentageGauche 
 * @param pourcentageDroit 
 */
void ajustementPWM ( int pourcentageGauche, int pourcentageDroit ) {

  pourcentageDroit < 0 ?  OCR1A = (-1)*(int)(pourcentageDroit*255/100) :   OCR1A = (int)(pourcentageDroit*255/100) ;

  pourcentageGauche < 0 ?  OCR1B = (-1)*(int)(pourcentageGauche*255/100) :   OCR1B = (int)(pourcentageGauche*255/100) ;

  
  if((pourcentageGauche > 0) && (pourcentageDroit > 0))
  {
    	PORTD = (1<<PIND0);
			PORTD |=(1<<PIND2);
  }
    if((pourcentageGauche > 0) && (pourcentageDroit < 0))
  {
    	PORTD = (1<<PIND0);
			PORTD |=(1<<PIND7);
  }
    if((pourcentageGauche < 0) && (pourcentageDroit > 0))
  {
    	PORTD = (1<<PIND1);
			PORTD |=(1<<PIND2);
  }
    if((pourcentageGauche < 0) && (pourcentageDroit < 0))
  {
    	PORTD = (1<<PIND1);
			PORTD |=(1<<PIND7);
  }


  // division d'horloge par 8 - implique une frequence de PWM fixe


  TCCR1A |= (1 << WGM10);
  TCCR1A |= (1 << COM1A1);
  TCCR1A |= (1 << COM1B1);

  TCCR1B |= (1 << CS11);

  TCCR1C = 0;

}

/**
 * @brief permet d'arreter une onde PWM en mettant les sortis a 0, et etteint les leds
 * 
 */
void stopPWM()
{
    OCR1A = 0;
    OCR1B = 0;
    TCCR1B = 0;
    TCCR1A = 0;
    PORTD |= ~(0<<PIND0);

}
