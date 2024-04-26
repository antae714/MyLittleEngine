#pragma once

#include "Math/Vector.h"

class COREMODULEAPI Line
{
public:
	Vector start;
	Vector end;


	Line operator+(Vector vector) const;
};

