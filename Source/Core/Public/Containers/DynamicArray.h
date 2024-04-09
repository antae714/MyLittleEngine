#pragma once

#include <type_traits>
#include <stdexcept>



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
	//void operator=(std::initializer_list list)
	//{

	//}
	~DynamicArray()
	{
		if (data == nullptr) return;

		if constexpr (IsElementClassType)
		{
			for (size_t i = 0; i < count; i++)
			{
				(data + i)->~ElementType();
			}
		}

		free(data);
		data = nullptr;
	}

public:
	/** ����� ũ�� (����Ʈ) */
	//static constexpr int ElementSize = sizeof(ElementType);
	/**
	 * @brief ����� ũ�⸦ ��ȯ �մϴ�.
	 * @return ����� ũ�� (����Ʈ)
	 */
	static constexpr unsigned int GetTypeSize()
	{
		return sizeof(ElementType);
	}

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
	 * @brief �迭���� Ư�� ��Ҹ� �����մϴ�.
	 * @param element ������ ����� �������Դϴ�.
	 * @throw std::out_of_range ����� ��ġ�� �迭�� ��ȿ�� ������ ��� �� �߻��մϴ�.
	 */
	void Remove(ElementType* element)
	{
		if (element < begin() || end() < element) throw std::out_of_range("Index out of range");
		element->~ElementType();

		memcpy(element, element + 1, (end() - 1 - element) * GetTypeSize());
		--count;
	}

	/**
	 * @brief �迭���� Ư�� ������ ��Ҹ� �����մϴ�.
	 * @param first ������ ������ �������� ����Ű�� ���ͷ������Դϴ�.
	 * @param last ������ ������ ������ ����Ű�� ���ͷ������Դϴ�.
	 */
	void RemoveRange(Iterator first, Iterator last)
	{
		if (first < begin() || end() < last) throw std::out_of_range("Index out of range");

		for (Iterator i = first; i != last; i++)
		{
			i->~ElementType();
		}

		memcpy(first, last, (end() - last) * GetTypeSize());
		count -= (last - first);
	}

	/**
	 * @brief �迭���� Ư�� �ε����� ��Ҹ� �����մϴ�.
	 * @param index ������ ����� �ε����Դϴ�.
	 */
	void RemoveIndex(int index)
	{
		Remove(data + index);
	}

	/**
	 * @brief �迭���� Ư�� ������ �����ϴ� ��Ҹ� �����մϴ�.
	 * @tparam Function ������ �Ǻ��� �Լ� ��ü Ÿ���Դϴ�.
	 * @param function ������ �Ǻ��ϴ� �Լ� ��ü�Դϴ�.
	 */
	template<class Function>
	bool Remove(Function function)
	{
		ElementType* removeObj = Find(function);
		if (removeObj)
		{
			Remove(removeObj);
		}
		return !!removeObj;
	}

	/**
	 * @brief �迭���� Ư�� ������ �����ϴ� ��� ��Ҹ� �����մϴ�.
	 * @tparam Function ������ �Ǻ��� �Լ� ��ü Ÿ���Դϴ�.
	 * @param function ������ �Ǻ��ϴ� �Լ� ��ü�Դϴ�.
	 */
	template<class Function>
	void RemoveAll(Function function)
	{
		DynamicArray<ElementType*> deleteArray = FindAll(function);
		for (size_t i = 0; i < deleteArray.GetCount(); i++)
		{
			Remove(deleteArray[i] - i);
		}

	}

	/**
	 * @brief �迭���� Ư�� ��Ҹ� �����մϴ�.
	 * @param element ������ ����� ���۷����Դϴ�.
	 */
	void Remove(ElementType& element)
	{
		Remove([element](ElementType& _element) { return element == _element; });
	}


	Iterator Find(ElementType& element)
	{
		return Find([element](ElementType& _element) { return element == _element; });
	}


	/**
	 * @brief �迭���� Ư�� ������ �����ϴ� ù ��° ��Ҹ� ã���ϴ�.
	 * @tparam Function ������ �Ǻ��� �Լ� ��ü Ÿ���Դϴ�.
	 * @param predicate ������ �Ǻ��ϴ� �Լ� ��ü�Դϴ�.
	 * @return ������ �����ϴ� ù ��° ��Ҹ� ����Ű�� �ݺ����Դϴ�.
	 */
	template<class Function>
	Iterator Find(Function predicate)
	{
		static_assert(std::is_invocable<Function, ElementType&>::value, "�Լ� �ñ״�ó�� �ٸ��ϴ�.");
		static_assert(!std::is_void<std::invoke_result<Function, ElementType&>::type>::value, "��ȯ���� �����ϴ�.");

		for (Iterator i = begin(); i != end(); i++)
		{
			if (predicate(*i))
			{
				return i;
			}
		}
		return nullptr;
	}

	/**
	 * @brief �迭���� Ư�� ������ �����ϴ� ��� ��Ҹ� ã�� ���� �迭�� ��ȯ�մϴ�.
	 * @tparam Function ������ �Ǻ��� �Լ� ��ü Ÿ���Դϴ�.
	 * @param predicate ������ �Ǻ��ϴ� �Լ� ��ü�Դϴ�.
	 * @return ������ �����ϴ� ��� ��Ҹ� ���� ���� �迭�Դϴ�.
	 */
	template<class Function>
	DynamicArray<ElementType*> FindAll(Function predicate)
	{
		static_assert(std::is_invocable<Function, ElementType&>::value, "�Լ� �ñ״�ó�� �ٸ��ϴ�.");
		static_assert(!std::is_void<std::invoke_result<Function, ElementType&>::type>::value, "��ȯ���� �����ϴ�.");

		DynamicArray<ElementType*> deleteArray;

		for (Iterator i = begin(); i != end(); i++)
		{
			if (predicate(*i))
			{
				deleteArray.Add(i);
			}
		}

		return deleteArray;
	}

	/**
	 * @brief �迭�� �뷮�� ���ο� ũ��� �����մϴ�.
	 * @param newCapacity ���ο� �뷮�Դϴ�.
	 * @throw std::exception �޸� �Ҵ� ���� �� ���ܸ� �����ϴ�.
	 */
	void ReSizeCapacity(unsigned int newCapacit, bool fitToCapacit = true)
	{
		PreResizeCapacity(newCapacit, fitToCapacit);

		ElementType* tempdata = data;
		tempdata = (ElementType*)realloc(data, capacity * GetTypeSize());
		if (tempdata == nullptr && capacity)
		{
			tempdata = (ElementType*)malloc(capacity * GetTypeSize());
			if (tempdata == nullptr) throw std::bad_alloc();

			memcpy(tempdata, data, GetLastIndex() * GetTypeSize());
			free(data);
		}
		data = tempdata;



		//ElementType* tempdata = data;
		//tempdata = (ElementType*)::operator new(MaxCount * TypeSize);
		//for (size_t i = 0; i < count - 1; i++)
		//{
		//	new (tempdata + i) ElementType(forward<ElementType>(data[i]));
		//}
		//for (size_t i = 0; i < count - 1; i++)
		//{
		//	(data + i)->~ElementType();
		//}
		//delete data;
		//data = tempdata;
	}

	/**
	 * @brief �迭�� �ʱ�ȭ �մϴ�.
	 */
	void Clear()
	{
		ReSizeCapacity(0);
	}


	bool IsContains(ElementType* element)
	{

	}

	/**
	 * @brief �迭�� �뷮�� ���ο� ũ��� �����մϴ�.
	 * @param newCapacity ���ο� �뷮�Դϴ�.
	 * @return �뷮 ������ �߻��ߴ��� ����
	 */
	bool ResizeCapacityIfNecessary(unsigned int newCapacit)
	{
		if (data == nullptr || newCapacit > capacity)
		{
			ReSizeCapacity(newCapacit);
			return true;
		}
		else
		{
			return false;
		}
	}

	bool IsEmpty()
	{
		return count == 0;
	}

