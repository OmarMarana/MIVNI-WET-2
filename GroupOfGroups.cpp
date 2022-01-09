//
// Created by omarm on 06/01/2022.
//

#include "GroupOfGroups.h"


int GroupOfGroups::getNumOfGroups()
{
    return num_of_groups;
}


int GroupOfGroups::getIndex()
{
    return index;
}


void GroupOfGroups::setRoot(Group* new_root)
{
    root = new_root;
}

Group* GroupOfGroups::getRoot()
{
    return root;
}

void GroupOfGroups::averageHighestPlayerLevelByGroup(int m, double * avgLevel)
{
    double sum =0;

    if(m <= num_of_players_with_positive_level)
    {
        auto LInode = level_and_id_player_tree->select(level_and_id_player_tree,num_of_players_with_positive_level-m+1);
        sum = level_and_id_player_tree->sumInfoOfHighest(level_and_id_player_tree,LInode->getKey());
        *avgLevel = sum/m;
        return;
    }
    else
    {
        *avgLevel = level_and_number_player_tree->getInfo()/m;
        return;
    }

}


int GroupOfGroups::getPercentOfPlayers ( int score, int lowerLevel, int higherLevel, double * players)
{
    auto LBnode = scaleTreeArray[score]->findClosestNodeFromAbove(scaleTreeArray[score],lowerLevel);
    auto HBnode = scaleTreeArray[score]->findClosestNodeFromBeneath(scaleTreeArray[score],higherLevel);


    double denominator =0;
    double nominator =0;

    if(scaleTreeArray[score] == nullptr)
    {
        if(lowerLevel <= 0)
        {
            if(scaleLevel0Array[score] == 0)
            {
                *players = 0;
                return SUCCESS;
            }
            else
            {
                nominator = scaleLevel0Array[score];
            }
        }
        else
        {
            *players = 0;
            return SUCCESS;
        }
    }
    else
    {
        if(HBnode== nullptr || LBnode== nullptr || HBnode->getKey().getLevel() < LBnode->getKey().getLevel())
        {
            return FAILURE; // catch FAILURE in DS func
        }

        int higher_than_HB = scaleTreeArray[score]->sumInfoOfHighest(scaleTreeArray[score],HBnode->getKey()) - HBnode->getKey().getNumber();
        int lower_than_LB = scaleTreeArray[score]->sumInfoOfLowest(scaleTreeArray[score],LBnode->getKey()) - LBnode->getKey().getNumber();
        nominator = scaleTreeArray[score]->getInfo() - higher_than_HB  - lower_than_LB;
    }




//    if(LBnode->getLeft_son()!= nullptr)
//    {
//        nominator -= LBnode->getLeft_son()->getInfo();
//    }
//    if(HBnode->getRight_son()!= nullptr)
//    {
//        nominator -= HBnode->getRight_son()->getInfo();
//    }


    auto LBnodeGlobal = level_and_number_player_tree->findClosestNodeFromAbove(level_and_number_player_tree,lowerLevel);
    auto HBnodeGlobal = level_and_number_player_tree->findClosestNodeFromBeneath(level_and_number_player_tree,higherLevel);

    if(HBnodeGlobal== nullptr || LBnodeGlobal== nullptr || HBnodeGlobal->getKey().getLevel() < LBnodeGlobal->getKey().getLevel())
    {
        return FAILURE; // catch FAILURE in DS func
    }


    int higher_than_HB_G = level_and_number_player_tree->sumInfoOfHighest(level_and_number_player_tree,HBnodeGlobal->getKey()) - HBnodeGlobal->getKey().getNumber();
    int lower_than_LB_G = level_and_number_player_tree->sumInfoOfLowest(level_and_number_player_tree,LBnodeGlobal->getKey()) - LBnodeGlobal->getKey().getNumber();
    denominator = level_and_number_player_tree->getInfo() - lower_than_LB_G - higher_than_HB_G;
//    if(LBnodeGlobal->getLeft_son()!= nullptr)
//    {
//        denominator -= LBnodeGlobal->getLeft_son()->getInfo();
//    }
//    if(HBnodeGlobal->getRight_son()!= nullptr)
//    {
//        denominator -= HBnodeGlobal->getRight_son()->getInfo();
//    }

    if(lowerLevel <=0)
    {
        nominator += scaleLevel0Array[score];
        int sum=0;
        for (int i = 0; i < scale; ++i) {
            sum+= scaleLevel0Array[i];
        }
        denominator += sum;
    }

    *players = (nominator/denominator) * 100 ;
    return SUCCESS;


}

