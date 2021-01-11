/*
TP2, pb2
Auteurs: Maximiliano Falicoff -2013658
        Philippe Desilets -2020566

Tableaux Detats du  PB2

 CURRENT STATE || ENTREE || NEXT STATE || SORTIE
 -----------------------------------------------
      INIT     ||   0    ||    INIT    || ROUGE
      INIT     ||   1    ||     S1     || ROUGE
       S1      ||   0    ||     S2     || AMBRE
       S1      ||   1    ||     S1     || AMBRE
       S2      ||   0    ||     S2     || VERT
       S2      ||   1    ||     S3     || VERT
       S3      ||   0    ||     S4     || ROUGE
       S3      ||   1    ||     S3     || ROUGE
       S4      ||   0    ||     S4     || ETEINT
       S4      ||   1    ||     S5     || ÉTEINT
       S5      ||   0    ||     S6     || VERT
       S5      ||   1    ||     S5     || VERT
       S6      ||   0    ||    INIT    || ROUGE
       S6      ||   1    ||    INIT    || ROUGE
 */



#include <avr/io.h>
#define F_CPU 8000000UL
#include <util/delay.h>

const int Rouge = 0x01;
const int Vert = 0x02;
const int Eteint = 0x00;
const int MODE_SORTIE = 0Xff;
const int MODE_ENTRE = 0x00;
const int PIN_SORTIE = 0x04;

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

void pb2()
{
    enum state{state0, state1, state2, state3, state4, state5};
     DDRD = MODE_ENTRE;
     DDRB = MODE_SORTIE;
  
     state statePres = state0;
  
    for(;;)
    {
        switch(statePres) 
        {
            case state0:
            PORTB = Rouge;
            if(ifpressed() == true){statePres = state1;}
            break;

            case state1 : 
            while(ifpressed() == true)
            {
                PORTB = Vert;
                _delay_ms(5);
                 PORTB = Rouge;
                 _delay_ms(5);
                 ifpressed();
            }
            statePres = state2;  
            break;
                     
            case state2 : 
            PORTB = Vert;
            if(ifpressed() == true) {statePres = state3;}
            break;

            case state3 : 
            while(ifpressed() == true){PORTB = Rouge;}
            statePres = state4;
            break;

            case state4 :
            PORTB = Eteint;
            if(ifpressed() == true){statePres = state5;}
            break;

            case state5 :
            while(ifpressed() ==  true){PORTB = Vert;}
            statePres = state0;
            break;
        }
    }      
}

int main(){
    pb2();

    return 0;
}