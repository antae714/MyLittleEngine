#pragma once


struct HINSTANCE__;
typedef struct HINSTANCE__* HINSTANCE;
typedef HINSTANCE HMODULE;

class COREMODULEAPI ModuleBase
{
public:
	HMODULE ModuleHandle;



};


#define IMPLEMENT_MODULE(Name)							\
class Name##Module : public ModuleBase					\
{														\
};														\
extern "C"												\
{														\
	__declspec(dllexport) ModuleBase* getModule()		\
	{													\
		return new Name##Module();						\
	}													\
}														\


