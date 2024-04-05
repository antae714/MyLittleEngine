#pragma once


#include "IRenderer.h"

class RENDERERMODULEAPI ConsoleRenderer : public IRenderer
{
public:
	ConsoleRenderer();

public:
	// Begin IRenderer Interface
	virtual void Init() override;
	virtual void EndPlay() override;
	virtual void Render(class World* world) override;

	virtual void BufferChange() override;
	virtual void BufferClear() override;

	virtual int GetWidth() override;
	virtual int GetHeight() override;
	// ~End IRenderer Interface

	virtual void processWindowSizeChange();

	bool SetChar(int x, int y, char ch, WORD attr = 0);
	bool SetString(int x, int y, const char* pStr, WORD attr = 0);
	bool SetAttribute(WORD _Attribute);


private:
	HANDLE buffer[2];
	int currentBufferIndex;
	COORD ScreenSize;


};

