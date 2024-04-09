#pragma once

#include "GameFramework/WorldSettings.h"
#include "Math/Vector.h"


enum class EObject
{
	Empty = 0,
	Wall,
	Start,
	Goal,

	MAX
};

class ConsoleWorldSetting : public WorldSettings
{
public:
    Vector GetStartPoint() { return Vector{ 1.0f, 1.0f }; };
    Vector GetGoalPoint() { return Vector{ 9.0f, 9.0f }; };
    int GetMapElement(Vector pos) { return Map[(int)pos.y * 10 + (int)pos.x]; }



	int Map[100] = {
             1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 
             1, 0, 1, 0, 0, 0, 0, 0, 0, 1, 
             1, 0, 1, 0, 1, 1, 1, 0, 0, 1,  
             1, 0, 1, 0, 0, 0, 1, 1, 1, 1,  
             1, 0, 1, 0, 0, 0, 0, 0, 0, 1,  
             1, 0, 0, 0, 0, 0, 0, 1, 0, 1,  
             1, 1, 1, 1, 1, 0, 1, 1, 0, 1,  
             1, 0, 0, 0, 0, 0, 0, 1, 0, 1,  
             1, 0, 0, 0, 0, 0, 0, 1, 0, 1,  
             1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
    };
};