HashTable<Player,int>* GroupOfGroups::GetPlayersHT()
{
    return &playersHT;
}

void GroupOfGroups::mergeGroupOfGroupsHelper(GroupOfGroups* groupOfGroups_dest , GroupOfGroups* groupOfGroups_src)
{
    auto src_HT = groupOfGroups_src->GetPlayersHT();
    auto dest_HT = groupOfGroups_dest->GetPlayersHT();
    for (int i = 0; i < src_HT->getSize(); ++i)
    {
        auto tmp = (*src_HT).getHT()[i].LinkedListGetHead();
        while (tmp != nullptr)
        {
            dest_HT->HashTableInsert(tmp->getInfo(),tmp->getKey());
            tmp = tmp->next;
        }
    }


    int m = groupOfGroups_dest->num_of_players_with_positive_level;
    int n = groupOfGroups_src->num_of_players_with_positive_level;

    if(m+n != 0)
    {
        int* mergedLevelSumArray= new int[m+n];
        auto new_dest_tree = groupOfGroups_dest->level_and_id_player_tree->mergeAvlTrees(groupOfGroups_dest->level_and_id_player_tree,
                                                                                         groupOfGroups_src->level_and_id_player_tree,mergedLevelSumArray,m,n);
        groupOfGroups_dest->level_and_id_player_tree->postOrderAndDestroy(groupOfGroups_dest->level_and_id_player_tree);
        groupOfGroups_src->level_and_id_player_tree->postOrderAndDestroy(groupOfGroups_src->level_and_id_player_tree);
        groupOfGroups_dest->level_and_id_player_tree= new_dest_tree;
        delete [] mergedLevelSumArray;


        m = groupOfGroups_dest->level_and_number_player_tree->countNodes( groupOfGroups_dest->level_and_number_player_tree);
        n = groupOfGroups_src->level_and_number_player_tree->countNodes( groupOfGroups_src->level_and_number_player_tree);
        int* mergedLevelSumArray1= new int[m+n];
        auto new_dest_tree1 = groupOfGroups_dest->level_and_number_player_tree->mergeAvlTrees(groupOfGroups_dest->level_and_number_player_tree,
                                                                                              groupOfGroups_src->level_and_number_player_tree,mergedLevelSumArray1,m,n);
        groupOfGroups_dest->level_and_number_player_tree->postOrderAndDestroy(groupOfGroups_dest->level_and_number_player_tree);
        groupOfGroups_src->level_and_number_player_tree->postOrderAndDestroy(groupOfGroups_src->level_and_number_player_tree);
        groupOfGroups_dest->level_and_number_player_tree= new_dest_tree1;
        delete [] mergedLevelSumArray1;


        for (int i = 0; i < scale; ++i)
        {
            m = groupOfGroups_dest->scaleTreeArray[i]->countNodes(groupOfGroups_dest->scaleTreeArray[i]);
            n = groupOfGroups_src->scaleTreeArray[i]->countNodes(groupOfGroups_src->scaleTreeArray[i]);
            int* mergedLevelSumArray2= new int[m+n];
            auto new_dest_tree2 = groupOfGroups_dest->scaleTreeArray[i]->mergeAvlTrees(groupOfGroups_dest->scaleTreeArray[i],
                                                                                       groupOfGroups_src->scaleTreeArray[i],mergedLevelSumArray2,m,n);
            groupOfGroups_dest->scaleTreeArray[i]->postOrderAndDestroy(groupOfGroups_dest->scaleTreeArray[i]);
            groupOfGroups_src->scaleTreeArray[i]->postOrderAndDestroy(groupOfGroups_src->scaleTreeArray[i]);
            groupOfGroups_dest->scaleTreeArray[i]= new_dest_tree2;
            delete [] mergedLevelSumArray2;

        }
    }




    for (int i = 0; i < scale; ++i)
    {
        groupOfGroups_dest->scaleLevel0Array[i] +=groupOfGroups_src->scaleLevel0Array[i];
    }

    groupOfGroups_dest->num_of_players +=groupOfGroups_src->num_of_players;

    groupOfGroups_dest->num_of_players_with_positive_level +=groupOfGroups_src->num_of_players_with_positive_level;

    groupOfGroups_dest->num_of_groups +=groupOfGroups_src->num_of_groups;
}


