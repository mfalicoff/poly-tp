#ifndef RECTANGLE_H
#define RECTANGLE_H

#include "shape.h"

/*
 * The rectangle class inherits from CShape.
 */
class Rectangle : public CShape {

public:

   /* Class constructor */
   Rectangle(float length, float width);

   /* Class destructor */
   ~Rectangle();

   /* Calculates the perimeter of the rectangle */
   virtual float PerimeterCpp() const;
   virtual float PerimeterAsm() const;

   /* Calculates the area of the rectangle */
   virtual float AreaCpp() const;
   virtual float AreaAsm() const;
  
   /* Calculates the diagonal of the rectangle */
   virtual float DiagonalCpp() const;
   virtual float DiagonalAsm() const;

   virtual std::string Name() const;

private:
   float length_;
   float width_;
};

#endif