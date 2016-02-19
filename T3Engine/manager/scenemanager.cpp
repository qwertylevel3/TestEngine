#include "scenemanager.h"
#include<QDir>
#include<QFile>
#include"T3Engine/manager/charactermanager.h"
#include"T3Engine/manager/terrainmanager.h"
#include"T3Engine/manager/decorationmanager.h"
#include"T3Engine/inputmodule.h"

SceneManager::SceneManager()
{

}

void SceneManager::init()
{
    QString fileName=GameConfigurator::instance()->getSceneConfigFileName();
    QString path=QDir::currentPath()+QDir::separator()+fileName;

    QFile file(path);

    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        qDebug()<<"can not open "<<fileName<<endl;
        return ;
    }
    reader.setDevice(&file);

    reader.readNextStartElement();//<SceneBox>
    reader.readNextStartElement();//<TotalSceneNumber>
    int totalSceneNumber=reader.readElementText().toInt();

    for(int i=0;i<totalSceneNumber;i++)
    {
        makeScene();
    }

    file.close();
}

Scene *SceneManager::getScene(const QString &sceneName)
{
    return sceneBox.value(sceneName);
}

void SceneManager::makeScene()
{
    reader.readNextStartElement();//<scene>

    reader.readNextStartElement();//<name>
    QString name=reader.readElementText();

    Scene* tempScene=new Scene();

    makeBackground(tempScene);
    makeTerrain(tempScene);
    makeDecoration(tempScene);
    makeCharacter(tempScene);
    makePlayer(tempScene);

    sceneBox.insert(name,tempScene);
}

void SceneManager::makeBackground(Scene *scene)
{
    reader.readNextStartElement();//<Background>

    reader.readNextStartElement();//<backgroundName>
    QString backgroundName=reader.readElementText();

    Terrain* terrain=TerrainManager::instance()->getTerrain(backgroundName);

    float w=terrain->getWidth();
    float h=terrain->getHeight();

    terrain->setWidth(scene->getWidth());
    terrain->setHeight(scene->getHeight());

    terrain->setRepeatX(int(scene->getWidth()/w));
    terrain->setRepeatY(int(scene->getHeight()/h));

    terrain->setZ(-10);

    scene->addTerrainToBox(terrain);

    reader.readNextStartElement();//</Background>
}

void SceneManager::makeTerrain(Scene *scene)
{
    reader.readNextStartElement();//<TerrainBox>

    reader.readNextStartElement();//<TotalTerrainNumber>
    int terrainNumber=reader.readElementText().toInt();

    for(int i=0;i<terrainNumber;i++)
    {
        reader.readNextStartElement();//<Terrain>

        reader.readNextStartElement();//<TerrainName>
        QString terrainName=reader.readElementText();

        reader.readNextStartElement();//<x>
        float x=reader.readElementText().toFloat();

        reader.readNextStartElement();//<y>
        float y=reader.readElementText().toFloat();

        reader.readNextStartElement();//<z>
        float z=reader.readElementText().toFloat();

        Terrain* terrain=TerrainManager::instance()->getTerrain(terrainName);
        terrain->setX(x);
        terrain->setY(y);
        terrain->setZ(z);

        scene->addTerrainToBox(terrain);

        reader.readNextStartElement();//</Terrain>

    }
    reader.readNextStartElement();//</TerrainBox>
}

void SceneManager::makeDecoration(Scene *scene)
{
    reader.readNextStartElement();//<DecorationBox>

    reader.readNextStartElement();//<TotalDecorationNumber>
    int decorationNumber=reader.readElementText().toInt();

    for(int i=0;i<decorationNumber;i++)
    {
        reader.readNextStartElement();//<Decoration>

        reader.readNextStartElement();//<DecorationName>
        QString decorationName=reader.readElementText();

        reader.readNextStartElement();//<x>
        float x=reader.readElementText().toFloat();

        reader.readNextStartElement();//<y>
        float y=reader.readElementText().toFloat();

        reader.readNextStartElement();//<z>
        float z=reader.readElementText().toFloat();

        Decoration* decoration=DecorationManager::instance()->getDecoration(decorationName);
        decoration->setX(x);
        decoration->setY(y);
        decoration->setZ(z);

        scene->addDecorationToBox(decoration);

        reader.readNextStartElement();//<Decoration>
        //qDebug()<<reader.name().toString()<<endl;
    }
    reader.readNextStartElement();//<decorationbox>
    //qDebug()<<reader.name().toString()<<endl;

}

void SceneManager::makeCharacter(Scene *scene)
{
    reader.readNextStartElement();//<CharacterBox>

    reader.readNextStartElement();//<TotalCharacterNumber>
    int characterNumber=reader.readElementText().toInt();

    for(int i=0;i<characterNumber;i++)
    {
        reader.readNextStartElement();//<Character>

        reader.readNextStartElement();//<CharacterName>
        QString characterName=reader.readElementText();

        reader.readNextStartElement();//<x>
        float x=reader.readElementText().toFloat();

        reader.readNextStartElement();//<y>
        float y=reader.readElementText().toFloat();

        reader.readNextStartElement();//<z>
        float z=reader.readElementText().toFloat();

        Character* character=CharacterManager::instance()->getCharacter(characterName);
        character->setX(x);
        character->setY(y);
        character->setZ(z);

        scene->addCharacterToBox(character);

        reader.readNextStartElement();//<character>
    }
    reader.readNextStartElement();//<characterBox>
}

void SceneManager::makePlayer(Scene *scene)
{
    reader.readNextStartElement();//<Player>

    reader.readNextStartElement();//<PlayerName>
    QString playerName=reader.readElementText();

    reader.readNextStartElement();//<x>
    float x=reader.readElementText().toFloat();

    reader.readNextStartElement();//<y>
    float y=reader.readElementText().toFloat();

    reader.readNextStartElement();//<z>
    float z=reader.readElementText().toFloat();

    Character* player=CharacterManager::instance()->getCharacter(playerName);
    player->setX(x);
    player->setY(y);
    player->setZ(z);

    InputModule::instance()->setEntity(player);

    scene->addCharacterToBox(player);
    reader.readNextStartElement();//</player>
}
