#pragma once

#include "Math/Line.h"
#include "Math/Rect.h"
#include "Math/Circle.h"

namespace ECollisonShape
{
	enum Type
	{
		Line,
		Box,
		Sphere,

		MAX
	};
};

class ENGINEMODULEAPI CollisonShape
{
public:
	CollisonShape(ECollisonShape::Type collisonShape = ECollisonShape::MAX);
	CollisonShape(const CollisonShape& other);

public:
	static CollisonShape CreateLine(Line _line);
	static CollisonShape CreateRect(Rect _rect);
	static CollisonShape CreateCircle(Circle _circle);

	void SetLine(Line _line);
	void SetRect(Rect _rect);
	void SetCircle(Circle _circle);

	Line GetLine() const;
	Rect GetRect() const;
	Circle GetCircle() const;
	ECollisonShape::Type GetCollisonShape() const { return collisonShape; }

	CollisonShape operator+(const Vector& vector) const;


private:

	ECollisonShape::Type collisonShape;

	union
	{
		Line line;
		Rect rect;
		Circle circle;
	};

};
