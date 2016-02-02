#include"scene.h"

Scene::Scene()
{

}

Scene::~Scene()
{

}

void Scene::init()
{
    Character* testCharacter=new Character("test");
    characterBox.append(testCharacter);

    testCharacter->setZ(-5);
    testCharacter->setX(1);
    testCharacter->setZoomX(0.7);
}

void Scene::draw()
{
    for(int i=0;i<characterBox.size();i++)
    {
        characterBox[i]->draw();
    }
}

void Scene::drawRect()
{
    for(int i=0;i<characterBox.size();i++)
    {
        characterBox[i]->drawRect();
    }
}

void Scene::update()
{
    for(int i=0;i<characterBox.size();i++)
    {
        characterBox[i]->update();
    }
}

void Scene::load(const QString &filename)
{

}

void Scene::unload()
{

}

void Scene::collision()
{

}
