#pragma once

#include <type_traits>
#include "DynamicArray.h"
#include "Template/Function.h"

template <class... Params>
class Delegate
{
public:
	using FunctionType = Function<void(Params...)>;

	void Excute(Params... args)
	{
		for (auto& item : functionArray)
		{
			item((args)...);
		}
	}
	

	template<class FN, class Object>
	void Bind(FN _function, Object* object)
	{
		functionArray.Add([_function, object](Params&&... args) { std::invoke(_function, object, std::forward<Params>(args)...); });
	}
	void Bind(const FunctionType& function)
	{
		functionArray.Add(function);
	}

	template<class FN, class Object>
	void UnBind(FN _function, Object* object)
	{
		functionArray.Remove(FunctionType([_function, object](Params&&... args) { std::invoke(_function, object, std::forward<Params>(args)...); }));
	}
	void UnBind(const FunctionType& function)
	{
		functionArray.Remove(function);
	}

	void operator+=(const FunctionType& function)
	{
		Bind(function);
	}

	void operator-=(const FunctionType& function)
	{
		UnBind(function);
	}

private:
	DynamicArray<FunctionType> functionArray;
};
