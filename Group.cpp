//
// Created by omarm on 06/01/2022.
//

#include "Group.h"

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