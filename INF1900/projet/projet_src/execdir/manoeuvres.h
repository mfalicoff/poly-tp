#include <avr/io.h>
#define F_CPU 8000000UL
#include <util/delay.h>
#include "LCD.h"
#include <avr/interrupt.h>
#include "sonar.h"
#include "affichage7Seg.h"
#include "pwmRoues.h"
#include "ifPressed.h"


#define MODE_SORTIE 0xff;
#define MODE_ENTREE 0x00;

uint8_t detection();
void man1();
void man2();
void man3();
void man4();
void man5();
void man6();
void manIconnue();

void initMan();
void finMan();
uint8_t choixManoeuvre(Distances Distance);