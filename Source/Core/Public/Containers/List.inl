#include "List.h"
template <class _Node, class ElementType>
_NodeIterater<_Node, ElementType>& _NodeIterater<_Node, ElementType>::operator++()
{
    data = static_cast<_Node*>(data->next);
    return *this;
}

template <class _Node, class ElementType>
_NodeIterater<_Node, ElementType> _NodeIterater<_Node, ElementType>::operator++(int)
{
    _NodeIterater temp = data;
    data = static_cast<_Node*>(data->next);
    return temp;
}

template <class _Node, class ElementType>
_NodeIterater<_Node, ElementType>& _NodeIterater<_Node, ElementType>::operator--()
{
    data = static_cast<_Node*>(data->prev);
    return *this;
}

template <class _Node, class ElementType>
_NodeIterater<_Node, ElementType> _NodeIterater<_Node, ElementType>::operator--(int)
{
    _NodeIterater temp = data;
    data = static_cast<_Node*>(data->prev);
    return temp;
}

template <class ElementType>
List<ElementType>::List() : head(new Node()), tail(new Node())
{
    head->next = tail;
    tail->prev = head;
}

template <class ElementType>
List<ElementType>::List(std::initializer_list<ElementType>&& list) : List()
{
    for (auto& item : list)
    {
        AddFront(item);
    }
}

template <class ElementType>
List<ElementType>::~List()
{
    Clear();
    delete head;
    delete tail;
}

template <class ElementType>
void List<ElementType>::InsertAfter(NodeItertater iter, Node* newNode)
{
    newNode->next = iter->next;
    newNode->prev = iter;

    iter->next->prev = newNode;
    iter->next = newNode;
}

template <class ElementType>
template <class... Args>
void List<ElementType>::Insert(NodeItertater iter, Args&&... args)
{
    if (iter == tail) throw std::out_of_range("out_of_range");

    Node* newNode = new ListNode<ElementType>(std::forward<Args>(args)...);
    InsertAfter(iter, newNode);
}

template <class ElementType>
typename List<ElementType>::Iterator List<ElementType>::Remove(Iterator iter)
{
    return static_cast<ListNode<ElementType>*>(Remove((Node*)iter).Get());
}

template <class ElementType>
typename List<ElementType>::NodeItertater List<ElementType>::Remove(NodeItertater iter)
{
    if (iter == head) throw std::out_of_range("out_of_range");
    if (iter == tail) throw std::out_of_range("out_of_range");

    iter->next->prev = iter->prev;
    iter->prev->next = iter->next;
    NodeItertater prevIter = iter->prev;
    delete static_cast<ListNode<ElementType>*>(iter.Get());
    return prevIter;
}

template <class ElementType>
void List<ElementType>::Merge(List<ElementType>& other)
{
    Node* otherFrontNode = other.head->next;
    Node* otherBacktNode = other.tail->prev;

    otherFrontNode->prev = tail->prev;
    otherBacktNode->next = tail;

    tail->prev->next = otherFrontNode;
    tail->prev = otherBacktNode;

    other.tail->prev = other.head;
    other.head->next = other.tail;
}

template<class ElementType>
inline List<ElementType>::Iterator List<ElementType>::Find(ElementType& element)
{
    return Find([element](ElementType& _element) { return element == _element; });
}

template<class ElementType>
template<class Function>
inline List<ElementType>::Iterator List<ElementType>::Find(Function predicate)
{
    static_assert(std::is_invocable<Function, ElementType&>::value, "함수 시그니처가 다릅니다.");
    static_assert(!std::is_void<std::invoke_result<Function, ElementType&>::type>::value, "반환값이 없습니다.");

    for (Iterator i = begin(); i != end(); i++)
    {
        if (predicate(i->value))
        {
            return i;
        }
    }
    return nullptr;
}


template <class ElementType>
void List<ElementType>::Clear()
{
    while (!IsEmpty())
    {
        Remove(head->next);
    }
}

