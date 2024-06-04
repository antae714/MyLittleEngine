#pragma once

#include "GameFramework/Component.h"
#include "Math/Vector.h"
#include "CoreMinimal.h"

namespace EMoveMentMode 
{
	enum Type
	{
		Walk,
		Fly
	};
}




class ENGINEMODULEAPI MovementComponent : public Component
{
	GENERATED_BODY(MovementComponent, Component)

public:
	MovementComponent();

public:
	// Begin Actor Implement
	virtual void BeginPlay() override;
	virtual void Update(float deltaTime) override;
	// ~End Actor Implement

public:
	virtual void Move(float deltaTime);
	virtual void MoveWalk(float deltaTime);
	virtual void MoveFly(float deltaTime);
	



	EMoveMentMode::Type movementMode;

	Vector velocity;
	Vector gravityDirection;
	float gravityScale;

	float moveSpeed;
	float moveMaxSpeed;

};
