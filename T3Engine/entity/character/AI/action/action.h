#ifndef ACTION_H
#define ACTION_H

#include"ainode.h"

class Action:public AINode
{
public:
    Action();
protected:
    virtual void run()=0;
};

#endif // ACTION_H
