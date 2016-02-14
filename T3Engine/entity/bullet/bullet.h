#ifndef BULLET_H
#define BULLET_H

#include"T3Engine/entity/entity.h"

class Bullet:public Entity
{
public:
    Bullet(const QString& spriteName);
    Bullet* clone();
};

#endif // BULLET_H
