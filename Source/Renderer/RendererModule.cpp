// dllmain.cpp : DLL 애플리케이션의 진입점을 정의합니다.

#include "Module/ModuleBase.h"
#include "IRenderer.h"
#include "ConsoleRenderer.h"

class RendererModule : public ModuleBase
{
	virtual void StartUpModule() override;
	virtual void ShotDownModule() override;
};

//IMPLEMENT_MODULE(Renderer)
DEFINE_MODULE(Renderer);



void RendererModule::StartUpModule()
{
	RendererFactory::Add("Console", new ConsoleRenderer());
}

void RendererModule::ShotDownModule()
{
	RendererFactory::Remove("Console");
}
