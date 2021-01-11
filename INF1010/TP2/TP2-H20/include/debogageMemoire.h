
#ifndef DEBOGAGEMEMOIRE_H
#define DEBOGAGEMEMOIRE_H

//! Ce fichier permet d'avoir un rapport des fuites de m�moires dans la fen�tre de "sortie" de
//! Visual Studio, lorsque le programme termine son ex�cution en mode d�bogage.  Il n'y a pas
//! actuellement de rapport fait si utilis� avec un autre compilateur (i.e. gcc ou clang), mais ce
//! fichier va tout de m�me compiler et ne rien faire. Il faut appeler "initDebogageMemoire()" au
//! d�but de l'ex�cution du programme (d�but du "main").
//! \note   Ce fichier doit �tre inclus dans
//! chaque fichier source qui utilise "new", pour avoir les num�ros de lignes o� se trouvent les
//! "new" qui n'ont pas de "delete" qui correspond.  Il ne fonctionne pas si vous utilisez le
//! "placement new".
//! \author Francois-R.Boyer@PolyMtl.ca
//! \since  2015-04
#ifdef _MSC_VER
// Pour avoir un rapport de fuites incluant les num�ros de lignes o� l'allocation a �t� faite.
// (source http://msdn.microsoft.com/en-us/library/x98tx3cf%28v=vs.100%29.aspx)
#define _CRTDBG_MAP_ALLOC ///< Utilise les allocations avec d�bogage.
#include <crtdbg.h>
#include <stdlib.h>
#define new \
    new (_NORMAL_BLOCK, __FILE__, __LINE__) ///< Ajoute le num�ro de ligne au rapport de fuites.

inline void initDebogageMemoire()
{
	_CrtSetDbgFlag(
		0 | _CRTDBG_ALLOC_MEM_DF // D�bogage d'allocation m�moire.
		| _CRTDBG_LEAK_CHECK_DF // Rapport de fuites � la sortie du programme.  Noter que le rapport
								// de fuites sera affich� dans la fen�tre "Sortie" de Visual Studio.
		| _CRTDBG_CHECK_ALWAYS_DF // V�rifie la corruption � chaque new/delete (lent).
	);
}
#else
inline void initDebogageMemoire()
{
	// On a actuellement le d�bogage m�moire seulement sur MSVC.
}
#endif

#endif
