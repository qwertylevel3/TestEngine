#ifndef FOCUS_H
#define FOCUS_H

#include"skill.h"

class Decoration;

class Focus:public Skill
{
public:
    Focus(Character* c);
    void start();
    void end();
    void run();
protected:
    int chooseFocusCharacter();
    Decoration* focus;

    int focusIndex;
};

#endif // FOCUS_H
