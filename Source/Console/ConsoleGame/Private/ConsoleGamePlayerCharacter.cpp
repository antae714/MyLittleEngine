#include "ConsoleGamePlayerCharacter.h"
#include "ConsoleMovementComponent.h"
#include "GameFramework/Controller.h"
#include "ConsoleRenderComponent.h"

void ConsoleGamePlayerCharacter::BeginPlay()
{
	Base::BeginPlay();	
	AddComponent(new ConsoleMovementComponent());
	ConsoleRenderComponent* renderComponent = new ConsoleRenderComponent();
	renderComponent->renderData = RenderData{ 10,7,'P' };
	AddComponent(renderComponent);
	speed = 0.05f;
}

void ConsoleGamePlayerCharacter::Update(float deltaTime)
{
	position = position + direction * deltaTime * speed;
	direction = Vector();

	if (position.x < 0) position.x = 0;
	if (position.x >= 50) position.x = 50 - 1;
	if (position.y < 0) position.y = 0;
	if (position.y >= 50) position.y = 50 - 1;
}

void ConsoleGamePlayerCharacter::EndPlay()
{
	Base::EndPlay();
}

void ConsoleGamePlayerCharacter::BindInput(Controller* controller)
{
	Base::BindInput(controller);


	controller->BindInput("UP", &ConsoleGamePlayerCharacter::MoveUP, this);
	controller->BindInput("Down", &ConsoleGamePlayerCharacter::MoveDown, this);
	controller->BindInput("Left", &ConsoleGamePlayerCharacter::MoveLeft, this);
	controller->BindInput("Right", &ConsoleGamePlayerCharacter::MoveRight, this);
}

void ConsoleGamePlayerCharacter::MoveUP()
{
	direction.y -= 1.0f;
}

void ConsoleGamePlayerCharacter::MoveDown()
{
	direction.y += 1.0f;
}

void ConsoleGamePlayerCharacter::MoveLeft()
{
	direction.x -= 1.0f;
}

void ConsoleGamePlayerCharacter::MoveRight()
{
	direction.x += 1.0f;
}
