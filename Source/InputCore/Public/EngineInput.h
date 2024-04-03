#pragma once

#include "Containers/String.h"


/** 입력 처리를 데이터화한 구조체 */
struct EngineInput
{
	/** 입력에 해당하는 이름 */
	String KeyName;
	/** 인풋 여부 */
	bool IsKeyPressed;
};


