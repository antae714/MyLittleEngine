#include "GameFramework/WinGDICamera.h"

#include "GameFramework/World.h"

void WinGDICamera::BeginPlay()
{
	Base::BeginPlay();
	GetWorld()->SetMainCamera(this);
}

void WinGDICamera::EndPlay()
{
	Base::EndPlay();
	GetWorld()->SetMainCamera(nullptr);
}
