#include "Application/WindowApplication.h"

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);


IApplication* IApplication::singletonInstance = nullptr;



bool bUseConsole = true;
constexpr int SCREEN_START_LEFT = 10;

constexpr int SCREEN_START_TOP = 10;

constexpr int SCREEN_WIDTH = 1024;

constexpr int SCREEN_HEIGHT = 768;

WindowApplication::WindowApplication(HINSTANCE _hInstance) : hInstance(_hInstance), hWindow(0), isTerminated(0)
{
	SetSingletonInstance(this);
}

WindowApplication::~WindowApplication()
{
	SetSingletonInstance(nullptr);
	if (bUseConsole)
	{
		FreeConsole();
	}
}

void WindowApplication::Launch()
{
	const TCHAR* appName = TEXT("Test Game Framework");

	//Step 1: Registering the Window Class

	WNDCLASS wndClass;

	wndClass.style = CS_HREDRAW | CS_VREDRAW;
	wndClass.lpfnWndProc = WndProc;
	wndClass.cbClsExtra = 0;
	wndClass.cbWndExtra = 0;
	wndClass.hInstance = hInstance;
	wndClass.hIcon = LoadIcon(hInstance, IDI_APPLICATION);
	wndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndClass.hbrBackground = static_cast<HBRUSH>(GetStockObject(WHITE_BRUSH));
	wndClass.lpszMenuName = NULL;
	wndClass.lpszClassName = appName;

	RegisterClass(&wndClass);

	// Step 2: Creating the Window

	RECT rect{ SCREEN_START_LEFT, SCREEN_START_TOP,
	SCREEN_START_LEFT + SCREEN_WIDTH, SCREEN_START_TOP + SCREEN_HEIGHT };

	::AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, FALSE);

	int width = rect.right - rect.left;
	int height = rect.bottom - rect.top;

	hWindow = CreateWindow(appName, appName, WS_OVERLAPPED | WS_SYSMENU,
		SCREEN_START_LEFT, SCREEN_START_TOP, width, height, NULL, NULL, hInstance, NULL);

	ShowWindow(hWindow, SW_SHOWNORMAL);
	UpdateWindow(hWindow);

	if (bUseConsole)
	{
		AllocConsole();
		FILE* _tempFile;
		freopen_s(&_tempFile, "CONOUT$", "w", stdout);
	}
}

bool WindowApplication::IsTerminated()
{
	return isTerminated;
}

void WindowApplication::Resize(ScreenSize screenSize)
{
	onResized.Excute(screenSize);
}

void WindowApplication::AddOnResized(Function<void(ScreenSize)> function)
{
	onResized.Bind(function);
}

void WindowApplication::RemoveOnResized(Function<void(ScreenSize)> function)
{
	onResized.UnBind(function);
}

void WindowApplication::Terminate()
{
	isTerminated = true;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_KEYDOWN:
		if (wParam == VK_ESCAPE)
		{
			PostQuitMessage(0);
			IApplication::GetSingletonInstance<WindowApplication>()->Terminate();
		}
		break;
	case WM_CREATE:
	
		break;
	case WM_SIZE:
		IApplication::GetSingletonInstance()->Resize({ LOWORD(lParam), HIWORD(lParam) });

		return DefWindowProc(hWnd, message, wParam, lParam);
	case WM_DESTROY:
		PostQuitMessage(0);
		IApplication::GetSingletonInstance<WindowApplication>()->Terminate();
		break;

	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}