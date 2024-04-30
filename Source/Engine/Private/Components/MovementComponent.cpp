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
	velocity += gravityDirection * gravityScale * deltaTime;
	Vector inputVelocity = velocity;

	if (input.x == 0.0f)
	{
		inputVelocity.x = LinearInterp(velocity.x, 0.0f, 0.002f);
	}
	else
	{
		inputVelocity.x = LinearInterp(velocity.x, input.x * moveSpeed * deltaTime, 0.005f);
	}

	velocity = inputVelocity;
	//velocity += input * moveSpeed * deltaTime;
	Vector targetPosition = owner->GetPosition() + velocity * deltaTime;
	owner->MovePosition(targetPosition);

}
