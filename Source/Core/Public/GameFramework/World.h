#pragma once

#include "Containers/DynamicArray.h"
#include "Containers/String.h"

class COREMODULEAPI World
{
public:
	World();
	~World();

public:
	void UpdateWorld(float TickTime);

	void AddLevel(class Level* level);
	void RemoveLevel(class Level* level);

	[[deprecated("This function has not been implemented yet")]]
	void AddLevelByName(String LevelName);
	void RemoveLevelByName(String LevelName);
	
private:
	DynamicArray<class Level*> levels;
	String name;
};

