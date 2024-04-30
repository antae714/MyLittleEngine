#include "GameFramework/WinGDICamera.h"

#include "GameFramework/World.h"

#include "GameFramework/Actor.h"

#include "GameFramework/Character.h"

void WinGDICamera::BeginPlay()
{
	Base::BeginPlay();
	GetWorld()->SetMainCamera(this);
	playerCharacter = dynamic_cast<Character*>(GetWorld()->FindActor("PlayerCharacter"));
}

void WinGDICamera::Update(float deltaTime)
{
	Vector tempvector = GetPosition();
	tempvector.x = playerCharacter->GetPosition().x;
	SetPosition(tempvector);
	
}

void WinGDICamera::EndPlay()
{
	Base::EndPlay();
	GetWorld()->SetMainCamera(nullptr);
}
