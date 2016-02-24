#ifndef MOVE_H
#define MOVE_H

#include"skill.h"
#include"orientation.h"

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
