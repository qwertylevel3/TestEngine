#include "world.h"
#include"decorationmanager.h"
#include"charactermanager.h"
#include"backgroundmanager.h"
#include"terrainmanager.h"
#include"scene.h"

World::World()
{

}

World::~World()
{
    clear();
}

bool World::init()
{
    QString path=setInitPath();
    return load(path);
}

bool World::open(const QString &path)
{
    return load(path);
}

void World::clear()
{
    QMap<QString,Scene*>::iterator i=sceneBox.begin();
    while(i!=sceneBox.end())
    {
        delete i.value();
        i++;
    }
    sceneBox.clear();
}

void World::update()
{
    sceneBox[currentScene]->update();
}

void World::draw()
{
    sceneBox[currentScene]->draw();
}

void World::switchScene(const QString &sceneName)
{
    currentScene=sceneName;
}
QString World::getName() const
{
    return name;
}

void World::setName(const QString &value)
{
    name = value;
}

void World::addScene(Scene *scene)
{
    sceneBox.insert(scene->getName(),scene);
}

void World::addDecoration(const QString &decorationName)
{
    Decoration* decoration=DecorationManager::instance()->getDecoration(decorationName);
    decoration->setX(0);
    decoration->setY(0);
    decoration->setZ(-10);
    sceneBox[currentScene]->addDecorationToBox(decoration);
}

void World::addCharacter(const QString &characterName)
{
    Character* character=CharacterManager::instance()->getCharacter(characterName);
    character->setX(0);
    character->setY(0);
    character->setZ(-10);
    sceneBox[currentScene]->addCharacterToBox(character);
}

void World::setBackground(const QString &backgroundName)
{
    Background* BK=BackgroundManager::instance()->getBackground(backgroundName);
    sceneBox[currentScene]->setBackground(BK);
}

Entity *World::selectEntity(const QPoint &p)
{
    return sceneBox[currentScene]->selectEntity(p);
}

int World::getTotalSceneNumber()
{
    return sceneBox.size();
}
QMap<QString, Scene *> World::getSceneBox() const
{
    return sceneBox;
}

bool World::save(const QString &fileName)
{
    QString path=setSavePath(fileName);

    QFile file(path);

    if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        qDebug()<<"can not write "<<fileName<<endl;
        return false;
    }
    writer.setDevice(&file);
    writer.setAutoFormatting(true);

    writer.writeStartDocument();

    writer.writeStartElement("World");

    writer.writeTextElement("WorldName",getName());
    writer.writeTextElement("TotalSceneNumber",QString::number(getTotalSceneNumber()));

    QMap<QString,Scene*>::const_iterator  i=sceneBox.constBegin();
    while(i!=sceneBox.constEnd())
    {
        i.value()->save(&writer);
        i++;
    }


    writer.writeEndElement();

    writer.writeEndDocument();

    file.close();
    return true;
}

bool World::load(const QString &path)
{
    QFile file(path);

    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        qDebug()<<"can not open "<<path<<endl;
        return false;
    }
    reader.setDevice(&file);

    reader.readNextStartElement();//<worldBox>

    reader.readNextStartElement();//<worldName>
    this->setName(reader.readElementText());


    reader.readNextStartElement();//<TotalSceneNumber>
    int totalSceneNumber=reader.readElementText().toInt();

    for(int i=0;i<totalSceneNumber;i++)
    {
        Scene* scene=makeScene();
        addScene(scene);
        if(i==0)
        {
            switchScene(scene->getName());
        }
    }

    file.close();
    return true;
}

QString World::setInitPath()
{
    QString fileName=GameConfigurator::instance()->getWorldConfigFileName();
    return QDir::currentPath()+QDir::separator()+fileName;
}

QString World::setSavePath(const QString &fileName)
{
    return QDir::currentPath()+QDir::separator()
            +"world"+QDir::separator()+fileName+".xml";
}

Scene *World::makeScene()
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
    makeSceneBorder(tempScene);

    return tempScene;
}

void World::makeBackground(Scene *scene)
{
    reader.readNextStartElement();//<Background>

    reader.readNextStartElement();//<backgroundName>
    QString backgroundName=reader.readElementText();

    Background* BK=BackgroundManager::instance()->getBackground(backgroundName);

    scene->setBackground(BK);

    reader.readNextStartElement();//</Background>

}

void World::makeTerrain(Scene *scene)
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

void World::makeDecoration(Scene *scene)
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

void World::makeCharacter(Scene *scene)
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

void World::makePlayer(Scene *scene)
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
    //player->setZoomX(3);
    //player->setZoomY(2);
    //player->setAlpha(0.5);

    InputModule::instance()->setEntity(player);

    scene->setPlayer(player);
    reader.readNextStartElement();//</player>

}

void World::makeTriggerBox(Scene *scene)
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

void World::makeTrigger(Scene *scene)
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

void World::makeSceneBorder(Scene *scene)
{
    Decoration* borderUp=DecorationManager::instance()->getDecoration("empty");
    Decoration* borderDown=DecorationManager::instance()->getDecoration("empty");
    Decoration* borderLeft=DecorationManager::instance()->getDecoration("empty");
    Decoration* borderRight=DecorationManager::instance()->getDecoration("empty");

    int width=scene->getWidth();
    int height=scene->getHeight();

    borderUp->setZoomX(width/borderUp->getWidth());
    borderDown->setZoomX(width/borderDown->getWidth());
    borderLeft->setZoomY(height/borderLeft->getHeight());
    borderRight->setZoomY(height/borderRight->getHeight());

    borderUp->setX(0);
    borderUp->setY(height/2);
    borderUp->setZ(-10);

    borderDown->setX(0);
    borderDown->setY(-height/2);
    borderDown->setZ(-10);

    borderLeft->setX(width/2);
    borderLeft->setY(0);
    borderLeft->setZ(-10);

    borderRight->setX(-width/2);
    borderRight->setY(0);
    borderRight->setZ(-10);

    scene->addDecorationToBox(borderUp);
    scene->addDecorationToBox(borderDown);
    scene->addDecorationToBox(borderLeft);
    scene->addDecorationToBox(borderRight);
}


