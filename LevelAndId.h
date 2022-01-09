//
// Created by omarm on 06/01/2022.
//

#ifndef MIVNI2_LEVELANDID_H
#define MIVNI2_LEVELANDID_H


class LevelAndId {
private:
    int Level;
    int Id;

public:
    LevelAndId(int Level, int Id) : Level(Level) , Id(Id) {};
    LevelAndId() : Level(0) , Id(0){};

    int getId() const;
    int getNumber() const;
    void setNumber(int new_number);

    bool operator==(const LevelAndId& other) const ;     // check how to declare as friend
    bool operator<(const LevelAndId& other) const ;
    bool operator>(const LevelAndId& other) const ;


};


#endif //MIVNI2_LEVELANDID_H
