#ifndef FOCUS_H
#define FOCUS_H

#include"skill.h"

class Decoration;

class Focus:public Skill
{
public:
    Focus(Character* c);
    void start(InputModule::Command c);
    void end(InputModule::Command c);
    void run();
protected:
    int chooseFocusCharacter();
    Decoration* focus;

    int focusIndex;
};

#endif // FOCUS_H
