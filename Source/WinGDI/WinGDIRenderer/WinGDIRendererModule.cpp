// dllmain.cpp : DLL 애플리케이션의 진입점을 정의합니다.

#include "Module/ModuleBase.h"
#include "IRenderer.h"
#include "WinGDIRenderer.h"

class WinGDIRendererModule : public ModuleBase
{
	virtual void StartUpModule() override;
	virtual void ShotDownModule() override;
};

//IMPLEMENT_MODULE(Renderer)
DEFINE_MODULE(WinGDIRenderer);



void WinGDIRendererModule::StartUpModule()
{
	RendererFactory::Add("WinGDIRenderer", new WinGDIRenderer());
}

void WinGDIRendererModule::ShotDownModule()
{
	RendererFactory::Remove("WinGDIRenderer");
}
