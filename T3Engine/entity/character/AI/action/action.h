#ifndef ACTION_H
#define ACTION_H

#include"ainode.h"
#include"character.h"

class Action:public AINode
{
public:
    Action();
    virtual void run(Character* character)=0;
};

#endif // ACTION_H
