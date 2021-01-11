/// les trois foncteurs pour le programme
/// \author Maximiliano Falicoff: 2013658
/// \author Bryan junior Ngatshou : 1956611 
/// \date 2020-04-16

#ifndef FONCT_H
#define FONCT_H



#include <fstream>
#include <iostream>
#include <memory>
#include <sstream>
#include <vector>
#include "LigneLog.h"


class EstDansIntervalleDatesFilm
{

public:

	/**
	 * @brief Construct a new Est Dans Intervalle Dates Film object
	 *
	 * @param inf
	 * @param sup
	 */
	EstDansIntervalleDatesFilm(int inf, int sup)
		: inf_(inf),
		sup_(sup)
	{
	}

	/**
	 * @brief permet de savoir si un film est entre deux dates
	 *
	 * @param film
	 * @return true  ou
	 * @return false
	 */
	bool operator()(const std::unique_ptr<Film>& film)
	{
		return (film->annee >= inf_ && film->annee <= sup_);
	}

private:
	int inf_;
	int sup_;
};


class ComparateurLog
{

public:

	/**
	 * @brief surcharge de l'oepratur () pour la classe comparateur log
	 * 			qui permet de comparer la dates de deux logs avec le format
	 * 			des timesamps
	 * @param ligne1
	 * @param ligne2
	 * @return true
	 * @return false
	 */
	bool operator()(const LigneLog& ligne1, const LigneLog& ligne2)
	{
		return (ligne1.timestamp < ligne2.timestamp);
	}

};

template <typename T1, typename T2>
class ComparateurSecondElementPaire
{

public:

	/**
	 * @brief Permet de compararer les deuxiemmes element de deux paires
	 *
	 * @param pair1
	 * @param pair2
	 * @return true
	 * @return false
	 */
	bool operator()(const std::pair<T1, T2>& pair1, const std::pair<T1, T2>& pair2)
	{
		return(pair1.second < pair2.second);
	}


};



#endif // FONCT_H
