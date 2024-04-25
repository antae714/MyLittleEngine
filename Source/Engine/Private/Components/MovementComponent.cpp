#include "Components/MovementComponent.h"
#include "GameFramework/Actor.h"
#include "GameFramework/World.h"
#include "Components/CollisionComponent.h"

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
	velocity += gravityDirection * gravityScale * deltaTime;
	float inputVelocity = LinearInterp(velocity.x, input.x * moveSpeed * deltaTime, 0.0012f);

	velocity.x = inputVelocity;
	Vector remainingVelocity = velocity;

	while (remainingVelocity.LengthSquared() > 0)
	{
		Vector targetPosition = owner->GetPosition() + remainingVelocity;
		remainingVelocity = owner->SetPosition(targetPosition, true);
	}

	


}

void MovementComponent::CheckCollison()
{
	// 아아아아아아악
	// 다시
	// 
	// 서로가 알고있는게 아니라 
	// 콜리전은 사각형, 원 제공만
	// 그러면 셋 포지션이 콜리전 타입과
	// 트레이스를 구현하여 해결!
	// 
	// 
	//CollisionComponent* myCollisionComponent = owner->GetComponent<CollisionComponent>();
	//for (auto& actorList : owner->GetWorld()->GetAllActor())
	//{
	//	for (auto& actor : *actorList)
	//	{
	//		CollisionComponent* collisionComponent = actor->GetComponent<CollisionComponent>();
	//		myCollisionComponent->HandleSweepCollision(collisionComponent, )
	//	}
	//}
}
