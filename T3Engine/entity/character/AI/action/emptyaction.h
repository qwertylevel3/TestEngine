#ifndef EMPTYACTION_H
#define EMPTYACTION_H

#include"action.h"

class EmptyAction:public Action
{
public:
    EmptyAction();
    void run(Character *character);
};

#endif // EMPTYACTION_H
