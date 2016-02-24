#include "character.h"
#include"inputmodule.h"
#include"move.h"
#include"shoot.h"


Character::Character(const QString &spriteName)
    :Entity(spriteName)
{
    initParamater();
    initSkill();
}

void Character::update()
{
    Entity::update();
    runSkill();
}

Character *Character::clone()
{
    Character* newCharacter=new Character(this->spriteName);
    newCharacter->setName(this->name);
    newCharacter->setHP(this->HP);
    newCharacter->setMP(this->MP);
    newCharacter->setCurrentHP(this->HP);
    newCharacter->setCurrentMP(this->MP);

    return newCharacter;
}

void Character::startCommand(InputModule::Command c)
{
    if(c==InputModule::up)
    {
        skillList[0]->start(c);
        orientation=Orientation::up;
        if(skillList[2]->isRunning())
        {
            orientation=Orientation::upLeft;
        }
        else if(skillList[3]->isRunning())
        {
            orientation=Orientation::upRight;
        }
    }
    if(c==InputModule::down)
    {
        skillList[1]->start(c);
        orientation=Orientation::down;
        if(skillList[2]->isRunning())
        {
            orientation=Orientation::downLeft;
        }
        if(skillList[3]->isRunning())
        {
            orientation=Orientation::downRight;
        }

    }
    if(c==InputModule::left)
    {
        skillList[2]->start(c);
        orientation=Orientation::left;
        if(skillList[0]->isRunning())
        {
            orientation=Orientation::upLeft;
        }
        else if(skillList[1]->isRunning())
        {
            orientation=Orientation::downLeft;
        }
    }
    if(c==InputModule::right)
    {
        skillList[3]->start(c);
        orientation=Orientation::right;
        if(skillList[0]->isRunning())
        {
            orientation=Orientation::upRight;
        }
        if(skillList[1]->isRunning())
        {
            orientation=Orientation::downRight;
        }
    }
    if(c==InputModule::A_C)
    {
        skillList[4]->start(c);
    }
}

void Character::endCommand(InputModule::Command c)
{
    if(c==InputModule::up)
    {
        skillList[0]->end(c);
    }
    if(c==InputModule::down)
    {
        skillList[1]->end(c);
    }
    if(c==InputModule::left)
    {
        skillList[2]->end(c);
    }
    if(c==InputModule::right)
    {
        skillList[3]->end(c);
    }
    if(c==InputModule::A_C)
    {
        skillList[4]->end(c);
    }

}
float Character::getSpeed() const
{
    return speed;
}

void Character::setSpeed(float value)
{
    speed = value;
}
Orientation::ORIENTATION Character::getOrientation() const
{
    return orientation;
}

void Character::setOrientation(const Orientation::ORIENTATION &value)
{
    orientation = value;
}
Orientation::ORIENTATION Character::getMoveOrientation() const
{
    return moveOrientation;
}

void Character::setMoveOrientation(const Orientation::ORIENTATION &value)
{
    moveOrientation = value;
}

void Character::initSkill()
{
    Move* moveUp=new Move(this);
    moveUp->setOrientation(Orientation::up);
    Move* moveDown=new Move(this);
    moveDown->setOrientation(Orientation::down);
    Move* moveLeft=new Move(this);
    moveLeft->setOrientation(Orientation::left);
    Move* moveRight=new Move(this);
    moveRight->setOrientation(Orientation::right);

    skillList.push_back(moveUp);
    skillList.push_back(moveDown);
    skillList.push_back(moveLeft);
    skillList.push_back(moveRight);

    Shoot* shoot=new Shoot(this);
    skillList.push_back(shoot);
}

void Character::initParamater()
{
    HP=0;
    MP=0;
    currentHP=0;
    currentMP=0;
    speed=0.01;
    moveOrientation=Orientation::empty;
    orientation=Orientation::down;
}

void Character::runSkill()
{
    for(int i=0;i<skillList.size();i++)
    {
        if(skillList[i]->isRunning())
        {
            skillList[i]->run();
        }
    }
}



