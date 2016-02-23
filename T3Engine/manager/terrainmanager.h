#ifndef TERRAINMANAGER_H
#define TERRAINMANAGER_H


#include"T3Engine/entity/terrain/terrain.h"

class TerrainManager:public Singleton<TerrainManager>
{
public:
    TerrainManager();
    void init();

    Terrain* getTerrain(const QString& terrainName);
    void addTerrain(const QString& terrainName,Terrain* terrain){terrainBox.insert(terrainName,terrain);}
protected:
    QMap<QString,Terrain*> terrainBox;
    QXmlStreamReader reader;

    Terrain* makeTerrain();
};

#endif // TERRAINMANAGER_H
