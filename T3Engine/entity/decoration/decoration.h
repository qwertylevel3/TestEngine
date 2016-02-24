#ifndef DECORATION_H
#define DECORATION_H

#include"entity.h"

class Decoration:public Entity
{
public:
    Decoration(const QString& spriteName);
    Decoration* clone();
};

#endif // DECORATION_H
