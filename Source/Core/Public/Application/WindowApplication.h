#pragma once

#include "Template/Function.h"
#include "Containers/Delegate.h"
#include "Application/Application.h"




class COREMODULEAPI WindowApplication : public IApplication
{
public:
	WindowApplication(HINSTANCE _hInstance);
	virtual ~WindowApplication();

public:
	// Begin IApplication Interface
	virtual void Launch() override;
	virtual bool IsTerminated() override;
	virtual void Resize(ScreenSize screenSize) override;
	virtual void AddOnResized(Function<void(ScreenSize)> function) override;
	virtual void RemoveOnResized(Function<void(ScreenSize)> function) override;
	// ~End IApplication Interface

	HINSTANCE GetInstanceHandle() { return hInstance; }
	HWND GetWindowHandle() { return hWindow; }
	void Terminate();


private:
	HINSTANCE hInstance;
	HWND hWindow;

	bool isTerminated;
	Delegate<ScreenSize> onResized;
};