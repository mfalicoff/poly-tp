#include "ifpressed.h"


/*Methode qui verifie si le boutton a ete appuye avec un debounce
 *Return un bool vrai si le boutton a ete appuye, faux sinon
 */

bool ifpressed()
{
  if((PIND & 0x04))
  {
    _delay_ms(20);

    if((PIND & 0x04))
    {
        return true;
    }
           
    else
    {
        return false;       
    }
  } 

  return false;

}
