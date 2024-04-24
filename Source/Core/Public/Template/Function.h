#pragma once

#include <type_traits>
/**
 * �Լ� ��ü�� �⺻ Ŭ�����Դϴ�.
 * �� Ŭ������ �Լ� ��ü�� ���� �������̽��� �����մϴ�.
 */
template <class Ret, class... Arg>
class FunctionBase
{
public:
	virtual ~FunctionBase() = default;

	/** �Լ��� ȣ���մϴ�. */
	virtual Ret Call(Arg&&... arg) = 0;

	/** �Լ� ��ü�� ����� �������� ���մϴ�. */
	virtual bool Compare(const FunctionBase<Ret, Arg...>& other) const = 0;

	/** ���� ���纻�� �����մϴ�. */
	virtual FunctionBase<Ret, Arg...>* Clone() const = 0;
};

/**
 * �Լ� ��ü�� ���� ���� Ŭ�����Դϴ�.
 * �� Ŭ������ ��� ��ü�� ���� ����� �����մϴ�.
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
		static_assert(std::is_invocable_v< FunctionType, Arg...>, "�Լ� �ñ״�ó ����ġ");
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
 * �Լ� ��ü�� ���� Ŭ�����Դϴ�.
 * �� Ŭ������ ��� ��ü�� �����ϰ� �ش� ��ɿ� ���� �׼����� �����մϴ�.
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
 * �Լ� ���� ������ �������� ����� Ŭ�����Դϴ�.
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
 * �Լ� ��ü�Դϴ�.
 * �Լ��� �����ϱ����� ����մϴ�.
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
		static_assert(!std::is_base_of_v<Base, FunctionType>, "�Լ���ü�� �Լ���ü�� ȣ����...");

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