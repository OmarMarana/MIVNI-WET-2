//
// Created by omarm on 10/01/2022.
//

#include "PlayersManager.h"
#include <exception>

PlayersManager::~PlayersManager()
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


StatusType PlayersManager::PMmergeGroups( int GroupID1, int GroupID2)
{
    if(GroupID1 <=0 || GroupID2 <=0 || GroupID2 > k ||  GroupID1 > k)
    {
        return INVALID_INPUT;
    }
    try
    {
        UF.Union(GroupID1,GroupID2);
    }
    catch(std::exception& e)
    {
        return ALLOCATION_ERROR;
    }
    return SUCCESS;
}


StatusType PlayersManager::PMaddPlayer( int PlayerID, int GroupID, int score)
{
    if(GroupID <= 0 || GroupID > k || PlayerID <= 0 || score > scale || score <= 0)
    {
        return  INVALID_INPUT;
    }
    if(playersHT.HashTableSearch(PlayerID) != nullptr)
    {
        return FAILURE;
    }
    try
    {
        Player player(PlayerID,GroupID,score);
        playersHT.HashTableInsert(player,PlayerID);

        scaleLevel0Array[score]++;

        num_of_players++;

        UF.Find(GroupID)->addPlayerID(PlayerID,GroupID,score);
    }
    catch(std::exception& e)
    {
        return ALLOCATION_ERROR;
    }
    return SUCCESS;
}



StatusType PlayersManager::PMremovePlayer(int PlayerID)
{

    if(PlayerID <=0 )
    {
        return  INVALID_INPUT;
    }
    if(playersHT.HashTableSearch(PlayerID) == nullptr)
    {
        return FAILURE;
    }

    try
    {
        auto node = playersHT.HashTableSearch(PlayerID);
        Player player = node->getInfo();
        int level = player.getLevel();
        int GroupID = player.getGroupId();
        playersHT.HashTableDelete(PlayerID);

        if(level != 0)
        {
            LevelAndId li(player.getLevel(),PlayerID);
            level_and_id_player_tree = level_and_id_player_tree->deleteNode(level_and_id_player_tree, li);

            LevelAndNumber ln(player.getLevel(), 0);
            auto global_lnNode = level_and_number_player_tree->find(level_and_number_player_tree,ln);

            int old_number = global_lnNode->getKey().getNumber();
            int old_level = global_lnNode->getKey().getLevel();
            level_and_number_player_tree = level_and_number_player_tree->deleteNode(level_and_number_player_tree,ln);
            if(  old_number != 1)
            {
                LevelAndNumber ln1(old_level , old_number-1);
                level_and_number_player_tree = level_and_number_player_tree->insert(level_and_number_player_tree,ln1,0);
                level_and_number_player_tree = level_and_number_player_tree->treeBalance(level_and_number_player_tree->find(level_and_number_player_tree,ln1));
            }

            auto lnNode = scaleTreeArray[player.getScore()]->find(scaleTreeArray[player.getScore()],ln);
            old_number = lnNode->getKey().getNumber();
            scaleTreeArray[player.getScore()] = scaleTreeArray[player.getScore()]->deleteNode(scaleTreeArray[player.getScore()],ln);
            if(  old_number != 1)
            {
                LevelAndNumber ln2(old_level , old_number-1);
                scaleTreeArray[player.getScore()] = scaleTreeArray[player.getScore()]->insert(scaleTreeArray[player.getScore()],ln2,0);
                scaleTreeArray[player.getScore()] = scaleTreeArray[player.getScore()]->treeBalance(scaleTreeArray[player.getScore()]->find(
                        scaleTreeArray[player.getScore()],ln2));
            }

            num_of_players_with_positive_level--;
        }

        if(level == 0)
        {
            scaleLevel0Array[player.getScore()]--;
        }

        num_of_players--;


        UF.Find(GroupID)->removePlayerID(PlayerID);

        //UPDATE ON THE RELEVANT GROUP

    }
    catch(std::exception& e)
    {
        return ALLOCATION_ERROR;
    }
    return SUCCESS;

}


