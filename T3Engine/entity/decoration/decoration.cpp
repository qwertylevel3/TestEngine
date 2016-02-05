#include "decoration.h"

Decoration::Decoration(const QString &spriteName)
    :Entity(spriteName)
{

}

Decoration *Decoration::clone()
{
    Decoration* newDecoration=new Decoration(this->spriteName);
    newDecoration->setName(this->name);

    return newDecoration;
}


