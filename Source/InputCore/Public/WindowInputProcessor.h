#pragma once
#include "IInputProcessor.h"

/** 윈도우로부터 입력을 처리하는 구조체 */
struct WindowInputAction
{
	/** Window VKeycode */ 
	int VKeyCode;
	/** VKKeycode에 해당하는 Action 이름 */
	String KeyName;
};

struct WindowInputAxis
{
	int positiveVKeyCode;
	int negativeVKeyCode;
	/** Axis 이름 */
	String KeyName;
};


/**
 * @brief Window OS에서 인풋을 처리하는 객체입니다.
 */
class INPUTCOREMODULEAPI WindowInputProcessor : public IInputProcessor
{
public:
	WindowInputProcessor();
	virtual ~WindowInputProcessor();

public:
	// Begin IInputProcessor Interface
	virtual void Init() override;
	virtual void EndPlay() override;
	virtual void ProcessInput() override;
	virtual class InputSettings* GetEngineInputArray() override;
	// ~End IInputProcessor Interface

private:
	/** 등록된 키코드만 입력 처리하는 배열 */
	DynamicArray<WindowInputAction> windowInputActionArray;
	DynamicArray<WindowInputAxis> windowInputAxisArray;

	/** 엔진에서 사용할 데이터 배열 */
	class InputSettings* inputSettings;

	
};

