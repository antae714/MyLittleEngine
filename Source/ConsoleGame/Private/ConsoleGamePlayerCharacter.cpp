#include "ConsoleGamePlayerCharacter.h"
#include "ConsoleMovementComponent.h"
#include "GameFramework/Controller.h"

void ConsoleGamePlayerCharacter::BeginPlay()
{
	Base::BeginPlay();
	AddComponent(new ConsoleMovementComponent());
	speed = 0.25f;
}

void ConsoleGamePlayerCharacter::Update(float deltaTime)
{
	position = position + direction * deltaTime * speed;
	direction = Vector2();
}

void ConsoleGamePlayerCharacter::EndPlay()
{
	Base::EndPlay();
}

void ConsoleGamePlayerCharacter::BindInput(Controller* controller)
{
	Base::BindInput(controller);


	controller->BindInput("Up", &ConsoleGamePlayerCharacter::MoveUP, this);
	controller->BindInput("Down", &ConsoleGamePlayerCharacter::MoveDown, this);
	controller->BindInput("Left", &ConsoleGamePlayerCharacter::MoveLeft, this);
	controller->BindInput("Right", &ConsoleGamePlayerCharacter::MoveRight, this);
}

void ConsoleGamePlayerCharacter::MoveUP()
{
	direction.y += 1.0f;
}

void ConsoleGamePlayerCharacter::MoveDown()
{
	direction.y -= 1.0f;
}

void ConsoleGamePlayerCharacter::MoveLeft()
{
	direction.x -= 1.0f;
}

void ConsoleGamePlayerCharacter::MoveRight()
{
	direction.x += 1.0f;
}
