//
// Created by omarm on 06/01/2022.
//

#ifndef MIVNI2_GROUPOFGROUPS_H
#define MIVNI2_GROUPOFGROUPS_H
#include "HashTable.h"
#include "Player.h"
#include "AVLnode.h"
#include "LevelAndId.h"
#include "LevelAndNumber.h"


class GroupOfGroups {

    private:

        int scale;

        HashTable<Player,int> playersHT;
        std::shared_ptr<AVL_node<int,LevelAndId>> level_and_id_player_tree; // only for level>0
        std::shared_ptr<AVL_node<int,LevelAndNumber>> level_and_number_player_tree;  // only for level>0
        std::shared_ptr<AVL_node<int,LevelAndNumber>>* scaleTreeArray; // only for level>0
        int* scaleLevel0Array;
        int num_of_players_with_positive_level;
        int num_of_players;

    public:
        GroupOfGroups(int k, int scale) : scale(scale) ,playersHT(k), level_and_id_player_tree(nullptr), level_and_number_player_tree(
                nullptr),scaleTreeArray(new std::shared_ptr<AVL_node<int,LevelAndNumber>>[scale]) ,scaleLevel0Array(new int[scale]),
                num_of_players_with_positive_level(0), num_of_players(0)
                {
                    for (int i = 0; i < scale; ++i)
                    {
                        scaleTreeArray[i] = nullptr;
                        scaleLevel0Array[i] =0;
                    }
        }
        ~GroupOfGroups();
        void insetToScaleTreeArray(LevelAndNumber ln, int score);
        void removePlayer(int player_id);
        void addPlayer(int player_id, int group_id, int score);
        void increaseLevel(int player_id , int delta);


};


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
        if(lnNode->getKey().getNumber()  != 1)
        {
            int old_number = lnNode->getKey().getNumber();
            LevelAndNumber ln1(old_level , old_number-1);
            level_and_number_player_tree = level_and_number_player_tree->insert(level_and_number_player_tree,ln1,0);
            level_and_number_player_tree = level_and_number_player_tree->treeBalance(level_and_number_player_tree->find(level_and_number_player_tree,ln1));
        }




//        LevelAndNumber ln4(old_level+delta, old_number);
        LevelAndNumber ln4(old_level + delta, old_number+1);
        level_and_number_player_tree = level_and_number_player_tree->deleteNode(level_and_number_player_tree, ln4);
        level_and_number_player_tree = level_and_number_player_tree->insert(level_and_number_player_tree,ln4,0);
        level_and_number_player_tree = level_and_number_player_tree->treeBalance(level_and_number_player_tree->find(level_and_number_player_tree,ln4));



    }





}

void GroupOfGroups::addPlayer(int player_id, int group_id, int score)
{
    Player player(player_id,group_id,score);
    playersHT.HashTableInsert(player,player_id);

    scaleLevel0Array[score]++;

    num_of_players++;
}



void GroupOfGroups::removePlayer(int player_id)
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

    for (int i = 0; i < scale; ++i)
    {
        auto current_tree = scaleTreeArray[i];
        scaleTreeArray[i] = nullptr;
        current_tree->postOrderAndDestroy(current_tree);
        current_tree = nullptr;
    }
    delete [] scaleTreeArray;

    delete [] scaleLevel0Array;
}



#endif //MIVNI2_GROUPOFGROUPS_H
