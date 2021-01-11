#ifndef CYLINDRE_H
#define CYLINDRE_H

#include "shape.h"

/*
 * The cylindre class inherits from CShape.
 */
class Cylinder : public CShape {

public:

   /* Class constructor */
    Cylinder(float radius, float height);

   /* Class destructor */
   ~Cylinder();

   /* Calculates the perimeter of the cylindre */
   virtual float PerimeterCpp() const;
   virtual float PerimeterAsm() const;

   /* Calculates the base area of the cylindre */
   virtual float BaseAreaCpp() const;
   virtual float BaseAreaAsm() const;

   /* Calculates the lateral area of the cylindre */
   virtual float LateralAreaCpp() const;
   virtual float LateralAreaAsm() const;

   /* Calculates the total area of the cylindre */
   virtual float AreaCpp() const;
   virtual float AreaAsm() const;
 
   /* Calculates the volume of the cylindre */
   float VolumeCpp() const;
   float VolumeAsm() const;

   virtual std::string Name() const;

private:

   float radius_;
   float height_;
};

#endif
