//
// Created by omarm on 06/01/2022.
//

#include "Player.h"

int Player::getPlayerId()
{
    return player_id;
}
int Player::getGroupId()
{
    return group_id;
}

int Player::getLevel()
{
    return level;
}
int Player::getScore()
{
    return score;
}
void Player::setLevel(int newLevel)
{
    level = newLevel;
}
void Player::setScore(int newScore)
{
    score = newScore;
}