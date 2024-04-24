#include "Components/MovementComponent.h"
#include "GameFramework/Actor.h"

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
	gravityScale = 0.001;
}

void MovementComponent::Update(float deltaTime)
{
	Move(deltaTime);
}

void MovementComponent::Move(float deltaTime)
{
	//velocity += gravityDirection * gravityScale * deltaTime;
	float inputVelocity = LinearInterp(velocity.x, input.x * moveSpeed, 0.0012 );

	velocity.x = inputVelocity;

	Vector targetPosition = owner->GetPosition() + velocity;
	//일단 충돌부터
	



	owner->SetPosition(targetPosition);
	


}
