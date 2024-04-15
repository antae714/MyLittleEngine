#pragma once

#include "Containers/Delegate.h"
#include "Template/Function.h"

struct COREMODULEAPI ScreenSize
{
	unsigned int width;
	unsigned int height;
};

class COREMODULEAPI IApplication
{
public:
	virtual ~IApplication() = default;

public:
	virtual void Launch() = 0;
	virtual bool IsTerminated() = 0;
	virtual void Resize(ScreenSize screenSize) = 0;
	virtual void AddOnResized(Function<void(ScreenSize)> function) = 0;
	virtual void RemoveOnResized(Function<void(ScreenSize)> function) = 0;

public:
	static IApplication* GetSingletonInstance() { return singletonInstance; }
	template<class T>
	static T* GetSingletonInstance() { return dynamic_cast<T*>(singletonInstance); }

protected:
	static void SetSingletonInstance(IApplication* instance);


private:
	static IApplication* singletonInstance;
};