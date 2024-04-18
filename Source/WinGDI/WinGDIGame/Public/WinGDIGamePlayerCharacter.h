#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Math/Vector.h"


class WINGDIGAMEMODULEAPI WinGDIGamePlayerCharacter : public Character
{
	GENERATED_BODY(WinGDIGamePlayerCharacter, Character)
public:
	// Begin Actor Implement
	virtual void BeginPlay() override;
	virtual void Update(float deltaTime);
	virtual void EndPlay() override;
	// ~End Actor Implement

	// Begin Actor Implement
	virtual void BindInput(class Controller* controller);
	// ~End Actor Implement



	void MoveUP();
	void MoveDown();
	void MoveLeft();
	void MoveRight();
	
private:
	Vector direction;

	float speed;	
};

