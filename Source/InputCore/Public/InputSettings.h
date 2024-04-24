#pragma once

#include "Containers/DynamicArray.h"
#include "Containers/String.h"

struct INPUTCOREMODULEAPI InputActionData
{
	/** 입력에 해당하는 이름 */
	String KeyName;
	/** 인풋 여부 */
	bool IsKeyPressed;
};

struct INPUTCOREMODULEAPI InputAxisData
{
	/** 입력에 해당하는 이름 */
	String KeyName;
	/** 인풋 여부 */
	float KeyValue;
};

class INPUTCOREMODULEAPI InputSettings
{
public:
	InputSettings();

public:
	DynamicArray<InputActionData>& GetInputActionData() { return inputActionArray; }
	DynamicArray<InputAxisData>& GetInputAxisData() { return inputAxisArray; }

private:
	DynamicArray<InputActionData> inputActionArray;
	DynamicArray<InputAxisData> inputAxisArray;
};


