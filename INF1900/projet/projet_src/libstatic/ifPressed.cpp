/*
Projet final 4081 ifPressed.cpp
Auteurs: Maximiliano Falicoff -2013658
        Philippe Desilets -2020566
		Guillaume Nadeau
		Alexis Thibeault

Permet de savoir si le boutton poussoir a ete appuye par srutation
*/

#include "ifPressed.h"


/*Methode qui verifie si le boutton a ete appuye avec un debounce
 *Return un bool vrai si le boutton a ete appuye, faux sinon
 */
bool ifpressed()
{
    if(!PIND & bouton)
    {
      _delay_ms(30);
      if(!PIND & bouton)
      {
        return true;
      }
    }
	
  
  return false;
}
