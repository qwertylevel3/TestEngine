#include "worldmanager.h"
#include"stable.h"
#include"charactermanager.h"
#include"terrainmanager.h"
#include"decorationmanager.h"
#include"inputmodule.h"
#include"facemanager.h"
#include"condition.h"
#include"event.h"
#include"trigger.h"
#include"backgroundmanager.h"

WorldManager::WorldManager()
{

}

void WorldManager::init()
{
    QString fileName=GameConfigurator::instance()->getWorldConfigFileName();
    QString path=QDir::currentPath()+QDir::separator()+fileName;

    QFile file(path);

    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        qDebug()<<"can not open "<<fileName<<endl;
        return ;
    }
    reader.setDevice(&file);

    world=new World();

    reader.readNextStartElement();//<worldBox>

    reader.readNextStartElement();//<worldName>
    world->setName(reader.readElementText());


    reader.readNextStartElement();//<TotalSceneNumber>
    int totalSceneNumber=reader.readElementText().toInt();

    for(int i=0;i<totalSceneNumber;i++)
    {
        Scene* scene=makeScene();
        world->addScene(scene);
        if(i==0)
        {
            world->switchScene(scene->getName());
        }
    }

    file.close();
}

World *WorldManager::getWorld()
{
    return world;
}


Scene *WorldManager::makeScene()
{
    reader.readNextStartElement();//<scene>

    reader.readNextStartElement();//<name>
    QString name=reader.readElementText();

    reader.readNextStartElement();//<width>
    int width=reader.readElementText().toInt();

    reader.readNextStartElement();//<height>
    int height=reader.readElementText().toInt();

    Scene* tempScene=new Scene();

    tempScene->setName(name);
    tempScene->setWidth(width);
    tempScene->setHeight(height);

    makeBackground(tempScene);
    makeTerrain(tempScene);
    makeDecoration(tempScene);
    makeCharacter(tempScene);
    makePlayer(tempScene);
    makeTriggerBox(tempScene);

    return tempScene;
}

void WorldManager::makeBackground(Scene *scene)
{
    reader.readNextStartElement();//<Background>

    reader.readNextStartElement();//<backgroundName>
    QString backgroundName=reader.readElementText();

    Background* BK=BackgroundManager::instance()->getBackground(backgroundName);

    scene->setBackground(BK);

    reader.readNextStartElement();//</Background>
}

void WorldManager::makeTerrain(Scene *scene)
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

void WorldManager::makeDecoration(Scene *scene)
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

void WorldManager::makeCharacter(Scene *scene)
{
    reader.readNextStartElement();//<CharacterBox>

    reader.readNextStartElement();//<TotalCharacterNumber>
    int characterNumber=reader.readElementText().toInt();

    for(int i=0;i<characterNumber;i++)
    {
        reader.readNextStartElement();//<Character>

        reader.readNextStartElement();//<CharacterName>
        QString characterName=reader.readElementText();

        reader.readNextStartElement();//<type>
        QString type=reader.readElementText();

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
        character->setType(type);

        scene->addCharacterToBox(character);

        reader.readNextStartElement();//<character>
    }
    reader.readNextStartElement();//<characterBox>
}

void WorldManager::makePlayer(Scene *scene)
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
    player->setType("PLAYER");

    //player->setRotateAngle(45);
    //player->setRotateZ(1);
    //player->setZoomX(2);
    //player->setZoomY(2);
    //player->setAlpha(0.5);

    InputModule::instance()->setEntity(player);

    scene->setPlayer(player);
    reader.readNextStartElement();//</player>
}

void WorldManager::makeTriggerBox(Scene *scene)
{
    reader.readNextStartElement();//<TriggerBox>

    reader.readNextStartElement();//<TotalTriggerNumber>
    int totalTriggerNumber=reader.readElementText().toInt();

    for(int i=0;i<totalTriggerNumber;i++)
    {
        makeTrigger(scene);
    }

    reader.readNextStartElement();//</TriggerBox>
}

void WorldManager::makeTrigger(Scene *scene)
{
    reader.readNextStartElement();//<Trigger>

    reader.readNextStartElement();//<condition>

    reader.readNextStartElement();//<conditionType>
    QString conditionType=reader.readElementText();

    Condition* condition=Condition::getCondition(conditionType);
    condition->setScene(scene);
    condition->config(&reader);


    reader.readNextStartElement();//</condition>

    //.....

    reader.readNextStartElement();//<event>

    reader.readNextStartElement();//<eventType>
    QString eventType=reader.readElementText();

    Event* event=Event::getEvent(eventType);
    event->setScene(scene);
    event->config(&reader);



    reader.readNextStartElement();//</event>

    reader.readNextStartElement();//</Trigger>

    Trigger* trigger=new Trigger();
    trigger->setCondition(condition);
    trigger->setEvent(event);

    scene->addTrigger(trigger);
}
