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
		// Window VKeycode
		int VKeyCode;
		// VKKeycode�� �ش��ϴ� �̸�
		String KeyName;
	};

	// Begin IInputProcessor Interface
	virtual void Init() override;
	virtual void ProcessInput() override;
	virtual class InputSettings* getEngineInputArray() override;
	// ~End IInputProcessor Interface

private:
	/** ��ϵ� Ű�ڵ常 �Է� ó���ϴ� �迭 */
	DynamicArray<WindowInput> windowInputArray;

	/** �������� ����� ������ �迭 */
	class InputSettings* inputSettings;
};