void GroupOfGroups::mergeGroupOfGroups(GroupOfGroups* groupOfGroups1 , GroupOfGroups* groupOfGroups2)
{
    if(groupOfGroups1->num_of_groups >= groupOfGroups2->num_of_groups)
    {
        mergeGroupOfGroupsHelper(groupOfGroups1,groupOfGroups2);
        groupOfGroups2->getRoot()->setFather(groupOfGroups1->getRoot());
        delete groupOfGroups2;
    }
    else
    {
        mergeGroupOfGroupsHelper(groupOfGroups2,groupOfGroups1);
        groupOfGroups1->getRoot()->setFather(groupOfGroups2->getRoot());
        delete groupOfGroups1;
    }
}


void GroupOfGroups::changeScore(int player_id , int new_score)
{
    auto hashNode = playersHT.HashTableSearch(player_id);
    auto old_score = hashNode->getInfo().getScore();
    auto level = hashNode->getInfo().getLevel();
    hashNode->getInfo().setScore(new_score);

    if(level == 0)
    {
        scaleLevel0Array[old_score]--;
        scaleLevel0Array[new_score]++;
    }
    else
    {

        LevelAndNumber ln(level,0);
        auto lnNode= scaleTreeArray[old_score]->find(scaleTreeArray[old_score],ln);
        int old_number  = lnNode->getKey().getNumber();
        scaleTreeArray[old_score] =scaleTreeArray[old_score]->deleteNode(scaleTreeArray[old_score] ,ln);
        if(old_number != 1)
        {
            LevelAndNumber ln1(level,old_number-1);
            scaleTreeArray[old_score] = scaleTreeArray[old_score]->insert(scaleTreeArray[old_score],ln1,0);
            scaleTreeArray[old_score] = scaleTreeArray[old_score]->treeBalance(scaleTreeArray[old_score]->find(scaleTreeArray[old_score],ln1));
        }

        auto lnNode1= scaleTreeArray[new_score]->find(scaleTreeArray[new_score],ln);
        int old_number1  = lnNode1->getKey().getNumber();
        scaleTreeArray[new_score] =scaleTreeArray[new_score]->deleteNode(scaleTreeArray[new_score] ,ln);

        LevelAndNumber ln2(level,old_number1+1);
        scaleTreeArray[new_score] = scaleTreeArray[new_score]->insert(scaleTreeArray[new_score],ln2,0);
        scaleTreeArray[new_score] = scaleTreeArray[new_score]->treeBalance(scaleTreeArray[new_score]->find(scaleTreeArray[new_score],ln2));

    }

}


