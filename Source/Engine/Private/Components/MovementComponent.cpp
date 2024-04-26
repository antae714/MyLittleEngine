#include "Components/MovementComponent.h"
#include "GameFramework/Actor.h"
#include "GameFramework/World.h"
#include "Components/CollisionComponent.h"
#include <iostream>     

MovementComponent::MovementComponent() :
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
	gravityScale = 0.01f;
}

void MovementComponent::Update(float deltaTime)
{
	Move(deltaTime);

}

void MovementComponent::Move(float deltaTime)
{
	velocity += gravityDirection * gravityScale * deltaTime;
	float inputVelocity = LinearInterp(velocity.x, input.x * moveSpeed * deltaTime, 0.0012f);

	velocity.x = inputVelocity;
	Vector remainingVelocity = velocity;
	
	Vector targetPosition = owner->GetPosition() + remainingVelocity;
	velocity += owner->MovePosition(targetPosition);
}
