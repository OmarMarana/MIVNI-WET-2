//
// Created by omarm on 06/01/2022.
//

#include "LevelAndNumber.h"



int LevelAndNumber::getNumber() const
{
    return Number;
}
int LevelAndNumber::getLevel() const
{
    return Level;
}

bool LevelAndNumber::operator==(const LevelAndNumber& other) const
{
    return Level == other.Level;
}

bool LevelAndNumber::operator<(const LevelAndNumber& other) const
{
    return Level < other.Level;
}
bool LevelAndNumber::operator>(const LevelAndNumber& other) const
{
    return Level > other.Level;
}

void LevelAndNumber::setNumber(int newNumber)
{
    Number = newNumber;
}
