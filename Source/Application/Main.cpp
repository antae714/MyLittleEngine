
#include "Module/ModuleManager.h"
#include "Engine.h"

#include <process.h>

#include <stdio.h>



void main() 
{
	
	ModuleBase* EngineModule = ModuleManager::LoadModule((L"Engine.dll"));
	ModuleBase* CoreModule = ModuleManager::LoadModule((L"Core.dll"));
	ModuleBase* InputCoreModule = ModuleManager::LoadModule((L"InputCore.dll"));
	ModuleBase* RendererModule = ModuleManager::LoadModule((L"Renderer.dll"));
	ModuleBase* ContentsModule = ModuleManager::LoadModule((L"ConsoleGame.dll"));
	
	Engine engine;
	engine.Run();

	ModuleManager::UnLoadModule(ContentsModule);
	ModuleManager::UnLoadModule(RendererModule);
	ModuleManager::UnLoadModule(InputCoreModule);
	ModuleManager::UnLoadModule(CoreModule);
	ModuleManager::UnLoadModule(EngineModule);


	system("pause");
}




