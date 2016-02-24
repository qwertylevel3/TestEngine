#ifndef TERRAIN_H
#define TERRAIN_H

#include"entity.h"

class Terrain:public Entity
{
public:
    Terrain(const QString& spriteName);
    Terrain* clone();
};

#endif // TERRAIN_H
