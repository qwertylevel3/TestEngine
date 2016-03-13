#include "world.h"

World::World()
{

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

