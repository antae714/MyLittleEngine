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
	 * @brief �迭���� Ư�� �ε����� ��Ҹ� �����մϴ�.
	 * @param index ������ ����� �ε����Դϴ�.
	 */
	void Remove(int index)
	{
		if (index >= count) throw std::out_of_range("Index out of range");

		(data + index)->~ElementType();
		memcpy(data + index, data + index + 1, (GetLastIndex() - index) * GetTypeSize());
		--count;

		//std::memcpy(data + index, data + index + 1, (count - index - 1) * ElementSize);
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
			ReSizeCapacity();
			return true;
		}
		else
		{
			return false;
		}
	}

	/**
	 * @brief �迭�� �뷮�� ���ο� ũ��� �����մϴ�.
	 * @param newCapacity ���ο� �뷮�Դϴ�.
	 * @throw std::exception �޸� �Ҵ� ���� �� ���ܸ� �����ϴ�.
	 */
	void ReSizeCapacity(unsigned int newCapacit = 0)
	{
		PreResizeCapacity(newCapacit);

		ElementType* tempdata = data;
		tempdata = (ElementType*)realloc(data, capacity * GetTypeSize());
		if (tempdata == nullptr)
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
	void PreResizeCapacity(unsigned int newCapacit)
	{
		if (data == nullptr)
		{
			capacity = newCapacit ? newCapacit : 1;
			return;
		}

		if (newCapacit && capacity > newCapacit)
		{
			count = newCapacit;
			for (size_t i = newCapacit; i < capacity - 1; i++)
			{
				(data + i)->~ElementType();
			}
		}

		capacity = newCapacit ? newCapacit : capacity << 1;
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