#ifndef PLAYER_H
#define PLAYER_H

#include"character.h"
#include"singleton.h"

class Player:public Character,public Singleton<Player>
{
public:
    Player();
    void init();
    void initParamater();
};

#endif // PLAYER_H
