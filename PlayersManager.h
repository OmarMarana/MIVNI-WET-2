//
// Created by omarm on 10/01/2022.
//

#ifndef MIVNI2_PLAYERSMANAGER_H
#define MIVNI2_PLAYERSMANAGER_H

#include "UnionFind.h"
#include "library2.h"
class PlayersManager {

    private:

    std::shared_ptr<AVL_node<int,LevelAndId>> level_and_id_player_tree; // only for level>0
    UnionFind UF;
    HashTable<Player,int> playersHT;
//    std::shared_ptr<AVL_node<int,LevelAndNumber>>* scaleTreeArray; // only for level>0
    int* scalePositiveLevelArray;
    std::shared_ptr<AVL_node<int,LevelAndNumber>> level_and_number_player_tree;  // only for level>0
    int* scaleLevel0Array;
    int num_of_players_with_positive_level;
    int num_of_players;
    int scale;
    int k;

public:
    PlayersManager(int scale, int k) : level_and_id_player_tree(nullptr), UF(scale,k), playersHT(k),
    scalePositiveLevelArray(new int[scale+1]) , level_and_number_player_tree(nullptr),
    scaleLevel0Array(new int[scale + 1]), num_of_players_with_positive_level(0), num_of_players(0), scale(scale), k(k)
    {
        for (int i = 0; i < scale+1; ++i)
        {
            scalePositiveLevelArray[i] =0;
            scaleLevel0Array[i] =0;
        }
    }
    ~PlayersManager();
//    void* init(int k, int scale);
    StatusType PMmergeGroups( int GroupID1, int GroupID2);
    StatusType PMaddPlayer( int PlayerID, int GroupID, int score);
    StatusType PMremovePlayer(int PlayerID);
    StatusType PMincreasePlayerIDLevel(int PlayerID, int LevelIncrease);
    StatusType PMchangePlayerIDScore(int PlayerID, int NewScore);
    StatusType PMgetPercentOfPlayersWithScoreInBounds ( int GroupID, int score, int lowerLevel, int higherLevel, double * players);
    StatusType PMaverageHighestPlayerLevelByGroup( int GroupID, int m, double * avgLevel);


};


#endif //MIVNI2_PLAYERSMANAGER_H
