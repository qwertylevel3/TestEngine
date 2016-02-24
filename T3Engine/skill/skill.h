#ifndef SKILL_H
#define SKILL_H

#include"inputmodule.h"

class Character;

class Skill
{
public:
    Skill(Character* c);
    virtual void start(InputModule::Command c)=0;
    virtual void end(InputModule::Command c)=0;
    virtual void run()=0;
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
