/*
 * Titre : PivoterMatrice.h - Travail Pratique #4 - Programmation Orient�e Objet
 * Date : 27 F�vrier 2020
 * Auteur : Nabil Dabouz
 */

#ifndef PIVOTER_MATRICE_H
#define PIVOTER_MATRICE_H

#include "def.h"

template <class M> class PivoterMatrice {
public:
  // Constructeurs
  PivoterMatrice();
  PivoterMatrice(M *matrice);
  // Destructeur
  ~PivoterMatrice() = default;
  void pivoterMatrice(Direction direction);

private:
  Coordonnees changerCoordonneesCentreMatrice(Coordonnees coords) const;
  Coordonnees recupererCoordonnees(Coordonnees coords) const;
  M *matrice_;
};

/**
 * @brief constructeur par défaut de la classe
 */
template <class M> inline PivoterMatrice<M>::PivoterMatrice() {
  // TO DO
}
/**
 * @brief constructeur par paramètre de la classe
 */
template <class M>
inline PivoterMatrice<M>::PivoterMatrice(M *matrice) : matrice_(matrice) {}
/**
 * @brief trouver les coordonnées du point par rapport au centre de la matrice
 * @param coords les coordonnées du point originales
 */
template <class M>
inline Coordonnees
PivoterMatrice<M>::changerCoordonneesCentreMatrice(Coordonnees coords) const {
  
	auto decal = (matrice_->getWidth()-1)/2;
	Coordonnees coor;
	coor.y = coords.y - decal;
	coor.x = coords.x - decal;


  return {coor};
}
/**
 * @brief revenir au système précédent, trouver les coordonnées du point par
 * rapport au premier élément de la matrice
 * @param coords les coordonnées du point originales
 */
template <class M>
inline Coordonnees
PivoterMatrice<M>::recupererCoordonnees(Coordonnees coords) const {

	auto decal = (matrice_->getWidth() - 1) / 2;
	Coordonnees coor;
	coor.y = coords.y + decal;
	coor.x = coords.x + decal;


	return { coor };
 }

template <class M> inline void PivoterMatrice<M>::pivoterMatrice(Direction direction)
{
	std::unique_ptr<M> matriceCopie = matrice_->clone();
	
	for (size_t j = 0; j < matrice_->getWidth(); j++)
	{
		for (size_t i = 0; i < matrice_->getHeight(); i++)
		{
			Coordonnees boucle;
			boucle.x = j; boucle.y = i;
			auto coor = changerCoordonneesCentreMatrice(boucle);
			if(direction == Direction::Right)
			{
				auto temp = coor.x;
				coor.x = coor.y *-1;
				coor.y = temp;
			}
			else if(direction == Direction::Left)
			{
				auto temp = coor.x;
				coor.x = coor.y;
				coor.y = temp * -1;
			}

			auto nv = recupererCoordonnees(coor);
			matrice_->ajouterElement(matriceCopie->operator()(i, j), nv.y, nv.x);

		}
	}





}


#endif
