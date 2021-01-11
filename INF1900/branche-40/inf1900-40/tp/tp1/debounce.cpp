#include <avr/io.h>
#define F_CPU 8000000UL
#include <util/delay.h>

//debounce
int main(){

    DDRA = 0xff;
    DDRD = 0X00;

    for(;;){

        if ( PIND & 0x04 ){
      _delay_ms(10);
      
        if ( (PIND & 0x04)){
          PORTA = 1;
          _delay_ms(5);
          PORTA = 2;
          _delay_ms(5);
        }
    }else{
      PORTA = 0;
    }
    }
   
}
