#ifndef LCD_H_
#define LCD_H_

#include "lcm_so1602dtr_m_fw.h"
#include "customprocs.h"

#define DDR	DDRB // `Data Direction Register' AVR occup� par l'aff.
#define PORT PORTB

void afficherDistances(double dist1, double dist2, double dist3);
void afficherManouevre(int manoeuvre);
void clearDispl();

#endif //LCD_H_