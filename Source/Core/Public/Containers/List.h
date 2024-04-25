#pragma once

#include <initializer_list>
#include <stdexcept>
#include <utility>

/**
 * @brief ����� ���
 */
struct Node
{
    Node* prev;
    Node* next;
};

/**
 * @brief ����Ʈ�� ����� ���
 * @tparam Type �����̳ʰ� ������ Ÿ��
 */
template <class ElementType>
struct ListNode : public Node
{
    template <class... Args>
    ListNode(Args&&... _value) : value(std::forward<Args>(_value)...) {}

    ElementType value;
};

/**
 * @brief ����� ��� �ݺ���
 * @tparam Type �����̳ʰ� ������ Ÿ��
 * @tparam _Node ��� Ÿ��
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
 * @brief ����� ����Ʈ
 * @tparam Type ����Ʈ�� ������ Ÿ��
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
     * @brief ������ �ݺ��� �ڿ� �߰��մϴ�
     * @param iter �߰��� ��ġ�� �ݺ���
     * @param newNode ���� �߰��� ���
     */
    void InsertAfter(NodeItertater iter, Node* newNode);

    /**
     * @brief ������ �ݺ��� �ڿ� �߰��մϴ�
     * @param iter �߰��� ��ġ�� �ݺ���
     * @param args �����ڿ� �Ѱ��� ���� ����
     * @tparam Args �����ڿ� �Ѱ��� ���� ���� Ÿ��
     */
    template <class... Args>
    void Insert(NodeItertater iter, Args&&... args);

    /**
     * @brief ����Ʈ�� ù�κп� �߰��մϴ�.
     * @param args �����ڿ� �Ѱ��� ���� ����
     * @tparam Args �����ڿ� �Ѱ��� ���� ���� Ÿ��
     */
    template <class... Args>
    void AddFront(Args&&... args) { Insert(head, std::forward<Args>(args)...); }
    
    /**
     * @brief ����Ʈ�� �������� �߰��մϴ�.
     * @param args �����ڿ� �Ѱ��� ���� ����
     * @tparam Args �����ڿ� �Ѱ��� ���� ���� Ÿ��
     */
    template <class... Args>
    void AddBack(Args&&... args) { Insert(tail->prev, std::forward<Args>(args)...); }

    /**
     * @brief ������ ����� �ݺ��ڸ� �����մϴ�.
     *
     * �� �Լ��� �־��� �ݺ��ڰ� ����Ʈ�� ���� �Ǵ� ���� �ִ��� Ȯ���� ��,
     * �ش� ��带 �����ϰ� �� ���� ����� �ݺ��ڸ� ��ȯ�մϴ�.
     *
     * @param iter ������ ����� �ݺ���
     * @return ������ ����� ���� ����� �ݺ���
     * @throw std::out_of_range �־��� �ݺ��ڰ� ����Ʈ�� ���� �Ǵ� ���� ���
     */
    Iterator Remove(Iterator iter);

    /**
     * @brief ������ ����� �ݺ��ڸ� �����մϴ�.
     *
     * �� �Լ��� �־��� �ݺ��ڰ� ����Ʈ�� ���� �Ǵ� ���� �ִ��� Ȯ���� ��,
     * �ش� ��带 �����ϰ� �� ���� ����� �ݺ��ڸ� ��ȯ�մϴ�.
     *
     * @param iter ������ ����� �ݺ���
     * @return ������ ����� ���� ����� �ݺ���
     * @throw std::out_of_range �־��� �ݺ��ڰ� ����Ʈ�� ���� �Ǵ� ���� ���
     */
    NodeItertater Remove(NodeItertater iter);

    /** �Ǿ� ��Ҹ� �����մϴ�. */
    void RemoveFront() { Remove(head->next); }

    /** �ǵ� ��Ҹ� �����մϴ�. */
    void RemoveBack() { Remove(tail->prev); }

    /**
     * @brief �� ����Ʈ�� �����մϴ�.
     * @param other ������ �ٸ� ����Ʈ
     */
    void Merge(List<ElementType>& other);

    Iterator Find(ElementType& element);

    /**
     * @brief �迭���� Ư�� ������ �����ϴ� ù ��° ��Ҹ� ã���ϴ�.
     * @tparam Function ������ �Ǻ��� �Լ� ��ü Ÿ���Դϴ�.
     * @param predicate ������ �Ǻ��ϴ� �Լ� ��ü�Դϴ�.
     * @return ������ �����ϴ� ù ��° ��Ҹ� ����Ű�� �ݺ����Դϴ�.
     */
    template<class Function = bool(*)(ElementType&)>
    Iterator Find(Function predicate);

    /** ����Ʈ�� ���ϴ�. */
    void Clear();

    /**
     * @brief ��Ұ� ������� üũ�մϴ�.
     * @return ��Ұ� ������� ��
     */
    bool IsEmpty() { return begin() == end(); }

    /** ù ������ ���� ��ȯ�մϴ�. */
    ElementType& Front() { return static_cast<ListNode<ElementType>*>(head->next)->value; }

    /** ������ ������ ���� ��ȯ�մϴ�. */
    ElementType& Back() { return static_cast<ListNode<ElementType>*>(tail->prev)->value; }

    Iterator begin() { return static_cast<ListNode<ElementType>*>(head->next); }
    Iterator end() { return static_cast<ListNode<ElementType>*>(tail); }

private:
    Node* head;
    Node* tail;
};

#include "List.inl" 
