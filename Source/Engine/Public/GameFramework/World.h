#pragma once

#include "Containers/DynamicArray.h"
#include "Containers/String.h"

class Level;

class ENGINEMODULEAPI World
{
public:
	World();
	~World();

public:

	void BeginPlay();
	void ProcessInput();
	void FixedUpdate(float fixedTickTime);
	void UpdateWorld(float tickTime);
	void EndPlay();

	void SetMainLevel(Level* mainLevel);
	Level* GetMainLevel();

	void AddLevel(Level* level);
	void RemoveLevel(Level* level);

	[[deprecated("This function has not been implemented yet")]]
	void AddLevelByName(String LevelName);
	void RemoveLevelByName(String LevelName);
	
private:
	Level* mainLevel;
	DynamicArray<Level*> subLevels;
	String name;
};
