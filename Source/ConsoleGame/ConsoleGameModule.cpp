#include "Module/ModuleBase.h"
#include "GameFramework/Level.h"

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
	String swapLevelName = "Deafault";
	if (LevelFactory::Get(swapLevelName))
	{
		LevelFactory::Remove(swapLevelName);
		LevelFactory::Add(swapLevelName, new Level());
	}
}

void ConsoleGameModule::ShotDownModule()
{

}
