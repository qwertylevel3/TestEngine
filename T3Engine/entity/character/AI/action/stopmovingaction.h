#ifndef STOPMOVINGACTION_H
#define STOPMOVINGACTION_H

#include"action.h"

class StopMovingAction:public Action
{
public:
    StopMovingAction();
    void run(Character *character);
};

#endif // STOPMOVINGACTION_H
