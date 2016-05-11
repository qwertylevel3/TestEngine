#include "world.h"
#include"decorationmanager.h"
#include"charactermanager.h"
#include"backgroundmanager.h"
#include"scene.h"
#include"player.h"
#include"stable.h"

World::World()
{

}

World::~World()
{
    clear();
}

bool World::init()
{
    setInitPath();
    return load(worldPath);
}

void World::destory()
{
     QMap<QString ,Scene*>::iterator i=sceneBox.begin();
     while(i!=sceneBox.end())
     {
         delete i.value();
         i++;
     }
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
    Player::instance()->init();
    Player::instance()->setX(0);
    Player::instance()->setY(0);
    Player::instance()->setZ(-10);

    InputModule::instance()->setEntity(Player::instance());

    sceneBox[currentScene]->setPlayer(Player::instance());
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

void World::changeScene(const QString &sceneName, float x, float y)
{
    
}

bool World::load(const QString &path)
{
    QString worldFile=path+QDir::separator()+"world.xml";
    QFile file(worldFile);

    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        qDebug()<<"can not open "<<path<<endl;
        exit(0);
    }
    reader.setDevice(&file);

    reader.readNextStartElement();//<world>

    reader.readNextStartElement();//<TotalSceneNumber>
    int totalSceneNumber=reader.readElementText().toInt();

    reader.readNextStartElement();//<sceneBox>


    QList<QString> sceneList;

    for(int i=0;i<totalSceneNumber;i++)
    {
        reader.readNextStartElement();//<sceneName>
        QString sceneName=reader.readElementText();

        sceneList.push_back(sceneName);
    }

    reader.readNextStartElement();//</sceneBox>

    reader.readNextStartElement();//</world>

    file.close();

    for(int i=0;i<totalSceneNumber;i++)
    {
        Scene* scene=makeScene(sceneList[i]);
        addScene(scene);
        if(i==0)
        {
            switchScene(scene->getName());
        }
    }
    return true;
}

QString World::setInitPath()
{
    name=GameConfigurator::instance()->getWorldConfigFileName();
    worldPath=QDir::currentPath()
            +QDir::separator()+"world"
            +QDir::separator()+name;
    return worldPath;
}

QString World::setSavePath(const QString &fileName)
{
    return QDir::currentPath()+QDir::separator()
            +"world"+QDir::separator()+fileName+".xml";
}

Scene *World::makeScene(const QString &sceneName)
{
    QString fileName=worldPath
            +QDir::separator()+"scene"
            +QDir::separator()+sceneName+".xml";
    QFile file(fileName);

    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        qDebug()<<"can not open "<<sceneName<<endl;
        exit(0);
    }
    reader.setDevice(&file);

    reader.readNextStartElement();//<scene>

    reader.readNextStartElement();//<width>
    int width=reader.readElementText().toInt();

    reader.readNextStartElement();//<height>
    int height=reader.readElementText().toInt();

    Scene* tempScene=new Scene();

    tempScene->setName(sceneName);
    tempScene->setWidth(width);
    tempScene->setHeight(height);

    makeBackground(tempScene);
    makeDecoration(tempScene);
    //makeCharacter(tempScene);
//    makePlayer(tempScene);
    makeTriggerBox(tempScene);
    makeSceneBorder(tempScene);

    reader.readNextStartElement();//</scene>

    file.close();

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

   // player->setRotateAngle(45);
   // player->setRotateZ(1);
   // player->setZoomX(3);
   // player->setZoomY(2);
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


