//
// Created by omarm on 05/01/2022.
//

#include <iostream>

#include "LinkedList.h"
#include "HashTable.h"
int main()
{

    HashTable<int,int> h1(2);


    h1.HashTableInsert(1,1);
    h1.HashTableInsert(2,2);
    h1.HashTableInsert(3,3);


//    (h1.getHT())[0].LinkedListInsert(1,1);
//    (h1.getHT())[0].LinkedListInsert(2,2);

//    LinkedList<int, int> l1;
//
//    l1.LinkedListInsert(1,1);
//    l1.LinkedListInsert(2,2);
//
//    ListNode<int,int>* nide = l1.LinkedListFind(2);
//
//    l1.LinkedListRemove(2);
//    l1.LinkedListRemove(1);
//
//
////    std::cout << l1.LinkedListGetHead()->getKey();

    return 0;
}