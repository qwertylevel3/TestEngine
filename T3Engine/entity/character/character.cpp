#include "character.h"
#include"T3Engine/inputmodule.h"


Character::Character(const QString &spriteName)
    :Entity(spriteName)
{
    HP=0;
    MP=0;
    currentHP=0;
    currentMP=0;
    speed=0.01;
    orientation=empty;
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

void Character::startCommand(int c)
{
    if(c==InputModule::up)
    {
        qDebug()<<"up"<<endl;
    }
}

void Character::endCommand(int c)
{

}
float Character::getSpeed() const
{
    return speed;
}

void Character::setSpeed(float value)
{
    speed = value;
}


