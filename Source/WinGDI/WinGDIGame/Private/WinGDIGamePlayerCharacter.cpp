#include "WinGDIGamePlayerCharacter.h"
#include "GameFramework/Controller.h"
#include "GameFramework/WinGDIRenderComponent.h"
#include "Components/MovementComponent.h"
#include "Components/CollisionComponent.h"

WinGDIGamePlayerCharacter::WinGDIGamePlayerCharacter()
{
	Rect size{ {-20,-20},{20,20} };
	name = "PlayerCharacter";
	WinGDIRenderComponent* winGDIRenderComponent = AddComponent<WinGDIRenderComponent>();
	winGDIRenderComponent->SetImageName(L"Test.bmp");
	winGDIRenderComponent->SetRenderArea(size);

	CollisionComponent* collisionComponent = AddComponent<CollisionComponent>();
	collisionComponent->SetCollisonShape(CollisonShape::CreateRect(size));

	movementComponent = AddComponent<MovementComponent>();
}

void WinGDIGamePlayerCharacter::BeginPlay()
{
	Base::BeginPlay();
}

void WinGDIGamePlayerCharacter::Update(float deltaTime)
{
	Base::Update(deltaTime);
}

void WinGDIGamePlayerCharacter::EndPlay()
{
	Base::EndPlay();
}

void WinGDIGamePlayerCharacter::BindInput(Controller* controller)
{
	Base::BindInput(controller);

	controller->BindAxisInput("Left/Right", &WinGDIGamePlayerCharacter::Move, this);

	//controller->BindInput("UP", &WinGDIGamePlayerCharacter::MoveUP, this);
	//controller->BindInput("Down", &WinGDIGamePlayerCharacter::MoveDown, this);
	//controller->BindInput("Left", &WinGDIGamePlayerCharacter::MoveLeft, this);
	//controller->BindInput("Right", &WinGDIGamePlayerCharacter::MoveRight, this);
}


void WinGDIGamePlayerCharacter::Move(float axis)
{
	movementComponent->input.x = axis;
}

void WinGDIGamePlayerCharacter::MoveUP()
{
	movementComponent->input.y = -1.0f;
}

void WinGDIGamePlayerCharacter::MoveDown()
{
	movementComponent->input.y = 1.0f;
}

void WinGDIGamePlayerCharacter::MoveLeft()
{
	movementComponent->input.x = -1.0f;
}

void WinGDIGamePlayerCharacter::MoveRight()
{
	movementComponent->input.x = 1.0f;
}
