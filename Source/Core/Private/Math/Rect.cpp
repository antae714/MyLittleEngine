#include "Math/Rect.h"



Rect Rect::operator+(Vector vector) const
{
	Rect returnRect;
	returnRect.Min = Min + vector;
	returnRect.Max = Max + vector;

	return returnRect;
}