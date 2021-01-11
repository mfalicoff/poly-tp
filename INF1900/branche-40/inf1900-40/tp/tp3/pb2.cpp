#include <avr/io.h>
#define F_CPU 8000000UL
#include <util/delay.h>

void delay(int temp)
{
  for(int i=0; i<temp;i++)
  {
    _delay_us(1);
  }
}
void PMW (int a,int b,int c)
{
  for (int i = 0; i < c/2; i++)
    {
      PORTB = 1;
      delay(a);
      PORTB = 0;
      delay(b-a);
    }
    
}


int main ()
{

DDRB = 0xff; // PORT B est en mode sortie
const int B1 = 0x04;
  for(;;)
  {
    //PORTB = 1;
    int a=0;
    int b=16666;//(1/freq)*1 000 000
    int c=0;
    PMW(a,b,120);
    a=4166;//(1/freq)*pourcentage*1 000 000 (pour le 25%)
    PMW(a,b,120);
    a = 8333;//(1/freq)*pourcentage*1 000 000 (pour le 50%)
    PMW(a, b, 120);
    a = 12500;//(1/freq)*pourcentage*1 000 000 (pour le 75%)
    PMW(a, b, 120);
    a = 16666;//(1/freq)*pourcentage*1 000 000 (pour le 100%)
    PMW(a, b, 120);
    a=0;
    b=2500;
    PMW(a, b, 800);
    a = 625;//(1/freq)*pourcentage*1 000 000 (pour le 25% avec 400hz)
    PMW(a, b, 800);
    a = 1250;//(1/freq)*pourcentage*1 000 000 (pour le 50% avec 400hz)
    PMW(a, b, 800);
    a = 1875;//(1/freq)*pourcentage*1 000 000 (pour le 75% avec 400hz)
    PMW(a, b, 800);
    a = 2500;//(1/freq)*pourcentage*1 000 000 (pour le 100% avec 400hz)
    PMW(a, b, 800);
  }
  return 0;
}
