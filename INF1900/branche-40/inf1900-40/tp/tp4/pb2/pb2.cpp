#include <avr/interrupt.h>
#include <avr/io.h>
#define F_CPU 8000000UL
#include <util/delay.h>

const int ROUGE = 0x01;
const int VERT = 0x02;
const int ETEINT = 0x00;
const int MODE_SORTIE = 0Xff;
const int MODE_ENTRE = 0x00;
const int PIN_SORTIE = 0x04;


volatile uint8_t minuterieExpiree;
volatile bool MinuterieCommencee = false;

volatile uint8_t boutonPoussoir;
volatile bool bouttonIsPressed = false;

void ifpressed()
{

    
        if(PIND & PIN_SORTIE)
        _delay_ms(30);
            if(PIND & PIN_SORTIE)
            {
                 bouttonIsPressed=true;
            }
           
        else{
            bouttonIsPressed = false;
        }

    

}

void partirMinuterie ( uint16_t duree ) 
{

    minuterieExpiree = 0;
    MinuterieCommencee = true;

    // mode CTC du timer 1 avec horloge divisée par 1024

    // interruption après la durée spécifiée

    TCNT1 = 0 ;

    OCR1A = duree;

    TCCR1A |= (1 << COM1A0) ; 

    TCCR1B |= (1 << CS12) | (1 << CS10) ;

    TCCR1C = 0; 

    TIMSK1 |= (1 << OCIE1A) ; 

}

ISR ( TIMER1_COMPA_vect ) 
{

    minuterieExpiree = 1;

}


ISR (INT0_vect) 
{

    ifpressed();
    if (bouttonIsPressed && MinuterieCommencee){
        boutonPoussoir = 1;
    }
    EIFR |= (1 << INTF0) ;

    


}

void routine(){
    do {

   
    } while ( minuterieExpiree == 0 && boutonPoussoir == 0 );



    cli ();

  

    if(boutonPoussoir)
    {
        PORTB = VERT;
    }
    else
        PORTB = ROUGE;

}

void initialisation (void)
{
    cli ();

    DDRD = MODE_ENTRE;
    DDRB = MODE_SORTIE;

    EIMSK |= (1 << INT0) ;

    EICRA |= (1 << ISC00) ;

    sei ();
}
int main ()
{
    initialisation();
    _delay_ms(10000);
    PORTB = VERT;
    _delay_ms(100);
    PORTB = ETEINT;
    partirMinuterie(0x1E84);
    routine();

}