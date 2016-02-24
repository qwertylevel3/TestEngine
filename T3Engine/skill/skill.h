#ifndef SKILL_H
#define SKILL_H

#include"inputmodule.h"

class Character;

class Skill
{
public:
    Skill(Character* c);
    virtual void start(InputModule::Command c);
    virtual void end(InputModule::Command c);
    virtual void run();
    int getCount() const;
    void setCount(int value);

    void incCount();
    void decCount();

    bool isRunning();
protected:
    Character* character;
    int count;
};

#endif // SKILL_H
