#ifndef SHOOT_H
#define SHOOT_H

#include"T3Engine/skill/skill.h"

class Shoot:public Skill
{
public:
    Shoot(Entity* e);
    void start(InputModule::Command c);
    void end(InputModule::Command c);
    void run();

};

#endif // SHOOT_H
