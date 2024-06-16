// dllmain.cpp : DLL 애플리케이션의 진입점을 정의합니다.

#include "Module/ModuleBase.h"
#include "D2DRenderee.h"


class D2DRendererModule : public ModuleBase
{
	virtual void StartUpModule() override;
	virtual void ShotDownModule() override;
};

DEFINE_MODULE(D2DRenderer);



void D2DRendererModule::StartUpModule()
{
	RendererFactory::Add("WinGDIRenderer", new D2DRenderer());
}

void D2DRendererModule::ShotDownModule()
{
	RendererFactory::Remove("WinGDIRenderer");
}