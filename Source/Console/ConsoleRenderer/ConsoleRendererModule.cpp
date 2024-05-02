// dllmain.cpp : DLL 애플리케이션의 진입점을 정의합니다.

#include "Module/ModuleBase.h"
#include "IRenderer.h"
#include "ConsoleRenderer.h"

class ConsoleRendererModule : public ModuleBase
{
	virtual void StartUpModule() override;
	virtual void ShotDownModule() override;
};

//IMPLEMENT_MODULE(Renderer)
DEFINE_MODULE(ConsoleRenderer);



void ConsoleRendererModule::StartUpModule()
{
	RendererFactory::Add<ConsoleRenderer>("Console");
}

void ConsoleRendererModule::ShotDownModule()
{
	RendererFactory::Remove("Console");
}
