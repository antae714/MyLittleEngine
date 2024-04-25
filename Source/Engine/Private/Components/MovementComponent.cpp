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
	// �ƾƾƾƾƾƾ�
	// �ٽ�
	// 
	// ���ΰ� �˰��ִ°� �ƴ϶� 
	// �ݸ����� �簢��, �� ������
	// �׷��� �� �������� �ݸ��� Ÿ�԰�
	// Ʈ���̽��� �����Ͽ� �ذ�!
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
