#include "skill.h"
#include"T3Engine/entity/character/character.h"

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


