/*
Nom: TP4p2


Alexis Thibeault 2017282
Guillaume Nadeau 2018665
*/

#define F_CPU 8000000UL
#include "controleMem.h"
#include "connect_pc.h"

/*Methode qui permet la lecture de la memoire.
 * IN: mot: endroit ou l'on va mettre les donnes de la memoire
 *    addr: addresse dedebut lecture
 *    fin_lect addresse de fin de lecture (longeure de donnee)
 *    Memoire24CXXX mem: objet memoire
 */
void lecture (uint8_t mot, uint16_t addr, uint16_t fin_lect, Memoire24CXXX& mem) 
{
  initialisationUART(); // at-on besoin de inituart?
  
  while(addr != fin_lect)
  {
    mem.lecture(addr, &mot);
    transmissionUART(mot);
    addr++;
  }
}

/*Methode qui permet l'ecriture a la memoire
 * IN: *mot: pointeur qui pointe vers le debut de la chaine de donnees
 *    addr: addresse ou l'on veut ecrire la donnee
 *    Memoire24CXXX mem: objet qui represente la memoire
 */
void ecriture(uint8_t *mot, uint16_t addr, uint16_t fin_lect, Memoire24CXXX& mem)
{
    uint8_t n = sizeof(*mot) / sizeof(mot[0]);

    mem.ecriture(addr, (uint8_t*)mot, n);
    _delay_ms(5);
}
