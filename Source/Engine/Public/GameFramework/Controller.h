#pragma once

#include "GameFramework/Actor.h"
#include "Containers/DynamicArray.h"
#include "Containers/String.h"
#include "Template/Function.h"
#include "InputSettings.h"
#include "Engine.h"


template <class T>
class InputDelegate;
template <class Ret, class... Arg>
class InputDelegate <Ret(Arg...)>
{
public:
	template <class _FunctionType>
	InputDelegate(_FunctionType&& function) : delegatefn(std::forward<_FunctionType>(function))
	{

	}
	virtual void Call(Arg... arg)
	{
		delegatefn(std::forward<Arg>(arg)...);
	}
	int keyCode = 0;
	Function<Ret(Arg...)> delegatefn;
};


class Pawn;

class ENGINEMODULEAPI Controller : public Actor
{
public:
	Controller();
	virtual ~Controller();

public:
	//void BindInput();
	void ProcessInput(class InputSettings* inputs);

	void Possess(Pawn* _pawn);
	void UnPossess();


	template<class T>
	T* GetPawn() { return (T*)GetPawn(); }
	Pawn* GetPawn();


	template <class Function, class... Arg>
	void BindInput(String inputName, Function _fuction, Arg&&... args)
	{
		auto temp = [_fuction, args...]() { std::invoke(_fuction, args...); };
		input.Add(temp);
		DynamicArray<InputActionData>& inputs = Engine::GEngine->GetInputSetting()->GetInputActionData();
		InputActionData* iter = inputs.Find([inputName](InputActionData& data) { return data.KeyName == inputName; });
		if (!iter) return;

		int index = iter - inputs.begin();


		input.Back()->keyCode = index;
	}

	template <class Function, class... Arg>
	void BindAxisInput(String inputName, Function _fuction, Arg&&... args)
	{
		auto temp = [_fuction, args...](float axis) { std::invoke(_fuction, args..., axis); };
		Axisinput.Add(temp);
		DynamicArray<InputAxisData>& inputs = Engine::GEngine->GetInputSetting()->GetInputAxisData();
		InputAxisData* iter = inputs.Find([inputName](InputAxisData& data) { return data.KeyName == inputName; });
		if (!iter) return;
		int index = iter - inputs.begin();


		Axisinput.Back()->keyCode = index;
	}

protected:
	Pawn* pawn;
	DynamicArray<InputDelegate<void()>> input;
	DynamicArray<InputDelegate<void(float)>> Axisinput;

};


