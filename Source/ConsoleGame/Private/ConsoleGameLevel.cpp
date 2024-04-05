#include "ConsoleGameLevel.h"
#include "ConsoleGamePlayerCharacter.h"
#include "GameFramework/PlayerController.h"
#include "GameFramework/WorldSettings.h"

void ConsoleGameLevel::BeginPlay()
{
	Character* PCharater = new ConsoleGamePlayerCharacter();
	PlayerController* playerController = new PlayerController();

	AddActor(PCharater);
	AddActor(playerController);

	Base::BeginPlay();

	worldSettings->playerController = playerController;
	playerController->Possess(PCharater);
}

void ConsoleGameLevel::EndPlay()
{
	Base::EndPlay();
}
