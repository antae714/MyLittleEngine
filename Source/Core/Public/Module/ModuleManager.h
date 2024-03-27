#pragma once




class ModuleBase;

class COREMODULEAPI ModuleManager
{
public:
	static ModuleBase* LoadModule(const wchar_t* ModuleName);
	static void UnLoadModule(ModuleBase*& Module);
};

