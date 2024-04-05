#pragma once

#include "GameFramework/Actor.h"

/**
 * 폰입니다.
 * 컨트롤러가 붙을수있습니다.
 */
class ENGINEMODULEAPI Pawn : public Actor
{
public:
	Pawn();
	virtual ~Pawn();


	virtual void BindInput(class Controller* controller);

private:

};

