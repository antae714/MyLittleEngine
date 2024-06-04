#include "Components/MovementComponent.h"
#include "GameFramework/Actor.h"
#include "GameFramework/World.h"
#include "Components/CollisionComponent.h"
#include <iostream>     

MovementComponent::MovementComponent() :
	movementMode(EMoveMentMode::Walk),
	gravityDirection(0.0f, -1.0f),
	gravityScale(1.0f),
	moveSpeed(1.0f),
	moveMaxSpeed(1.0f),
	velocity(0)
{
}

float LinearInterp(float a, float b, float t) 
{
	return a + (b - a) * t;
}

void MovementComponent::BeginPlay()
{
	gravityScale = 0.005f;
	moveSpeed = 0.3f;
	velocity = Vector();
}

void MovementComponent::Update(float deltaTime)
{
	Move(deltaTime);

}

void MovementComponent::Move(float deltaTime)
{
	switch (movementMode)
	{
	case EMoveMentMode::Walk:
	{
		MoveWalk(deltaTime);
	}
		break;
	case EMoveMentMode::Fly:
	{
		MoveFly(deltaTime);
	}
		break;
	default:
		break;
	}
}

void MovementComponent::MoveWalk(float deltaTime)
{
	velocity += gravityDirection * gravityScale * deltaTime;

	owner->MovePosition(owner->GetPosition() + velocity * deltaTime);
}

void MovementComponent::MoveFly(float deltaTime)
{
	owner->MovePosition(owner->GetPosition() + velocity * deltaTime);
}
