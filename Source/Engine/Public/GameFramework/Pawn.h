#pragma once

#include "GameFramework/Actor.h"

/**
 * ���Դϴ�.
 * ��Ʈ�ѷ��� �������ֽ��ϴ�.
 */
class ENGINEMODULEAPI Pawn : public Actor
{
public:
	Pawn();
	virtual ~Pawn();


	virtual void BindInput(class Controller* controller);

private:

};

