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
	DynamicArray<InputAxisData>& inputAxisArray = inputs->GetInputAxisData();
	for (auto& item : Axisinput)
	{
		item.Call(inputAxisArray[item.keyCode].KeyValue);
	}

	DynamicArray<InputActionData>& inputActionArray = inputs->GetInputActionData();
	for (auto& item : input)
	{
		if (inputActionArray[item.keyCode].IsKeyPressed)
		{
			item.Call();
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
	input.Clear();
	Axisinput.Clear();
}

Pawn* Controller::GetPawn()
{
	return pawn;
}
