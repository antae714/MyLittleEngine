#include "WindowInputProcessor.h"

void WindowInputProcessor::ProcessInput()
{
	// 윈도우 인풋을 모두 엔진에맞는 입력으로 바꿉니다.
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
