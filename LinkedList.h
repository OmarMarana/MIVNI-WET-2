//
// Created by omarm on 05/01/2022.
//

#ifndef MIVNI2_LINKEDLIST_H
#define MIVNI2_LINKEDLIST_H


template<class T, class S>
class ListNode{

    public:
    T info;
    S key;
    ListNode* next;
    ListNode* prev;


        ListNode(T info, S key) : info(info), key(key), next(nullptr), prev(nullptr) {};
};

template<class T, class S>
class LinkedList {
    private:
        ListNode<T,S>* head;


    public:
    LinkedList() : head(nullptr) {};
    ~LinkedList();
    void LinkedListInsert(T info, S key);
    void LinkedListRemove(S key);
    ListNode<T,S>* LinkedListFind(S key);
    ListNode<T,S>* LinkedListGetHead();
    void LinkedListSetHead(ListNode<T,S>* node);


};

template<class T, class S>
ListNode<T,S>* LinkedList<T,S>::LinkedListGetHead()
{
    return this->head;
}

template<class T, class S>
void LinkedList<T,S>::LinkedListSetHead(ListNode<T,S>* node){
    this->head = node;
}

template<class T, class S>
ListNode<T,S>* LinkedList<T,S>::LinkedListFind(S key)
{
    if(head == nullptr)
    {
        return nullptr;
    }
    ListNode<T,S>* tmp = head->next;
    while(tmp != nullptr)
    {
        if(tmp->key == key)
        {
            return tmp;
        }
        tmp = tmp->next;
    }
    return nullptr;
}

template<class T, class S>
void LinkedList<T,S>::LinkedListInsert(T info, S key)
{
    ListNode<T,S>* node = new ListNode<T,S>(info, key);
    if(head == nullptr)
    {
        head = node;
        return;
    }

    head->prev = node;
    node->next = head;
    head = head->prev;

}


template<class T, class S>
void LinkedList<T,S>::LinkedListRemove(S key)
{
    if(head == nullptr)
    {
        return;
    }
    if(head->key == key)
    {
        ListNode<T,S>* tmp = head;
        head = head->next;
        head->prev = nullptr;
        delete tmp;
        return;
    }
    ListNode<T,S>* tmp =head;
    while (tmp!= nullptr)
    {
        if(tmp->key == key)
        {
            tmp->prev->next =  tmp->next;
            if(tmp->next!= nullptr)
            {
                tmp->next->prev = tmp->prev;
            }
            delete tmp;
            return;
        }
        tmp = tmp->next;
    }
}

template<class T, class S>
LinkedList<T,S>::~LinkedList()
{
    if(head == nullptr)
    {
        return;
    }
    while(head != nullptr) // check if the negligence of prev and next causes problems
    {
        auto tmp = head;
        head = head->next;
        delete tmp;
    }
}

#endif //MIVNI2_LINKEDLIST_H
