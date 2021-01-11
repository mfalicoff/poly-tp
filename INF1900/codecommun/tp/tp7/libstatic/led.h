#include <avr/io.h>
#define F_CPU 8000000UL
#include <util/delay.h>
#include "partirminuterie.h"


void clignoterLed(uint8_t couleur, uint16_t duree, uint8_t repeterXFois, volatile bool& minuterieExpiree);
void ambre (void);
