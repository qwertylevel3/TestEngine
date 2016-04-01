#ifndef RUNNINGSELECTOR_H
#define RUNNINGSELECTOR_H

#include"selector.h"

class RunningSelector:public Selector
{
public:
    RunningSelector();
    bool judge(Character *character);

};

#endif // RUNNINGSELECTOR_H
