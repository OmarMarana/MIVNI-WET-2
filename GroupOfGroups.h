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
#define FAILURE -1
#define SUCCESS 0




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
        int num_of_groups;
//        int num_of_positive_levels;

    public:
        GroupOfGroups(int k, int scale) : scale(scale) ,playersHT(k), level_and_id_player_tree(nullptr), level_and_number_player_tree(
                nullptr),scaleTreeArray(new std::shared_ptr<AVL_node<int,LevelAndNumber>>[scale]) ,scaleLevel0Array(new int[scale]),
                num_of_players_with_positive_level(0), num_of_players(0) , num_of_groups(1)
                {
                    for (int i = 0; i < scale; ++i)
                    {
                        scaleTreeArray[i] = nullptr;
                        scaleLevel0Array[i] =0;
                    }
        }
        ~GroupOfGroups();
        void insetToScaleTreeArray(LevelAndNumber ln, int score);
        void removePlayerID(int player_id);
        void addPlayerID(int player_id, int group_id, int score);
        void increaseLevel(int player_id , int delta);
        void changeScore(int player_id , int new_score);
        void mergeGroupOfGroups(GroupOfGroups* groupOfGroups1 , GroupOfGroups* groupOfGroups2);
        void mergeGroupOfGroupsHelper(GroupOfGroups* groupOfGroups_dest , GroupOfGroups* groupOfGroups_src);
        HashTable<Player,int>* GetPlayersHT();
        //return -1 incase of FAILURE ELSE RETURN 0
        int getPercentOfPlayers ( int score, int lowerLevel, int higherLevel, double * players);
        void averageHighestPlayerLevelByGroup(int m, double * avgLevel);


};





#endif //MIVNI2_GROUPOFGROUPS_H
