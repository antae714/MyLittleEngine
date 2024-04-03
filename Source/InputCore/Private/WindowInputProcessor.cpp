#include "WindowInputProcessor.h"

void WindowInputProcessor::ProcessInput()
{
	for (auto& item : windowInputArray)
	{
		String& KeyName = item.KeyName;
		EngineInput* iter = engineInputArray.Find([KeyName](EngineInput& element) { return element.KeyName == KeyName; });
		iter->IsKeyPressed = GetAsyncKeyState(item.KeyCode) & 0x8000;
	}
}

DynamicArray<EngineInput>* WindowInputProcessor::getEngineInputArray()
{
	return &engineInputArray;
}
