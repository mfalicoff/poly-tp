/*
Projet final 4081 LCD.cpp
Auteurs: Maximiliano Falicoff -2013658
        Philippe Desilets -2020566
		Guillaume Nadeau
		Alexis Thibeault

Permet d'afficher les distances sur l'ecran lcd
*/

#include "LCD.h"


/**
 * @brief  Afficher la distance et si cela poserai un probleme
 * 
 * @param dist1 
 * @param dist2 
 * @param dist3 
 */
void afficherDistances(double dist1, double dist2, double dist3)
{
    

    LCM disp(&DDR, &PORT);

    int dist1Av = (int) dist1;
    int dist1Ap = (dist1*10);
    dist1Ap = dist1Ap %10;

    int dist2Av = (int) dist2;
    int dist2Ap = (dist2*10);
    dist2Ap = dist2Ap %10;

    int dist3Av = (int) dist3;
    int dist3Ap = (dist3*10);
    dist3Ap = dist3Ap %10;

    const char *string1,*string2,*string3;
    if(dist1 < 1)
        string1 = "DNGR";
    else if(dist1 >= 1 && dist1 <= 3)
        string1 = "ATTN";
    else
        string1 = " OK ";

    if(dist2 < 1)
        string2 = "DNGR";
    else if(dist2 >= 1 && dist2 <= 3)
        string2 = "ATTN";
    else
        string2 = " OK ";

    if(dist3 < 1)
        string3 = "DNGR";
    else if(dist3 >= 1 && dist3 <= 3)
        string3 = "ATTN";
    else
        string3 = " OK ";

    disp << dist1Av << '.' << dist1Ap << 'm' << "  " <<
         dist2Av << '.' << dist2Ap << 'm' <<  "  " <<
          dist3Av << '.' << dist3Ap << 'm';
    disp << string1 << "  " << string2 << "  " << string3;

}

/**
 * @brief affiche la manouevre a l'ecran LCD
 * On a six manoeuvres, si la comb n'existe pas, envoyer manooevre = 0
 * @param manoeuvre 
 */
void afficherManouevre(int manoeuvre)
{
    
    
    LCM disp(&DDR, &PORT);
    disp.clear();

    if (manoeuvre == 0)
    {
        disp << "Combinaison ";
        disp.write("non evaluee", 16, 0);
    }else
    {
        disp << "Manoeuvre " << manoeuvre;
    }
    

    
}

/**
 * @brief fait juste clear l'ecran LCD
 * 
 */
void clearDispl()
{
    LCM disp(&DDR, &PORT);
    disp.clear();
}
