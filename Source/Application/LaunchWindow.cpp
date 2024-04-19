
#include "Module/ModuleManager.h"
#include "Engine.h"
#include "Application/WindowApplication.h"
#include <cstdlib>
#include "Misc/Path.h"


int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPWSTR    lpCmdLine,
	_In_ int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

	WindowApplication windowApplication(hInstance);
	windowApplication.Launch();

	ModuleBase* CoreModule = ModuleManager::LoadModule((L"Core.dll"));
	ModuleBase* RenderCorerModule = ModuleManager::LoadModule((L"RenderCore.dll"));
	ModuleBase* InputCoreModule = ModuleManager::LoadModule((L"InputCore.dll"));
	ModuleBase* EngineModule = ModuleManager::LoadModule((L"Engine.dll"));

	ModuleBase* RendererModule = ModuleManager::LoadModule((L"WinGDIRenderer.dll"));
	ModuleBase* ContentsModule = ModuleManager::LoadModule((L"WinGDIGame.dll"));
	
	{
		Engine engine;
		engine.Run();
	}

	//ModuleManager::UnLoadModule(ContentsModule);
	ModuleManager::UnLoadModule(RendererModule);

	ModuleManager::UnLoadModule(InputCoreModule);
	ModuleManager::UnLoadModule(EngineModule);
	ModuleManager::UnLoadModule(RenderCorerModule);
	ModuleManager::UnLoadModule(CoreModule);
	

	return EXIT_SUCCESS;
}





#pragma warning(pop)