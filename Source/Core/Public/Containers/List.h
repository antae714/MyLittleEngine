#pragma once

#include <initializer_list>
#include <stdexcept>
#include <utility>

/**
 * @brief 양방향 노드
 */
struct Node
{
    Node* prev;
    Node* next;
};

/**
 * @brief 리스트용 양방향 노드
 * @tparam Type 컨테이너가 보관할 타입
 */
template <class ElementType>
struct ListNode : public Node
{
    template <class... Args>
    ListNode(Args&&... _value) : value(std::forward<Args>(_value)...) {}

    ElementType value;
};

/**
 * @brief 양방향 노드 반복자
 * @tparam Type 컨테이너가 보관할 타입
 * @tparam _Node 노드 타입
 */
template<class _Node, class ElementType>
class _NodeIterater
{
public:
    _NodeIterater(_Node* _data) : data(_data) {}

    operator _Node* () { return data; }

    ElementType& operator*() { return data->value; }

    _Node* Get() { return data; }

    _NodeIterater& operator++();

    _NodeIterater operator++(int);

    _NodeIterater& operator--();

    _NodeIterater operator--(int);

    _Node* operator->() { return data; }

    bool operator==(_Node* other) { return other == this->data; }

    bool operator==(_NodeIterater other) { return other.data == this->data; }

    bool operator!=(_NodeIterater other) { return other.data != this->data; }

private:
    _Node* data;
};

/**
 * @brief 연결된 리스트
 * @tparam Type 리스트가 보관할 타입
 */
template <class ElementType>
class List
{
public:
    using Iterator = _NodeIterater<ListNode<ElementType>, ElementType>;
    using NodeItertater = _NodeIterater<Node, ElementType>;

public:
    List();
    List(std::initializer_list<ElementType>&& list);
    ~List();

    /**
     * @brief 지정된 반복자 뒤에 추가합니다
     * @param iter 추가할 위치의 반복자
     * @param newNode 새로 추가할 노드
     */
    void InsertAfter(NodeItertater iter, Node* newNode);

    /**
     * @brief 지정된 반복자 뒤에 추가합니다
     * @param iter 추가할 위치의 반복자
     * @param args 생성자에 넘겨줄 가변 인자
     * @tparam Args 생성자에 넘겨줄 가변 인자 타입
     */
    template <class... Args>
    void Insert(NodeItertater iter, Args&&... args);

    /**
     * @brief 리스트의 첫부분에 추가합니다.
     * @param args 생성자에 넘겨줄 가변 인자
     * @tparam Args 생성자에 넘겨줄 가변 인자 타입
     */
    template <class... Args>
    void AddFront(Args&&... args) { Insert(head, std::forward<Args>(args)...); }
    
    /**
     * @brief 리스트의 마지막에 추가합니다.
     * @param args 생성자에 넘겨줄 가변 인자
     * @tparam Args 생성자에 넘겨줄 가변 인자 타입
     */
    template <class... Args>
    void AddBack(Args&&... args) { Insert(tail->prev, std::forward<Args>(args)...); }

    /**
     * @brief 지정된 노드의 반복자를 삭제합니다.
     *
     * 이 함수는 주어진 반복자가 리스트의 시작 또는 끝에 있는지 확인한 후,
     * 해당 노드를 삭제하고 그 이전 노드의 반복자를 반환합니다.
     *
     * @param iter 삭제할 노드의 반복자
     * @return 삭제된 노드의 이전 노드의 반복자
     * @throw std::out_of_range 주어진 반복자가 리스트의 시작 또는 끝인 경우
     */
    Iterator Remove(Iterator iter);

    /**
     * @brief 지정된 노드의 반복자를 삭제합니다.
     *
     * 이 함수는 주어진 반복자가 리스트의 시작 또는 끝에 있는지 확인한 후,
     * 해당 노드를 삭제하고 그 이전 노드의 반복자를 반환합니다.
     *
     * @param iter 삭제할 노드의 반복자
     * @return 삭제된 노드의 이전 노드의 반복자
     * @throw std::out_of_range 주어진 반복자가 리스트의 시작 또는 끝인 경우
     */
    NodeItertater Remove(NodeItertater iter);

    /** 맨앞 요소를 삭제합니다. */
    void RemoveFront() { Remove(head->next); }

    /** 맨뒤 요소를 삭제합니다. */
    void RemoveBack() { Remove(tail->prev); }

    /**
     * @brief 두 리스트를 병합합니다.
     * @param other 병합할 다른 리스트
     */
    void Merge(List<ElementType>& other);

    Iterator Find(ElementType& element);

    /**
     * @brief 배열에서 특정 조건을 만족하는 첫 번째 요소를 찾습니다.
     * @tparam Function 조건을 판별할 함수 객체 타입입니다.
     * @param predicate 조건을 판별하는 함수 객체입니다.
     * @return 조건을 만족하는 첫 번째 요소를 가리키는 반복자입니다.
     */
    template<class Function = bool(*)(ElementType&)>
    Iterator Find(Function predicate);

    /** 리스트를 비웁니다. */
    void Clear();

    /**
     * @brief 요소가 비었는지 체크합니다.
     * @return 요소가 비었을시 참
     */
    bool IsEmpty() { return begin() == end(); }

    /** 첫 원소의 값을 반환합니다. */
    ElementType& Front() { return static_cast<ListNode<ElementType>*>(head->next)->value; }

    /** 마지막 원소의 값을 반환합니다. */
    ElementType& Back() { return static_cast<ListNode<ElementType>*>(tail->prev)->value; }

    Iterator begin() { return static_cast<ListNode<ElementType>*>(head->next); }
    Iterator end() { return static_cast<ListNode<ElementType>*>(tail); }

private:
    Node* head;
    Node* tail;
};

#include "List.inl" 
