#pragma once

#include "Containers/String.h"
#include "Containers/DynamicArray.h"
#include "Template/Factory.h"

// 입력 처리를 데이터화한 구조체
struct EngineInput
{
	// VKKeycode에 해당하는 이름
	String KeyName;
	// 해당 키가 눌렸는지 여부
	bool IsKeyPressed;
};

class INPUTCOREMODULEAPI IInputProcessor
{
public:
	virtual void ProcessInput() = 0;
	virtual const DynamicArray<EngineInput>& getEngineInputArray() = 0;
};

class INPUTCOREMODULEAPI InputProcessorFactory : public Factory<IInputProcessor, String> { };

