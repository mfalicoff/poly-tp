#include <avr/interrupt.h>
#include <avr/io.h>
#define F_CPU 8000000UL
#include <util/delay.h>
#include "can.h"

const int ROUGE = 0x01;
const int VERT = 0x02;
const int ETEINT = 0x00;
const int MODE_SORTIE = 0Xff;
const int MODE_ENTRE = 0x00;
const int PIN_SORTIE = 0x04;

void initialisation ( void ) {
    DDRB = 0xff;    // PORT B est en mode sortie
    DDRD = 0x00;    // PORTD en entree
    PORTB = 0x00;   // La LED est ETEINT
}
void couleurAmbree()
{
    PORTB = ROUGE;
    _delay_ms(3);
    PORTB = VERT;
    _delay_ms(4);
}

int main()
{
    initialisation();
    uint8_t valeurNumerique = 0;

    can signal;

    for(;;)
    {
        valeurNumerique = signal.lecture(0); // Appel la fonction lecture dans can.cpp 
        // Faire une conversion et aller retourner le resultat sur 16 bits
        // dont seulement les 10 de poids faibles sont significatifs.
    
        if (0 <= valeurNumerique && valeurNumerique <= 25 )
            PORTB = VERT;
        while ( 25 < valeurNumerique && valeurNumerique <= 122 )
        {
            couleurAmbree();
            valeurNumerique = signal.lecture(0); //Faire une nouvelle lecture de la valeur
        }
        if ( 122 < valeurNumerique && valeurNumerique <= 128 )
            PORTB = ROUGE; 
    }
    

}