#include "Components/MovementComponent.h"
#include "GameFramework/Actor.h"

MovementComponent::MovementComponent()
{
	gravityDirection = { 0.0f, -1.0f };
	gravityScale = 1.0f;
}

void MovementComponent::Move(float deltaTime)
{
	velocity += gravityDirection * gravityScale * deltaTime;
	velocity.x += input.x * deltaTime;
	//hmmmmm

	Vector targetPosition = owner->GetPosition() + velocity;
	
	//�ϴ� �浹����
	
	owner->SetPosition(targetPosition);
	


}
