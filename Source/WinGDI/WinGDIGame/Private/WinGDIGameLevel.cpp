#include "WinGDIGameLevel.h"
#include "WinGDIGamePlayerCharacter.h"
#include "GameFramework/PlayerController.h"
#include "GameFramework/WorldSettings.h"
#include "GameFramework/WinGDICamera.h"


WinGDIGameLevel::WinGDIGameLevel()
{
	WinGDIGamePlayerCharacter* PCharater = new WinGDIGamePlayerCharacter();
	PlayerController* playerController = new PlayerController();

	AddActor(PCharater);
	AddActor(playerController);

	worldSettings = new WorldSettings();
	worldSettings->playerController = playerController;
	worldSettings->playerCharacter = PCharater;

	AddActor(new WinGDICamera());
}

void WinGDIGameLevel::BeginPlay()
{
	Base::BeginPlay();
	worldSettings->playerController->Possess(worldSettings->playerCharacter);
}

void WinGDIGameLevel::EndPlay()
{
	Base::EndPlay();
}