StatusType PlayersManager::PMincreasePlayerIDLevel(int PlayerID, int LevelIncrease)
{
    if(PlayerID <= 0 || LevelIncrease <= 0)
    {
        return  INVALID_INPUT;
    }
    if(playersHT.HashTableSearch(PlayerID) == nullptr)
    {
        return FAILURE;
    }

    try
    {
        auto node = playersHT.HashTableSearch(PlayerID);
        Player player = node->getInfo();
        int old_level = player.getLevel();
        int GroupID = player.getGroupId();
        int score = player.getScore();
//        node->getInfo().setLevel(node->getInfo().getLevel() + LevelIncrease);
//        int GroupID = player.getGroupId();
//    node->getInfo().setLevel(node->getInfo().getLevel() + delta);
        Player player1(PlayerID,GroupID,score);
        player1.setLevel(old_level + LevelIncrease);
        node->setInfo(player1);
        if(old_level == 0)
        {
            LevelAndId li( old_level + LevelIncrease, PlayerID);
            level_and_id_player_tree =level_and_id_player_tree->insert(level_and_id_player_tree, li, 0);
            level_and_id_player_tree = level_and_id_player_tree->treeBalance(level_and_id_player_tree->find(level_and_id_player_tree,li));

            LevelAndNumber ln(old_level + LevelIncrease,1);
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
                LevelAndNumber ln1(old_level + LevelIncrease, old_number+1);
                level_and_number_player_tree = level_and_number_player_tree->insert(level_and_number_player_tree,ln1,0);
                level_and_number_player_tree = level_and_number_player_tree->treeBalance(level_and_number_player_tree->find(level_and_number_player_tree,ln1));
            }

            LevelAndNumber ln2(old_level + LevelIncrease,1);
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
                LevelAndNumber ln3(old_level + LevelIncrease, old_number2+1);
                scaleTreeArray[score] = scaleTreeArray[score]->insert(scaleTreeArray[score],ln3,0);
                scaleTreeArray[score] = scaleTreeArray[score]->treeBalance(scaleTreeArray[score]->find(scaleTreeArray[score],ln3));
            }
            scaleLevel0Array[score]--;
            num_of_players_with_positive_level++;
        }
        else
        {
            LevelAndId li( old_level, PlayerID);
            level_and_id_player_tree = level_and_id_player_tree->deleteNode(level_and_id_player_tree,li);
            LevelAndId li1( old_level+LevelIncrease, PlayerID);
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


//        LevelAndNumber ln4(old_level+LevelIncrease, old_number);
            LevelAndNumber ln4(old_level + LevelIncrease, 1);
            auto lnNode2 = level_and_number_player_tree->find(level_and_number_player_tree,ln4);
            int old_number2 = lnNode2->getKey().getNumber();
            ln4.setNumber(old_number2+1);
            level_and_number_player_tree = level_and_number_player_tree->deleteNode(level_and_number_player_tree, ln4);
            level_and_number_player_tree = level_and_number_player_tree->insert(level_and_number_player_tree,ln4,0);
            level_and_number_player_tree = level_and_number_player_tree->treeBalance(level_and_number_player_tree->find(level_and_number_player_tree,ln4));


            LevelAndNumber ln3(old_level,1);
            auto lnNode1 = scaleTreeArray[score]->find(scaleTreeArray[score],ln3);
            int old_number1 = lnNode1->getKey().getNumber();

            scaleTreeArray[score] = scaleTreeArray[score]->deleteNode(scaleTreeArray[score],ln3);
            if(old_number1  != 1)
            {
//            int old_number = lnNode->getKey().getNumber();
                LevelAndNumber ln1(old_level , old_number-1);
                scaleTreeArray[score] = scaleTreeArray[score]->insert(scaleTreeArray[score],ln1,0);
                scaleTreeArray[score] = scaleTreeArray[score]->treeBalance(scaleTreeArray[score]->find(scaleTreeArray[score],ln1));
            }

//        LevelAndNumber ln4(old_level+LevelIncrease, old_number);
            LevelAndNumber ln5(old_level + LevelIncrease, 1);
            auto lnNode3 = scaleTreeArray[score] ->find(scaleTreeArray[score] ,ln5);
            int old_number3 = lnNode3->getKey().getNumber();
            ln5.setNumber(old_number3+1);
            scaleTreeArray[score] = scaleTreeArray[score]->deleteNode(scaleTreeArray[score], ln5);
            scaleTreeArray[score] = scaleTreeArray[score]->insert(scaleTreeArray[score],ln5,0);
            scaleTreeArray[score] = scaleTreeArray[score]->treeBalance(scaleTreeArray[score]->find(scaleTreeArray[score],ln5));
        }

        UF.Find(GroupID)->increaseLevel(PlayerID,LevelIncrease);
    }
    catch(std::exception& e)
    {
        return ALLOCATION_ERROR;
    }
    return SUCCESS;

}


