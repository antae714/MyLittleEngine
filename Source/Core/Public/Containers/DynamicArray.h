#pragma once

#include <type_traits>
#include <stdexcept>

// ���ø��� dll���� ������� ������ �߻��ϴ� ���
// ���ø� �Լ��� ����� �ش� ������Ʈ���� �����ϱ⿡
// �ܺ� dll, exe���� ������������ �Լ� ���Ұ���
// ���������ڷ� �ܺο��� ���ø��� ���� ������ �ϸ� ��κ� �ذᰡ��
// �̰� �Ǽ��ϸ� Ȯ���Ҽ����� �ܺ����� �������� �����صα�
#pragma warning(disable : 4251)


/**
 * @brief ���� �迭 Ŭ�����Դϴ�.
 * @tparam ElementType �迭�� ����Ǵ� ����� Ÿ���Դϴ�.
 */
template <class ElementType>
class DynamicArray
{
public:
	using Iterator = ElementType*;

	/** ��Ұ� Ŭ���� Ÿ������ ���� */
	static constexpr bool IsElementClassType = std::is_class<ElementType>::value;

public:
	DynamicArray() : data(nullptr), count(0), capacity(0)
	{
	}

	DynamicArray(std::initializer_list<ElementType>&& list) : data(nullptr), count(0), capacity(0)
	{
		for (auto& i : list)
		{
			Add(i);
		}
	}

	~DynamicArray();


public:
	/** ����� ũ�� (����Ʈ) */
	//static constexpr int ElementSize = sizeof(ElementType);
	/**
	 * @brief ����� ũ�⸦ ��ȯ �մϴ�.
	 * @return ����� ũ�� (����Ʈ)
	 */
	static constexpr unsigned int GetTypeSize() { return sizeof(ElementType); }

	/**
	 * @brief �迭�� ���� ��Ҹ� �߰��մϴ�.
	 * @param value �߰��� ����� �� �Ǵ� �������Դϴ�.
	 * @return �߰��� ����� ���۷���
	 */
	template<class ...VarType>
	ElementType& Add(VarType&&... value) { return _Add(std::forward<VarType>(value)...); }

	/**
	 * @brief �迭�� Ư�� �ε����� ��Ҹ� �����մϴ�.
	 * @param index ������ ��ġ�� �ε����Դϴ�.
	 * @param value ������ ����� �� �Ǵ� �������Դϴ�.
	 * @return ���Ե� ����� ���۷���
	 */
	template<class ...VarType>
	ElementType& Insert(int index, VarType&&... value) { return _Insert(index, std::forward<VarType>(value)...); }

	/**
	 * @brief �迭���� Ư�� �ε����� ��Ҹ� �����մϴ�.
	 * @param index ������ ����� �ε����Դϴ�.
	 */
	void RemoveIndex(int index) { Remove(data + index); }

	/**
	 * @brief �迭���� Ư�� ��Ҹ� �����մϴ�.
	 * @param element ������ ����� �������Դϴ�.
	 * @throw std::out_of_range ����� ��ġ�� �迭�� ��ȿ�� ������ ��� �� �߻��մϴ�.
	 */
	void Remove(ElementType* element);

	/**
	 * @brief �迭���� Ư�� ������ ��Ҹ� �����մϴ�.
	 * @param first ������ ������ �������� ����Ű�� ���ͷ������Դϴ�.
	 * @param last ������ ������ ������ ����Ű�� ���ͷ������Դϴ�.
	 */
	void RemoveRange(Iterator first, Iterator last);

	/**
	 * @brief �迭���� Ư�� ������ �����ϴ� ��Ҹ� �����մϴ�.
	 * @tparam Function ������ �Ǻ��� �Լ� ��ü Ÿ���Դϴ�.
	 * @param function ������ �Ǻ��ϴ� �Լ� ��ü�Դϴ�.
	 */
	template<class Function = bool(*)(ElementType&)>
	bool Remove(Function function);

	/**
	 * @brief �迭���� Ư�� ������ �����ϴ� ��� ��Ҹ� �����մϴ�.
	 * @tparam Function ������ �Ǻ��� �Լ� ��ü Ÿ���Դϴ�.
	 * @param function ������ �Ǻ��ϴ� �Լ� ��ü�Դϴ�.
	 */
	template<class Function = bool(*)(ElementType&)>
	void RemoveAll(Function function);

	/**
	 * @brief �迭���� Ư�� ��Ҹ� �����մϴ�.
	 * @param element ������ ����� ���۷����Դϴ�.
	 */
	void Remove(ElementType& element);

	Iterator Find(ElementType& element);

	/**
	 * @brief �迭���� Ư�� ������ �����ϴ� ù ��° ��Ҹ� ã���ϴ�.
	 * @tparam Function ������ �Ǻ��� �Լ� ��ü Ÿ���Դϴ�.
	 * @param predicate ������ �Ǻ��ϴ� �Լ� ��ü�Դϴ�.
	 * @return ������ �����ϴ� ù ��° ��Ҹ� ����Ű�� �ݺ����Դϴ�.
	 */
	template<class Function = bool(*)(ElementType&)>
	Iterator Find(Function predicate);

