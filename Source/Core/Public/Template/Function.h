#pragma once

#include <type_traits>
/**
 * 함수 겍체의 기본 클래스입니다.
 * 이 클래스는 함수 개체에 대한 인터페이스를 정의합니다.
 */
template <class Ret, class... Arg>
class FunctionBase
{
public:
	virtual ~FunctionBase() = default;

	/** 함수를 호출합니다. */
	virtual Ret Call(Arg&&... arg) = 0;

	/** 함수 객체의 멤버가 동일한지 비교합니다. */
	virtual bool Compare(const FunctionBase<Ret, Arg...>& other) const = 0;

	/** 깊은 복사본을 생성합니다. */
	virtual FunctionBase<Ret, Arg...>* Clone() const = 0;
};

/**
 * 함수 개체에 대한 구현 클래스입니다.
 * 이 클래스는 기능 객체에 대한 기능을 구현합니다.
 */
template <class Function, class Ret, class... Arg >
class FunctionImplement : public FunctionBase<Ret, Arg...>
{
public:
	using THISCLASS = FunctionImplement<Function, Ret, Arg...>;
	static_assert(!std::is_reference_v<Function>);
	//using CFunctionType = std::remove_reference<Function>::type;
	using FunctionType = std::remove_const<Function >::type;

public:
	/**
	 *
	 */
	FunctionImplement(Function& _function) : function(nullptr)
	{
		function = new FunctionType(std::forward<Function>(_function));
	}
	FunctionImplement(Function&& _function) : function(nullptr)
	{
		function = new FunctionType(std::forward<Function>(_function));
	}

	virtual ~FunctionImplement()
	{
		delete function;
	}

public:

	// Begin FunctionBase Interface
	virtual Ret Call(Arg&&... arg) override
	{
		static_assert(std::is_invocable_v< FunctionType, Arg...>, "함수 시그니처 불일치");
		return std::invoke(*function, std::forward<Arg>(arg)...);
	}

	virtual bool Compare(const FunctionBase<Ret, Arg...>& other) const
	{
		const THISCLASS* otherImplement = reinterpret_cast<const THISCLASS*>(&other);
		return !memcmp(function, otherImplement->function, sizeof(*function));
	}

	virtual FunctionBase<Ret, Arg...>* Clone() const override
	{
		return new THISCLASS(*function);
	}
	// ~End FunctionBase Interface

private:
	FunctionType* function;
};

/**
 * 함수 개체에 대한 클래스입니다.
 * 이 클래스는 기능 개체를 관리하고 해당 기능에 대한 액세스를 제공합니다.
 */
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

		function = new FunctionImplement< std::remove_reference<FunctionType>::type, Ret, Arg...>(std::forward<FunctionType>(_function));
	}

	void Copy(const FunctionClass<Ret, Arg...>& other)
	{
		//function = new FunctionImplement<FunctionType, Ret, Arg...>(std::forward<FunctionType>(other.function));
		function = other.function->Clone();
	}

public:
	Ret operator()(Arg... arg)
	{
		if (!function) return;
		return function->Call(std::forward<Arg>(arg)...);
	}

	bool operator==(const FunctionClass<Ret, Arg...>& other) const
	{
		return function->Compare(*other.function);
	}

protected:
	FunctionBase<Ret, Arg...>* function;
};

/**
 * 함수 구현 유형을 가져오는 도우미 클래스입니다.
 */
template <class T>
class GetFunctionImplement;
template <class Ret, class... Arg>
class GetFunctionImplement <Ret(Arg...)>
{
public:
	using Type = FunctionClass<Ret, Arg...>;
};

/**
 * 함수 객체입니다.
 * 함수를 생성하기위해 사용합니다.
 */
template <class Type>
class Function : public GetFunctionImplement<Type>::Type
{
public:
	using Base = GetFunctionImplement<Type>::Type;

public:
	Function() = default;
	virtual ~Function() = default;

	Function(const Function<Type>& other)
	{
		this->Copy(other);
	}

	template <class FunctionType>
	Function(FunctionType&& _function)
	{
		static_assert(!std::is_base_of_v<Base, FunctionType>, "함수객체가 함수객체를 호출함...");

		this->Set(std::forward<FunctionType>(_function));
	}
};


template <class Ret, class... Params>
class Binder
{
private:
	Binder() = delete;
public:
	template<class FN, class Object>
	static Function<Ret(Params...)> Bind(FN _function, Object* object)
	{
		return [_function, object](Params&&... args) { std::invoke(_function, object, std::forward<Params>(args)...); };
	}
};