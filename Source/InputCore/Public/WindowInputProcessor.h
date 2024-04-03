#pragma once
#include "IInputProcessor.h"

/**
 * @brief Window OS���� ��ǲ�� ó���ϴ� ��ü�Դϴ�.
 */
class INPUTCOREMODULEAPI WindowInputProcessor : public IInputProcessor
{
public:
	/** ������κ��� �Է��� ó���ϴ� ����ü */
	struct WindowInput
	{
		// Window VKKeycode
		int KeyCode;
		// VKKeycode�� �ش��ϴ� �̸�
		String KeyName;
	};

	// Begin IInputProcessor Interface
	virtual void ProcessInput() override;
	virtual DynamicArray<EngineInput>* getEngineInputArray() override;
	// ~End IInputProcessor Interface

private:
	/** ��ϵ� Ű�ڵ常 �Է� ó���ϴ� �迭 */
	DynamicArray<WindowInput> windowInputArray;

	/** �������� ����� ������ �迭 */
	DynamicArray<EngineInput> engineInputArray;
};

