#ifndef CHARACTER_H
#define CHARACTER_H

#include"T3Engine/sprite/sprite.h"
#include"T3Engine/manager/spritemanager.h"
#include"T3Engine/entity/entity.h"

class Character:public Entity
{
public:
    Character(const QString& spriteName);
};

#endif // CHARACTER_H
