#include "skill.h"
#include"character.h"

Skill::Skill(Character *c)
    :character(c)
{
    count=0;
}

void Skill::start(InputModule::Command c)
{
    Q_UNUSED(c)
    incCount();
}

void Skill::end(InputModule::Command c)
{
    Q_UNUSED(c)
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


