#pragma once

#include "Math/Vector.h"

class COREMODULEAPI Rect
{
public:
	Vector Min;
	Vector Max;

	Vector GetCenter() const
	{
		return (Min + Max) * 0.5f;
	}
	Vector GetExtents() const
	{
		return Max - GetCenter();
	}
};

