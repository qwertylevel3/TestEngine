#ifndef FACE_H
#define FACE_H

#include"entity.h"

class Face:public Entity
{
public:
    Face(const QString& spriteName);
    Face* clone();
};

#endif // FACE_H
