#include "Math/Rect.h"
#include <algorithm>
#include <utility>


Rect::Rect(Vector _min, Vector _max) : Min(_min), Max(_max)
{

}

Rect Rect::GetBoundBox(const Rect& first, const Rect& second)
{
	Rect resultRect = Rect();

	resultRect.Max.x = (std::max)(first.Max.x, second.Max.x);
	resultRect.Max.y = (std::max)(first.Max.y, second.Max.y);
	resultRect.Min.x = (std::min)(first.Min.x, second.Min.x);
	resultRect.Min.x = (std::min)(first.Min.x, second.Min.x);

	return resultRect;
}



Rect Rect::operator+(Vector vector) const
{
	Rect returnRect;
	returnRect.Min = Min + vector;
	returnRect.Max = Max + vector;

	return returnRect;
}