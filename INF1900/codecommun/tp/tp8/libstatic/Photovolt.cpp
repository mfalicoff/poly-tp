/*
Nom: TP6p2
Alexis Thibeault 2017282
Guillaume Nadeau 2018665

Description:
Programme qui fait changer la couleur de une DEL
selon la intensite lumineuse  absorbee  par  une
photoresistance.  

Identification et materielle:
Broches B1 et B2 du Port B en mode sortie  relié
avec la DEL, photoresistance relié  au   vcc-gnd
du  Port  B  ainsi qu'au broches  A0  et  A1  du 
Port A.
*/

#include "Photovolt.h"

/*Methde qui permet la lecture de la valeure de la photoresistance. 
 *IN: Objet convertisseur analogique-numerique.
 *On prend les 8 bits les plus significatifs
 *OUT: un unint8_t avec la valeur de la photoresistance
 */
uint8_t photo(can& photo)
{
  DDRA = 0x00;
  return photo.lecture(PORTA) >> 2;
}

