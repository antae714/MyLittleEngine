#pragma once

#include "GameFramework/Component.h"
#include "Math/Vector.h"
#include "Containers/Delegate.h"
#include "CoreMinimal.h"

class ENGINEMODULEAPI MovementComponent : public Component
{
	GENERATED_BODY(MovementComponent, Component)

public:
	MovementComponent();

public:
	void Move(float deltaTime);
	void SetInput(Vector _input) { input = _input; }

	Delegate<void> OnCollision;
	Delegate<void> OnTriger;

	Vector input;
	Vector velocity;
	Vector gravityDirection;
	float gravityScale;
};
