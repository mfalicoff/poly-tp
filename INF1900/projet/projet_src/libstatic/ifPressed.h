#ifndef IF_PRESSED
#define IF_PRESSED

#include <avr/io.h>
#define F_CPU 8000000UL
#include <util/delay.h>

#define bouton 0x03

bool ifpressed ();

#endif //IF_PRESSED
