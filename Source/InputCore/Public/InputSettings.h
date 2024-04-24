#pragma once

#include "Containers/DynamicArray.h"
#include "Containers/String.h"

struct INPUTCOREMODULEAPI InputActionData
{
	/** �Է¿� �ش��ϴ� �̸� */
	String KeyName;
	/** ��ǲ ���� */
	bool IsKeyPressed;
};

struct INPUTCOREMODULEAPI InputAxisData
{
	/** �Է¿� �ش��ϴ� �̸� */
	String KeyName;
	/** ��ǲ ���� */
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


