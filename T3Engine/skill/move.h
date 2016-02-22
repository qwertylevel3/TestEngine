#ifndef MOVE_H
#define MOVE_H

#include"T3Engine/skill/skill.h"
#include"T3Engine/orientation.h"

class Move:public Skill
{
public:
    Move(Character* c);
    void start(InputModule::Command c);
    void end(InputModule::Command c);
    void run();
protected:
    Orientation::ORIENTATION orientation;

    InputModule::Command nextCommand;
};

#endif // MOVE_H
