#pragma once

#include "Containers/DynamicArray.h"
#include "Containers/String.h"
#include "Template/Factory.h"

class ENGINEMODULEAPI Level
{
public:
	Level();
	~Level();
public:	
	void BeginPlay();
	void UpdateLevel(float TickTime);
	void EndPlay();
	
	String GetName() { return name; }
	class WorldSettings* getWorldSettings();

	void AddGameObject(class Actor* actor);
	void RemoveGameObject(class Actor* actor);

private:

private:
	DynamicArray<class Actor*> actors;
	class WorldSettings* worldSettings;
	String name;
};

class ENGINEMODULEAPI LevelFactory : public Factory<Level, String> {};