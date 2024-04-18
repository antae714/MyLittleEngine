#include "WinGDIGamePlayerCharacter.h"
#include "GameFramework/Controller.h"


void WinGDIGamePlayerCharacter::BeginPlay()
{
	Base::BeginPlay();
	//ConsoleRenderComponent* renderComponent = new ConsoleRenderComponent();
	
	//AddComponent(renderComponent);
}

void WinGDIGamePlayerCharacter::Update(float deltaTime)
{
	Base::Update(deltaTime);
	Vector targetPosition = position + direction * deltaTime * speed;


	position = targetPosition;

	direction = Vector();
}

void WinGDIGamePlayerCharacter::EndPlay()
{
	Base::EndPlay();
}

void WinGDIGamePlayerCharacter::BindInput(Controller* controller)
{
	Base::BindInput(controller);


	controller->BindInput("UP", &WinGDIGamePlayerCharacter::MoveUP, this);
	controller->BindInput("Down", &WinGDIGamePlayerCharacter::MoveDown, this);
	controller->BindInput("Left", &WinGDIGamePlayerCharacter::MoveLeft, this);
	controller->BindInput("Right", &WinGDIGamePlayerCharacter::MoveRight, this);
}


void WinGDIGamePlayerCharacter::MoveUP()
{
	direction.y -= 1.0f;
}

void WinGDIGamePlayerCharacter::MoveDown()
{
	direction.y += 1.0f;
}

void WinGDIGamePlayerCharacter::MoveLeft()
{
	direction.x -= 1.0f;
}

void WinGDIGamePlayerCharacter::MoveRight()
{
	direction.x += 1.0f;
}
