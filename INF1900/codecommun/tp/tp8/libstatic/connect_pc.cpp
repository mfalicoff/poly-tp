/*
Nom: TP4p2


Alexis Thibeault 2017282
Guillaume Nadeau 2018665
*/

//#define F_CPU 8000000UL
#include "connect_pc.h"
#include <util/delay.h>


/*Methode qui permet l'init qui va permettre la transmission de robot vers le PC avec l'uart.
 */
void initialisationUART(void)
{

  // 2400 bauds. Nous vous donnons la valeur des deux

  // premier registres pour vous éviter des complications

  UBRR0H = 0;

  UBRR0L = 0xCF;

  // permettre la réception et la transmission par le UART0

  UCSR0A = (1 << RXC0) | (1 << TXC0);

  UCSR0B = (1<< RXEN0) | (1 << TXEN0);

  // Format des trames: 8 bits, 1 stop bits, none parity

  UCSR0C = ( 1 << UCSZ01) | (1 << UCSZ00);
}



/*De l'USART vers le PC
 *IN: la donne que l'on veut transmettre
 */

void transmissionUART(char donnee)
{
  /* Wait for empty transmit buffer */
  while ( !( UCSR0A & (1<<UDRE0)) );
  /* Put data into buffer, sends the data */
  UDR0 = donnee;
}


/*Methode qui permet l'affichage d'une donnee sur le PC en appelant la methode transmissionUART
 *IN: la serie de char que l'on veut envoyer au PC
 *
 */

void Afficher(char* mots)
{
  int size = sizeof(mots)/sizeof(mots[0]);

  for(int i = 0; i < size; i++)
  {
     transmissionUART((mots[i]));
      _delay_ms(5);
  }
}

