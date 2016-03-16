#include "face.h"

Face::Face(const QString &spriteName)
    :Entity(spriteName)
{
}


Face* Face::clone()
{
    Face* newFace=new Face(this->spriteName);
    newFace->setName(this->name);

    return newFace;
}
