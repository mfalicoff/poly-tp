#include "controleMem.h"
#include "connect_pc.h"
#include "memoire_24.h"

#define DEBUG 

#ifdef DEBUG

#define DEBUG_PRINT(x) Afficher(x);

#else

#define DEBUG_PRINT(x) do {} while (0) // code mort

#endif
