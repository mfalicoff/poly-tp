/*
Projet final 4081
Auteurs: Maximiliano Falicoff -2013658
        Philippe Desilets -2020566
		Guillaume Nadeau
		Alexis Thibeault

Le Projet consiste d'un robot qui detecte des obstacles avec un sonar
et reagit aux distances de trois obstacles detectees par les sonars.

Tableaux Detats du robot

 CURRENT STATE   || ENTREE || NEXT STATE 
 -----------------------------------------------
      Detection  ||   0    ||    Detection
      Detection  ||   1    ||    ManoeuvreX
      ManoeuvreX ||   X    ||    Detection 


Identification Materielle

	Sonar: PORTA et PORTB
	LCD: PORTB
	Roues: PORTD
	Boutton poussoir PORTD
	7 segment display: PORTC et PORTA
 */



#include "manoeuvres.h"

int main(void)
{
	enum State
	{
		detect, 
		maneouvre1, 
		maneouvre2, 
		maneouvre3, 
		maneouvre4, 
		maneouvre5, 
		maneouvre6, 
		maneouvreInconnue
	};


	State statePres = detect;
	uint8_t man;
	while (1)
	{
		switch (statePres)
		{

		case detect:
		{
			man = detection();
			if(man == 1)
			{
				statePres = maneouvre1;
				break;
			}
			else if(man == 2)
			{
				statePres = maneouvre2;
				break;
			}
			else if(man == 3)
			{
				statePres = maneouvre3;
				break;
			}
			else if(man == 4)
			{
				statePres = maneouvre4;
				break;
			}
			else if(man == 5)
			{
				statePres = maneouvre5;
				break;
			}
			else if(man == 6)
			{
				statePres = maneouvre6;
				break;
			}
			else
			{
				statePres = maneouvreInconnue;
				break;
			}
			
			break;
		}
			
		case maneouvre1:
		{
			man1();
			statePres = detect;
			break;
		}

		case maneouvre2:
		{
			man2();
			statePres = detect;
			break;
		}

		case maneouvre3:
		{
			man3();
			statePres = detect;
			break;
		}

		case maneouvre4:
		{
			man4();
			statePres = detect;
			break;
		}

		case maneouvre5:
		{
			man5();
			statePres = detect;
			break;
		}

		case maneouvre6:
		{
			man6();
			statePres = detect;
			break;
		}

		case maneouvreInconnue:
		{
			manIconnue();
			statePres = detect;
			break;
		}

		}
	}
	
	
 
}
		
		
		
		
		
		



				
				
				
		
		


	




 
