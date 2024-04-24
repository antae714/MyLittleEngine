#include "GameFramework/World.h"
#include "GameFramework/Level.h"

World::World() : mainLevel(nullptr)
{
}

World::~World()
{
	//if (mainLevel) delete mainLevel;
	//for (auto& i : subLevels)
	//{
	//	delete i;
	//}
	subLevels.Clear();
}

void World::BeginPlay()
{
	if (!mainLevel)
	{
		SetMainLevel(LevelFactory::Get("Default"));

	}
	mainLevel->BeginPlay();
}

void World::FixedUpdate(float fixedTickTime)
{
}

void World::Update(float TickTime)
{
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
	mainLevel = _mainLevel;
	mainLevel->ownedWorld = this;
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
	DynamicArray<class Level*>::Iterator findIter = subLevels.Find(level);
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
