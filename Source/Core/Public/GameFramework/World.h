#pragma once

#include "Containers/DynamicArray.h"

class COREMODULEAPI World
{
public:
	void UpdateWorld();


private:
	DynamicArray<class Level> Levels;
};

