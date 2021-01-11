#include <avr/io.h>
#define F_CPU 8000000UL
#include <util/delay.h>

int led (){


  DDRB = 0xff; // PORT B est en mode sortie

    for(;;){
        PORTB = 1; //VERT
      _delay_ms(2000);
      PORTB = 2; //VERT
      _delay_ms(2000);
      for(int i = 0; i < 200; i++)
      {
        PORTB = 1;
        _delay_ms(10);
        PORTB = 2;
        _delay_ms(10);
        }
    }
}