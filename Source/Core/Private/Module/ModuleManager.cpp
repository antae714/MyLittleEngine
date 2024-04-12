
#include "Module/ModuleManager.h"
#include "Module/ModuleBase.h"
#include <Windows.h>

#include <exception>



ModuleBase* ModuleManager::LoadModule(const wchar_t* ModuleName)
{
	using GetModuleFN = ModuleBase*(*)();
	HMODULE DllHandle = LoadLibrary(ModuleName);
	if (DllHandle)
	{
		GetModuleFN MyFunct = (GetModuleFN)GetProcAddress(DllHandle, "getModule");
		if (MyFunct)
		{
			ModuleBase* RetunModule = MyFunct();
			RetunModule->ModuleHandle = DllHandle;
			RetunModule->StartUpModule();
			return RetunModule;
		}

	}
	throw std::exception();
	return nullptr;
}

void ModuleManager::UnLoadModule(ModuleBase*& Module)
{
	if (!Module) return;
	Module->ShotDownModule();
	
	FreeLibrary(Module->ModuleHandle);
	if (Module)
	{
		delete Module;
		Module = nullptr;
	}
}