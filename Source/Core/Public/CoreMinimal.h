#pragma once

#include "Containers/DynamicArray.h"
#include "Containers/String.h"

#define GENERATED_BODY(CLASS, BASECLASS)	\
public:										\
	virtual ~CLASS() {}						\
private:									\
	using Base = BASECLASS;


