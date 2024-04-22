#include "GameFramework/Actor.h"
#include "GameFramework/Component.h"
#include "GameFramework/Level.h"

Actor::Actor()
{
}

Actor::~Actor()
{
	for (auto& item : components)
	{
		delete item;
	}
	components.Clear();
}

void Actor::BeginPlay()
{
	for (auto& item : components)
	{
		item->BeginPlay();
	}
}

void Actor::Update(float deltaTime)
{
	for (auto& item : components)
	{
		item->Update(deltaTime);
	}
}

void Actor::EndPlay()
{
	for (auto& item : components)
	{
		item->EndPlay();
	}
}

void Actor::AddComponent(Component* component)
{
	components.Add(component);
}

void Actor::RemoveComponent(Component* component)
{
	components.Remove(component);
}

World* Actor::GetWorld()
{
	return ownedLevel->ownedWorld;
}
