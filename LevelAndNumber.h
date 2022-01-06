//
// Created by omarm on 06/01/2022.
//

#ifndef MIVNI2_LEVELANDNUMBER_H
#define MIVNI2_LEVELANDNUMBER_H


class LevelAndNumber {
private:
    int Level;
    int Number;

public:
    LevelAndNumber(int Level, int Number) : Level(Level) , Number(Number) {};
    LevelAndNumber() : Level(0) , Number(0){};

    int getLevel() const;
    int getNumber() const;
    void setNumber(int newNumber);

    bool operator==(const LevelAndNumber& other) const ;     // check how to declare as friend
    bool operator<(const LevelAndNumber& other) const ;
    bool operator>(const LevelAndNumber& other) const ;

};





#endif //MIVNI2_LEVELANDNUMBER_H
