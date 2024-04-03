#include "GameFramework/Level.h"
#include "GameFramework/Actor.h"
#include "GameFramework/WorldSettings.h"

Level::Level() : worldSettings(nullptr)
{
}

Level::~Level()
{
	if (worldSettings)
	{
		delete worldSettings;
	}
	for (auto& i : actors)
	{
		delete i;
	}
	actors.Clear();
}

void Level::BeginPlay()
{
	if (!worldSettings)
	{
		worldSettings = new WorldSettings();
	}
	for (auto& item : actors)
	{
		item->BeginPlay();
	}
}

void Level::UpdateLevel(float TickTime)
{
	for (auto& item : actors)
	{
		item->Update(TickTime);
	}
}

void Level::EndPlay()
{
	for (auto& item : actors)
	{
		item->EndPlay();
	}
}

WorldSettings* Level::getWorldSettings()
{
	return worldSettings;
}

void Level::AddActor(Actor* gameObject)
{
	actors.Add(gameObject);
}

void Level::RemoveActor(Actor* gameobject)
{
	DynamicArray<class Actor*>::Iterator foundIter = actors.Find(gameobject);
	Actor* foundGameObject = *foundIter;
	actors.Remove(foundIter);
	delete foundGameObject;
}
