#pragma once

#include <Windows.h>
#include "ConsoleConfig.h"

class RENDERERMODULEAPI IRenderer
{
public:
	IRenderer() {}
	~IRenderer() {}

	virtual void Init() = 0;
	virtual void EndPlay() = 0;

	virtual void BufferChange() = 0;
	virtual void BufferClear() = 0;

	virtual int GetWidth() = 0;
	virtual int GetHeight() = 0;

	virtual void processWindowSizeChange() = 0;
private:

};


