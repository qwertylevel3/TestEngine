#include "character.h"
#include"T3Engine/inputmodule.h"
#include"T3Engine/skill/move.h"


Character::Character(const QString &spriteName)
    :Entity(spriteName)
{
    HP=0;
    MP=0;
    currentHP=0;
    currentMP=0;
    speed=0.01;
    orientation=empty;

    Move* move=new Move(this);
    skillList.push_back(move);

}

void Character::update()
{
    Entity::update();

    if(skillList[0])
    {
        skillList[0]->run();
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
        skillList[0]->start(c);
    }
}

void Character::endCommand(InputModule::Command c)
{
    skillList[0]->end(c);
}
float Character::getSpeed() const
{
    return speed;
}

void Character::setSpeed(float value)
{
    speed = value;
}
Character::ORIENTATION Character::getOrientation() const
{
    return orientation;
}

void Character::setOrientation(const ORIENTATION &value)
{
    orientation = value;
}
