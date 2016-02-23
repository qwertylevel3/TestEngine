#include "skill.h"
#include"character.h"

Skill::Skill(Character *c)
    :character(c)
{
    count=0;
}
int Skill::getCount() const
{
    return count;
}

void Skill::setCount(int value)
{
    count = value;
}


