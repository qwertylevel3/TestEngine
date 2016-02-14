#include "terrainmanager.h"
#include"T3Engine/gameconfigurator.h"
#include<QDir>
#include<QFile>

TerrainManager::TerrainManager()
{

}

void TerrainManager::init()
{
    QString fileName=GameConfigurator::instance()->getTerrainConfigFileName();
    QString path=QDir::currentPath()+QDir::separator()+fileName;


    QFile file(path);

    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        qDebug()<<"can not open "<<fileName<<endl;
        return ;
    }
    reader.setDevice(&file);

    reader.readNextStartElement();//<TerrainBox>
    reader.readNextStartElement();//<TotalTerrainNumber>
    int totalTerrainNumber=reader.readElementText().toInt();

    for(int i=0;i<totalTerrainNumber;i++)
    {
        Terrain* terrain=makeTerrain();
        addTerrain(terrain->getName(),terrain);
    }

    file.close();
}

Terrain *TerrainManager::getTerrain(const QString &terrainName)
{
    return terrainBox[terrainName]->clone();
}

Terrain *TerrainManager::makeTerrain()
{
    reader.readNextStartElement();//<Terrain>

    reader.readNextStartElement();//<Name>
    QString name=reader.readElementText();

    reader.readNextStartElement();//<SpriteName>
    QString spriteName=reader.readElementText();

    reader.readNextStartElement();//</Terrain>

    Terrain* terrain=new Terrain(spriteName);
    terrain->setName(name);
    return terrain;
}