private:
	/**
	 * @brief �迭�� Ư�� �ε����� ��Ҹ� �����մϴ�.
	 * @param index ������ ��ġ�� �ε����Դϴ�.
	 * @param arg ������ ����� �� �Ǵ� �������Դϴ�.
	 * @return ���Ե� ����� ���۷���
	 */
	template<class ...VarType>
	ElementType& _Insert(unsigned int index, VarType&&... arg)
	{
		ResizeCapacityIfNecessary(++count);

		memmove(data + index + 1, data + index, (GetLastIndex() - index) * GetTypeSize());

		return ConstructAtIndex(index, std::forward<VarType>(arg)...);
	}

	/**
	 * @brief �迭�� ���� ��Ҹ� �߰��մϴ�.
	 * @param arg �߰��� ����� �� �Ǵ� �������Դϴ�.
	 * @return �߰��� ����� ���۷���
	 */
	template<class ...VarType>
	ElementType& _Add(VarType&&... arg)
	{
		ResizeCapacityIfNecessary(++count);

		return ConstructAtIndex(GetLastIndex(), std::forward<VarType>(arg)...);
	}

	/**
	 * @brief �迭�� Ư�� �ε����� ��Ҹ� �����մϴ�.
	 * @param index ��Ҹ� ������ �ε����Դϴ�.
	 * @param arg ������ ����� �� �Ǵ� �������Դϴ�.
	 * @return ������ ����� ���۷���
	 */
	template<class ...VarType>
	ElementType& ConstructAtIndex(unsigned int index, VarType&&... arg)
	{
		if (index >= count) throw std::out_of_range("Index out of range");

		if constexpr (IsElementClassType)
		{
			static_assert(std::is_constructible<ElementType, VarType...>::value, "������ �����ڰ� �����ϴ�.");
			return *new (data + index) ElementType(std::forward<VarType>(arg)...);
		}
		else
		{
			memcpy(data + index, &arg..., GetTypeSize());
			return *(data + index);
		}
	}


	/**
	 * @brief �迭�� �뷮�� �����ϱ� ���� �ʿ��� �۾��� �����մϴ�.
	 * @param newCapacity ���ο� �뷮�Դϴ�.
	 *                    ������ ��� �ش� �뷮���� �뷮�� �����ϰ�, �׷��� ������ ���� �뷮�� 2�踦 ����մϴ�.
	 */
	void PreResizeCapacity(unsigned int newCapacit, bool fitToCapacit = true)
	{
		if (capacity > (int)newCapacit)
		{
			count = newCapacit;
			for (size_t i = newCapacit; i < capacity - 1; i++)
			{
				(data + i)->~ElementType();
			}
		}

		do
		{
			capacity = fitToCapacit ? newCapacit : capacity << 1;
		} while (capacity < newCapacit);
	}

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
	ElementType& At(size_t index)
	{
		if (index >= count) throw std::out_of_range("Index out of range");


		return data[index];
	}
private:
	/** �迭 �������� ������ */
	ElementType* data;
	/** �迭�� ��� ���� */
	unsigned int count;
	/** �迭�� �뷮 */
	unsigned int capacity;

};


