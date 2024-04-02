#pragma once

#include "Containers/DynamicArray.h";


//class MODULEAPI NameFactory : public Factory<Name, String> {};

/**
 * �̱��� ���丮 Ŭ����
 * @tparam Type ������ Ÿ��
 * @tparam Key �˻������̵� Ÿ��
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

