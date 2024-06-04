#pragma once

#include "Containers/String.h"
#include "Template/Factory.h"


/**
 * @brief 인풋 처리자 인터페이스
 *
 * 이 클래스는 인풋을 처리하는 인터페이스를 정의합니다.
 */
class INPUTCOREMODULEAPI IInputProcessor
{
public:
	virtual ~IInputProcessor() = default;

public:
	virtual void Init() = 0;
	virtual void EndPlay() = 0;
	/** os의 인풋을 처리합니다. */
	virtual void ProcessInput() = 0;

    /**
     * @brief 처리된 인풋을 반환합니다.
     * @return 처리된 인풋을 담고 있는 동적 배열
     */
	virtual class InputSettings* GetEngineInputArray() = 0;
};

class INPUTCOREMODULEAPI InputProcessorFactory : public Factory<IInputProcessor, String> { };

