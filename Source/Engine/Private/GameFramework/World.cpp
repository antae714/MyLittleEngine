#include "GameFramework/World.h"
#include "GameFramework/Level.h"
#include "GameFramework/Actor.h"

World::World()
{
}

World::~World()
{
	for (auto& i : subLevels)
	{
		delete i;
	}
	subLevels.Clear();
}

void World::BeginPlay()
{
}

void World::ProcessInput()
{
	WorldSettings*  worldSetting = mainLevel->getWorldSettings();
	worldSetting->playerController->processInput();
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
	//리소스 매니저 추가후 구현
}

void World::RemoveLevelByName(String LevelName)
{
	DynamicArray<class Level*>::Iterator findIter = subLevels.Find([LevelName](Level* level) { return level->GetName() == LevelName; });
	Level* findLevel = *findIter;
	subLevels.Remove(findIter);
	delete findLevel;
}
