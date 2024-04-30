#pragma once

#include "GameFramework/Component.h"
#include "Math/Vector.h"
#include "CoreMinimal.h"

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
	void Move(float deltaTime);
	void SetInput(Vector _input) { input = _input; }
	



	Vector input;
	Vector velocity;
	Vector gravityDirection;
	float gravityScale;

	float moveSpeed;
	float moveMaxSpeed;

};
