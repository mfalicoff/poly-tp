#include "memoire_24.h"
#include <util/delay.h>

void lecture (uint8_t mot, uint16_t addr, uint16_t fin_lect, Memoire24CXXX& mem);
void ecriture(uint8_t *mot, uint16_t addr, uint16_t fin_lect, Memoire24CXXX& mem);
