#ifndef AI_H
#define AI_H

#include"inputmodule.h"
class Character;

class AI
{
public:
    AI(Character* c);
    virtual void update();
protected:
    Character* character;
    InputModule::Command currentCommand;
};

#endif // AI_H
