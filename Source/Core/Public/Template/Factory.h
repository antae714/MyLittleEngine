#pragma once

#include "Containers/DynamicArray.h";


//class MODULEAPI NameFactory : public Factory<Name, String> {};

/**
 * 싱글톤 팩토리 클래스
 * @tparam Type 생성할 타입
 * @tparam Key 검색기준이될 타입
 */
template <class Type, class Key>
class Factory
{
public:
	struct TypeElement
	{
		Type* value;
		Key key;
	};

	static DynamicArray<TypeElement>* GetElementArray()
	{
		static DynamicArray<TypeElement> InputProcessorArray;
		return &InputProcessorArray;
	}

	static Type* Get(Key key)
	{
		TypeElement* iter = GetElementArray()->Find([key](TypeElement& element) { return element.key == key; });
		return iter ? iter->value : nullptr;
	}
	static bool Remove(Key key)
	{
		return GetElementArray()->Remove([key](TypeElement& element) { return element.key == key; });
	}
	static void Add(Key key, Type* value)
	{
		TypeElement& element = GetElementArray()->Add();
		element.key = key;
		element.value = value;
	}
};

