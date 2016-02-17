#include "move.h"
#include"T3Engine/entity/character/character.h"

Move::Move(Entity *e)
    :Skill(e)
{
    orientation=empty;
    nextCommand=InputModule::empty;
}

void Move::start(InputModule::Command c)
{
    chooseOrientation(c);
}

void Move::end(InputModule::Command c)
{
    if(nextCommand==c)
    {
        nextCommand=InputModule::empty;
        return;
    }
    switch(orientation)
    {
    case upLeft:
        if(c==InputModule::up)
        {
            orientation=left;
        }
        else if(c==InputModule::left)
        {
            orientation=up;
        }
        break;
    case downLeft:
        if(c==InputModule::down)
        {
            orientation=left;
        }
        else if(c==InputModule::left)
        {
            orientation=down;
        }
        break;
    case upRight:
        if(c==InputModule::up)
        {
            orientation=right;
        }
        else if(c==InputModule::right)
        {
            orientation=up;
        }
        break;
    case downRight:
        if(c==InputModule::down)
        {
            orientation=right;
        }
        else if(c==InputModule::right)
        {
            orientation=down;
        }
        break;
    default:
        orientation=empty;
    }
}

void Move::run()
{
    if(orientation==empty)
    {
        if(nextCommand!=InputModule::empty)
        {
            if(nextCommand==InputModule::right)
            {
                orientation=right;
                nextCommand=InputModule::empty;
            }
            else if(nextCommand==InputModule::left)
            {
                orientation=left;
                nextCommand=InputModule::empty;
            }
        }
    }
    float speed=static_cast<Character*>(entity)->getSpeed();
    switch(orientation)
    {
    case up:
        entity->setY(entity->getY()+speed);
        break;
    case down:
        entity->setY(entity->getY()-speed);
        break;
    case right:
        entity->setX(entity->getX()+speed);
        break;
    case left:
        entity->setX(entity->getX()-speed);
        break;
    case upLeft:
        entity->setX(entity->getX()-speed/1.4);
        entity->setY(entity->getY()+speed/1.4);
        break;
    case upRight:
        entity->setX(entity->getX()+speed/1.4);
        entity->setY(entity->getY()+speed/1.4);
        break;
    case downLeft:
        entity->setX(entity->getX()-speed/1.4);
        entity->setY(entity->getY()-speed/1.4);
        break;
    case downRight:
        entity->setX(entity->getX()+speed/1.4);
        entity->setY(entity->getY()-speed/1.4);
        break;
    default:
        break;
    }
}

void Move::chooseOrientation(InputModule::Command c)
{
    switch(orientation)
    {
    case empty:
        if(c==InputModule::left)
        {
            orientation=left;
        }
        else if(c==InputModule::right)
        {
            orientation=right;
        }
        else if(c==InputModule::up)
        {
            orientation=up;
        }
        else if(c==InputModule::down)
        {
            orientation=down;
        }
        break;
    case up:
        if(c==InputModule::left)
        {
            orientation=upLeft;
        }
        else if(c==InputModule::right)
        {
            orientation=upRight;
        }
        break;
    case down:
        if(c==InputModule::left)
        {
            orientation=downLeft;
        }
        else if(c==InputModule::right)
        {
            orientation=downRight;
        }
        break;
    case left:
        if(c==InputModule::up)
        {
            orientation=upLeft;
        }
        else if(c==InputModule::down)
        {
            orientation=downLeft;
        }
        else if(c==InputModule::right)
        {
//            orientation=right;
            nextCommand=c;
        }
        break;
    case right:
        if(c==InputModule::up)
        {
            orientation=upRight;
        }
        else if(c==InputModule::down)
        {
            orientation=downRight;
        }
        else if(c==InputModule::left)
        {
//            orientation=left;
            nextCommand=c;
        }
        break;
    default:
        break;
    }
}

