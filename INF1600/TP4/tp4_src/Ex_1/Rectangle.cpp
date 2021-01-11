#include "Rectangle.h"
#include <cmath>

/****************************************/
/****************************************/

Rectangle::Rectangle(float length, float width) 
	: length_(length) 
	, width_(width) 
{}

/****************************************/
/****************************************/

Rectangle::~Rectangle() 
{}

/****************************************/
/****************************************/

float Rectangle::PerimeterCpp() const {
   return 2.0 * (length_ + width_);
}

/****************************************/
/****************************************/

float Rectangle::AreaCpp() const {
   return length_ * width_;
}

/****************************************/
/****************************************/

float Rectangle::DiagonalCpp() const {
   return sqrt(length_ * length_ + width_ * width_);
}


/****************************************/
/****************************************/

std::string Rectangle::Name() const {
    return "Rectangle";
}

/****************************************/
/****************************************/

