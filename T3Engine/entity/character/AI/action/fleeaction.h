#ifndef FLEEACTION_H
#define FLEEACTION_H

#include"action.h"

class FleeAction:public Action
{
public:
    FleeAction();
    void run(Character *character);
};

#endif // FLEEACTION_H
