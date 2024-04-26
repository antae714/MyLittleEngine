#include "Math/Line.h"



Line Line::operator+(Vector vector) const
{
	return { start + vector, end + vector };
}