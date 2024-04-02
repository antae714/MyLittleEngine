#include "GameFramework/Level.h"
#include "GameFramework/Actor.h"

Level::Level()
{
}

Level::~Level()
{
	for (auto& i : actors)
	{
		delete i;
	}
	actors.Clear();
}

void Level::UpdateLevel(float TickTime)
{
	for (auto& item : actors)
	{
		item->Update(TickTime);
	}
}

WorldSettings* Level::getWorldSettings()
{
	return worldSettings;
}

void Level::AddGameObject(Actor* gameObject)
{
	actors.Add(gameObject);
}

void Level::RemoveGameObject(Actor* gameobject)
{
	DynamicArray<class Actor*>::Iterator foundIter = actors.Find(gameobject);
	Actor* foundGameObject = *foundIter;
	actors.Remove(foundIter);
	delete foundGameObject;
}