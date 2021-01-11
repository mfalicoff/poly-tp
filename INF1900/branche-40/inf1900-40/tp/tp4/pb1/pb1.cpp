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



#include <avr/interrupt.h>
#include <avr/io.h>
#define F_CPU 8000000UL
#include <util/delay.h>

const int Rouge = 0x01;
const int Vert = 0x02;
const int Eteint = 0x00;
const int MODE_SORTIE = 0Xff;
const int MODE_ENTRE = 0x00;
const int PIN_SORTIE = 0x04;

enum State {state0, state1, state2, state3, state4, state5, state6}; //Les 7 etat sont definis
volatile State statePres = state0;
volatile bool bouttonIsPressed = false;

void ifpressed()
{

    
        if(PIND & PIN_SORTIE)
        _delay_ms(30);
            if(PIND & PIN_SORTIE)
            {
                 bouttonIsPressed=true;
            }
           
        else{
            bouttonIsPressed = false;
        }

    

}

void pb2()
{
    
  
        switch(statePres) 
        {
            case state0:
            PORTB = Rouge;
            if(bouttonIsPressed == true){statePres = state1;}
            break;

            case state1 : 
            while(bouttonIsPressed == true)
            {
                PORTB = Vert;
                _delay_ms(5);
                 PORTB = Rouge;
                 _delay_ms(5);
                 bouttonIsPressed;
            }
            statePres = state2;  
            break;
                     
            case state2 : 
            PORTB = Vert;
            if(bouttonIsPressed == true) {statePres = state3;}
            break;

            case state3 : 
            while(bouttonIsPressed == true){PORTB = Rouge;}
            statePres = state4;
            break;

            case state4 :
            PORTB = Eteint;
            if(bouttonIsPressed == true){statePres = state5;}
            break;

            case state5 :
            while(bouttonIsPressed ==  true){PORTB = Vert;}
            statePres = state0;
            break;
        
    }      
}
// placer le bon type de signal d'interruption

// à prendre en charge en argument

ISR ( INT0_vect ) 
{

// laisser un delai avant de confirmer la réponse du

// bouton-poussoir: environ 30 ms (anti-rebond)


// se souvenir ici si le bouton est pressé ou relâché

ifpressed();
// changements d'états tels que ceux de la

// semaine précédente


pb2();

// Voir la note plus bas pour comprendre cette instruction et son rôle

EIFR |= (1 << INTF0) ;

}

void initialisation ( void ) {

// cli est une routine qui bloque toutes les interruptions.

// Il serait bien mauvais d'être interrompu alors que

// le microcontroleur n'est pas prêt...

cli ();


// configurer et choisir les ports pour les entrées

// et les sorties. DDRx... Initialisez bien vos variables


     DDRD = MODE_ENTRE;
     DDRB = MODE_SORTIE;


// cette procédure ajuste le registre EIMSK

// de l’ATmega324PA pour permettre les interruptions externes

EIMSK |= (1 << INT0) ;


// il faut sensibiliser les interruptions externes aux

// changements de niveau du bouton-poussoir

// en ajustant le registre EICRA

EICRA |= (1 << ISC00) ;


// sei permet de recevoir à nouveau des interruptions.

sei ();

}







int main(){
    DDRD = 0xF0;
    initialisation();
    for(;;){
        pb2();
    }
    return 0;
}