#include "world.h"
#include"decorationmanager.h"
#include"charactermanager.h"
#include"backgroundmanager.h"

World::World()
{

}

World::~World()
{
    QMap<QString,Scene*>::const_iterator i=sceneBox.constBegin();
    while(i!=sceneBox.constEnd())
    {
        delete i.value();
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

