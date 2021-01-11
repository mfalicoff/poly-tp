#include "Cylinder.h"
#include <math.h>

/****************************************/
/****************************************/

Cylinder::Cylinder(float radius, float height) 
	: radius_(radius) 
	, height_(height) 
{}

/****************************************/
/****************************************/

Cylinder::~Cylinder() 
{}

/****************************************/
/****************************************/

float Cylinder::PerimeterCpp() const {
   return 2.0f * M_PI * radius_;
}

/****************************************/
/****************************************/

float Cylinder::BaseAreaCpp() const {
   return M_PI * radius_ * radius_;
}

/****************************************/
/****************************************/

float Cylinder::LateralAreaCpp() const {
   return PerimeterCpp() * height_;
}

/****************************************/
/****************************************/

float Cylinder::AreaCpp() const {
   return LateralAreaCpp() + BaseAreaCpp();
}

/****************************************/
/****************************************/

float Cylinder::VolumeCpp() const {
   return BaseAreaCpp() * height_;
}

/****************************************/
/****************************************/

std::string Cylinder::Name() const {
    return "Cylinder";
}

/****************************************/
/****************************************/

