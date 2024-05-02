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
	String swapLevelName = "Default";
	if (LevelFactory::Has(swapLevelName))
	{
		LevelFactory::Remove(swapLevelName);
	}

	LevelFactory::Add<WinGDIGameLevel>(swapLevelName);
}

void WinGDIGameModule::ShotDownModule()
{
	LevelFactory::Remove("Default");
}
