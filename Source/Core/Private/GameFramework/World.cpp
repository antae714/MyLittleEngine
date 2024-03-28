#include "GameFramework/World.h"
#include "GameFramework/Level.h"
#include "GameFramework/GameObject.h"

World::World()
{
}

World::~World()
{
	for (auto& i : levels)
	{
		delete i;
	}
	levels.Clear();
}

void World::UpdateWorld(float TickTime)
{
	for (auto& item : levels)
	{
		item->UpdateLevel(TickTime);
	}
}

void World::AddLevel(Level* level)
{
	levels.Add(level);
}

void World::RemoveLevel(Level* level)
{
	DynamicArray<class Level*>::Iterator findIter = levels.Find(level);
	Level* findLevel = *findIter;
	levels.Remove(findIter);
	delete findLevel;
}

void World::AddLevelByName(String LevelName)
{
	//리소스 매니저 추가후 구현
}

void World::RemoveLevelByName(String LevelName)
{
	DynamicArray<class Level*>::Iterator findIter = levels.Find([LevelName](Level* level) { return level->GetName() == LevelName; });
	Level* findLevel = *findIter;
	levels.Remove(findIter);
	delete findLevel;
}
