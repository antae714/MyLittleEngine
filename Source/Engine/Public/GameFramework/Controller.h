#pragma once

#include "GameFramework/Actor.h"

#ifdef IF_USE_STL...
class InputData
{
public:
	template<class ClASS, class Function>
	void bind(ClASS* obj, Function _fn)
	{
		fn = [obj, _fn]() { invoke(_fn, obj); };
	}
	template<class ClASS, class Function>
	void bind(shared_ptr<ClASS> obj, Function _fn)
	{
		fn = [obj, _fn]() { invoke(_fn, obj); };
	}
	function<void()> fn;
};

#endif // IF_USE_STL...

class Pawn;

class ENGINEMODULEAPI Controller : public Actor
{
public:
	Controller();
	~Controller();

public:
	//void BindInput();
	void processInput();

	Pawn* getPawn();
	void setPawn(Pawn* _pawn);


	template<class T>
	T* getPawn();


private:
	Pawn* pawn;
};

template<class T>
inline T* Controller::getPawn()
{
	return (T*)getPawn();
}
