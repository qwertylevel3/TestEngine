#include "move.h"
#include"character.h"

Move::Move(Character *c)
    :Skill(c)
{
    orientation=Orientation::empty;
    count=-1;
}

void Move::start()
{
    Skill::start();
}

void Move::end()
{
    Skill::end();
}

void Move::run()
{
    float speed=character->getSpeed();
    switch(orientation)
    {
    case Orientation::up:
        character->moveY(speed);
        break;
    case Orientation::down:
        character->moveY(-speed);
        break;
    case Orientation::left:
        character->moveX(-speed);
        break;
    case Orientation::right:
        character->moveX(speed);
        break;
    default:
        break;
    }
}
Orientation::ORIENTATION Move::getOrientation() const
{
    return orientation;
}

void Move::setOrientation(const Orientation::ORIENTATION &value)
{
    orientation = value;
}


