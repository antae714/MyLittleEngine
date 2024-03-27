
#include "Module/ModuleManager.h"
#include "Engine.h"

#include <process.h>




void main() 
{
	ModuleBase* EngineModule = ModuleManager::LoadModule((L"Engine.dll"));
	Engine engine;
	engine.Run();

	ModuleBase* CoreModule = ModuleManager::LoadModule((L"Core.dll"));
	ModuleBase* ContentsModule = ModuleManager::LoadModule((L"Contents.dll"));
	ModuleManager::UnLoadModule(CoreModule);
	ModuleManager::UnLoadModule(ContentsModule);
	

	system("pause");
}