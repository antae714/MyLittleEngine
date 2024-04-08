// dllmain.cpp : DLL 애플리케이션의 진입점을 정의합니다.

#include "Module/ModuleBase.h"
#include "IRenderer.h"

class ConsoleEngineModule : public ModuleBase
{
	virtual void StartUpModule() override;
	virtual void ShotDownModule() override;
};

//IMPLEMENT_MODULE(Renderer)
DEFINE_MODULE(ConsoleEngine);



void ConsoleEngineModule::StartUpModule()
{
	
}

void ConsoleEngineModule::ShotDownModule()
{
	
}
