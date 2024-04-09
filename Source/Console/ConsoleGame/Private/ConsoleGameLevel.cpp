#include "ConsoleGameLevel.h"
#include "ConsoleGamePlayerCharacter.h"
#include "GameFramework/PlayerController.h"
#include "GameFramework/WorldSettings.h"
#include "ConsoleWorldSetting.h"
#include "ConsoleWorldSetting.h"
#include "ConsolePathFinder.h"

void ConsoleGameLevel::BeginPlay()
{
	ConsoleGamePlayerCharacter* PCharater = new ConsoleGamePlayerCharacter();
	ConsolePathFinder* PCPathFinder = PCharater->AddComponent<ConsolePathFinder>();

	PlayerController* playerController = new PlayerController();

	AddActor(PCharater);
	AddActor(playerController);

	Base::BeginPlay();
	ConsoleWorldSetting* consoleWorldSetting = dynamic_cast<ConsoleWorldSetting*>(worldSettings);
	worldSettings->playerController = playerController;
	playerController->Possess(PCharater);
	PCharater->consoleWorldSetting = consoleWorldSetting;
	PCPathFinder->worldSettings = consoleWorldSetting;
}

void ConsoleGameLevel::EndPlay()
{
	Base::EndPlay();
}
