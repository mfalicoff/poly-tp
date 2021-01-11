#include <avr/io.h>
#define F_CPU 8000000UL
#include <util/delay.h>
#include "../libstatic/led.h"
#include "../libstatic/can.h"
#include "../libstatic/connect_pc.h"
#include "../libstatic/ifpressed.h"
#include "../libstatic/memoire_24.h"
#include "../libstatic/partirminuterie.h"
#include "../libstatic/Photovolt.h"
#include "../libstatic/PWM_roues_.h"

int main()
{
    DDRB = 0xFF;

    while(1)
    {
        ambre();
    }
}

