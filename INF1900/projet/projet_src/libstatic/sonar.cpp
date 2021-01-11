/*
Projet final 4081 sonar.cpp
Auteurs: Maximiliano Falicoff -2013658
        Philippe Desilets -2020566
		Guillaume Nadeau
		Alexis Thibeault

Permet de savoir les distances des trois obstacles avec trois sonars
*/

#include "sonar.h"


/**
 * @brief Methode principale qui permet de setup le clk
 *        et appelle le methode qui eevalue les trois distances
 *        et les affiche a l'ecran lcd, ilsuffit juste de l'appelr
 *        a partir du main et de specifier l'intervalle 
 *        a laquelle on veut l'appeler.
 * 
 */
Distances sonar()
{
	Distances frontDistance;
	frontDistance.distanceSonar1 = 0;
	frontDistance.distanceSonar2 = 0;
	frontDistance.distanceSonar3 = 0;
	
	DDRB |= (1 << SONAR_OUT);
		
	//Timer
	TCCR1B |=(0 << CS12) | (1 << CS11) | (1 << CS10);	//64 pre-scale

	frontDistance = evaluerDistances();
			
	afficherDistances(frontDistance.distanceSonar1/10, frontDistance.distanceSonar2/10, frontDistance.distanceSonar3/10);
	return frontDistance;
}

/**
 * @brief Permet d'evaluer la distance que mesure chaque sonar
 * 
 * Utilisation de la methode qui envoie un trigger pour chaque sonar un a la fois
 * cela me semblait comme la methode la plus facile mais qui gaspille un peu plus de temps
 * Utilisation d'un struct distnaces afin de pouvoir retourner les trois distances en meme 
 * temps.
 * 
 * @return struct distances 
 */
Distances evaluerDistances()		
{
	Distances distances;
	distances.distanceSonar1 = 0;
	distances.distanceSonar2 = 0;
	distances.distanceSonar3 = 0;

	PORTB |= (1 << SONAR_OUT);
	_delay_us(12);
	PORTB &= ~(1 << SONAR_OUT);
	
	while (!(PINA & (1 << SONAR_1))){};
    TCNT1 = 0;
    while ( ( PINA & ( 1 << SONAR_1 ) ) && ( TCNT1 < 58800 ) );
	distances.distanceSonar1 = (TCNT1 *8)/580;
	

	PORTB |= (1 << SONAR_OUT);
	_delay_us(12);
	PORTB &= ~(1 << SONAR_OUT);
	
	while (!(PINA & (1 << SONAR_2))){};
    TCNT1 = 0;
    while ( ( PINA & ( 1 << SONAR_2 ) ) && ( TCNT1 < 58800 ) );
	distances.distanceSonar2 = (TCNT1 *8)/580;


	PORTB |= (1 << SONAR_OUT);
	_delay_us(12);
	PORTB &= ~(1 << SONAR_OUT);
	
	while (!(PINA & (1 << SONAR_3))){};
    TCNT1 = 0;
    while ( ( PINA & ( 1 << SONAR_3 ) ) && ( TCNT1 < 58800 ) );
	distances.distanceSonar3 = (TCNT1 *8)/580;
	
	
	
	return distances;	
}