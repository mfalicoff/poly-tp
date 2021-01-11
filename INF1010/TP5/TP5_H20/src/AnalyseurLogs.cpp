/// Classe AnalyseurLogs
/// \author Misha Krieger-Raynauld
/// \date 2020-01-12
/// \modifié Maximiliano Falicoff: 2013658
/// \modifié Bryan junior Ngatshou : 1956611
/// \date 2020-04-16

#include "AnalyseurLogs.h"
#include <algorithm>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <unordered_set>
#include "Foncteurs.h"

/// Ajoute les lignes de log en ordre chronologique à partir d'un fichier de logs.
/// \param nomFichier               Le fichier à partir duquel lire les logs.
/// \param gestionnaireUtilisateurs Référence au gestionnaire des utilisateurs pour lier un utilisateur à un log.
/// \param gestionnaireFilms        Référence au gestionnaire des films pour pour lier un film à un log.
/// \return                         True si tout le chargement s'est effectué avec succès, false sinon.
bool AnalyseurLogs::chargerDepuisFichier(const std::string& nomFichier,
    GestionnaireUtilisateurs& gestionnaireUtilisateurs,
    GestionnaireFilms& gestionnaireFilms)
{
    std::ifstream fichier(nomFichier);
    if (fichier)
    {
        logs_.clear();
        vuesFilms_.clear();

        bool succesParsing = true;

        std::string ligne;
        while (std::getline(fichier, ligne))
        {
            std::istringstream stream(ligne);

            std::string timestamp;
            std::string idUtilisateur;
            std::string nomFilm;

            if (stream >> timestamp >> idUtilisateur >> std::quoted(nomFilm))
            {
                // TODO: Uncomment une fois que la fonction creerLigneLog est écrite
                creerLigneLog(timestamp, idUtilisateur, nomFilm, gestionnaireUtilisateurs, gestionnaireFilms);
            }
            else
            {
                std::cerr << "Erreur AnalyseurLogs: la ligne " << ligne
                    << " n'a pas pu être interprétée correctement\n";
                succesParsing = false;
            }
        }
        return succesParsing;
    }
    std::cerr << "Erreur AnalyseurLogs: le fichier " << nomFichier << " n'a pas pu être ouvert\n";
    return false;
}

/**
 * @brief Cree une nouvelle ligne log
 *
 * @param timestamp
 * @param idUtilisateur
 * @param nomFilm
 * @param gestionnaireUtilisateurs
 * @param gestionnaireFilms
 * @return true
 * @return false
 */
bool AnalyseurLogs::creerLigneLog(const std::string& timestamp, const std::string& idUtilisateur, const std::string& nomFilm,
    GestionnaireUtilisateurs& gestionnaireUtilisateurs, GestionnaireFilms& gestionnaireFilms)
{
    LigneLog lignelog;
    lignelog.film = gestionnaireFilms.getFilmParNom(nomFilm);
    lignelog.timestamp = timestamp;
    lignelog.utilisateur = gestionnaireUtilisateurs.getUtilisateurParId(idUtilisateur);
    ajouterLigneLog(lignelog);
    return (lignelog.film != nullptr && lignelog.utilisateur != nullptr);

}

/**
 * @brief ajoute une ligne de log au parametre logs_
 *
 * @param ligneLog
 */
void AnalyseurLogs::ajouterLigneLog(const LigneLog& ligneLog)
{

    logs_.size() == 0 ? vuesFilms_.clear() : logs_.resize(logs_.size()); //au cas ou ou logs_ contient 0 elem
    logs_.insert(std::upper_bound(logs_.begin(), logs_.end(), ligneLog, [&](const LigneLog& ligneLog, const LigneLog& ligne)
        {
            ComparateurLog comp;
            return comp.operator()(ligneLog, ligne);
        }), ligneLog);
    vuesFilms_.find(ligneLog.film) != vuesFilms_.end() ? vuesFilms_.find(ligneLog.film)->second++ : vuesFilms_.emplace(ligneLog.film, 0).first->second++;


}

/**
 * @brief permet de savoir le nombre de vues qu'a un film associe dans son map
 *
 * @param film
 * @return int retourne le nombre de vues que le film possede
 */
int AnalyseurLogs::getNombreVuesFilm(const Film* film) const
{
    if (vuesFilms_.find(film) != vuesFilms_.end() && film != nullptr)
        return vuesFilms_.find(film)->second;
    return 0;
}

/**
 * @brief Permet de savoir le film le plus populaire dans le systeme
 *
 * @return const Film*
 */
const Film* AnalyseurLogs::getFilmPlusPopulaire() const
{
    ComparateurSecondElementPaire<const Film*, int> comparateur;
    return (vuesFilms_.empty()) ? nullptr :
        std::max_element(vuesFilms_.begin(), vuesFilms_.end(), [&](const std::pair<const Film*, int>& pair1, const std::pair<const Film*, int>& pair2)
            {
                return comparateur.operator()(pair1, pair2);
            })->first;
}

/**
 * @brief Permet d'avoir une liste des films les plus populaire
 *
 * @param nombre de films que l'on veut recevoir
 * @return std::vector<std::pair<const Film*, int>> la liste des films
 */
std::vector<std::pair<const Film*, int>> AnalyseurLogs::getNFilmsPlusPopulaires(std::size_t nombre) const
{


    std::vector<std::pair<const Film*, int>> retourVector;
    retourVector.resize(vuesFilms_.size());

    std::copy(vuesFilms_.begin(), vuesFilms_.end(), retourVector.begin());

    std::sort(retourVector.begin(), retourVector.end(), [&](const std::pair<const Film*, int>& pair1, const std::pair<const Film*, int>& pair2)
        {  ComparateurSecondElementPaire<const Film*, int> comparateurFilms;
    return comparateurFilms.operator()(pair2, pair1);
        });

    if (nombre < vuesFilms_.size()) retourVector.resize(nombre);
    return retourVector;
}

/**
 * @brief Permet d'avoir le nombre de vues d'un utilisateur
 *
 * @param utilisateur
 * @return int le nombre de vues
 */
int AnalyseurLogs::getNombreVuesPourUtilisateur(const Utilisateur* utilisateur) const
{
    return (int)std::count_if(logs_.begin(), logs_.end(), [utilisateur](const LigneLog& ligneLog)
        {
            return ligneLog.utilisateur == utilisateur;
        });
}

/**
 * @brief Permet d'avoir le film le vues visualisee par l'utilisateur
 *
 * @param utilisateur
 * @return std::vector<const Film*>
 */
std::vector<const Film*> AnalyseurLogs::getFilmsVusParUtilisateur(const Utilisateur* utilisateur) const
{

    std::vector<const Film*> vecteurRetour;
    std::vector<LigneLog> ligneLog;

    std::copy_if(logs_.begin(), logs_.end(), back_inserter(ligneLog), [utilisateur](const LigneLog& ligne)
        {
            return ligne.utilisateur == utilisateur; //copie toutes les ligne de l'utilisateur voulue
        });
    std::for_each(ligneLog.begin(), ligneLog.end(), [ligneLog, &vecteurRetour](const LigneLog& ligne)
        {
            vecteurRetour.push_back(ligne.film); //mets touts ces films dans le vecteur
        });

    std::sort(vecteurRetour.begin(), vecteurRetour.end());
    vecteurRetour.erase(std::unique(vecteurRetour.begin(), vecteurRetour.end()), vecteurRetour.end());
    return vecteurRetour;
}

