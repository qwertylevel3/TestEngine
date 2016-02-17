#include "entity.h"
#include"T3Engine/inputmodule.h"


Entity::Entity(const QString &spriteName)
{
    this->spriteName=spriteName;
    sprite=SpriteManager::instance()->getSprite(spriteName);

    localX=0;
    localY=0;
    localZ=0;
    parent=0;
}

Entity::~Entity()
{
    if(sprite)
    {
        delete sprite;
    }
}

void Entity::startCommand(InputModule::Command c)
{
}

void Entity::endCommand(InputModule::Command c)
{
}

void Entity::draw()
{
    sprite->draw();
}

void Entity::drawRect()
{
    sprite->drawRect();
}

void Entity::update()
{
    sprite->update();
}

void Entity::setX(float x)
{
    sprite->setX(x);
    for(int i=0;i<child.size();i++)
    {
        child[i]->setX(x+child[i]->getLocalX());
    }
}

void Entity::setY(float y)
{
    sprite->setY(y);
    for(int i=0;i<child.size();i++)
    {
        child[i]->setY(y+child[i]->getLocalY());
    }
}

void Entity::setZ(float z)
{
    sprite->setZ(z);
    for(int i=0;i<child.size();i++)
    {
        child[i]->setZ(z+child[i]->getLocalZ());
    }
}

void Entity::setZoomX(float z)
{
    sprite->setZoomX(z);
    for(int i=0;i<child.size();i++)
    {
        child[i]->setZoomX(z);
    }
}

void Entity::setZoomY(float z)
{
    sprite->setZoomY(z);
    for(int i=0;i<child.size();i++)
    {
        child[i]->setZoomY(z);
    }
}

Entity *Entity::getParent() const
{
    return parent;
}

void Entity::setParent(Entity *value)
{
    parent = value;
}