void GroupOfGroups::increaseLevel(int player_id , int delta)
{
    auto node = playersHT.HashTableSearch(player_id);
    Player player = node->getInfo();
    int old_level = player.getLevel();
    int score = player.getScore();
    node->getInfo().setLevel(node->getInfo().getLevel() + delta);

    if(old_level == 0)
    {
        LevelAndId li( old_level + delta, player_id);
        level_and_id_player_tree =level_and_id_player_tree->insert(level_and_id_player_tree, li, 0);
        level_and_id_player_tree = level_and_id_player_tree->treeBalance(level_and_id_player_tree->find(level_and_id_player_tree,li));

        LevelAndNumber ln(old_level + delta,1);
        auto lnNode = level_and_number_player_tree->find(level_and_number_player_tree,ln);
        if(lnNode == nullptr)
        {
            level_and_number_player_tree = level_and_number_player_tree->insert(level_and_number_player_tree,ln,0);
            level_and_number_player_tree = level_and_number_player_tree->treeBalance(level_and_number_player_tree->find(level_and_number_player_tree,ln));
        }
        else
        {
            int old_number = lnNode->getKey().getNumber();
            level_and_number_player_tree = level_and_number_player_tree->deleteNode(level_and_number_player_tree, ln);
            LevelAndNumber ln1(old_level + delta, old_number+1);
            level_and_number_player_tree = level_and_number_player_tree->insert(level_and_number_player_tree,ln1,0);
            level_and_number_player_tree = level_and_number_player_tree->treeBalance(level_and_number_player_tree->find(level_and_number_player_tree,ln1));
        }

        LevelAndNumber ln2(old_level + delta,1);
        auto lnNode2 = scaleTreeArray[score]->find(scaleTreeArray[score],ln2);
        if(lnNode2 == nullptr)
        {
            scaleTreeArray[score] =  scaleTreeArray[score]->insert( scaleTreeArray[score],ln2,0);
            scaleTreeArray[score] =  scaleTreeArray[score]->treeBalance( scaleTreeArray[score]->find( scaleTreeArray[score],ln2));
        }
        else
        {
            int old_number2 = lnNode2->getKey().getNumber();
            scaleTreeArray[score] =  scaleTreeArray[score]->deleteNode( scaleTreeArray[score], ln2);
            LevelAndNumber ln3(old_level + delta, old_number2+1);
            scaleTreeArray[score] = scaleTreeArray[score]->insert(scaleTreeArray[score],ln3,0);
            scaleTreeArray[score] = scaleTreeArray[score]->treeBalance(scaleTreeArray[score]->find(scaleTreeArray[score],ln3));
        }
        scaleLevel0Array[score]--;
        num_of_players_with_positive_level++;
    }
    else
    {
        LevelAndId li( old_level, player_id);
        level_and_id_player_tree = level_and_id_player_tree->deleteNode(level_and_id_player_tree,li);
        LevelAndId li1( old_level+delta, player_id);
        level_and_id_player_tree =level_and_id_player_tree->insert(level_and_id_player_tree, li1, 0);
        level_and_id_player_tree = level_and_id_player_tree->treeBalance(level_and_id_player_tree->find(level_and_id_player_tree,li1));


        LevelAndNumber ln2(old_level,1);
        auto lnNode = level_and_number_player_tree->find(level_and_number_player_tree,ln2);
        int old_number = lnNode->getKey().getNumber();

        level_and_number_player_tree = level_and_number_player_tree->deleteNode(level_and_number_player_tree,ln2);
        if(old_number  != 1)
        {
//            int old_number = lnNode->getKey().getNumber();
            LevelAndNumber ln1(old_level , old_number-1);
            level_and_number_player_tree = level_and_number_player_tree->insert(level_and_number_player_tree,ln1,0);
            level_and_number_player_tree = level_and_number_player_tree->treeBalance(level_and_number_player_tree->find(level_and_number_player_tree,ln1));
        }


//        LevelAndNumber ln4(old_level+delta, old_number);
        LevelAndNumber ln4(old_level + delta, 1);
        auto lnNode2 = level_and_number_player_tree->find(level_and_number_player_tree,ln4);
        int old_number2 = lnNode2->getKey().getNumber();
        ln4.setNumber(old_number2+1);
        level_and_number_player_tree = level_and_number_player_tree->deleteNode(level_and_number_player_tree, ln4);
        level_and_number_player_tree = level_and_number_player_tree->insert(level_and_number_player_tree,ln4,0);
        level_and_number_player_tree = level_and_number_player_tree->treeBalance(level_and_number_player_tree->find(level_and_number_player_tree,ln4));


        LevelAndNumber ln3(old_level,1);
        auto lnNode1 = level_and_number_player_tree->find(level_and_number_player_tree,ln3);
        int old_number1 = lnNode1->getKey().getNumber();

        scaleTreeArray[score] = scaleTreeArray[score]->deleteNode(scaleTreeArray[score],ln3);
        if(old_number1  != 1)
        {
//            int old_number = lnNode->getKey().getNumber();
            LevelAndNumber ln1(old_level , old_number-1);
            scaleTreeArray[score] = scaleTreeArray[score]->insert(scaleTreeArray[score],ln1,0);
            scaleTreeArray[score] = scaleTreeArray[score]->treeBalance(scaleTreeArray[score]->find(scaleTreeArray[score],ln1));
        }

//        LevelAndNumber ln4(old_level+delta, old_number);
        LevelAndNumber ln5(old_level + delta, 1);
        auto lnNode3 = level_and_number_player_tree->find(level_and_number_player_tree,ln5);
        int old_number3 = lnNode3->getKey().getNumber();
        ln5.setNumber(old_number3+1);
        scaleTreeArray[score] = scaleTreeArray[score]->deleteNode(scaleTreeArray[score], ln5);
        scaleTreeArray[score] = scaleTreeArray[score]->insert(scaleTreeArray[score],ln5,0);
        scaleTreeArray[score] = scaleTreeArray[score]->treeBalance(scaleTreeArray[score]->find(scaleTreeArray[score],ln5));

    }






}

