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
	// 윈도우 인풋을 모두 엔진에맞는 입력으로 바꿉니다.
	// 윈도우 메세지 구현시 변경
	for (size_t i = 0; i < windowInputArray.GetCount(); i++)
	{
		inputSettings->getInputData()[i].IsKeyPressed = GetAsyncKeyState(windowInputArray[i].VKeyCode) & 0x8000;
	}
}

InputSettings* WindowInputProcessor::getEngineInputArray()
{
	return inputSettings;
}
