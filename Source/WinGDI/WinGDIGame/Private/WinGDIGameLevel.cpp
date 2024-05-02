#include "WinGDIGameLevel.h"
#include "WinGDIGamePlayerCharacter.h"
#include "GameFramework/PlayerController.h"
#include "GameFramework/WorldSettings.h"
#include "GameFramework/WinGDICamera.h"
#include "GameFramework/WinGDIRenderComponent.h"
#include "Components/CollisionComponent.h"

Actor* CreateWall(Vector pos, Rect size)
{
	Actor* wall = new Actor();
	wall->SetPosition(pos);

	wall->SetName("Wall");
	WinGDIRenderComponent* winGDIRenderComponent = wall->AddComponent<WinGDIRenderComponent>();
	winGDIRenderComponent->SetImageName(L"Wall.bmp");
	winGDIRenderComponent->SetRenderArea(size);

	CollisionComponent* collisionComponent = wall->AddComponent<CollisionComponent>();
	collisionComponent->SetCollisonShape(CollisonShape::CreateRect(size));
	return wall;
}


WinGDIGameLevel::WinGDIGameLevel()
{
	name = "Default";

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
	AddActor(CreateWall({ 200, 100 }, { {-50,-50},{50,50} }));
	//AddActor(CreateWall({ 400, -200 }, { {-50,-50},{50,50} }));
	AddActor(CreateWall({ 500, -200 }, { {-50,-50},{50,50} }));
	AddActor(CreateWall({ 500, -100 }, { {-50,-50},{50,50} }));
	AddActor(CreateWall({ 500, -00 }, { {-50,-50},{50,50} }));
	AddActor(CreateWall({ 600, -200 }, { {-50,-50},{50,50} }));
	AddActor(CreateWall({ 700, -200 }, { {-50,-50},{50,50} }));

	AddActor(CreateWall({ -100, -200 }, { {-50,-50},{50,50} }));
	AddActor(CreateWall({ -200, -200 }, { {-50,-50},{50,50} }));
	AddActor(CreateWall({ -300, -200 }, { {-50,-50},{50,50} }));
	//AddActor(CreateWall({ -300, 100 }, { {-50,-50},{50,50} }));
	AddActor(CreateWall({ -400, -200 }, { {-50,-50},{50,50} }));
	AddActor(CreateWall({ -500, -200 }, { {-50,-50},{50,50} }));
	AddActor(CreateWall({ -600, -200 }, { {-50,-50},{50,50} }));
	AddActor(CreateWall({ -700, -200 }, { {-50,-50},{50,50} }));
}

void WinGDIGameLevel::BeginPlay()
{
	Base::BeginPlay();
	worldSettings->playerController->Possess(worldSettings->playerCharacter);
}

void WinGDIGameLevel::EndPlay()
{
	Base::EndPlay();
	worldSettings->playerController->UnPossess();
}
