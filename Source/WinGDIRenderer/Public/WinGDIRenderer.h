#pragma once


#include "IRenderer.h"
#include "Math/Vector.h"




class WINGDIRENDERERMODULEAPI WinGDIRenderer : public IRenderer
{
public:
	WinGDIRenderer();

public:
	// Begin IRenderer Interface
	virtual void Init() override;
	virtual void EndPlay() override;
	virtual void Render(class World* world) override;

	virtual unsigned int GetWidth() override { return width; }
	virtual unsigned int GetHeight() override { return height; }
	// ~End IRenderer Interface

	void OnResizedScreen(struct ScreenSize screenSize);
	void PlaceInCenterOfScreen();

private:
	HWND hWindow;
	HDC frontBufferDC;
	HDC backBufferDC;

	HBITMAP backBitmap;

	unsigned int width;
	unsigned int height;
};

