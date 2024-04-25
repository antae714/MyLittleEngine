#include "GameFramework/Level.h"
#include "GameFramework/Actor.h"
#include "GameFramework/WorldSettings.h"

Level::Level() : worldSettings(nullptr), ownedWorld(nullptr)
{
}

Level::~Level()
{
	if (worldSettings)
	{
		delete worldSettings;
	}
	for (auto& i : actorList)
	{
		delete i;
	}
	actorList.Clear();
}

void Level::BeginPlay()
{
	for (auto& item : actorList)
	{
		item->BeginPlay();
	}
}

void Level::UpdateLevel(float TickTime)
{
	for (auto& item : actorList)
	{
		item->Update(TickTime);
	}
}

void Level::EndPlay()
{
	for (auto& item : actorList)
	{
		item->EndPlay();
	}
}

WorldSettings* Level::GetWorldSettings()
{
	return worldSettings;
}

void Level::SetWorldSettings(WorldSettings* _worldSetting)
{
	worldSettings = _worldSetting;
}

List<Actor*>& Level::GetActorList()
{
	return actorList;
}

void Level::AddActor(Actor* gameObject)
{
	actorList.AddBack(gameObject);
	gameObject->ownedLevel = this;
}

void Level::RemoveActor(Actor* gameobject)
{
	auto foundIter = actorList.Find(gameobject);
	Actor* foundGameObject = *foundIter;
	actorList.Remove(foundIter);
	delete foundGameObject;
}
