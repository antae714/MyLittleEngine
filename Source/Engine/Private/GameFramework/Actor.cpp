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

	HitResult result;
	memset(&result, 0, sizeof(result));

	CollisionComponent* collisionComponent = GetComponent<CollisionComponent>();

	if (collisionComponent)
	{
		CollisonAlgorithm::Overlap(
			result,
			GetWorld(),
			GetPosition(),
			collisionComponent->shape,
			{ this }
		);

		if (collisionComponent && result.isHit)
		{

		}
	}

}

void Actor::MovePosition(Vector targetPosition)
{
	HitResult result;
	memset(&result, 0, sizeof(result));

	CollisionComponent* collisionComponent = GetComponent<CollisionComponent>();
	if (collisionComponent)
	{
		CollisonAlgorithm::Sweep(
			result,
			GetWorld(),
			GetPosition(),
			targetPosition,
			collisionComponent->shape,
			{ this },
			collisionComponent->collisionType,
			collisionComponent->collisionReactionArray
		);

	}

	if (collisionComponent && result.isHit)
	{

		collisionComponent->onCollision.Excute(result);
		SetPosition(result.hitPosition);
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
