#include "face.h"

Face::Face(const QString &spriteName)
    :Entity(spriteName)
{
    sprite=SpriteManager::instance()->getFaceSprite(spriteName);
}


Face* Face::clone()
{
    Face* newFace=new Face(this->spriteName);
    newFace->setName(this->name);

    return newFace;
}
