#include "Physics/CollisonShape.h"
#include <exception>


CollisonShape::CollisonShape(ECollisonShape::Type collisonShape) 
	: collisonShape(collisonShape)
{
}

CollisonShape::CollisonShape(const CollisonShape& other)
	: collisonShape(other.collisonShape)
{
	switch (collisonShape)
	{
	case ECollisonShape::Line:
		line = other.line;

		break;
	case ECollisonShape::Box:
		rect = other.rect;
		
		break;
	case ECollisonShape::Sphere:
		circle = other.circle;
		
		break;	
	default:
		break;
	}
}

CollisonShape CollisonShape::CreateLine(Line _line)
{
	CollisonShape newCollisonShape(ECollisonShape::Line);
	newCollisonShape.SetLine(_line);
	return newCollisonShape;
}

CollisonShape CollisonShape::CreateRect(Rect _rect)
{
	CollisonShape newCollisonShape(ECollisonShape::Box);
	newCollisonShape.SetRect(_rect);
	return newCollisonShape;
}

CollisonShape CollisonShape::CreateCircle(Circle _circle)
{
	CollisonShape newCollisonShape(ECollisonShape::Sphere);
	newCollisonShape.SetCircle(_circle);
	return newCollisonShape;
}

void CollisonShape::SetLine(Line _line)
{
	collisonShape = ECollisonShape::Line;
	line = _line;
}

void CollisonShape::SetRect(Rect _rect)
{
	collisonShape = ECollisonShape::Box;
	rect = _rect;
}

void CollisonShape::SetCircle(Circle _circle)
{
	collisonShape = ECollisonShape::Sphere;
	circle = _circle;
}

Line CollisonShape::GetLine() const
{
	if (collisonShape == ECollisonShape::Box)
	{
		return line;
	}
	else
	{
		return Line();
	}
}

Rect CollisonShape::GetRect() const
{
	if (collisonShape == ECollisonShape::Box)
	{
		return rect;
	}
	else
	{
		return Rect();
	}
}

Circle CollisonShape::GetCircle() const
{
	if (collisonShape == ECollisonShape::Sphere)
	{
		return circle;
	}
	else
	{
		return Circle();
	}
}

CollisonShape CollisonShape::operator+(const Vector& vector) const
{
	CollisonShape resultCollisonShape;
	switch (collisonShape)
	{
	case ECollisonShape::Line:
		resultCollisonShape.SetLine(line + vector);
		break;
	case ECollisonShape::Box:
		resultCollisonShape.SetRect(rect + vector);

		break;
	case ECollisonShape::Sphere:
		resultCollisonShape.SetCircle(circle + vector);

		break;
	default:
		break;
	}
	return resultCollisonShape;
}
