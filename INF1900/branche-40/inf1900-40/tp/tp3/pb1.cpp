#include <avr/io.h>
#define F_CPU 8000000UL
#include <util/delay.h>

void delay(int temp)
{
  for(int i=0; i<temp;i++)
  {
    _delay_us(0.5);
  }
}

int main (){

DDRB = 0xff; // PORT B est en mode sortie
int a=1500;
const int b=1500;


for(;;)
{
  while(a>=0)
    {
      PORTB = 2;
      delay(a);
      PORTB = 0;
      delay(b-a);
      a--;
    }
}
}

