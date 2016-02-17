#ifndef SKILL_H
#define SKILL_H

//#include"T3Engine/entity/entity.h"

#include"T3Engine/inputmodule.h"
class Character;

class Skill
{
public:
    Skill(Character* c);
    virtual void start(InputModule::Command c)=0;
    virtual void end(InputModule::Command c)=0;
    virtual void run()=0;
protected:
    Character* character;
};

#endif // SKILL_H
