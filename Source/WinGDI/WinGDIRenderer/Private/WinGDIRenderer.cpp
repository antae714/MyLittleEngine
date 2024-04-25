#include "Application/WindowApplication.h"
#include "GameFramework/Actor.h"
#include "GameFramework/Camera.h"
#include "GameFramework/Level.h"
#include "GameFramework/WinGDIRenderComponent.h"
#include "GameFramework/World.h"
#include "WinGDIRenderer.h"

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
	Camera* camera = world->GetMainCamera();
	if (!camera) return;

	::PatBlt(backBufferDC, 0, 0, width, height, BLACKNESS);
	::SelectObject(backBufferDC, backBitmap);

	for (auto& item : world->GetMainLevel()->GetActorList())
	{
		// 렌더링 컴포넌트가 존재하면 그립니다.
		WinGDIRenderComponent* winGDIRenderComponent = item->GetComponent<WinGDIRenderComponent>();
		if (!winGDIRenderComponent) continue;

		// 그릴 영역을 계산합니다
		Rect renderArea = winGDIRenderComponent->GetRenderArea();
		renderArea.Min = ViewPortToScreen(camera->WorldToViewPort(renderArea.Min + item->GetPosition()));
		renderArea.Max = ViewPortToScreen(camera->WorldToViewPort(renderArea.Max + item->GetPosition()));

		std::swap(renderArea.Min.y, renderArea.Max.y);


		// 그리기 세팅을 합니다
		HDC bitmapMemDC = CreateCompatibleDC(frontBufferDC);
		HBITMAP hBitmap = winGDIRenderComponent->GetHBITMAP();
		HBITMAP hOldBitmap = (HBITMAP)SelectObject(bitmapMemDC, hBitmap);

		BITMAP bm;
		GetObject(hBitmap, sizeof(BITMAP), &bm);

		// 뒷면 버퍼에 그립니다
		//::BitBlt(backBufferDC, ScreenPosition.x, ScreenPosition.y, bm.bmWidth, bm.bmHeight, bitmapMemDC, 0, 0, SRCCOPY);

		::StretchBlt(
			backBufferDC,
			renderArea.Min.x, renderArea.Min.y,
			renderArea.Max.x - renderArea.Min.x, renderArea.Max.y - renderArea.Min.y,
			bitmapMemDC,
			0, 0,
			bm.bmWidth, bm.bmHeight,
			SRCCOPY
		);

		//hOldBitmap = (HBITMAP)SelectObject(bitmapMemDC, hOldBitmap);
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

Vector WinGDIRenderer::ViewPortToScreen(Vector viewportPosition)
{
	return Vector(viewportPosition.x * width, (1 - viewportPosition.y) * height);
}

Vector WinGDIRenderer::ScreenToViewPort(Vector screenPosition)
{
	return Vector(screenPosition.x * invWidth, (1 - screenPosition.y) * invHeight);
}
