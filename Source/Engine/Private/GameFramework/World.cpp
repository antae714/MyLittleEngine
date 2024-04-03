#include "GameFramework/World.h"
#include "GameFramework/Level.h"
#include "GameFramework/Actor.h"

World::World() : mainLevel(nullptr)
{
}

World::~World()
{
	if (mainLevel) delete mainLevel;
	for (auto& i : subLevels)
	{
		delete i;
	}
	subLevels.Clear();
}

void World::BeginPlay()
{
	if (!mainLevel)
	{
		mainLevel = LevelFactory::Get("Deafault");
		mainLevel->BeginPlay();
	}
}

void World::FixedUpdate(float fixedTickTime)
{
}

void World::UpdateWorld(float TickTime)
{
	mainLevel->UpdateLevel(TickTime);

	for (auto& item : subLevels)
	{
		item->UpdateLevel(TickTime);
	}
}

void World::EndPlay()
{
}

void World::SetMainLevel(Level* _mainLevel)
{
	mainLevel = _mainLevel;
}

Level* World::GetMainLevel()
{
	return mainLevel;
}

WorldSettings* World::getWorldSettings()
{
	return mainLevel->getWorldSettings();
}

void World::AddLevel(Level* level)
{
	subLevels.Add(level);
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
