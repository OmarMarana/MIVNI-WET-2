//
// Created by omarm on 06/01/2022.
//

#ifndef MIVNI2_PLAYER_H
#define MIVNI2_PLAYER_H


class Player {
    private:
        int player_id;
        int group_id;
        int level;
        int score;


    public:
        Player(int player_id,int group_id,int score) : player_id(player_id), group_id(group_id),level(0), score(score){}
        int getPlayerId();
        int getGroupId();
        int getLevel();
        int getScore();
        void setLevel(int newLevel);
        void setScore(int newScore);
};



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



#endif //MIVNI2_PLAYER_H
