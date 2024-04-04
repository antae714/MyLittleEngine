#pragma once
#include "IInputProcessor.h"

/**
 * @brief Window OS에서 인풋을 처리하는 객체입니다.
 */
class INPUTCOREMODULEAPI WindowInputProcessor : public IInputProcessor
{
public:
	/** 윈도우로부터 입력을 처리하는 구조체 */
	struct WindowInput
	{
		// Window VKeycode
		int VKeyCode;
		// VKKeycode에 해당하는 이름
		String KeyName;
	};

	// Begin IInputProcessor Interface
	virtual void Init() override;
	virtual void ProcessInput() override;
	virtual class InputSettings* getEngineInputArray() override;
	// ~End IInputProcessor Interface

private:
	/** 등록된 키코드만 입력 처리하는 배열 */
	DynamicArray<WindowInput> windowInputArray;

	/** 엔진에서 사용할 데이터 배열 */
	class InputSettings* inputSettings;
};

