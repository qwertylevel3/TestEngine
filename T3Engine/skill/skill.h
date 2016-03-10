#ifndef SKILL_H
#define SKILL_H

#include"inputmodule.h"

class Character;

class Skill
{
public:
    Skill(Character* c);
    virtual void start();
    virtual void end();
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
