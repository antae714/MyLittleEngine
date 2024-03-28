#pragma once

#include "Containers/DynamicArray.h"
#include "Containers/String.h"


class COREMODULEAPI Level
{
public:
	void UpdateLevel(float TickTime);
	void AddGameObject(class GameObject* gameObjects);
	void RemoveGameObject(class GameObject* gameobject);

	String GetName() { return name; }

private:
	DynamicArray<class GameObject> gameObjects;
	String name;
};