StatusType PlayersManager::PMchangePlayerIDScore(int PlayerID, int NewScore)
{
    if(PlayerID <= 0 || NewScore <=0 || NewScore > scale)
    {
        return INVALID_INPUT;
    }
    if(playersHT.HashTableSearch(PlayerID) == nullptr)
    {
        return FAILURE;
    }
    try
    {
        auto hashNode = playersHT.HashTableSearch(PlayerID);
        auto old_score = hashNode->getInfo().getScore();
        auto level = hashNode->getInfo().getLevel();
        int GroupID = hashNode->getInfo().getGroupId();
        hashNode->getInfo().setScore(NewScore);

        if(level == 0)
        {
            scaleLevel0Array[old_score]--;
            scaleLevel0Array[NewScore]++;
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

            auto lnNode1= scaleTreeArray[NewScore]->find(scaleTreeArray[NewScore],ln);
            if(lnNode1 == nullptr)
            {
                LevelAndNumber ln2(level,1);
                scaleTreeArray[NewScore] = scaleTreeArray[NewScore]->insert(scaleTreeArray[NewScore],ln2,0);
                scaleTreeArray[NewScore] = scaleTreeArray[NewScore]->treeBalance(scaleTreeArray[NewScore]->find(scaleTreeArray[NewScore],ln2));
            }
            else
            {
                int old_number1  = lnNode1->getKey().getNumber();
                scaleTreeArray[NewScore] =scaleTreeArray[NewScore]->deleteNode(scaleTreeArray[NewScore] ,ln);

                LevelAndNumber ln2(level,old_number1+1);
                scaleTreeArray[NewScore] = scaleTreeArray[NewScore]->insert(scaleTreeArray[NewScore],ln2,0);
                scaleTreeArray[NewScore] = scaleTreeArray[NewScore]->treeBalance(scaleTreeArray[NewScore]->find(scaleTreeArray[NewScore],ln2));
            }

        }

        UF.Find(GroupID)->changeScore(PlayerID,NewScore);
    }
    catch(std::exception& e)
    {
        return ALLOCATION_ERROR;
    }
    return SUCCESS;
    
}

StatusType PlayersManager::PMgetPercentOfPlayersWithScoreInBounds ( int GroupID, int score, int lowerLevel, int higherLevel, double * players)
{
    if(players == nullptr || GroupID < 0 || GroupID > k)
    {
        return  INVALID_INPUT;
    }
    try
    {
        if(GroupID == 0)
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

            auto LBnodeGlobal = level_and_number_player_tree->findClosestNodeFromAbove(level_and_number_player_tree,lowerLevel);
            auto HBnodeGlobal = level_and_number_player_tree->findClosestNodeFromBeneath(level_and_number_player_tree,higherLevel);

            if(HBnodeGlobal== nullptr || LBnodeGlobal== nullptr || HBnodeGlobal->getKey().getLevel() < LBnodeGlobal->getKey().getLevel())
            {
                return FAILURE; // catch FAILURE in DS func
            }


            int higher_than_HB_G = level_and_number_player_tree->sumInfoOfHighest(level_and_number_player_tree,HBnodeGlobal->getKey()) - HBnodeGlobal->getKey().getNumber();
            int lower_than_LB_G = level_and_number_player_tree->sumInfoOfLowest(level_and_number_player_tree,LBnodeGlobal->getKey()) - LBnodeGlobal->getKey().getNumber();
            denominator = level_and_number_player_tree->getInfo() - lower_than_LB_G - higher_than_HB_G;

            if(lowerLevel <=0)
            {
                nominator += scaleLevel0Array[score];
                int sum=0;
                for (int i = 0; i < scale + 1; ++i) {
                    sum+= scaleLevel0Array[i];
                }
                denominator += sum;
            }

            *players = (nominator/denominator) * 100 ;
            return SUCCESS;
        }
        else
        {
            if(UF.Find(GroupID)->getPercentOfPlayers(score, lowerLevel,higherLevel,players) == -1)
            {
                return FAILURE;
            }
        }


    }
    catch(std::exception& e)
    {
        return ALLOCATION_ERROR;
    }
    return SUCCESS;

}


StatusType PlayersManager::PMaverageHighestPlayerLevelByGroup( int GroupID, int m, double * avgLevel)
{
    if(avgLevel == nullptr || GroupID < 0 || GroupID > k || m <= 0)
    {
        return  INVALID_INPUT;
    }

    try
    {
        if(GroupID == 0)
        {
            if(m > num_of_players)
            {
                return  FAILURE;
            }
            double sum =0;
            double m_double = (double)m;
            if(m <= num_of_players_with_positive_level)
            {
                auto LInode = level_and_id_player_tree->select(level_and_id_player_tree,num_of_players_with_positive_level-m+1);
                sum = level_and_id_player_tree->sumInfoOfHighest(level_and_id_player_tree,LInode->getKey());
                *avgLevel = sum/m; // maybe change to double
            }
            else
            {
                *avgLevel = level_and_number_player_tree->getInfo()/m_double;
            }
        }
        else
        {
            if(m > UF.Find(GroupID)->getNumOfPlayers())
            {
                return  FAILURE;
            }
            else
            {
                UF.Find(GroupID)->averageHighestPlayerLevelByGroup(m,avgLevel);
            }
        }
    }
    catch(std::exception& e)
    {
        return ALLOCATION_ERROR;
    }
    return SUCCESS;

}