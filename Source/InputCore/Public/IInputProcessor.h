#pragma once

#include "Containers/String.h"
#include "Containers/DynamicArray.h"
#include "Template/Factory.h"
#include "EngineInput.h"


/**
 * @brief ��ǲ ó���� �������̽�
 *
 * �� Ŭ������ ��ǲ�� ó���ϴ� �������̽��� �����մϴ�.
 */
class INPUTCOREMODULEAPI IInputProcessor
{
public:
	/** os�� ��ǲ�� ó���մϴ�. */
	virtual void ProcessInput() = 0;

    /**
     * @brief ó���� ��ǲ�� ��ȯ�մϴ�.
     * @return ó���� ��ǲ�� ��� �ִ� ���� �迭
     */
	virtual DynamicArray<EngineInput>* getEngineInputArray() = 0;
};

class INPUTCOREMODULEAPI InputProcessorFactory : public Factory<IInputProcessor, String> { };

