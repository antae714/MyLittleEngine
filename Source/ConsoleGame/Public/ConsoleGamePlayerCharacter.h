#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"

struct Vector2
{
	Vector2() : x(0.0f), y(0.0f) {}
	Vector2(const Vector2& other) : x(other.x), y(other.y) {}
	float x, y;
	Vector2 operator *(float scalar)
	{
		Vector2 returnVec;
		returnVec.x = this->x * scalar;
		returnVec.y = this->y * scalar;
		return returnVec;
	}

	Vector2 operator +(const Vector2& other)
	{
		Vector2 returnVec = *this;
		returnVec.x += other.x;
		returnVec.y += other.y;
		return returnVec;
	}
};


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

	void MoveUP();
	void MoveDown();
	void MoveLeft();
	void MoveRight();


private:
	Vector2 position;
	Vector2 direction;
	float speed;
};

