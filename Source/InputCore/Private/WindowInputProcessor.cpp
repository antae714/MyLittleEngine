#include "WindowInputProcessor.h"
#include "Misc/Config.h"
#include "InputSettings.h"
#include <cassert>

WindowInputProcessor::WindowInputProcessor() : inputSettings(nullptr)
{
}

WindowInputProcessor::~WindowInputProcessor()
{
	assert(!inputSettings);
}

void WindowInputProcessor::Init()
{
	inputSettings = new InputSettings();
		//직렬화 구현시 변경 Config사용 
	windowInputActionArray.Add(VK_UP, "Up");
	windowInputActionArray.Add(VK_DOWN, "Down");
	windowInputActionArray.Add(VK_LEFT, "Left");
	windowInputActionArray.Add(VK_RIGHT, "Right");

	windowInputAxisArray.Add(VK_RIGHT, VK_LEFT, "Left/Right");
}

void WindowInputProcessor::EndPlay()
{
	delete inputSettings;
	inputSettings = nullptr;
}

void WindowInputProcessor::ProcessInput()
{
	MSG msg;

	while (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
	{
		DispatchMessage(&msg);
	}

	for (size_t i = 0; i < windowInputActionArray.GetCount(); i++)
	{
		inputSettings->GetInputActionData()[i].IsKeyPressed = GetAsyncKeyState(windowInputActionArray[i].VKeyCode) & 0x8000;
	}

	for (size_t i = 0; i < windowInputAxisArray.GetCount(); i++)
	{
		InputAxisData& inputAxisData = inputSettings->GetInputAxisData()[i];
		inputAxisData.KeyValue = (GetAsyncKeyState(windowInputAxisArray[i].positiveVKeyCode) & 0x8000) ? 1.0f : 0.0f;
		inputAxisData.KeyValue += (GetAsyncKeyState(windowInputAxisArray[i].negativeVKeyCode) & 0x8000) ? -1.0f : 0.0f;

	}

}

InputSettings* WindowInputProcessor::GetEngineInputArray()
{
	return inputSettings;
}
