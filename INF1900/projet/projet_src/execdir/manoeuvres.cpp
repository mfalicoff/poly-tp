/*
Projet final 4081 manouevres.cpp
Auteurs: Maximiliano Falicoff -2013658
        Philippe Desilets -2020566
		Guillaume Nadeau
		Alexis Thibeault

Implmentation des differentes manouevres decrite dans les consignes
*/

#include "manoeuvres.h"

bool bouttonPoussoir = false;

/**
 * @brief Mode detection du robot, recoie les distances envoye par les trois sonars
 * et attend que le boutton poussoir soit appuye et 
 * se lance dans une manoeuvre
 * 
 * @return uint8_t Correspond a la manoeuvre que l'on va executer
 */
uint8_t detection()
{
    DDRB = MODE_SORTIE;
	DDRD = 0b11000111;
    DDRA = MODE_ENTREE;
    PORTD = 0x00;
    PORTA =0x00;

    Distances distances;
    uint8_t choix = 0;
    while(!bouttonPoussoir)
    {
       
        distances = sonar();
        _delay_ms(250);
        bouttonPoussoir = ifpressed();
        choix = choixManoeuvre(distances);
    }
    return choix;
    
}

/**
 * @brief Set les ports pour les manoeuvres
 * 
 */
void initMan()
{
    DDRA = MODE_SORTIE;
    DDRC = MODE_SORTIE;
	DDRD = 0b11110111; //le port du boutton poussoir est en input
}

void man1()
{
    initMan();

	afficherManouevre(1);
	ajustementPWM(90, 90);

	for (int i = 90; i > 51; i--) //c'est la valeur qu'affiche l'ecran
	{
		ajustementPWM(i, 90);
		affichage7FPS(i,90, 100);
	}

	ajustementPWM(52,90);		
	affichage7FPS(52,90, 1000);

	for (int i = 52; i <= 90; i++) //c'est la valeur qu'affiche l'ecran
	{
		ajustementPWM(i, 90);
		affichage7FPS(i,90,100);
	}

	affichage7FPS(90,90, 2000);
	finMan();
}

void man2()
{
    initMan();

    afficherManouevre(2);
	ajustementPWM(90, 90);

	for (int i = 90; i > 51; i--) //c'est la valeur qu'affiche l'ecran
	{
		ajustementPWM(90, i);
		affichage7FPS(90,i, 100);
	}

	ajustementPWM(90,52);		
	affichage7FPS(90,52, 1000);

	for (int i = 52; i <= 90; i++) //c'est la valeur qu'affiche l'ecran
	{
		ajustementPWM(90, i);
		affichage7FPS(90,i,100);
	}

	affichage7FPS(90,90, 2000);

    finMan();
}

void man3()
{
    initMan();

    afficherManouevre(3);

    ajustementPWM(-50,50);
    affichage7FPS(50,50,1000);

    ajustementPWM(66,66);
    affichage7FPS(66,66,2000);

    ajustementPWM(50,-50);
    affichage7FPS(50,50,1000);

    ajustementPWM(78,78);
    affichage7FPS(78,78,2000);

    finMan();
}

void man4()
{
    initMan();
    afficherManouevre(4);

    ajustementPWM(50,-50);
    affichage7FPS(50,50,1000);

    ajustementPWM(66,66);
    affichage7FPS(66,66,2000);

    ajustementPWM(-50,50);
    affichage7FPS(50,50,1000);

    ajustementPWM(78,78);
    affichage7FPS(78,78,2000);

    finMan();

}



void man5()
{
    initMan();
	afficherManouevre(5);

    ajustementPWM(50,-50);
    affichage7FPS(50,50,2000);
    
    for (int i = 0; i <= 63; i++)
    {   
        ajustementPWM(i,i);
        affichage7FPS(i,i,125);
        i = i+2;
    }

    affichage7FPS(63,63,2000);
	finMan();
    
}



void man6()
{
	initMan();
    afficherManouevre(6);
	ajustementPWM(90, 90);

	for (int i = 90; i >= 41; i--)
	{
		ajustementPWM(i, i);
		affichage7FPS(i, i, 71);
	}

	affichage7FPS(41,41,2000);
	finMan();
}

void manIconnue()
{
    initMan();
	afficherManouevre(0);
    _delay_ms(2000);
    finMan();
    
}

void finMan()
{
    stopPWM();
	clear7Seg(); 
	clearDispl();
    bouttonPoussoir = false;
}

uint8_t choixManoeuvre(Distances distances)
{
   

    if(distances.distanceSonar1 >= 30 && distances.distanceSonar2 >= 30 && (distances.distanceSonar3 >= 10 && distances.distanceSonar3 < 30) )
        return 1;
    else if(distances.distanceSonar3 >= 30 && distances.distanceSonar2 >= 30 && (distances.distanceSonar1 >= 10 && distances.distanceSonar1 < 30) )
        return 2;
    else if(distances.distanceSonar1 >= 30 && distances.distanceSonar2 < 10 && (distances.distanceSonar3 < 10 ))
        return 3;
    else if(distances.distanceSonar1 < 10 && distances.distanceSonar2 <10 && distances.distanceSonar3 >= 30 )
        return 4;
    else if(distances.distanceSonar1 < 10 && distances.distanceSonar3 < 10 && distances.distanceSonar3 < 10 )
        return 5;
    else if((distances.distanceSonar1 >= 10 && distances.distanceSonar1 < 30) && distances.distanceSonar2 >= 30 && (distances.distanceSonar3 >= 10 && distances.distanceSonar3 < 30) )
        return 6;
    else
    {
        return 0;
    }
    
}