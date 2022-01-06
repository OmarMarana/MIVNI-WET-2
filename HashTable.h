//
// Created by omarm on 05/01/2022.
//

#ifndef MIVNI2_HASHTABLE_H
#define MIVNI2_HASHTABLE_H

#include "LinkedList.h"
#include <cmath>
#define A  (sqrt(5) -1)/2
#define SHRINK 4
#define EXPAND 2



template<class T, class S>
class HashTable {
    private:
        LinkedList<T,S> * hash_table;
        int size;
        int num_of_elements;
//        static const double A = (sqrt(5) -1)/2;
    public:
        explicit HashTable(int Hsize);
        ~HashTable();
        LinkedList<T,S> * getHT();
        int HashFunction(S key);
        void HashTableInsert(T info , S key);
        void HashTableDelete(S key);
        ListNode<T,S> * HashTableSearch(S key);
        void resizeHashTable();
        void CopyElements(LinkedList<T,S> * hash_table_dest, LinkedList<T,S> * hash_table_src, int src_size);
        int getSize();

};

template<class T, class S>
int  HashTable<T,S>::getSize()
{
    return  size;
}

template<class T, class S>
void HashTable<T,S>::CopyElements(LinkedList<T,S> * hash_table_dest, LinkedList<T,S> * hash_table_src, int src_size)
{
    for (int i = 0; i < src_size; ++i)
    {
        ListNode<T,S>* tmp = hash_table_src[i].LinkedListGetHead();

        while (tmp != nullptr)
        {
            int index = HashFunction(tmp->getKey());
            hash_table_dest[index].LinkedListInsert(tmp->getInfo(),tmp->getKey());
            tmp = tmp->next;
        }

    }
}

template<class T, class S>
void HashTable<T,S>::resizeHashTable()
{
    if(num_of_elements == size)
    {
        size =  EXPAND * size;
        auto new_hash_table = new LinkedList<T,S>[size];
        CopyElements(new_hash_table, hash_table, size/EXPAND);
        for (int i = 0; i < size/EXPAND ; ++i)
        {
            hash_table[i].clearList();
        }

        auto tmp = hash_table;
        hash_table = new_hash_table;
        delete [] tmp;
        return;
    }
    if(num_of_elements== size/SHRINK)
    {
        size =   size/EXPAND;
        auto new_hash_table = new LinkedList<T,S>[size];
        CopyElements(new_hash_table, hash_table, size * EXPAND);
        for (int i = 0; i < size*EXPAND ; ++i)
        {
            hash_table[i].clearList();
        }

        auto tmp = hash_table;
        hash_table = new_hash_table;
        delete [] tmp;
        return;
    }

}

template<class T, class S>
void HashTable<T,S>::HashTableInsert(T info , S key)
{
    resizeHashTable();
    int index = HashFunction(key);
    hash_table[index].LinkedListInsert(info,key);
    num_of_elements++;
}

template<class T, class S>
ListNode<T,S> * HashTable<T,S>::HashTableSearch(S key)
{
    int index = HashFunction(key);
    return hash_table[index].LinkedListFind(key);
}

template<class T, class S>
void HashTable<T,S>::HashTableDelete(S key)
{
    resizeHashTable();
    int index = HashFunction(key);
    hash_table[index].LinkedListRemove(key);
    num_of_elements--;
}

template<class T, class S>
int HashTable<T,S>::HashFunction(S key)
{
    double tmp;
    return floor(size * modf(A*key, &tmp));
}

template<class T, class S>
LinkedList<T,S> * HashTable<T,S>::getHT()
{
    return  hash_table;
}

template<class T, class S>
HashTable<T,S>::HashTable(int Hsize) : hash_table(new LinkedList<T,S>[Hsize]) ,size(Hsize), num_of_elements(0)  {}


template<class T, class S>
HashTable<T,S>::~HashTable()
{
    for (int i = 0; i < size ; ++i)
    {
        hash_table[i].clearList();
    }
    delete [] hash_table;
}

#endif //MIVNI2_HASHTABLE_H