void GroupOfGroups::addPlayerID(int player_id, int group_id, int score)
{
    Player player(player_id,group_id,score);
    playersHT.HashTableInsert(player,player_id);

    scaleLevel0Array[score]++;

    num_of_players++;
}



void GroupOfGroups::removePlayerID(int player_id)
{
    auto node = playersHT.HashTableSearch(player_id);
    Player player = node->getInfo();
    playersHT.HashTableDelete(player_id);

    LevelAndId li(player.getLevel(),player_id);
    level_and_id_player_tree = level_and_id_player_tree->deleteNode(level_and_id_player_tree, li);

    LevelAndNumber ln(player.getLevel(), 0);
    auto global_lnNode = level_and_number_player_tree->find(level_and_number_player_tree,ln);
    global_lnNode->getKey().setNumber(global_lnNode->getKey().getNumber() -1);
    if(global_lnNode->getKey().getNumber() == 0)
    {
        level_and_number_player_tree = level_and_number_player_tree->deleteNode(level_and_number_player_tree,ln);
    }

    auto lnNode = scaleTreeArray[player.getScore()]->find(scaleTreeArray[player.getScore()],ln);
    lnNode->getKey().setNumber(lnNode->getKey().getNumber() -1);
    if(lnNode->getKey().getNumber() == 0)
    {
        scaleTreeArray[player.getScore()] = scaleTreeArray[player.getScore()]->deleteNode(scaleTreeArray[player.getScore()],ln);
    }

    if(player.getLevel() == 0)
    {
        scaleLevel0Array[player.getScore()]--;
    }

    if(player.getLevel() > 0)
    {
        num_of_players_with_positive_level--;
    }

    num_of_players--;

}

void GroupOfGroups::insetToScaleTreeArray(LevelAndNumber ln, int score)
{
    scaleTreeArray[score] = scaleTreeArray[score]->insert(scaleTreeArray[score],ln,ln.getNumber());
    scaleTreeArray[score] = scaleTreeArray[score]->treeBalance(scaleTreeArray[score]->find(scaleTreeArray[score],ln));

}

GroupOfGroups::~GroupOfGroups()
{
    level_and_id_player_tree->postOrderAndDestroy(level_and_id_player_tree);
    level_and_number_player_tree->postOrderAndDestroy(level_and_number_player_tree);

    for (int i = 0; i < scale + 1; ++i)
    {
        auto current_tree = scaleTreeArray[i];
        scaleTreeArray[i] = nullptr;
        current_tree->postOrderAndDestroy(current_tree);
        current_tree = nullptr;
    }
    delete [] scaleTreeArray;

    delete [] scaleLevel0Array;
}


//*****************************************************************
//Group
//*****************************************************************


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