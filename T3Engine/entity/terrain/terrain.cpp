#include "terrain.h"

Terrain::Terrain(const QString &spriteName)
    :Entity(spriteName)
{
    sprite=SpriteManager::instance()->getTerrainSprite(spriteName);
}

Terrain *Terrain::clone()
{
    Terrain* newTerrain=new Terrain(this->spriteName);
    newTerrain->setName(this->name);

    return newTerrain;
}

