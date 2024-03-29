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
