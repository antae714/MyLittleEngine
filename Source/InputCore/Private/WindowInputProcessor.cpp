#include "WindowInputProcessor.h"
#include "Misc/Config.h"
#include "InputSettings.h"

void WindowInputProcessor::Init()
{
	inputSettings = new InputSettings();
		//����ȭ ������ ���� Config��� 
	windowInputArray.Add(VK_UP, "Up");
	windowInputArray.Add(VK_DOWN, "Down");
	windowInputArray.Add(VK_LEFT, "Left");
	windowInputArray.Add(VK_RIGHT, "Right");

}

void WindowInputProcessor::ProcessInput()
{
	// ������ ��ǲ�� ��� �������´� �Է����� �ٲߴϴ�.
	// ������ �޼��� ������ ����
	for (size_t i = 0; i < windowInputArray.GetCount(); i++)
	{
		inputSettings->getInputData()[i].IsKeyPressed = GetAsyncKeyState(windowInputArray[i].VKeyCode) & 0x8000;
	}
}

InputSettings* WindowInputProcessor::getEngineInputArray()
{
	return inputSettings;
}
