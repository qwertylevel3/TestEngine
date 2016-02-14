#ifndef MOVE_H
#define MOVE_H

#include"T3Engine/skill/skill.h"

class Move:public Skill
{
public:
    enum ORIENTATION{empty,up,down,left,right,
                     upLeft,upRight,downLeft,downRight};
    Move(Entity* e);
    void start(InputModule::Command c);
    void end(InputModule::Command c);
    void run();
protected:
    void chooseOrientation(InputModule::Command c);
    ORIENTATION orientation;
};

#endif // MOVE_H
