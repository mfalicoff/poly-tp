#ifndef AFFICHAGE_7_SEG
#define AFFICHAGE_7_SEG

#include <avr/io.h>
#define F_CPU 8000000UL
#include <util/delay.h>

#define display1 0x78
#define display2 0xB8
#define display3 0xD8
#define display4 0xE8
#define display5 0xF0

uint8_t trouverChiffre(uint8_t chiffre);
void affichage7FPS(int vitesseG, int vitesseD,int temps);
void clear7Seg();

#endif // AFFICHAGE_7_SEG