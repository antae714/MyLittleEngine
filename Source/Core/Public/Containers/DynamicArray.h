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
	 * @brief 배열에서 특정 요소를 제거합니다.
	 * @param element 제거할 요소의 포인터입니다.
	 * @throw std::out_of_range 요소의 위치가 배열의 유효한 범위를 벗어날 때 발생합니다.
	 */
	void Remove(ElementType* element)
	{
		if (element < begin() || end() < element) throw std::out_of_range("Index out of range");
		element->~ElementType();

		memcpy(element, element + 1, (end() - 1 - element) * GetTypeSize());
		--count;
	}

	/**
	 * @brief 배열에서 특정 범위의 요소를 제거합니다.
	 * @param first 제거할 범위의 시작점을 가리키는 이터레이터입니다.
	 * @param last 제거할 범위의 끝점을 가리키는 이터레이터입니다.
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
	 * @brief 배열에서 특정 인덱스의 요소를 제거합니다.
	 * @param index 제거할 요소의 인덱스입니다.
	 */
	void RemoveIndex(int index)
	{
		Remove(data + index);
	}

	/**
	 * @brief 배열에서 특정 조건을 만족하는 요소를 제거합니다.
	 * @tparam Function 조건을 판별할 함수 객체 타입입니다.
	 * @param function 조건을 판별하는 함수 객체입니다.
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
	 * @brief 배열에서 특정 조건을 만족하는 모든 요소를 제거합니다.
	 * @tparam Function 조건을 판별할 함수 객체 타입입니다.
	 * @param function 조건을 판별하는 함수 객체입니다.
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
	 * @brief 배열에서 특정 요소를 제거합니다.
	 * @param element 제거할 요소의 레퍼런스입니다.
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
	 * @brief 배열에서 특정 조건을 만족하는 첫 번째 요소를 찾습니다.
	 * @tparam Function 조건을 판별할 함수 객체 타입입니다.
	 * @param predicate 조건을 판별하는 함수 객체입니다.
	 * @return 조건을 만족하는 첫 번째 요소를 가리키는 반복자입니다.
	 */
	template<class Function>
	Iterator Find(Function predicate)
	{
		static_assert(std::is_invocable<Function, ElementType&>::value, "함수 시그니처가 다릅니다.");
		static_assert(!std::is_void<std::invoke_result<Function, ElementType&>::type>::value, "반환값이 없습니다.");

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
	 * @brief 배열에서 특정 조건을 만족하는 모든 요소를 찾아 동적 배열로 반환합니다.
	 * @tparam Function 조건을 판별할 함수 객체 타입입니다.
	 * @param predicate 조건을 판별하는 함수 객체입니다.
	 * @return 조건을 만족하는 모든 요소를 담은 동적 배열입니다.
	 */
	template<class Function>
	DynamicArray<ElementType*> FindAll(Function predicate)
	{
		static_assert(std::is_invocable<Function, ElementType&>::value, "함수 시그니처가 다릅니다.");
		static_assert(!std::is_void<std::invoke_result<Function, ElementType&>::type>::value, "반환값이 없습니다.");

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
	 * @brief 배열의 용량을 새로운 크기로 조정합니다.
	 * @param newCapacity 새로운 용량입니다.
	 * @throw std::exception 메모리 할당 실패 시 예외를 던집니다.
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
	 * @brief 배열을 초기화 합니다.
	 */
	void Clear()
	{
		ReSizeCapacity(0);
	}


	bool IsContains(ElementType* element)
	{

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


