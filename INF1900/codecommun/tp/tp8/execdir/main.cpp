#include <avr/io.h>
#define F_CPU 8000000UL
#include <util/delay.h>
#include "connect_pc.h"
#include "debug.h"


const int Rouge = 0x01;
const int Vert = 0x02;
const int Eteint = 0x00;
const int MODE_SORTIE = 0Xff;
const int MODE_ENTRE = 0x00;
const int PIN_SORTIE = 0x04;
#define DEBUG 


bool ifpressed()
{

    
        if(PIND & PIN_SORTIE)
        _delay_ms(10);
            if(PIND & PIN_SORTIE)
            {
                return true;
            }
           
        else{
            return false;
        }
        

    

}

// void pb2()
// {
//     enum state{state0, state1, state2, state3, state4, state5};
//      DDRD = MODE_ENTRE;
//      DDRB = MODE_SORTIE;
  
//      state statePres = state0;
//     //  unsigned char x0[] = {'0'};
//     //  unsigned char x1[] = {'1'};
//     //  unsigned char x2[] = {'2'};
//     //  unsigned char x3[] = {'3'};
//     //  unsigned char x4[] = {'4'};
//     //  unsigned char x5[] = {'5'};

//      uint8_t x0 = 0;
//      uint8_t x1 = 1;
//      uint8_t x2 = 2;
//      uint8_t x3 = 3;
//      uint8_t x4 = 4;
//      uint8_t x5 = 5;

    

  
//     for(;;)
//     {
//         switch(statePres) 
//         {
//             case state0:
//             DEBUG_PRINT(x0);
//             PORTB = Rouge;
//             if(ifpressed() == true){statePres = state1;}
//             break;

//             case state1 :
//             DEBUG_PRINT(x1);
//             while(ifpressed() == true)
//             {
//                 PORTB = Vert;
//                 _delay_ms(5);
//                  PORTB = Rouge;
//                  _delay_ms(5);
//                  ifpressed();
//             }
//             statePres = state2;  
//             break;
                     
//             case state2 : 
//             DEBUG_PRINT(x2);
//             PORTB = Vert;
//             if(ifpressed() == true) {statePres = state3;}
//             break;

//             case state3 : 
//             DEBUG_PRINT(x3);
//             while(ifpressed() == true){PORTB = Rouge;}
//             statePres = state4;
//             break;

//             case sAffichertate4 :
//             DEBUG_AfficherPRINT(x4);
//             PORTB Afficher= Eteint;
//             if(ifpAfficherressed() == true){statePres = state5;}
//             break;

//             case state5 :
//             DEBUG_PRINT(x5);
//             while(ifpressed() ==  true){PORTB = Vert;}
//             statePres = state0;
//             break;
//         }
//     }      
// }

int main(){

    //pb2();
    initialisationUART();

    DDRD = 0xff;
    char * mo = "ok";
    for(;;)
    {
        DEBUG_PRINT(mo);
    }
    
    return 0;
}

