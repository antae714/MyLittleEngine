
#include "Module/ModuleManager.h"
#include "Engine.h"

#include <process.h>

#include <stdio.h>



void main() 
{
	
	ModuleBase* CoreModule = ModuleManager::LoadModule((L"Core.dll"));
	ModuleBase* RenderCorerModule = ModuleManager::LoadModule((L"RenderCore.dll"));
	ModuleBase* InputCorerModule = ModuleManager::LoadModule((L"InputCore.dll"));
	ModuleBase* EngineModule = ModuleManager::LoadModule((L"Engine.dll"));
	ModuleBase* InputCoreModule = ModuleManager::LoadModule((L"InputCore.dll"));
	ModuleBase* RendererModule = ModuleManager::LoadModule((L"Renderer.dll"));
	ModuleBase* ContentsModule = ModuleManager::LoadModule((L"ConsoleGame.dll"));
	
	Engine engine;
	engine.Run();

	ModuleManager::UnLoadModule(ContentsModule);
	ModuleManager::UnLoadModule(RendererModule);
	ModuleManager::UnLoadModule(InputCoreModule);
	ModuleManager::UnLoadModule(EngineModule);
	ModuleManager::UnLoadModule(InputCorerModule);
	ModuleManager::UnLoadModule(RenderCorerModule);
	ModuleManager::UnLoadModule(CoreModule);


	system("pause");
}




