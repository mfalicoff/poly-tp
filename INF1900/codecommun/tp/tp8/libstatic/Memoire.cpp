#include "Memoire.h"



void lirememoire()
{
  DDRB = 0xff;
 

  char *message = "*P*O*L*Y*T*E*C*H*N*I*Q*U*E* *M*O*N*T*R*E*A*L*\0";
  char * lect = "000000000000000000000000000000000000000000000\0";
  int longueur = 45;

  Memoire24CXXX memoire;
   
  const uint16_t adresse = 0x00;
  


    memoire.ecriture(adresse, (uint8_t*)message, longueur);
  
    _delay_ms(5);
    
    memoire.lecture(adresse, (uint8_t*) lect, longueur);

    
    bool ok = true;

      
      for(int i = 0; i < sizeof(lect); i++)
      {

        if(lect[i] !=  message[i])
        {
          ok = false;
          break;
        }

      }
    
    if(ok)
      PORTB = 1;
    else
      PORTB=2;
}

/*int main()
{
  DDRB = 0xff;
 

  char *message = "*P*O*L*Y*T*E*C*H*N*I*Q*U*E* *M*O*N*T*R*E*A*L*\0";
  char * lect = "000000000000000000000000000000000000000000000\0";
  int longueur = 45;

  Memoire24CXXX memoire;
   
  const uint16_t adresse = 0x00;
  


    memoire.ecriture(adresse, (uint8_t*)message, longueur);
  
    _delay_ms(5);
    
    memoire.lecture(adresse, (uint8_t*) lect, longueur);

    
    bool ok = true;

      
      for(int i = 0; i < sizeof(lect); i++)
      {

        if(lect[i] !=  message[i])
        {
          ok = false;
          break;
        }

      }
    
    if(ok)
      PORTB = 1;
    else
      PORTB=2;
}*/
