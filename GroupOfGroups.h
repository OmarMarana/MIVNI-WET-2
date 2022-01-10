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
#define GOG_FAILURE -1
#define GOG_SUCCESS 0

class GroupOfGroups;

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


class GroupOfGroups {

    private:

        int scale;

        HashTable<Player,int> playersHT;
        std::shared_ptr<AVL_node<int,LevelAndId>> level_and_id_player_tree; // only for level>0
        std::shared_ptr<AVL_node<int,LevelAndNumber>> level_and_number_player_tree;  // only for level>0
//        std::shared_ptr<AVL_node<int,LevelAndNumber>>* scaleTreeArray; // only for level>0
        int* scalePositiveLevelArray;
        int* scaleLevel0Array;
        int num_of_players_with_positive_level;
        int num_of_players;
        int num_of_groups;
        Group * root;
        int index;
//        int num_of_positive_levels;

    public:
        GroupOfGroups(int k, int scale, int index) : scale(scale) ,playersHT(k), level_and_id_player_tree(nullptr), level_and_number_player_tree(
                nullptr), scalePositiveLevelArray(new int[scale+1]),scaleLevel0Array(new int[scale+1]),
                num_of_players_with_positive_level(0), num_of_players(0) , num_of_groups(1), root(nullptr), index(index)
                {
                    for (int i = 0; i < scale+1; ++i)
                    {
                        scaleLevel0Array[i] =0;
                        scalePositiveLevelArray[i] =0;
                    }
        }
        ~GroupOfGroups();
//        void insetToScaleTreeArray(LevelAndNumber ln, int score);
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
        void setRoot(Group* new_root);
        Group* getRoot();
        int getIndex();
        int getNumOfGroups();
        int getNumOfPlayers();


};





#endif //MIVNI2_GROUPOFGROUPS_H
