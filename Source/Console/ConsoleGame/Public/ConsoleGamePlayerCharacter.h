#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Math/Vector.h"


class CONSOLEGAMEMODULEAPI ConsoleGamePlayerCharacter : public Character
{
	GENERATED_BODY(ConsoleGamePlayerCharacter, Character)
public:
	// Begin Actor Implement
	virtual void BeginPlay() override;
	virtual void Update(float deltaTime);
	virtual void EndPlay() override;
	// ~End Actor Implement

	// Begin Actor Implement
	virtual void BindInput(class Controller* controller);
	// ~End Actor Implement

	void CheckWall(Vector& _pos, Vector _direction);

	void MoveUP();
	void MoveDown();
	void MoveLeft();
	void MoveRight();
	
	
	class ConsoleWorldSetting* consoleWorldSetting;
private:
	Vector direction;

	float speed;	
};

