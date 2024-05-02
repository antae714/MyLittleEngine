#include "GameFramework/World.h"
#include "GameFramework/Level.h"
#include "GameFramework/Component.h"
#include "GameFramework/Actor.h"


World::World() : mainLevel(nullptr), mainCamera(nullptr), willChageMainLevel(nullptr)
{
}

World::~World()
{
	if (mainLevel) delete mainLevel;
	
	subLevels.Clear();
}

void World::BeginPlay()
{
	if (!mainLevel)
	{
		SetMainLevel(LevelFactory::Get("Default"));
		ChangeMainLevel();
	}
	mainLevel->BeginPlay();
}

void World::FixedUpdate(float fixedTickTime)
{

}

void World::Update(float TickTime)
{
	ChangeMainLevel();
	mainLevel->UpdateLevel(TickTime);

	for (auto& item : subLevels)
	{
		item->UpdateLevel(TickTime);
	}
}

void World::EndPlay()
{
	mainLevel->EndPlay();
	for (auto& item : subLevels)
	{
		item->EndPlay();
	}
}

void World::SetMainLevel(Level* _mainLevel)
{
	willChageMainLevel = _mainLevel;
	willChageMainLevel->ownedWorld = this;
}

void World::SetMainLevelByName(String LevelName)
{
	SetMainLevel(LevelFactory::Get(LevelName));
}

Level* World::GetMainLevel()
{
	return mainLevel;
}

DynamicArray<Level*>& World::GetSubLevel()
{
	return subLevels;
}

WorldSettings* World::getWorldSettings()
{
	return mainLevel->GetWorldSettings();
}

void World::AddLevel(Level* level)
{
	subLevels.Add(level);
	level->ownedWorld = this;
}

void World::RemoveLevel(Level* level)
{
	DynamicArray<Level*>::Iterator findIter = subLevels.Find(level);
	Level* findLevel = *findIter;
	subLevels.Remove(findIter);
	delete findLevel;
}

void World::AddLevelByName(String LevelName)
{

}

void World::RemoveLevelByName(String LevelName)
{
	DynamicArray<class Level*>::Iterator findIter = subLevels.Find([LevelName](Level* level) { return level->GetName() == LevelName; });
	Level* findLevel = *findIter;
	subLevels.Remove(findIter);
	delete findLevel;
}

DynamicArray<List<Actor*>*> World::GetAllActor()
{
	DynamicArray<List<Actor*>*> allActor(subLevels.GetCount() + 1);

	allActor.Add(&mainLevel->GetActorList());
	for (auto& item : subLevels)
	{
		allActor.Add(&item->GetActorList());
	}


	return allActor;
}

Actor* World::FindActor(String _name)
{
	for (auto& actorList : GetAllActor())
	{
		for (auto& actor : *actorList)
		{
			if (actor->GetName() == _name) return actor;
		}
	}
	return nullptr;
}

void World::ChangeMainLevel()
{
	if (willChageMainLevel)
	{
		delete mainLevel;
		mainLevel = willChageMainLevel;
		willChageMainLevel = nullptr;
		mainLevel->BeginPlay();
	}
}


