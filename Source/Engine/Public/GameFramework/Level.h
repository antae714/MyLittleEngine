#pragma once

#include "Containers/DynamicArray.h"
#include "Containers/String.h"
#include "GameFramework/WorldSettings.h"


class ENGINEMODULEAPI Level
{
public:
	Level();
	~Level();
public:
	void UpdateLevel(float TickTime);

	String GetName() { return name; }
	WorldSettings* getWorldSettings();

	void AddGameObject(class Actor* actor);
	void RemoveGameObject(class Actor* actor);

private:

private:
	DynamicArray<class Actor*> actors;
	class WorldSettings* worldSettings;
	String name;
};

