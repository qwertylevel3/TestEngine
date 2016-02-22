#include "character.h"
#include"T3Engine/inputmodule.h"
#include"T3Engine/skill/move.h"
#include"T3Engine/skill/shoot.h"


Character::Character(const QString &spriteName)
    :Entity(spriteName)
{
    HP=0;
    MP=0;
    currentHP=0;
    currentMP=0;
    speed=0.01;
    moveOrientation=Orientation::empty;
    orientation=Orientation::down;

    skillIndex=-1;

    Move* move=new Move(this);
    skillList.push_back(move);

    Shoot* shoot=new Shoot(this);
    skillList.push_back(shoot);
}

void Character::update()
{
    Entity::update();

    if(skillIndex!=-1)
    {
        if(skillList[skillIndex])
        {
            skillList[skillIndex]->run();
        }
    }
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
    if(c==InputModule::up
            || c==InputModule::down
            || c==InputModule::left
            || c==InputModule::right)
    {
        //skillIndexCount++;
        skillIndex=0;
        skillList[skillIndex]->setCount(skillList[skillIndex]->getCount()+1);
        skillList[skillIndex]->start(c);
    }
    if(c==InputModule::A_C)
    {
        //skillIndexCount++;
        skillIndex=1;
        skillList[skillIndex]->setCount(skillList[skillIndex]->getCount()+1);
        skillList[skillIndex]->start(c);
    }
}

void Character::endCommand(InputModule::Command c)
{
    if(skillIndex!=-1)
    {
        skillList[skillIndex]->end(c);

        skillList[skillIndex]->setCount(skillList[skillIndex]->getCount()-1);

        if(skillList[skillIndex]->getCount()==0)
        {
            skillIndex=-1;
        }
    }
//    if(--skillIndexCount==0)
//    {
//        skillIndex=-1;
//    }
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



