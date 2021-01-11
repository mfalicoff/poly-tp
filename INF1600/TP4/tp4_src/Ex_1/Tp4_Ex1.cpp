#include <iostream>
#include <cmath>
#include <cstdlib>
#include <sstream>
#include <iomanip>

#include "Rectangle.h"
#include "Cylinder.h"

/****************************************/
/****************************************/

/*
 * Constant used to test float equality.
 */
static const float EPSILON = 1e-4;

/*
 * Returns true if the given values are close enough.
 * Not the best possible float comparison ever, but it's
 * enough for this TP.
 */
bool Equals(float a, float b) {
   /* Take care of obvious case */
   if(a == b) return true;
   /* Take care of approximations */
   if(std::fabs(a-b) < EPSILON) return true;
   /* If we get here, the numbers are most probably not equal */
   return false;
}

/****************************************/
/****************************************/

float StringToFloat(const char* str) {
   float f;
   std::istringstream iss(str);
   iss >> f;
   return f;
}

/****************************************/
/****************************************/

void TestShape(CShape& s) {
   /* Calculate perimeter and area using C++ methods */
   float perimetercpp = s.PerimeterCpp();
   float areacpp = s.AreaCpp();
   /* Calculate perimeter and area using assembler methods */
   float perimeterasm = s.PerimeterAsm();
   float areaasm = s.AreaAsm();
   /* Print and test calculated values */
   std::cout << s.Name() << " perimeter:" << std::endl
             << "\tC++ -> " << std::fixed << std::setprecision(2) << perimetercpp << std::endl
             << "\tASM -> " << std::fixed << std::setprecision(2) << perimeterasm << std::endl;
   if(!Equals(perimetercpp, perimeterasm))
      std::cerr << "ERROR: the perimeters do not match" << std::endl;
   else
      std::cout << "\tThe perimeters match" << std::endl << std::endl;
   std::cout << s.Name() << " area:" << std::endl
             << "\tC++ -> " << std::fixed << std::setprecision(2) << areacpp << std::endl
             << "\tASM -> " << std::fixed << std::setprecision(2) << areaasm << std::endl;
   if(!Equals(areacpp, areaasm))
      std::cerr << "ERROR: the areas do not match" << std::endl;
   else
      std::cout << "\tThe areas match" << std::endl << std::endl;
}

/****************************************/
/****************************************/

void TestRectangle(float longeur, float largeur) {

   Rectangle r(longeur, largeur);
   TestShape(r);

   /* Calculate diagonal using C++ and assembler methods */
    float diagonalcpp = r.DiagonalCpp();
    float diagonalasm = r.DiagonalAsm();

    /* Print and test calculated values */
    std::cout << r.Name() << " diagonal:" << std::endl
        << "\tC++ -> " << std::fixed << std::setprecision(2) << diagonalcpp << std::endl
        << "\tASM -> " << std::fixed << std::setprecision(2) << diagonalasm << std::endl;

    if (!Equals(diagonalcpp, diagonalasm))
        std::cerr << "ERROR: the diagonals do not match" << std::endl;
    else
        std::cout << "\tThe diagonals match" << std::endl << std::endl;
}

/****************************************/
/****************************************/

void TestCylinder(float rayon, float hauteur) {

    Cylinder c(rayon, hauteur);
    TestShape(c);

    /* Calculate volume using C++ and assembler methods */
    float volumecpp = c.VolumeCpp();
    float volumeasm = c.VolumeAsm();

    /* Print and test calculated values */
    std::cout << c.Name() << " volume:" << std::endl
        << "\tC++ -> " << std::fixed << std::setprecision(2) << volumecpp << std::endl
        << "\tASM -> " << std::fixed << std::setprecision(2) << volumeasm << std::endl;

    if (!Equals(volumecpp, volumeasm))
        std::cerr << "ERROR: the volumes do not match" << std::endl;
    else
        std::cout << "\tThe volumes match" << std::endl << std::endl;
}

/****************************************/
/****************************************/

int main() {
   TestRectangle(2, 3);
   TestCylinder(2, 3);
   return 0;
}

