#include "WinGDIGameLevel.h"
#include "WinGDIGamePlayerCharacter.h"
#include "GameFramework/PlayerController.h"
#include "GameFramework/WorldSettings.h"


void WinGDIGameLevel::BeginPlay()
{
	WinGDIGamePlayerCharacter* PCharater = new WinGDIGamePlayerCharacter();


	PlayerController* playerController = new PlayerController();

	AddActor(PCharater);
	AddActor(playerController);

	Base::BeginPlay();
	
	worldSettings->playerController = playerController;
	playerController->Possess(PCharater);
	

}

void WinGDIGameLevel::EndPlay()
{
	Base::EndPlay();
}
