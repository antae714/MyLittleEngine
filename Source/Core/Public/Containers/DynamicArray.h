#pragma once

#include <type_traits>
#include <stdexcept>



/**
 * @brief 동적 배열 클래스입니다.
 * @tparam ElementType 배열에 저장되는 요소의 타입입니다.
 */
template <class ElementType>
class DynamicArray
{
public:
	using Iterator = ElementType*;

	/** 요소가 클래스 타입인지 여부 */
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
	/** 요소의 크기 (바이트) */
	//static constexpr int ElementSize = sizeof(ElementType);
	/** 
	 * @brief 요소의 크기를 반환 합니다.
	 * @return 요소의 크기 (바이트)
	 */
	static constexpr unsigned int GetTypeSize()
	{
		return sizeof(ElementType);
	}

	/**
	 * @brief 배열의 끝에 요소를 추가합니다.
	 * @param value 추가할 요소의 값 또는 생성자입니다.
	 * @return 추가된 요소의 레퍼런스
	 */
	template<class ...VarType>
	ElementType& Add(VarType&&... value) { return _Add(std::forward<VarType>(value)...); }

	/**
	 * @brief 배열의 특정 인덱스에 요소를 삽입합니다.
	 * @param index 삽입할 위치의 인덱스입니다.
	 * @param value 삽입할 요소의 값 또는 생성자입니다.
	 * @return 삽입된 요소의 레퍼런스
	 */
	template<class ...VarType>
	ElementType& Insert(int index, VarType&&... value) { return _Insert(index, std::forward<VarType>(value)...); }

	/**
	 * @brief 배열에서 특정 인덱스의 요소를 제거합니다.
	 * @param index 제거할 요소의 인덱스입니다.
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
	 * @brief 배열의 용량을 새로운 크기로 조정합니다.
	 * @param newCapacity 새로운 용량입니다.
	 * @return 용량 조정이 발생했는지 여부
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
	 * @brief 배열의 용량을 새로운 크기로 조정합니다.
	 * @param newCapacity 새로운 용량입니다.
	 * @throw std::exception 메모리 할당 실패 시 예외를 던집니다.
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
	 * @brief 배열의 특정 인덱스에 요소를 삽입합니다.
	 * @param index 삽입할 위치의 인덱스입니다.
	 * @param arg 삽입할 요소의 값 또는 생성자입니다.
	 * @return 삽입된 요소의 레퍼런스
	 */
	template<class ...VarType>
	ElementType& _Insert(unsigned int index, VarType&&... arg)
	{
		ResizeCapacityIfNecessary(++count);

		memmove(data + index + 1, data + index, (GetLastIndex() - index) * GetTypeSize());

		return ConstructAtIndex(index, std::forward<VarType>(arg)...);
	}

	/**
	 * @brief 배열의 끝에 요소를 추가합니다.
	 * @param arg 추가할 요소의 값 또는 생성자입니다.
	 * @return 추가된 요소의 레퍼런스
	 */
	template<class ...VarType>
	ElementType& _Add(VarType&&... arg)
	{
		ResizeCapacityIfNecessary(++count);

		return ConstructAtIndex(GetLastIndex(), std::forward<VarType>(arg)...);
	}

	/**
	 * @brief 배열의 특정 인덱스에 요소를 생성합니다.
	 * @param index 요소를 생성할 인덱스입니다.
	 * @param arg 생성할 요소의 값 또는 생성자입니다.
	 * @return 생성된 요소의 레퍼런스
	 */
	template<class ...VarType>
	ElementType& ConstructAtIndex(unsigned int index, VarType&&... arg)
	{
		if (index >= count) throw std::out_of_range("Index out of range");

		if constexpr (IsElementClassType)
		{
			static_assert(std::is_constructible<ElementType, VarType...>::value, "적절한 생성자가 없습니다.");
			return *new (data + index) ElementType(std::forward<VarType>(arg)...);
		}
		else
		{
			memcpy(data + index, &arg..., GetTypeSize());
			return *(data + index);
		}
	}
	/**
	 * @brief 배열의 용량을 조정하기 전에 필요한 작업을 수행합니다.
	 * @param newCapacity 새로운 용량입니다.
	 *                    지정된 경우 해당 용량으로 용량을 조정하고, 그렇지 않으면 현재 용량의 2배를 사용합니다.
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
	/** 배열의 마지막 요소의 인덱스를 반환합니다. */
	int GetLastIndex() { return count - 1; }
	/** 배열의 요소 개수를 반환합니다. */
	unsigned int GetCount() { return count; }
	/** 배열의 용량을 반환합니다. */
	unsigned int GetCapacity() { return capacity; }

	/** 배열의 시작점을 가리키는 이터레이터를 반환합니다. */
	Iterator begin() { return data; }
	/** 배열의 끝점을 가리키는 이터레이터를 반환합니다. */
	Iterator end() { return data + count; }
	/** 배열의 마지막 요소를 반환합니다. */
	Iterator Back() { return data + GetLastIndex(); }

	/**
	 * @brief 배열의 특정 인덱스에 있는 요소에 접근합니다.
	 * @param index 접근할 요소의 인덱스
	 * @return 해당 인덱스에 있는 요소
	 * @throw std::out_of_range 인덱스가 범위를 벗어날 때 예외를 던집니다.
	 */
	ElementType& operator[](size_t index) { return At(index); }

	/**
	  * @brief 배열의 특정 인덱스에 있는 요소에 접근합니다.
	  * @param index 접근할 요소의 인덱스
	  * @return 해당 인덱스에 있는 요소
	  * @throw std::out_of_range 인덱스가 범위를 벗어날 때 예외를 던집니다.
	  */
	ElementType& At(size_t index)
	{
		if (index >= count) throw std::out_of_range("Index out of range");


		return data[index];
	}
private:
	/** 배열 데이터의 포인터 */
	ElementType* data;
	/** 배열의 요소 개수 */
	unsigned int count;
	/** 배열의 용량 */
	unsigned int capacity;

};