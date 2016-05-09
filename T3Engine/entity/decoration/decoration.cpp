#include "decoration.h"

Decoration::Decoration(const QString &spriteName)
    :Entity(spriteName)
{
}

Decoration *Decoration::clone()
{
    Decoration* newDecoration=new Decoration(this->spriteName);
    newDecoration->setName(this->name);
    newDecoration->setCollisionAble(this->collisionAble);
    newDecoration->setDestructible(this->destructible);

    return newDecoration;
}
int Decoration::getHP() const
{
    return HP;
}

void Decoration::setHP(int value)
{
    HP = value;
}
