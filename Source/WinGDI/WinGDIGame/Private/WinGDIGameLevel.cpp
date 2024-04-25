#include "WinGDIGameLevel.h"
#include "WinGDIGamePlayerCharacter.h"
#include "GameFramework/PlayerController.h"
#include "GameFramework/WorldSettings.h"
#include "GameFramework/WinGDICamera.h"
#include "GameFramework/WinGDIRenderComponent.h"

Actor* CreateWall(Vector pos, Rect size)
{
	Actor* wall = new Actor();
	wall->SetPosition(pos);

	WinGDIRenderComponent* winGDIRenderComponent = wall->AddComponent<WinGDIRenderComponent>();
	winGDIRenderComponent->SetImageName(L"Wall.bmp");
	winGDIRenderComponent->SetRenderArea(size);
	return wall;
}


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




	AddActor(CreateWall({ 0, -200 }, { {-50,-50},{50,50} }));
	AddActor(CreateWall({ 100, -200 }, { {-50,-50},{50,50} }));
	AddActor(CreateWall({ 200, -200 }, { {-50,-50},{50,50} }));
	AddActor(CreateWall({ 300, -200 }, { {-50,-50},{50,50} }));
	AddActor(CreateWall({ 400, -200 }, { {-50,-50},{50,50} }));
	AddActor(CreateWall({ 500, -200 }, { {-50,-50},{50,50} }));
	AddActor(CreateWall({ 600, -200 }, { {-50,-50},{50,50} }));
	AddActor(CreateWall({ 700, -200 }, { {-50,-50},{50,50} }));

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
