#include "WinGDIRenderer.h"
#include "Application/WindowApplication.h"
#include "GameFramework/World.h"
#include "GameFramework/Level.h"
#include "GameFramework/Actor.h"
#include "GameFramework/WinGDIRenderComponent.h"

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

	::PatBlt(backBufferDC, 0, 0, width, height, WHITENESS);
	::SelectObject(backBufferDC, backBitmap);

	for (auto& item : world->GetMainLevel()->GetActorArray())
	{
		WinGDIRenderComponent* winGDIRenderComponent = item->GetComponent<WinGDIRenderComponent>();

		if (!winGDIRenderComponent) continue;

		Rect renderArea = winGDIRenderComponent->GetRenderArea();

		HDC bitmapMemDC = CreateCompatibleDC(frontBufferDC);
		HBITMAP hBitmap = winGDIRenderComponent->GetHBITMAP();
		HBITMAP hOldBitmap = (HBITMAP)SelectObject(bitmapMemDC, hBitmap);

		BITMAP bm;
		GetObject(hBitmap, sizeof(BITMAP), &bm);

		::BitBlt(backBufferDC, renderArea.Min.x, renderArea.Min.y, bm.bmWidth, bm.bmHeight, bitmapMemDC, 0, 0, SRCCOPY);

		hOldBitmap = (HBITMAP)SelectObject(bitmapMemDC, hOldBitmap);
		DeleteDC(bitmapMemDC);
	} 

	::BitBlt(frontBufferDC, 0, 0, width, height, backBufferDC, 0, 0, SRCCOPY);

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
