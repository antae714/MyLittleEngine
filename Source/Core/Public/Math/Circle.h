#pragma once

#include "Math/Vector.h"

class COREMODULEAPI Circle
{
public:
	Vector Center;
	float Radius;


	Circle operator+(Vector vector) const;
};