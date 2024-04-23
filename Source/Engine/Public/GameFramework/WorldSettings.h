#pragma once

#include "GameFramework/PlayerController.h"
#include "GameFramework/Character.h"


/**
 * @brief 월드 설정 객체입니다.
 */
class ENGINEMODULEAPI WorldSettings
{
public:
	WorldSettings();
	virtual  ~WorldSettings();
public:
	/** 월드에서 쓸 플레이어 컨트롤러 입니다. */
	class PlayerController* playerController;
	class Character* playerCharacter;
};

