#ifndef MOVE_H
#define MOVE_H

#include"T3Engine/skill/skill.h"

class Move:public Skill
{
public:
    enum ORIENTATION{empty,up,down,left,right,
                     upLeft,upRight,downLeft,downRight};
    Move(Character* c);
    void start(InputModule::Command c);
    void end(InputModule::Command c);
    void run();
protected:
    ORIENTATION orientation;

    InputModule::Command nextCommand;
};

#endif // MOVE_H
