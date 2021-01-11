/// Fonction main.
/// \author Misha Krieger-Raynauld
/// \date 2020-01-12
/// \modifié Maximiliano Falicoff: 2013658
/// \modifié Bryan junior Ngatshou : 1956611
/// \date 2020-04-16

#include <iostream>
#include "AnalyseurLogs.h"
#include "GestionnaireFilms.h"
#include "GestionnaireUtilisateurs.h"
#include "Tests.h"
#include "WindowsUnicodeConsole.h"
#include "debogageMemoire.h"

int main()
{
    // Change le code page de la console Windows en UTF-8 si l'OS est Windows
    initializeConsole();

    Tests::testAll();

    // Écrivez le code pour le bonus ici
        
    initDebogageMemoire();      // comme dans les precedants tps, nous avons ajouté un debogeurMemoire
    GestionnaireUtilisateurs gestionnaireUtilisateurs;
    gestionnaireUtilisateurs.chargerDepuisFichier("utilisateurs.txt");
    std::cout << gestionnaireUtilisateurs;

    GestionnaireFilms gestionnaireFilms;  
    gestionnaireFilms.chargerDepuisFichier("films.txt");

    auto filmsAvan = gestionnaireFilms.getFilmsParGenre(Film::Genre::Aventure);
    std::cout << "\nFilms D'aventure:\n"; // affichage des films d aventure
    for (auto const& film : filmsAvan)
    {
        std::cout << '\t' << *film << std::endl;
    }

    std::cout << "\nFilms produits de 1960 à 1961:\n"; // affichage des films produits entre 60 et 61
    auto filmsDecenie = gestionnaireFilms.getFilmsEntreAnnees(1960, 1961);
    for (auto const& film : filmsDecenie)
    {
        std::cout << '\t' << *film << std::endl;
    }

    AnalyseurLogs analyseurLog;
    analyseurLog.chargerDepuisFichier("logs.txt", gestionnaireUtilisateurs, gestionnaireFilms);

    auto filmPop = analyseurLog.getFilmPlusPopulaire(); // affchage du film le plus populaire
    std::cout << "\nFilm le plus populaire (" << analyseurLog.getNombreVuesFilm(filmPop) << " vues): " << *filmPop << std::endl;

    auto films5Pop = analyseurLog.getNFilmsPlusPopulaires(5);
    std::cout << "\n5 films les plus populaires:\n";
    for (auto const& film : films5Pop)    //  affichage des 5 films les plus populaires et de leur nombre de vues
    {
        std::cout << '\t' << *film.first << " (" << film.second << " vues)" << std::endl;
    }

    auto utilisateur = gestionnaireUtilisateurs.getUtilisateurParId("karasik@msn.com");
    auto vuesUtil = analyseurLog.getNombreVuesPourUtilisateur(utilisateur); // affichage du nombre de films vues par karasik
    std::cout << "\nNombre de films vus par l'utilisateur " << utilisateur->id << ": " << vuesUtil << std::endl;;

    std::cout << "\n \n \n ~~~~~travail fait par maximiliano et bryan / tp5~~~~~ \n \n \n" << std::endl;
}
