#ifndef SHOOT_H
#define SHOOT_H

#include"skill.h"

class Shoot:public Skill
{
public:
    Shoot(Character *e);
    void start(InputModule::Command c);
    void end(InputModule::Command c);
    void run();

};

#endif // SHOOT_H
