#include "GameFramework/Controller.h"
#include "GameFramework/Pawn.h"


Controller::Controller()
{
}

Controller::~Controller()
{
}

void Controller::processInput()
{
}

Pawn* Controller::getPawn()
{
    return pawn;
}

void Controller::setPawn(Pawn* _pawn)
{
    pawn = _pawn;
}

void Controller::Exec(int execKeyCode, float value)
{
	for (auto& i : input)
	{
		if (i.keyCode == execKeyCode)
		{
			i.Call();
		}
	}
	for (auto& i : Axisinput)
	{
		if (i.keyCode == execKeyCode)
		{
			i.Call(value);
		}
	}
}
