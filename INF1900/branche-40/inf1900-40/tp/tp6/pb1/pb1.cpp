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

enum State{INIT, ATTENTE, CLIGNOTEMENT};
State state = INIT;


volatile uint8_t minuterieExpiree;
volatile bool MinuterieCommencee = false;
volatile uint8_t compteur;

volatile uint8_t boutonPoussoir = 0;
volatile uint8_t boutonPoussoirPrec = 0;
volatile bool bouttonIsPressed = false;

void ifpressed()
{

    
        if((PIND & PIN_SORTIE))
        _delay_ms(30);
            if((PIND & PIN_SORTIE))
            {
                 bouttonIsPressed = true;
            }
           
        else{
            bouttonIsPressed = false;
            
        }

    

}

void partirMinuterie ( uint16_t duree ) 
{
    cli();
    minuterieExpiree = 0;
    MinuterieCommencee = true;

    // mode CTC du timer 1 avec horloge divisée par 1024

    // interruption après la durée spécifiée

    TCNT1 = 0 ;

    OCR1A = duree;

    TCCR1A |= (1 << COM1A1) | (1 << COM1A0) ; //registre de controle
    TCCR1B |= (1 << CS10) | (1 << CS12 )| (1 << WGM12);

    TCCR1C = 0; 

    TIMSK1 |= (1 << OCIE1A) ; 
    sei();
}

ISR ( TIMER1_COMPA_vect ) 
{

    minuterieExpiree = 1;
    switch(state)
    {
        case ATTENTE:
            compteur += 10;
            minuterieExpiree = 1;
            break;
    }


}


ISR (INT0_vect) 
{


        ifpressed();
        if(!bouttonIsPressed && (state == ATTENTE))
            boutonPoussoir = 1;
    


    EIFR |= (1 << INTF0) ;

    


}


void clignoterLed(uint8_t couleur, uint16_t duree, uint8_t repeterXFois)
{
    for (uint8_t i = 0; i < repeterXFois; i++)
    {
        PORTB = couleur;
        partirMinuterie( duree); 
        while (minuterieExpiree == 0) {}           
        minuterieExpiree = 0;
        PORTB = 0;
        partirMinuterie( duree);
        while (minuterieExpiree == 0) {}
    } 
} 

void initialisation (void)
{
    cli ();

    DDRD = MODE_ENTRE;
    DDRB = MODE_SORTIE;

    sei ();
} 

int main ()
{
    initialisation();
    ifpressed();
    
    for(;;)
    {

        switch(state)
        {
            case INIT:
                ifpressed();
                compteur = 0;

                if(!bouttonIsPressed ^ boutonPoussoirPrec && !bouttonIsPressed)
                    state = ATTENTE;
                
                boutonPoussoirPrec = boutonPoussoir;
                break;

            case ATTENTE:
                while(!(PIND && PIN_SORTIE) && compteur < 110)
                {
                    partirMinuterie(7812);
                    while(minuterieExpiree == 0){}
                }
                state = CLIGNOTEMENT;
                break;
            case CLIGNOTEMENT:
                clignoterLed(VERT, 976, 2);
                clignoterLed(0, 7812, 1);
                for(uint8_t i =0; i < compteur/2; i++)
                {
                    clignoterLed(ROUGE, 1953, 1);
                }
                clignoterLed(VERT, 7812, 1);
                ifpressed();
                boutonPoussoirPrec = boutonPoussoir;
                state = INIT;
                break;

        }

    }
    


}