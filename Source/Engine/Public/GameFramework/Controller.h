#pragma once

#include "GameFramework/Actor.h"
#include "Containers/DynamicArray.h"
#include "Template/Function.h"


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
	void processInput(DynamicArray<struct EngineInput>* inputs);

	Pawn* getPawn();
	void setPawn(Pawn* _pawn);


	template<class T>
	T* getPawn() { return (T*)getPawn(); }

	template <class Function, class... Arg>
	void bind(int inputid, Function _fuction, Arg&&... args)
	{
		auto temp = [_fuction, args...]() { invoke(_fuction, args...); };
		input.Add(temp);
		input.Back()->keyCode = inputid;
	}

	template <class Function, class... Arg>
	void bindAxis(int inputid, Function _fuction, Arg&&... args)
	{
		auto temp = [_fuction, args...](float axis) { invoke(_fuction, args..., axis); };
		Axisinput.Add(temp);
		Axisinput.Back()->keyCode = inputid;
	}

	void Exec(int execKeyCode, float value);



private:
	Pawn* pawn;
	DynamicArray<InputDelegate<void()>> input;
	DynamicArray<InputDelegate<void(float)>> Axisinput;
};


