#pragma once

#include "Math/Vector.h"

class COREMODULEAPI Rect
{
public:
	Rect(Vector _min = Vector(), Vector _max = Vector());
	
public:
	Vector Min;
	Vector Max;




public:
	Vector GetCenter() const { return (Min + Max) * 0.5f; }
	Vector GetExtents() const { return Max - GetCenter(); }

	static Rect GetBoundBox(const Rect& first, const Rect& second);


	Rect operator+(Vector vector) const;

};

