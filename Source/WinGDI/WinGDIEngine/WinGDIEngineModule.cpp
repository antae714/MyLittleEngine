// dllmain.cpp : DLL 애플리케이션의 진입점을 정의합니다.

#include "Module/ModuleBase.h"
#include "IRenderer.h"

class WinGDIEngineModule : public ModuleBase
{
	virtual void StartUpModule() override;
	virtual void ShotDownModule() override;
};

//IMPLEMENT_MODULE(Renderer)
DEFINE_MODULE(WinGDIEngine);



void WinGDIEngineModule::StartUpModule()
{
	
}

void WinGDIEngineModule::ShotDownModule()
{
	
}
