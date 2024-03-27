#pragma once


#include "IRenderer.h"

class RENDERERMODULEAPI ConsoleRenderer : public IRenderer
{
public:
	ConsoleRenderer();

public:
	virtual void Init();
	virtual void EndPlay();

	virtual void BufferChange();
	virtual void BufferClear();

	virtual int GetWidth();
	virtual int GetHeight();

	virtual void processWindowSizeChange();

	bool SetChar(int x, int y, char ch, WORD attr = 0);
	bool SetString(int x, int y, const char* pStr, WORD attr = 0);
	bool SetAttribute(WORD _Attribute);


private:
	HANDLE buffer[2];
	int currentBufferIndex;
	COORD ScreenSize;


};

