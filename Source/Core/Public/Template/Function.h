#pragma once

#include <type_traits>

template <class Ret, class... Arg>
class FunctionBase
{
public:
	virtual ~FunctionBase()
	{

	}

	virtual Ret Call(Arg&&... arg) = 0;
};

template <class Function, class Ret, class... Arg >
class FunctionImplement : public FunctionBase<Ret, Arg...>
{
public:
	using FunctionType = std::remove_reference<Function>::type;

	FunctionImplement(Function&& _function) : function(nullptr)
	{
		//?????????????????????
		function = new FunctionType(std::forward<Function>(_function));
	}

	virtual ~FunctionImplement()
	{
		//?????????????????????
		delete function;
	}

	virtual Ret Call(Arg&&... arg) override
	{
		return std::invoke(*function, std::forward<Arg>(arg)...);
	}

	FunctionType* function;
};

template <class Ret, class... Arg>
class FunctionClass
{
protected:
	virtual ~FunctionClass()
	{
		delete function;
	}

	template <class FunctionType>
	void Set(FunctionType&& _function)
	{
		function = new FunctionImplement<FunctionType, Ret, Arg...>(std::forward<FunctionType>(_function));
	}

	template <class FunctionType>
	void Copy(const FunctionClass<Ret, Arg...>& other)
	{
		function = new FunctionImplement<FunctionType, Ret, Arg...>(std::forward<FunctionType>(other.function));

	}
public:
	Ret operator()(Arg... arg)
	{
		if (!function) return;
		return function->Call(std::forward<Arg>(arg)...);
	}

protected:
	FunctionBase<Ret, Arg...>* function;
};


template <class T>
class GetFunctionImplement;
template <class Ret, class... Arg>
class GetFunctionImplement <Ret(Arg...)>
{
public:
	using Type = FunctionClass<Ret, Arg...>;


};


template <class Type>
class Function : public GetFunctionImplement<Type>::Type
{
public:
	using Base = GetFunctionImplement<Type>::Type;
public:
	Function() = default;

	template <class FunctionType>
	Function(const FunctionType& _function)
	{
		this->Copy(std::forward<FunctionType>(_function));
	}
	

	template <class FunctionType>
	Function(FunctionType&& _function)
	{
		this->Set(std::forward<FunctionType>(_function));
	}
	virtual ~Function()
	{
	}


};