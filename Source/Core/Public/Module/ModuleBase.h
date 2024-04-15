#pragma once


struct HINSTANCE__;
typedef struct HINSTANCE__* HINSTANCE;
typedef HINSTANCE HMODULE;

class COREMODULEAPI ModuleBase
{
public:
	HMODULE ModuleHandle;

	virtual void StartUpModule();
	virtual void ShotDownModule();
};


#define IMPLEMENT_MODULE(Name)							\
class Name##Module : public ModuleBase					\
{														\
};														\
extern "C"												\
{														\
	__declspec(dllexport) ModuleBase* GetModule()		\
	{													\
		return new Name##Module();						\
	}													\
}														\


#define DEFINE_MODULE(Name)								\
class Name##Module;										\
extern "C"												\
{														\
	__declspec(dllexport) ModuleBase* GetModule()		\
	{													\
		return new Name##Module();						\
	}													\
}														\
