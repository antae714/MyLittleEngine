#include "GameFramework/Actor.h"
#include "GameFramework/Component.h"
#include "GameFramework/Level.h"
#include "Physics/CollisionAlgorithm.h"
#include "Components/CollisionComponent.h"
#include <iostream>     

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
	onCollision.Clear();
}

void Actor::AddComponent(Component* component)
{
	components.Add(component);
}

void Actor::RemoveComponent(Component* component)
{
	components.Remove(component);
}

void Actor::SetPosition(Vector targetPosition)
{
	position = targetPosition;
}

void Actor::MovePosition(Vector targetPosition)
{
	HitResult result;

	CollisionComponent* collisionComponent = GetComponent<CollisionComponent>();
	if (collisionComponent)
	{
		CollisonAlgorithm::Sweep(
			GetWorld(),
			result,
			GetPosition(),
			targetPosition,
			collisionComponent->GetCollisonShape(),
			{ this }
		);

	}

	if (result.isHit)
	{
		SetPosition(result.hitPosition);
		onCollision.Excute(result);
	}
	else
	{
		SetPosition(targetPosition);
	}
}

World* Actor::GetWorld()
{
	return ownedLevel->ownedWorld;
}
