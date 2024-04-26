#include "Math/Circle.h"



Circle Circle::operator+(Vector vector) const
{
	Circle returnCircle;
	returnCircle.Center = Center + vector;
	returnCircle.Radius = Radius;
	return returnCircle;
}