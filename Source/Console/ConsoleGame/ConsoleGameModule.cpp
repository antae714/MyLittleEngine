#include "Module/ModuleBase.h"
#include "GameFramework/Level.h"
#include "ConsoleGameLevel.h"
#include "ConsoleWorldSetting.h"

class ConsoleGameModule : public ModuleBase
{
	virtual void StartUpModule() override;
	virtual void ShotDownModule() override;
};

//IMPLEMENT_MODULE(Contents)
DEFINE_MODULE(ConsoleGame);


void ConsoleGameModule::StartUpModule()
{
	//많이 부족한 프레임 워크라 사용자가 바꿔치기 합니다.
	String swapLevelName = "Default";
	if (LevelFactory::Get(swapLevelName))
	{
		//LevelFactory::Remove(swapLevelName);

		//ConsoleGameLevel* consoleDefaultLevel = new ConsoleGameLevel();
		//consoleDefaultLevel->SetWorldSettings(new ConsoleWorldSetting());
		//LevelFactory::Add(swapLevelName, consoleDefaultLevel);
	}
}

void ConsoleGameModule::ShotDownModule()
{

}