	/**
	 * @brief �迭���� Ư�� ������ �����ϴ� ��� ��Ҹ� ã�� ���� �迭�� ��ȯ�մϴ�.
	 * @tparam Function ������ �Ǻ��� �Լ� ��ü Ÿ���Դϴ�.
	 * @param predicate ������ �Ǻ��ϴ� �Լ� ��ü�Դϴ�.
	 * @return ������ �����ϴ� ��� ��Ҹ� ���� ���� �迭�Դϴ�.
	 */
	template<class Function>
	DynamicArray<ElementType*> FindAll(Function predicate);

	/**
	 * @brief �迭�� �뷮�� ���ο� ũ��� �����մϴ�.
	 * @param newCapacity ���ο� �뷮�Դϴ�.
	 * @throw std::exception �޸� �Ҵ� ���� �� ���ܸ� �����ϴ�.
	 */
	void ReSizeCapacity(unsigned int newCapacit, bool fitToCapacit = true);

	/**
	 * @brief �迭�� �ʱ�ȭ �մϴ�.
	 */
	void Clear() { ReSizeCapacity(0); }

	/**
	 * @brief �迭�� �뷮�� ���ο� ũ��� �����մϴ�.
	 * @param newCapacity ���ο� �뷮�Դϴ�.
	 * @return �뷮 ������ �߻��ߴ��� ����
	 */
	bool ResizeCapacityIfNecessary(unsigned int newCapacit);
	
	bool IsEmpty() { return count == 0; }

private:
	/**
	 * @brief �迭�� Ư�� �ε����� ��Ҹ� �����մϴ�.
	 * @param index ������ ��ġ�� �ε����Դϴ�.
	 * @param arg ������ ����� �� �Ǵ� �������Դϴ�.
	 * @return ���Ե� ����� ���۷���
	 */
	template<class ...VarType>
	ElementType& _Insert(unsigned int index, VarType&&... arg);

	/**
	 * @brief �迭�� ���� ��Ҹ� �߰��մϴ�.
	 * @param arg �߰��� ����� �� �Ǵ� �������Դϴ�.
	 * @return �߰��� ����� ���۷���
	 */
	template<class ...VarType>
	ElementType& _Add(VarType&&... arg);
	
	/**
	 * @brief �迭�� Ư�� �ε����� ��Ҹ� �����մϴ�.
	 * @param index ��Ҹ� ������ �ε����Դϴ�.
	 * @param arg ������ ����� �� �Ǵ� �������Դϴ�.
	 * @return ������ ����� ���۷���
	 */
	template<class ...VarType>
	ElementType& ConstructAtIndex(unsigned int index, VarType&&... arg);

	/**
	 * @brief �迭�� �뷮�� �����ϱ� ���� �ʿ��� �۾��� �����մϴ�.
	 * @param newCapacity ���ο� �뷮�Դϴ�.
	 *                    ������ ��� �ش� �뷮���� �뷮�� �����ϰ�, �׷��� ������ ���� �뷮�� 2�踦 ����մϴ�.
	 */
	void PreResizeCapacity(unsigned int newCapacit, bool fitToCapacit = true);

public:
	/** �迭�� ������ ����� �ε����� ��ȯ�մϴ�. */
	int GetLastIndex() { return count - 1; }
	/** �迭�� ��� ������ ��ȯ�մϴ�. */
	unsigned int GetCount() { return count; }
	/** �迭�� �뷮�� ��ȯ�մϴ�. */
	unsigned int GetCapacity() { return capacity; }

	/** �迭�� �������� ����Ű�� ���ͷ����͸� ��ȯ�մϴ�. */
	Iterator begin() { return data; }
	/** �迭�� ������ ����Ű�� ���ͷ����͸� ��ȯ�մϴ�. */
	Iterator end() { return data + count; }
	/** �迭�� ������ ��Ҹ� ��ȯ�մϴ�. */
	Iterator Back() { return data + GetLastIndex(); }

	/**
	 * @brief �迭�� Ư�� �ε����� �ִ� ��ҿ� �����մϴ�.
	 * @param index ������ ����� �ε���
	 * @return �ش� �ε����� �ִ� ���
	 * @throw std::out_of_range �ε����� ������ ��� �� ���ܸ� �����ϴ�.
	 */
	ElementType& operator[](size_t index) { return At(index); }

	/**
	  * @brief �迭�� Ư�� �ε����� �ִ� ��ҿ� �����մϴ�.
	  * @param index ������ ����� �ε���
	  * @return �ش� �ε����� �ִ� ���
	  * @throw std::out_of_range �ε����� ������ ��� �� ���ܸ� �����ϴ�.
	  */
	ElementType& At(size_t index);

private:
	/** �迭 �������� ������ */
	ElementType* data;
	/** �迭�� ��� ���� */
	unsigned int count;
	/** �迭�� �뷮 */
	unsigned int capacity;

};


#include "Containers/DynamicArray.inl"

