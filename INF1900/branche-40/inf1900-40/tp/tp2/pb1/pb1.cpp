/*
TP2, pb1
Auteurs: Maximiliano Falicoff -2013658
        Philippe Desilets -2020566

Tableaux Detats du  PB1

 CURRENT STATE || INPUT || NEXT STATE || OUTPUT
 -----------------------------------------------
      INIT     ||   0    ||    INIT    || ETEINT
      INIT     ||   1    ||     S0     || ETEINT
       S0      ||   0    ||     S0     || ETEINT
       S0      ||   1    ||     S1     || ETEINT
       S1      ||   0    ||     S1     || ETEINT
       S1      ||   1    ||     S2     || ETEINT
       S2      ||   0    ||     S2     || ETEINT
       S2      ||   1    ||     S3     || ETEINT
       S3      ||   0    ||     S3     || ETEINT
       S3      ||   1    ||     S4     || ETEINT
       S4      ||   0    ||     S4     || ETEINT
       S4      ||   1    ||    INIT    || ROUGE

 */







#include <avr/io.h>
#define F_CPU 8000000UL
#include <util/delay.h>

const int Rouge = 0x02;
const int Vert = 0x01;
const int Eteint = 0x00;
const int MODE_SORTIE = 0Xff;
const int MODE_ENTRE = 0x00;
const int PIN_SORTIE = 0x04;

void pb1(){
    enum state{state0, state1, state2, state3, state4, state5};
     DDRD = MODE_ENTRE;
     DDRB = MODE_SORTIE;
     state statePres = state1;
     int temp=0;
    for(;;)
    {
        if(PIND & PIN_SORTIE)
        {
            _delay_ms(10);
            if(PIND & PIN_SORTIE && temp==0)
            {
                temp+=1;        
                switch(statePres) 
                {
                    case state1 : statePres = state2; 
                    break;
                    case state2 : statePres = state3; 
                    break;
                    case state3 : statePres = state4; 
                    break;
                    case state4 : statePres = state5; 
                    break;
                    case state5 : 
                    statePres = state1; 
                    PORTB = Vert;
                    _delay_ms(1000);
                    PORTB = Eteint;
                    break;
                }
            }      

        }
        else{temp =0;}
    }
}

int main()
{
    pb1();
    return 0;
}