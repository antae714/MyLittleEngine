#pragma once

#include "GameFramework/Actor.h"
#include "Containers/DynamicArray.h"
#include "Containers/String.h"
#include "Template/Function.h"
#include "InputSettings.h"


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
	void processInput(class InputSettings* inputs);

	void Possess(Pawn* _pawn);
	void UnPossess();


	template<class T>
	T* getPawn() { return (T*)getPawn(); }
	Pawn* getPawn();


	template <class Function, class... Arg>
	void bind(String inputName, Function _fuction, Arg&&... args)
	{
		auto temp = [_fuction, args...]() { invoke(_fuction, args...); };
		input.Add(temp);
		DynamicArray<InputData>* inputs = GEngine->GetInputSetting()->getInputData();
		InputData* iter = inputs->Find([inputName](InputData& data) { data.KeyName == inputName; });

		int index = iter - inputs->begin();


		Axisinput.Back()->keyCode = index;
	}

	template <class Function, class... Arg>
	void bindAxis(String inputName, Function _fuction, Arg&&... args)
	{
		auto temp = [_fuction, args...](float axis) { invoke(_fuction, args..., axis); };
		Axisinput.Add(temp);
		DynamicArray<InputData>* inputs = GEngine->GetInputSetting()->getInputData();
		InputData* iter = inputs->Find([inputName](InputData& data) { data.KeyName == inputName; });
		
		int index = iter - inputs->begin();


		Axisinput.Back()->keyCode = index;
	}

	void Exec(int execKeyCode, float value);



protected:
	Pawn* pawn;
	DynamicArray<InputDelegate<void()>> input;
	DynamicArray<InputDelegate<void(float)>> Axisinput;

};


