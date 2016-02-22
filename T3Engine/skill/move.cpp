#include "move.h"
#include"T3Engine/entity/character/character.h"

Move::Move(Character *c)
    :Skill(c)
{
    orientation=Orientation::empty;
    nextCommand=InputModule::empty;
}

void Move::start(InputModule::Command c)
{
    switch(character->getMoveOrientation())
    {
    case Orientation::empty:
        if(c==InputModule::left)
        {
            character->setMoveOrientation(Orientation::left);
            character->setOrientation(Orientation::left);
        }
        else if(c==InputModule::right)
        {
            character->setMoveOrientation(Orientation::right);
            character->setOrientation(Orientation::right);
        }
        else if(c==InputModule::up)
        {
            character->setMoveOrientation(Orientation::up);
            character->setOrientation(Orientation::up);
        }
        else if(c==InputModule::down)
        {
            character->setMoveOrientation(Orientation::down);
            character->setOrientation(Orientation::down);
        }
        break;
    case Orientation::up:
        if(c==InputModule::left)
        {
            character->setMoveOrientation(Orientation::upLeft);
            character->setOrientation(Orientation::upLeft);
        }
        else if(c==InputModule::right)
        {
            character->setMoveOrientation(Orientation::upRight);
            character->setOrientation(Orientation::upRight);
        }
        else if(c==InputModule::down)
        {
            nextCommand=c;
        }
        break;
    case Orientation::down:
        if(c==InputModule::left)
        {
            character->setMoveOrientation(Orientation::downLeft);
            character->setOrientation(Orientation::downLeft);
        }
        else if(c==InputModule::right)
        {
            character->setMoveOrientation(Orientation::downRight);
            character->setOrientation(Orientation::downRight);
        }
        else if(c==InputModule::up)
        {
            nextCommand=c;
        }
        break;
    case Orientation::left:
        if(c==InputModule::up)
        {
            character->setMoveOrientation(Orientation::upLeft);
            character->setOrientation(Orientation::upLeft);
        }
        else if(c==InputModule::down)
        {
            character->setMoveOrientation(Orientation::downLeft);
            character->setOrientation(Orientation::downLeft);
        }
        else if(c==InputModule::right)
        {
            nextCommand=c;
        }
        break;
    case Orientation::right:
        if(c==InputModule::up)
        {
            character->setMoveOrientation(Orientation::upRight);
            character->setOrientation(Orientation::upRight);
        }
        else if(c==InputModule::down)
        {
            character->setMoveOrientation(Orientation::downRight);
            character->setOrientation(Orientation::downRight);
        }
        else if(c==InputModule::left)
        {
            nextCommand=c;
        }
        break;
    default:
        break;
    }
}

void Move::end(InputModule::Command c)
{
    if(nextCommand==c)
    {
        nextCommand=InputModule::empty;
        return;
    }
    switch(character->getMoveOrientation())
    {
    case Orientation::upLeft:
        if(c==InputModule::up)
        {
            character->setMoveOrientation(Orientation::left);
            character->setOrientation(Orientation::left);
        }
        else if(c==InputModule::left)
        {
            character->setMoveOrientation(Orientation::up);
            character->setOrientation(Orientation::up);
        }
        break;
    case Orientation::downLeft:
        if(c==InputModule::down)
        {
            character->setMoveOrientation(Orientation::left);
            character->setOrientation(Orientation::left);
        }
        else if(c==InputModule::left)
        {
            character->setMoveOrientation(Orientation::down);
            character->setOrientation(Orientation::down);
        }
        break;
    case Orientation::upRight:
        if(c==InputModule::up)
        {
            character->setMoveOrientation(Orientation::right);
            character->setOrientation(Orientation::right);
        }
        else if(c==InputModule::right)
        {
            character->setMoveOrientation(Orientation::up);
            character->setOrientation(Orientation::up);
        }
        break;
    case Orientation::downRight:
        if(c==InputModule::down)
        {
            character->setMoveOrientation(Orientation::right);
            character->setOrientation(Orientation::right);
        }
        else if(c==InputModule::right)
        {
            character->setMoveOrientation(Orientation::down);
            character->setOrientation(Orientation::down);
        }
        break;
    default:
        character->setMoveOrientation(Orientation::empty);
    }
}

void Move::run()
{
    if(character->getMoveOrientation()==Orientation::empty)
    {
        if(nextCommand!=InputModule::empty)
        {
            if(nextCommand==InputModule::right)
            {
                character->setMoveOrientation(Orientation::right);
                character->setOrientation(Orientation::right);
                nextCommand=InputModule::empty;
            }
            else if(nextCommand==InputModule::left)
            {
                character->setMoveOrientation(Orientation::left);
                character->setOrientation(Orientation::left);
                nextCommand=InputModule::empty;
            }
            else if(nextCommand==InputModule::up)
            {
                character->setMoveOrientation(Orientation::up);
                character->setOrientation(Orientation::up);
                nextCommand=InputModule::empty;
            }
            else if(nextCommand==InputModule::down)
            {
                character->setMoveOrientation(Orientation::down);
                character->setOrientation(Orientation::down);
                nextCommand=InputModule::empty;
            }
        }
    }
    float speed=character->getSpeed();
    switch(character->getMoveOrientation())
    {
    case Orientation::up:
        character->setY(character->getY()+speed);
        break;
    case Orientation::down:
        character->setY(character->getY()-speed);
        break;
    case Orientation::right:
        character->setX(character->getX()+speed);
        break;
    case Orientation::left:
        character->setX(character->getX()-speed);
        break;
    case Orientation::upLeft:
        character->setX(character->getX()-speed/1.4);
        character->setY(character->getY()+speed/1.4);
        break;
    case Orientation::upRight:
        character->setX(character->getX()+speed/1.4);
        character->setY(character->getY()+speed/1.4);
        break;
    case Orientation::downLeft:
        character->setX(character->getX()-speed/1.4);
        character->setY(character->getY()-speed/1.4);
        break;
    case Orientation::downRight:
        character->setX(character->getX()+speed/1.4);
        character->setY(character->getY()-speed/1.4);
        break;
    default:
        break;
    }
}

