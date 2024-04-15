#include "WindowInputProcessor.h"
#include "Misc/Config.h"
#include "InputSettings.h"

void WindowInputProcessor::Init()
{
	inputSettings = new InputSettings();
		//직렬화 구현시 변경 Config사용 
	windowInputArray.Add(VK_UP, "Up");
	windowInputArray.Add(VK_DOWN, "Down");
	windowInputArray.Add(VK_LEFT, "Left");
	windowInputArray.Add(VK_RIGHT, "Right");

}

void WindowInputProcessor::ProcessInput()
{
	MSG msg;
	if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
	{
		DispatchMessage(&msg);
	}

	for (size_t i = 0; i < windowInputArray.GetCount(); i++)
	{
		inputSettings->getInputData()[i].IsKeyPressed = GetAsyncKeyState(windowInputArray[i].VKeyCode) & 0x8000;
	}
}

InputSettings* WindowInputProcessor::getEngineInputArray()
{
	return inputSettings;
}
