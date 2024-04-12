#pragma once

#include "Template/Function.h"

class IApplication
{
public:
	virtual ~IApplication() = default;

public:
	virtual void Resize(unsigned int width, unsigned int height) = 0;
	virtual void AddOnResized(Function<void(int, int)> function) = 0;
	virtual void RemoveOnResized(Function<void(int, int)> function) = 0;
};



class WindowApplication : public IApplication
{
public:
	WindowApplication(HINSTANCE _hInstance);

public:

	virtual void Resize(unsigned int width, unsigned int height) override;
	virtual void AddOnResized(unsigned int width, unsigned int height) override;
	virtual void RemoveOnResized(unsigned int width, unsigned int height) override;
	
	HINSTANCE GetInstanceHandle() { return hInstance; }


private:
	HINSTANCE hInstance;


};