#pragma once

#include "Containers/DynamicArray.h";

//���� ����� vvv
//class MODULEAPI NameFactory : public Factory<Name, String> {};
//���� ����� ^^^

/**
 * @brief �̱��� ���丮 Ŭ����
 * 
 * @tparam Type ������ Ÿ��
 * @tparam Key �˻������̵� Ÿ��
 */
template <class Type, class Key>
class Factory
{
public:
	/** ��ü ������ ���� ���� ����Ʈ ������ ���� */
	Factory() = delete;

public: 
	/** �迭�� ����� ��Ҹ� ��� ����ü */
	struct TypeElement
	{
		Type* value;
		Key key;
	};

	/**
	 * @brief �̱��� �迭�� ��ȯ�մϴ�.
	 * 
	 * @return ���� �迭�� ������
	 */
	static DynamicArray<TypeElement>* GetElementArray()
	{
		// ������ �����մϴ�.
		static DynamicArray<TypeElement> InputProcessorArray;
		return &InputProcessorArray;
	}

	/**
	 * @brief �迭���� Ư�� Ű�� ���� ��Ҹ� ã�� ��ȯ�մϴ�.
	 * 
	 * @param key ã���� �ϴ� ����� Ű
	 * @return �ش� Ű�� ���� ����� ������
	 */
	static Type* Get(Key key)
	{
		TypeElement* iter = GetElementArray()->Find([key](TypeElement& element) { return element.key == key; });
		return iter ? iter->value : nullptr;
	}
	
	/**
	 * @brief �迭���� Ư�� Ű�� ���� ��Ҹ� �����մϴ�.
	 *
	 * @param key �����ϰ��� �ϴ� ����� Ű
	 * @return ��Ұ� ���������� ���ŵǾ����� ����
	 */
	static bool Remove(Key key)
	{
		return GetElementArray()->Remove([key](TypeElement& element) { return element.key == key; });
	}

	/**
	 * @brief �迭�� ���ο� ��Ҹ� �߰��մϴ�.
	 *
	 * @param key �߰��� ����� Ű
	 * @param value �߰��� ����� ��
	 */
	static void Add(Key key, Type* value)
	{
		TypeElement& element = GetElementArray()->Add();
		element.key = key;
		element.value = value;
	}
};

