#pragma once

#include "GameFramework/PlayerController.h"
#include "GameFramework/Character.h"


/**
 * @brief ���� ���� ��ü�Դϴ�.
 */
class ENGINEMODULEAPI WorldSettings
{
public:
	WorldSettings();
	virtual  ~WorldSettings();
public:
	/** ���忡�� �� �÷��̾� ��Ʈ�ѷ� �Դϴ�. */
	class PlayerController* playerController;
	class Character* playerCharacter;
};

