#pragma once

#include "Containers/String.h"
#include "Containers/DynamicArray.h"
#include "Template/Factory.h"

// �Է� ó���� ������ȭ�� ����ü
struct EngineInput
{
	// VKKeycode�� �ش��ϴ� �̸�
	String KeyName;
	// �ش� Ű�� ���ȴ��� ����
	bool IsKeyPressed;
};

class INPUTCOREMODULEAPI IInputProcessor
{
public:
	virtual void ProcessInput() = 0;
	virtual const DynamicArray<EngineInput>& getEngineInputArray() = 0;
};

class INPUTCOREMODULEAPI InputProcessorFactory : public Factory<IInputProcessor, String> { };

