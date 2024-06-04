#pragma once
#include "IInputProcessor.h"

/** ������κ��� �Է��� ó���ϴ� ����ü */
struct WindowInputAction
{
	/** Window VKeycode */ 
	int VKeyCode;
	/** VKKeycode�� �ش��ϴ� Action �̸� */
	String KeyName;
};

struct WindowInputAxis
{
	int positiveVKeyCode;
	int negativeVKeyCode;
	/** Axis �̸� */
	String KeyName;
};


/**
 * @brief Window OS���� ��ǲ�� ó���ϴ� ��ü�Դϴ�.
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
	/** ��ϵ� Ű�ڵ常 �Է� ó���ϴ� �迭 */
	DynamicArray<WindowInputAction> windowInputActionArray;
	DynamicArray<WindowInputAxis> windowInputAxisArray;

	/** �������� ����� ������ �迭 */
	class InputSettings* inputSettings;

	
};

