#pragma once
#include "IInputProcessor.h"

class INPUTCOREMODULEAPI WindowInputProcessor : public IInputProcessor
{
public:
	// 윈도우로부터 입력을 처리하는 구조체
	struct WindowInput
	{
		// Window VKKeycode
		int KeyCode;
		// VKKeycode에 해당하는 이름
		String KeyName;
	};

	// Begin IInputProcessor Interface
	virtual void ProcessInput() override;
	virtual const DynamicArray<EngineInput>& getEngineInputArray() override;
	// ~End IInputProcessor Interface

private:
	// 등록된 키코드만 입력 처리하는 배열
	DynamicArray<WindowInput> windowInputArray;

	// 엔진에서 사용할 데이터 배열
	DynamicArray<EngineInput> engineInputArray;
};

