#pragma once

#include "Containers/String.h"
#include "Template/Factory.h"


/**
 * @brief ��ǲ ó���� �������̽�
 *
 * �� Ŭ������ ��ǲ�� ó���ϴ� �������̽��� �����մϴ�.
 */
class INPUTCOREMODULEAPI IInputProcessor
{
public:
	virtual ~IInputProcessor() = default;

public:
	virtual void Init() = 0;
	virtual void EndPlay() = 0;
	/** os�� ��ǲ�� ó���մϴ�. */
	virtual void ProcessInput() = 0;

    /**
     * @brief ó���� ��ǲ�� ��ȯ�մϴ�.
     * @return ó���� ��ǲ�� ��� �ִ� ���� �迭
     */
	virtual class InputSettings* GetEngineInputArray() = 0;
};

class INPUTCOREMODULEAPI InputProcessorFactory : public Factory<IInputProcessor, String> { };

