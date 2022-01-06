//
// Created by omarm on 06/01/2022.
//

#ifndef MIVNI2_GROUP_H
#define MIVNI2_GROUP_H
#include "GroupOfGroups.h"

class Group {
private:
    int group_id;
    Group * father;
    GroupOfGroups * label;

public:
    Group(int group_id) : group_id(group_id), father(nullptr), label(nullptr) {}
    void setFather(Group * newFather);
    void setLabel(GroupOfGroups * label);
    Group * getFather();
    GroupOfGroups * getLabel();
    int getGroupId();

};

void Group::setFather(Group * newFather)
{
    father = newFather;
}

void Group::setLabel(GroupOfGroups * newLabel)
{
       label = newLabel;
}

Group * Group::getFather()
{
    return father;
}

GroupOfGroups * Group::getLabel()
{
    return label;
}

int Group::getGroupId()
{
    return group_id;
}


#endif //MIVNI2_GROUP_H
