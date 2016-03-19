#ifndef WANDER_H
#define WANDER_H

#include"ai.h"

class Wander:public AI
{
public:
    Wander(Character* c);
    void update();
};

#endif // WANDER_H
