#pragma once

#include "Containers/DynamicArray.h"
#include "Containers/String.h"

struct INPUTCOREMODULEAPI InputData
{
	/** �Է¿� �ش��ϴ� �̸� */
	String KeyName;
	/** ��ǲ ���� */
	bool IsKeyPressed;
};

class INPUTCOREMODULEAPI InputSettings
{
public:
	InputSettings();

public:
	DynamicArray<InputData>& getInputData();

private:
	DynamicArray<InputData> inputArray;
};


