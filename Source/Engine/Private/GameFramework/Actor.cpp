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

Vector Actor::MovePosition(Vector targetPosition)
{
	HitResult result;
	CollisonAlgorithm::Sweep(
		GetWorld(),
		result,
		GetPosition(),
		targetPosition,
		GetComponent<CollisionComponent>()->GetCollisonShape(),
		{ this }
	);

	if (result.isHit)
	{
		Vector resultVector = targetPosition - GetPosition();
		std::cout << "boudnce" << (targetPosition - GetPosition()).y << std::endl;
		resultVector.y *= -1.0f;
		resultVector.y += 3.0f;
		resultVector.x = 0;
		return resultVector;
	}
	else
	{
		std::cout << (targetPosition - GetPosition()).y << std::endl;
		position = targetPosition;

		return targetPosition - GetPosition();
	}
}

World* Actor::GetWorld()
{
	return ownedLevel->ownedWorld;
}
