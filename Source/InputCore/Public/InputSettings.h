#pragma once

#include "Containers/DynamicArray.h"
#include "Containers/String.h"

struct INPUTCOREMODULEAPI InputData
{
	/** 입력에 해당하는 이름 */
	String KeyName;
	/** 인풋 여부 */
	bool IsKeyPressed;
};

class InputSettings
{
public:
	INPUTCOREMODULEAPI InputSettings();

public:
	INPUTCOREMODULEAPI DynamicArray<InputData>& getInputData();

private:
	DynamicArray<InputData> inputArray;
};


