#pragma once

#include "GameFramework/PlayerController.h"


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
};

