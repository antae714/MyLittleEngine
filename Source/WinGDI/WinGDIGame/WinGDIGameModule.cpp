#include "Module/ModuleBase.h"
#include "GameFramework/Level.h"
#include "WinGDIGameLevel.h"

class WinGDIGameModule : public ModuleBase
{
	virtual void StartUpModule() override;
	virtual void ShotDownModule() override;
};

//IMPLEMENT_MODULE(Contents)
DEFINE_MODULE(WinGDIGame);


void WinGDIGameModule::StartUpModule()
{
	//많이 부족한 프레임 워크라 사용자가 바꿔치기 합니다.
	String swapLevelName = "Default";
	if (LevelFactory::Get(swapLevelName))
	{
		LevelFactory::Remove(swapLevelName);
	}

	WinGDIGameLevel* winGDIGameLevel = new WinGDIGameLevel();
	LevelFactory::Add(swapLevelName, winGDIGameLevel);
}

void WinGDIGameModule::ShotDownModule()
{
	LevelFactory::Remove("Default");
}
