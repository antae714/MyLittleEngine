#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Math/Vector.h"


class WINGDIGAMEMODULEAPI WinGDIGamePlayerCharacter : public Character
{
	GENERATED_BODY(WinGDIGamePlayerCharacter, Character)

public:
	WinGDIGamePlayerCharacter();

public:
	// Begin Actor Implement
	virtual void BeginPlay() override;
	virtual void Update(float deltaTime) override;
	virtual void EndPlay() override;
	// ~End Actor Implement

	// Begin Pawn Implement
	virtual void BindInput(class Controller* controller);
	// ~End Pawn Implement

	void OnCollision(struct HitResult result);

	void Move(float axis);
	
private:

	class MovementComponent* movementComponent;
	class Camera* camera;
	String currentLevelName;
};
