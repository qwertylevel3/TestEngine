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

    Orientation::ORIENTATION getOrientation() const;
    void setOrientation(const Orientation::ORIENTATION &value);

protected:
    Orientation::ORIENTATION orientation;
    int count;
};

#endif // MOVE_H
