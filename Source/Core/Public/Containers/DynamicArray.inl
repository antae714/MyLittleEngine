#include "DynamicArray.h"
#pragma once


template<class ElementType>
inline DynamicArray<ElementType>::~DynamicArray()
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

template<class ElementType>
inline void DynamicArray<ElementType>::Remove(ElementType* element)
{
	if (element < begin() || end() < element) throw std::out_of_range("Index out of range");
	element->~ElementType();

	memcpy(element, element + 1, (end() - 1 - element) * GetTypeSize());
	--count;
}

template<class ElementType>
inline void DynamicArray<ElementType>::RemoveRange(Iterator first, Iterator last)
{
	if (first < begin() || end() < last) throw std::out_of_range("Index out of range");

	for (Iterator i = first; i != last; i++)
	{
		i->~ElementType();
	}

	memcpy(first, last, (end() - last) * GetTypeSize());
	count -= (last - first);
}

template<class ElementType>
template<class Function>
inline bool DynamicArray<ElementType>::Remove(Function function)
{
	ElementType* removeObj = Find(function);
	if (removeObj)
	{
		Remove(removeObj);
	}
	return !!removeObj;
}

template<class ElementType>
template<class Function>
inline void DynamicArray<ElementType>::RemoveAll(Function function)
{
	DynamicArray<ElementType*> deleteArray = FindAll(function);
	for (size_t i = 0; i < deleteArray.GetCount(); i++)
	{
		Remove(deleteArray[i] - i);
	}
}

template<class ElementType>
inline void DynamicArray<ElementType>::Remove(ElementType& element)
{
	Remove([element](ElementType& _element) { return element == _element; });
}

template<class ElementType>
inline DynamicArray<ElementType>::Iterator DynamicArray<ElementType>::Find(ElementType& element)
{
	return Find([element](ElementType& _element) { return element == _element; });
}

template<class ElementType>
template<class Function>
inline DynamicArray<ElementType>::Iterator DynamicArray<ElementType>::Find(Function predicate)
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

template<class ElementType>
template<class Function>
inline DynamicArray<ElementType*> DynamicArray<ElementType>::FindAll(Function predicate)
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

template<class ElementType>
inline void DynamicArray<ElementType>::ReSizeCapacity(unsigned int newCapacit, bool fitToCapacit)
{
	PreResizeCapacity(newCapacit, fitToCapacit);

	ElementType* tempdata = (ElementType*)realloc(data, capacity * GetTypeSize());
	if (tempdata == nullptr && capacity)
	{
		tempdata = (ElementType*)malloc(capacity * GetTypeSize());
		if (tempdata == nullptr) throw std::bad_alloc();

		memcpy(tempdata, data, GetLastIndex() * GetTypeSize());
		free(data);
	}
	data = tempdata;
}

template<class ElementType>
inline bool DynamicArray<ElementType>::ResizeCapacityIfNecessary(unsigned int newCapacit)
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

template<class ElementType>
template<class ...VarType>
inline ElementType& DynamicArray<ElementType>::_Insert(unsigned int index, VarType && ...arg)
{
	ResizeCapacityIfNecessary(++count);

	memmove(data + index + 1, data + index, (GetLastIndex() - index) * GetTypeSize());

	return ConstructAtIndex(index, std::forward<VarType>(arg)...);
}

template<class ElementType>
template<class ...VarType>
inline ElementType& DynamicArray<ElementType>::_Add(VarType && ...arg)
{
	ResizeCapacityIfNecessary(++count);

	return ConstructAtIndex(GetLastIndex(), std::forward<VarType>(arg)...);
}

template<class ElementType>
template<class ...VarType>
inline ElementType& DynamicArray<ElementType>::ConstructAtIndex(unsigned int index, VarType && ...arg)
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

template<class ElementType>
inline void DynamicArray<ElementType>::PreResizeCapacity(unsigned int newCapacit, bool fitToCapacit)
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

template<class ElementType>
inline ElementType& DynamicArray<ElementType>::At(size_t index)
{
	if (index >= count) throw std::out_of_range("Index out of range");

	return data[index];
}
