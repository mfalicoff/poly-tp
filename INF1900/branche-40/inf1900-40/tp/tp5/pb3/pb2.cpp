#include <avr/io.h>
#define F_CPU 8000000UL
#include <util/delay.h>
#include <memoire_24.h>

const int MODE_SORTIE = 0xff;


void initialisationUART ( void ) {

  // 2400 bauds. Nous vous donnons la valeur des deux

  // premier registres pour vous éviter des complications

  UBRR0H = 0;

  UBRR0L = 0xCF;

  // permettre la réception et la transmission par le UART0

  UCSR0A = 0;

  UCSR0B = (1 << RXEN0) | (1 << TXEN0);

  // Format des trames: 8 bits, 1 stop bits, none parity

  UCSR0C = (1 << UCSZ11) | (1 << UCSZ10);
}




    // De l'USART vers le PC

void transmissionUART ( uint8_t donnee ) {

  while ( !( UCSR0A & (1<<UDRE0)) );
    UDR0 = donnee;

}

int main()
{
  DDRD = MODE_SORTIE;

  Memoire24CXXX memoire;
  const uint16_t adresse = 0x00;

  unsigned char mots[]= "Le robot en INF1900\n";
  memoire.ecriture(adresse,mots, 29);
  _delay_ms(5);
  initialisationUART();
  unsigned char lecture[] = "";
  uint8_t  j;
  memoire.lecture(0x00, &lecture[0], 29);
  for ( j=0; j < 20; j++ ) {
    transmissionUART(lecture[j]);
    _delay_ms(5);
  }   
}





