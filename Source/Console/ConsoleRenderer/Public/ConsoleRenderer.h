#pragma once


#include "IRenderer.h"
#include "Math/Vector.h"
#include "ConsoleRenderComponent.h"



class CONSOLERENDERERMODULEAPI ConsoleRenderer : public IRenderer
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

	void RenderObject(Vector position, RenderData data);
	bool SetChar(int x, int y, char ch, WORD attr = 0);
	bool SetString(int x, int y, const char* pStr, WORD attr = 0);
	bool SetAttribute(WORD _Attribute);


private:
	HANDLE buffer[2];
	int currentBufferIndex;
	COORD ScreenSize;


};

