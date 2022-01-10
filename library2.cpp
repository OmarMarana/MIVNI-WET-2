//
// Created by omarm on 10/01/2022.
//

#include "library2.h"
#include "PlayersManager.h"



void *Init(int k, int scale)
{
    PlayersManager* DS = new PlayersManager(scale,k);
    return (void*) DS;
}

StatusType MergeGroups(void *DS, int GroupID1, int GroupID2)
{
    if(DS == nullptr)
    {
        return INVALID_INPUT;
    }
    return ((PlayersManager*)DS)->PMmergeGroups(GroupID1,GroupID2);
}

StatusType AddPlayer(void *DS, int PlayerID, int GroupID, int score)
{
    if(DS == nullptr)
    {
        return INVALID_INPUT;
    }
    return ((PlayersManager*)DS)->PMaddPlayer(PlayerID,GroupID,score);
}


StatusType RemovePlayer(void *DS, int PlayerID)
{
    if(DS == nullptr)
    {
        return INVALID_INPUT;
    }
    return ((PlayersManager*)DS)->PMremovePlayer(PlayerID);
}


StatusType IncreasePlayerIDLevel(void *DS, int PlayerID, int LevelIncrease)
{
    if(DS == nullptr)
    {
        return INVALID_INPUT;
    }
    return ((PlayersManager*)DS)->PMincreasePlayerIDLevel(PlayerID,LevelIncrease);
}


StatusType ChangePlayerIDScore(void *DS, int PlayerID, int NewScore)
{
    if(DS == nullptr)
    {
        return INVALID_INPUT;
    }
    return ((PlayersManager*)DS)->PMchangePlayerIDScore(PlayerID,NewScore);
}


StatusType GetPercentOfPlayersWithScoreInBounds(void *DS, int GroupID, int score, int lowerLevel, int higherLevel,
                                                double * players)
{
    if(DS == nullptr)
    {
        return INVALID_INPUT;
    }
    return ((PlayersManager*)DS)->PMgetPercentOfPlayersWithScoreInBounds(GroupID,score,lowerLevel,higherLevel,players);
}

StatusType AverageHighestPlayerLevelByGroup(void *DS, int GroupID, int m, double * level)
{
    if(DS == nullptr)
    {
        return INVALID_INPUT;
    }
    return ((PlayersManager*)DS)->PMaverageHighestPlayerLevelByGroup(GroupID, m, level);
}

void Quit(void** DS)
{
    // check if DS is null
    if(DS== nullptr || *DS== nullptr){
        return;
    }
    delete ((PlayersManager*)(*DS));
    *DS= nullptr;

}
//StatusType GetPlayersBound(void *DS, int GroupID, int score, int m,
//                           int * LowerBoundPlayers, int * HigherBoundPlayers);