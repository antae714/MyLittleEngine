#include "WinGDIGamePlayerCharacter.h"
#include "GameFramework/Controller.h"
#include "GameFramework/WinGDIRenderComponent.h"
#include "Components/MovementComponent.h"
#include "Components/CollisionComponent.h"
#include "GameFramework/World.h"
#include "GameFramework/Camera.h"
#include "GameFramework/Level.h"
#include "Physics/CollisionAlgorithm.h"


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

	camera = dynamic_cast<Camera*>(GetWorld()->FindActor("Camera"));
	currentLevelName = GetWorld()->GetMainLevel()->GetName();

	onCollision.Bind(&WinGDIGamePlayerCharacter::OnCollision, this);
}

void WinGDIGamePlayerCharacter::Update(float deltaTime)
{
	Base::Update(deltaTime);

	if (camera->WorldToViewPort(GetPosition()).y < 0)
	{
		GetWorld()->SetMainLevelByName(GetWorld()->GetMainLevel()->GetName());
	}


}

void WinGDIGamePlayerCharacter::EndPlay()
{
	Base::EndPlay();
	onCollision.UnBind(&WinGDIGamePlayerCharacter::OnCollision, this);

}

void WinGDIGamePlayerCharacter::BindInput(Controller* controller)
{
	Base::BindInput(controller);

	controller->BindAxisInput("Left/Right", &WinGDIGamePlayerCharacter::Move, this);

}


void WinGDIGamePlayerCharacter::OnCollision(HitResult result)
{
	if (result.hitNormal.y != 0.0f)
	{
		movementComponent->velocity.y = result.hitNormal.y * 2.0f;
	}
	if (result.hitNormal.x != 0.0f)
	{
		movementComponent->velocity.x *= -1.0f;
	}
}


void WinGDIGamePlayerCharacter::Move(float axis)
{
	movementComponent->input.x = axis;
}

