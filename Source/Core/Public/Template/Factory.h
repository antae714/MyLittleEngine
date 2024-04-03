#pragma once

#include "Containers/DynamicArray.h";

//권장 사용방법 vvv
//class MODULEAPI NameFactory : public Factory<Name, String> {};
//권장 사용방법 ^^^

/**
 * @brief 싱글톤 팩토리 클래스
 * 
 * @tparam Type 생성할 타입
 * @tparam Key 검색기준이될 타입
 */
template <class Type, class Key>
class Factory
{
public:
	/** 객체 생성을 막기 위해 디폴트 생성자 삭제 */
	Factory() = delete;

public: 
	/** 배열에 저장된 요소를 담는 구조체 */
	struct TypeElement
	{
		Type* value;
		Key key;
	};

	/**
	 * @brief 싱글톤 배열을 반환합니다.
	 * 
	 * @return 동적 배열의 포인터
	 */
	static DynamicArray<TypeElement>* GetElementArray()
	{
		// 지연된 생성합니다.
		static DynamicArray<TypeElement> InputProcessorArray;
		return &InputProcessorArray;
	}

	/**
	 * @brief 배열에서 특정 키를 가진 요소를 찾아 반환합니다.
	 * 
	 * @param key 찾고자 하는 요소의 키
	 * @return 해당 키를 가진 요소의 포인터
	 */
	static Type* Get(Key key)
	{
		TypeElement* iter = GetElementArray()->Find([key](TypeElement& element) { return element.key == key; });
		return iter ? iter->value : nullptr;
	}
	
	/**
	 * @brief 배열에서 특정 키를 가진 요소를 제거합니다.
	 *
	 * @param key 제거하고자 하는 요소의 키
	 * @return 요소가 성공적으로 제거되었는지 여부
	 */
	static bool Remove(Key key)
	{
		return GetElementArray()->Remove([key](TypeElement& element) { return element.key == key; });
	}

	/**
	 * @brief 배열에 새로운 요소를 추가합니다.
	 *
	 * @param key 추가할 요소의 키
	 * @param value 추가할 요소의 값
	 */
	static void Add(Key key, Type* value)
	{
		TypeElement& element = GetElementArray()->Add();
		element.key = key;
		element.value = value;
	}
};

