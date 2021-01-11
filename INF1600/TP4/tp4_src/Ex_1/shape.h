#ifndef SHAPE_H
#define SHAPE_H

//# define M_PI          3.141592653589793238462643383279502884L /* pi */

#include <string>

/*
 * Base class for shapes.
 */
class CShape {

public:

   /* Class destructor */
   ~CShape() {}

   /* Calculates the perimeter of the shape */
   virtual float PerimeterCpp() const = 0;

   /* Calculates the perimeter of the shape */
   virtual float PerimeterAsm() const = 0;

   /* Calculates the area of the surface */
   virtual float AreaCpp() const = 0;

   /* Calculates the area of the surface */
   virtual float AreaAsm() const = 0;

   virtual std::string Name() const = 0;

};

#endif
