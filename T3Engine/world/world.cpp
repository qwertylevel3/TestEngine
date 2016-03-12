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

void World::switchScene(QString sceneName)
{
    currentScene=sceneName;
}
