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
    h1.HashTableInsert(4,4);

    h1.HashTableDelete(1);
    h1.HashTableDelete(2);
    h1.HashTableDelete(4);
//    h1.HashTableDelete(3);

    std::cout << h1.getSize()<< "\n";



//    auto n1 = h1.HashTableSearch(1);
//    std::cout << n1->getKey() << "\n";
//
//
//    h1.HashTableDelete(2);
//
//    auto n2 = h1.HashTableSearch(2);
//
//
//    if(n2 == nullptr)
//    {
//        std::cout << "2 null"  << "\n";
//    }
//
//    h1.HashTableDelete(3);
//
//    auto n3 = h1.HashTableSearch(3);
//
//
//    if(n3 == nullptr)
//    {
//        std::cout << "3 null"  << "\n";
//    }
//
//    h1.HashTableDelete(1);
//
//    auto n4 = h1.HashTableSearch(1);
//
//
//    if(n4 == nullptr)
//    {
//        std::cout << "1 null"  << "\n";
//    }


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