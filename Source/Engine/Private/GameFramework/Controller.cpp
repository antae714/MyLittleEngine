#include "GameFramework/Controller.h"
#include "GameFramework/Pawn.h"


Controller::Controller()
{
}

Controller::~Controller()
{
}

void Controller::ProcessInput(InputSettings* inputs)
{
	DynamicArray<InputData>& inputDataArray = inputs->getInputData();
	for (size_t i = 0; i < inputDataArray.GetCount(); i++)
	{
		if (inputDataArray[i].IsKeyPressed)
		{
			Exec(i, 1.0f);
		}
	}
}

void Controller::Possess(Pawn* _pawn)
{
	pawn = _pawn;
	pawn->BindInput(this);
}

void Controller::UnPossess()
{
	pawn = nullptr;
}

Pawn* Controller::GetPawn()
{
	return pawn;
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
