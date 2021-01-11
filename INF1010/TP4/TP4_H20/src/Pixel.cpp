/* ////////////////////////////////////////////////////////////////
/	TP4 : fichier Pixel.cpp                                       /
/	travail fait par Bryan junior Ngatshou : 1956611              /
/					 Maximiliano falicoff  : 2013658              /
/                                                                 /
/	Date de remise : 17  mars 2020 à 23h55                        /
/   Description: Implementation de la classe Pixel                /
*//////////////////////////////////////////////////////////////////


#include "Pixel.h"

/**
 * @brief constructeur par défaut de la classe
 */
Pixel::Pixel() : rouge_(0), vert_(0), bleu_(0) {}
/**
 * @brief constructeur par paramètres de la classe
 * @param rouge, l'élément R du pixel, entre 0 -> 255
 * @param vert, l'élément G du pixel, entre 0 -> 255
 * @param bleu, l'élément B du pixel, entre 0 -> 255
 */
Pixel::Pixel(uint8_t rouge, uint8_t vert, uint8_t bleu)
    : rouge_(rouge), vert_(vert), bleu_(bleu) {}

void Pixel::operator=(const Pixel &pixel) {
  
	rouge_ = pixel.getRouge();
	vert_ = pixel.getVert();
	bleu_ = pixel.getBleu();

}

void Pixel::setRouge(int rouge) {
  
	rouge_ =
		rouge < 0 ? 0 :
		rouge > 255 ? 255 :
		rouge;

	/* nous avons utilise le ternary operator (?) qui est assez fun
	--- si rouge est plus petit que 0, aors rouge_ = 0, sinon alors on verifier si
	rouge est superieur a 255*
	---- si rouge est superieur a 255 , alors rouge_ =  255 sinon on rouge_ est la valuer en parametre*/

}

void Pixel::setVert(int vert) {
	vert_ =
		vert < 0 ? 0 :
		vert > 255 ? 255 :
		vert;
}

void Pixel::setBleu(int bleu) {
	bleu_ =
		bleu < 0 ? 0 :
		bleu > 255 ? 255 :
		bleu;
}

/**
 * @brief retourn l'attribut rouge_ du pixel
 * @return rouge_ du type uint8_t
 */
uint8_t Pixel::getRouge() const { return rouge_; }

/**
 * @brief retourn l'attribut vert_ du pixel
 * @return vert_ du type uint8_t
 */
uint8_t Pixel::getVert() const { return vert_; }

/**
 * @brief retourn l'attribut bleu_ du pixel
 * @return bleu_ du type uint8_t
 */
uint8_t Pixel::getBleu() const { return bleu_; }

/**
 * @brief permet l'affichage des pixels
 * @param os, variable de type ostream
 * @ parametre pixel, le pixel dont la couleur doit etre afficher, de type Pixel
 * @return os du type ostream
 */
std::ostream &operator<<(std::ostream &os, Pixel pixel) {
  
	os << "#";
	os << std::hex << std::uppercase << std::setfill('0') << std::setw(2) << unsigned(pixel.getRouge()) << " " << std::setw(2) << unsigned(pixel.getVert()) << " " << std::setw(2) << unsigned(pixel.getBleu());
	return os;

}

/**
 * @brief permet la lecture des pixels
 * @param is, variable de type istream
 * @ parametre pixel, le pixel dont la couleur doit etre lue, de type Pixel
 * @return is du type istream
 */
std::istream &operator>>(std::istream &is, Pixel &pixel) {
  
	int rouge, vert, bleu;
	is >> rouge >> vert >> bleu;

	pixel.setRouge(rouge); 
	pixel.setBleu(bleu); 
	pixel.setVert(vert); 

	return is;
}