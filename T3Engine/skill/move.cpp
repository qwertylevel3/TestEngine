#include "move.h"
#include"T3Engine/entity/character/character.h"

Move::Move(Character *c)
    :Skill(c)
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
    switch(character->getOrientation())
    {
    case Character::upLeft:
        if(c==InputModule::up)
        {
            character->setOrientation(Character::left);
        }
        else if(c==InputModule::left)
        {
            character->setOrientation(Character::up);
        }
        break;
    case Character::downLeft:
        if(c==InputModule::down)
        {
            character->setOrientation(Character::left);
        }
        else if(c==InputModule::left)
        {
            character->setOrientation(Character::down);
        }
        break;
    case Character::upRight:
        if(c==InputModule::up)
        {
            character->setOrientation(Character::right);
        }
        else if(c==InputModule::right)
        {
            character->setOrientation(Character::up);
        }
        break;
    case Character::downRight:
        if(c==InputModule::down)
        {
            character->setOrientation(Character::right);
        }
        else if(c==InputModule::right)
        {
            character->setOrientation(Character::down);
        }
        break;
    default:
        character->setOrientation(Character::empty);
    }
}

void Move::run()
{
    if(character->getOrientation()==Character::empty)
    {
        if(nextCommand!=InputModule::empty)
        {
            if(nextCommand==InputModule::right)
            {
                character->setOrientation(Character::right);
                nextCommand=InputModule::empty;
            }
            else if(nextCommand==InputModule::left)
            {
                character->setOrientation(Character::left);
                nextCommand=InputModule::empty;
            }
        }
    }
    float speed=character->getSpeed();
    switch(character->getOrientation())
    {
    case Character::up:
        character->setY(character->getY()+speed);
        break;
    case Character::down:
        character->setY(character->getY()-speed);
        break;
    case right:
        character->setX(character->getX()+speed);
        break;
    case left:
        character->setX(character->getX()-speed);
        break;
    case upLeft:
        character->setX(character->getX()-speed/1.4);
        character->setY(character->getY()+speed/1.4);
        break;
    case upRight:
        character->setX(character->getX()+speed/1.4);
        character->setY(character->getY()+speed/1.4);
        break;
    case downLeft:
        character->setX(character->getX()-speed/1.4);
        character->setY(character->getY()-speed/1.4);
        break;
    case downRight:
        character->setX(character->getX()+speed/1.4);
        character->setY(character->getY()-speed/1.4);
        break;
    default:
        break;
    }
}

void Move::chooseOrientation(InputModule::Command c)
{
    switch(character->getOrientation())
    {
    case Character::empty:
        if(c==InputModule::left)
        {
            character->setOrientation(Character::left);
        }
        else if(c==InputModule::right)
        {
            character->setOrientation(Character::right);
        }
        else if(c==InputModule::up)
        {
            character->setOrientation(Character::up);
        }
        else if(c==InputModule::down)
        {
            character->setOrientation(Character::down);
        }
        break;
    case Character::up:
        if(c==InputModule::left)
        {
            character->setOrientation(Character::upLeft);
        }
        else if(c==InputModule::right)
        {
            character->setOrientation(Character::upRight);
        }
        break;
    case Character::down:
        if(c==InputModule::left)
        {
            character->setOrientation(Character::downLeft);
        }
        else if(c==InputModule::right)
        {
            character->setOrientation(Character::downRight);
        }
        break;
    case Character::left:
        if(c==InputModule::up)
        {
            character->setOrientation(Character::upLeft);
        }
        else if(c==InputModule::down)
        {
            character->setOrientation(Character::downLeft);
        }
        else if(c==InputModule::right)
        {
            nextCommand=c;
        }
        break;
    case Character::right:
        if(c==InputModule::up)
        {
            character->setOrientation(Character::upRight);
        }
        else if(c==InputModule::down)
        {
            character->setOrientation(Character::downRight);
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

