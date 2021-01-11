/*
Projet final 4081 affichage7Seg.cpp
Auteurs: Maximiliano Falicoff -2013658
        Philippe Desilets -2020566
		Guillaume Nadeau
		Alexis Thibeault
Permet l'affichage sur le display
*/

#include "affichage7Seg.h"

/**
 * @brief permet de convertir les chiffres de 0-9 en hex pour le affichage en 7 segments
 * 
 * @param chiffre 
 * @return uint8_t le nombre en hex pour pouvoir le display en segments
 */
uint8_t trouverChiffre(uint8_t chiffre) 
{
  //tableau qui comporte les chiffres en affichage de 7 segments
  uint8_t TableauNombre[10] = { 0xFC, 0x60, 0xDA, 0xF2, 0x66, 0xB6, 0xBE, 0xE0, 0xFE, 0xE6 };

  return TableauNombre[chiffre];
}

/**
 * @brief 
 * 
 * @param vitesseG 
 * @param vitesseD 
 * @param temps en ms
 */
void affichage7FPS(int vitesseG, int vitesseD,int temps) //FPS pour frames per second (mm si pas en secondes)
{
	int vitDrUn = trouverChiffre(vitesseD%10);
	int vitGaUn = trouverChiffre(vitesseG%10);
	int vitDrDz = trouverChiffre(vitesseD/10);
	int vitGaDZ = trouverChiffre(vitesseG/10);

	for (int j = 0; j < temps/5; j++) //50 c'est la fps
	{
		PORTA = display1;
		PORTC = vitDrUn;
		_delay_ms(1);
		PORTA = display2;
		PORTC = vitDrDz;
		_delay_ms(1);
		PORTA = display3;
		PORTC = 0x02; //tiret
		_delay_ms(1);
		PORTA = display4;
		PORTC = vitGaUn;
		_delay_ms(1);
		PORTA = display5; 
		PORTC = vitGaDZ;
		_delay_ms(1);
					
	}
}

/**
 * @brief Clear le diplay et n'affiche plus rien
 * 
 */
void clear7Seg()
{
  PORTA = 0xFF;   //desactive le afficheur en 7 segments uns fois le temps ecoule
  PORTC = 0x00;
}