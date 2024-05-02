#pragma once

#include "Containers/DynamicArray.h";

//���� ����� vvv
//class MODULEAPI NameFactory : public Factory<Name, String> {};
//���� ����� ^^^

struct ObjectCreator
{
	ObjectCreator(const type_info& key) : key(key) {}
	virtual  void* NewFunction() = 0;

	const type_info& key;
};

template <class T>
struct TypedObjectCreator : public ObjectCreator
{
	TypedObjectCreator(const type_info& key) : ObjectCreator(key) {}
	virtual void* NewFunction() { return new T(); }
};


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
		TypeElement() : value(nullptr), key() {}
		~TypeElement() { if (value) delete value; }
		ObjectCreator* value;
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
		return iter ? (Type*)iter->value->NewFunction() : nullptr;
	}
	
	static bool Has(Key key)
	{
		TypeElement* iter = GetElementArray()->Find([key](TypeElement& element) { return element.key == key; });
		return !!iter;
	}


	/**
	 * @brief �迭���� Ư�� Ű�� ���� ��Ҹ� �����մϴ�.
	 *
	 * @param key �����ϰ��� �ϴ� ����� Ű
	 * @return ��Ұ� ���������� ���ŵǾ����� ����
	 */
	static bool Remove(Key key)
	{
		if (!Has(key)) return false;

		GetElementArray()->Remove([key](TypeElement& element) { return element.key == key; });
		return true;
	}

	/**
	 * @brief �迭�� ���ο� ��Ҹ� �߰��մϴ�.
	 *
	 * @param key �߰��� ����� Ű
	 * @param value �߰��� ����� ��
	 */
	template<class T>
	static void Add(Key key)
	{
		TypeElement& element = GetElementArray()->Add();
		element.key = key;
		element.value = new TypedObjectCreator<T>(typeid(T));
	}
};




/*


struct ObjectCreator
{
	template <class T>
	static T* CreateObject(T* original = nullptr);

protected:
	ObjectCreator(const type_info& key) : key(key) {}
	virtual  void* NewFunction() = 0;

	static DynamicArray<ObjectCreator*> ObjectCreatorArray;

	const type_info& key;

};

template <class T>
struct TypedObjectCreator : public ObjectCreator
{
public:
	TypedObjectCreator(const type_info& key) : ObjectCreator(key) {}
	virtual void* NewFunction() { return new T(); }
};

DynamicArray<ObjectCreator*> ObjectCreator::ObjectCreatorArray;

template<class T>
T* ObjectCreator::CreateObject(T* original)
{
	const type_info& typeKey = original ? typeid(*original) : typeid(T);
	ObjectCreator** iter = ObjectCreatorArray.Find(
		[&typeKey](ObjectCreator*& element) { return element->key == typeKey; }
	);

	if (iter)
	{
		return (T*)(*iter)->NewFunction();
	}
	else
	{
		return (T*)ObjectCreatorArray.Add(new TypedObjectCreator<T>(typeKey))->NewFunction();
	}
}

*/