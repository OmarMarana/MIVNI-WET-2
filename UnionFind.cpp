//
// Created by omarm on 06/01/2022.
//

#include "UnionFind.h"


void UnionFind::Union(int group_id1, int group_id2)
{
    auto group_of_groups1 = Find(group_id1);
    auto group_of_groups2 = Find(group_id2);

    group_of_groups1->mergeGroupOfGroups(group_of_groups1,group_of_groups2);

}

GroupOfGroups* UnionFind::Find(int group_id)
{

    auto root = groups[group_id-1];
    while (root->getFather() != nullptr)
    {

        root = root->getFather();
    }
    auto iterator = groups[group_id-1];
    Group* temp;
    while (iterator->getFather() != root&& iterator!= root)
    {
        temp=iterator;
        iterator = iterator->getFather();
        temp->setFather(root);
    }

    return root->getLabel();
}



UnionFind::~UnionFind()
{
    for (int i = 0; i < k; ++i)
    {
        delete groups[i];
        delete groupOfGroups[i];
    }
    delete [] groups;
    delete [] groupOfGroups;

}