#ifndef SONAR_H
#define SONAR_H

#include <avr/io.h>
#define F_CPU 8000000UL
#include <util/delay.h>
#include "LCD.h"

#define SONAR_OUT PORTB0
#define SONAR_1 PINA0
#define SONAR_2 PINA1
#define SONAR_3 PINA2

	
#ifndef struct_Dis
#define struct_Dis
struct Distances
{
	double distanceSonar1;
	double distanceSonar2;
	double distanceSonar3;
};
#endif

Distances evaluerDistances();

Distances sonar();

#endif //SONAR_H