//
// Created by omarm on 06/01/2022.
//

#ifndef MIVNI2_UNIONFIND_H
#define MIVNI2_UNIONFIND_H
#include "Group.h"
#include "GroupOfGroups.h"


class UnionFind {
    private:
        int scale;
        Group ** groups;
        GroupOfGroups** groupOfGroups;
        int k;

    public:
        UnionFind(int scale , int k) : scale(scale) , groups(new Group*[k+1]) , groupOfGroups(new GroupOfGroups*[k+1]) , k(k)
        {
            for (int i = 0; i < k+1; ++i)
            {
                groups[i] = new Group(i);
                groupOfGroups[i] = new GroupOfGroups(k,scale,i);
                groups[i]->setLabel(groupOfGroups[i]);
                groupOfGroups[i]->setRoot(groups[i]);
            }
        }
        ~UnionFind();
        GroupOfGroups* Find(int group_id);
        void Union(int group_id1, int group_id2);



};



#endif //MIVNI2_UNIONFIND_H
