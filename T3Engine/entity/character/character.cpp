#include "character.h"
#include"inputmodule.h"
#include"move.h"
#include"shoot.h"


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

    for(int i=0;i<skillList.size();i++)
    {
        if(skillList[i]->isRunning())
        {
            skillList[i]->run();
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
        skillList[0]->incCount();
        skillList[0]->start(c);
    }
    if(c==InputModule::A_C)
    {
        skillList[1]->incCount();
        skillList[1]->start(c);
    }
}

void Character::endCommand(InputModule::Command c)
{
    if(c==InputModule::up
            || c==InputModule::down
            || c==InputModule::left
            || c==InputModule::right)
    {
        //skillIndexCount++;
        skillList[0]->end(c);
        skillList[0]->decCount();
    }
    if(c==InputModule::A_C)
    {
        //skillIndexCount++;
        skillList[1]->end(c);
        skillList[1]->decCount();
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



