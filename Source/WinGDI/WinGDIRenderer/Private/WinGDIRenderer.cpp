#include "WinGDIRenderer.h"
#include "Application/WindowApplication.h"

WinGDIRenderer::WinGDIRenderer() : hWindow(nullptr), frontBufferDC(nullptr), backBufferDC(nullptr), backBitmap(nullptr)
{
}

void WinGDIRenderer::Init()
{
	WindowApplication* windowApplication = IApplication::GetSingletonInstance<WindowApplication>();
	windowApplication->AddOnResized(Binder<void, ScreenSize>::Bind(&WinGDIRenderer::OnResizedScreen, this));
	hWindow = windowApplication->GetWindowHandle();

	RECT rect;
	GetWindowRect(hWindow, &rect);

	int width = rect.right - rect.left;
	int height = rect.bottom - rect.top;
	SetWindowPos(hWindow, NULL, 0, 0, width, height, SWP_NOZORDER | SWP_NOACTIVATE);

	PlaceInCenterOfScreen();


    frontBufferDC = GetDC(hWindow);
    
	backBufferDC = CreateCompatibleDC(frontBufferDC);

    backBitmap = CreateCompatibleBitmap(frontBufferDC, width, height);
}

void WinGDIRenderer::EndPlay()
{
	WindowApplication* windowApplication = IApplication::GetSingletonInstance<WindowApplication>();
	
	windowApplication->RemoveOnResized(Binder<void, ScreenSize>::Bind(&WinGDIRenderer::OnResizedScreen, this));
}

void WinGDIRenderer::Render(World* world)
{
}

void WinGDIRenderer::OnResizedScreen(ScreenSize screenSize)
{
	width = screenSize.width;
	height = screenSize.height;
}

void WinGDIRenderer::PlaceInCenterOfScreen()
{
	int screenWidth = GetSystemMetrics(SM_CXSCREEN);
	int screenHeight = GetSystemMetrics(SM_CYSCREEN);

	RECT clientRect;
	GetClientRect(hWindow, &clientRect);

	int clientWidth = clientRect.right - clientRect.left;
	int clientHeight = clientRect.bottom - clientRect.top;

	SetWindowPos(hWindow, NULL,
		screenWidth / 2 - clientWidth / 2,
		screenHeight / 2 - clientHeight / 2,
		clientWidth, clientHeight, 0
	);
}
