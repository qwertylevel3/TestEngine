#ifndef BACKGROUND_H
#define BACKGROUND_H

#include"entity.h"

class Background:public Entity
{
public:
    Background(const QString& spriteName);
    Background* clone();
};

#endif // BACKGROUND_H
