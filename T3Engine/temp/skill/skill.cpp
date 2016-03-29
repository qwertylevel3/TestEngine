#include "skill.h"
#include"character.h"

Skill::Skill(Character *c)
    :character(c)
{
    count=0;
}

void Skill::start()
{
    incCount();
}

void Skill::end()
{
    decCount();
}

void Skill::run()
{

}

int Skill::getCount() const
{
    return count;
}

void Skill::setCount(int value)
{
    count = value;
}

void Skill::incCount()
{
    count++;
}

void Skill::decCount()
{
    count--;
}

bool Skill::isRunning()
{
    if(count==0)
    {
        return false;
    }
    else
    {
        return true;
    }
}


