#ifndef PWM_ROUES_H
#define PWM_ROUES_H

#include <avr/io.h>
#define F_CPU 8000000UL
#include "affichage7Seg.h"

void ajustementPWM (int pourcentageGauche, int pourcentageDroit );
void stopPWM();

#endif //PWM_ROUES_H

