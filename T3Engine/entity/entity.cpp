#include "entity.h"
#include"inputmodule.h"
#include"scene.h"
#include"module.h"


Entity::Entity(const QString &spriteName)
{
    this->spriteName=spriteName;
    sprite=SpriteManager::instance()->getSprite(spriteName);

    localX=0;
    localY=0;
    localZ=0;
    parent=0;

    state=ALIVE;
    remainTime=-1;
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
    Q_UNUSED(c)
}

void Entity::endCommand(InputModule::Command c)
{
    Q_UNUSED(c)
}

void Entity::updateRemainTime()
{
    if(remainTime>0)
    {
        remainTime--;
    }
    if(remainTime==0)
    {
        state=DEAD;
        for(int i=0;i<childList.size();i++)
        {
            childList[i]->setState(DEAD);
        }
    }
}

bool Entity::isAlive()
{
    return state==ALIVE?true:false;
}

void Entity::draw()
{
    if(isAlive())
    {
        sprite->draw();
        for(int i=0;i<childList.size();i++)
        {
            childList[i]->draw();
        }
        for(int i=0;i<moduleList.size();i++)
        {
            moduleList[i]->draw();
        }
    }

}

void Entity::drawRect()
{
    sprite->drawRect();
}

void Entity::update()
{
    sprite->update();
    updateRemainTime();
    for(int i=0;i<childList.size();i++)
    {
        childList[i]->update();
    }
    for(int i=0;i<moduleList.size();i++)
    {
        moduleList[i]->update();
    }
}

void Entity::moveX(float dx)
{
    setX(getX()+dx);
}

void Entity::moveY(float dy)
{
    setY(getY()+dy);
}

void Entity::setX(float x)
{
    sprite->setX(x);
    for(int i=0;i<childList.size();i++)
    {
        childList[i]->setX(x+childList[i]->getLocalX());
    }
}

void Entity::setY(float y)
{
    sprite->setY(y);
    for(int i=0;i<childList.size();i++)
    {
        childList[i]->setY(y+childList[i]->getLocalY());
    }
}

void Entity::setZ(float z)
{
    sprite->setZ(z);
    for(int i=0;i<childList.size();i++)
    {
        childList[i]->setZ(z+childList[i]->getLocalZ());
    }
}

void Entity::setZoomX(float z)
{
    sprite->setZoomX(z);
    for(int i=0;i<childList.size();i++)
    {
        childList[i]->setZoomX(z);
    }
}

void Entity::setZoomY(float z)
{
    sprite->setZoomY(z);
    for(int i=0;i<childList.size();i++)
    {
        childList[i]->setZoomY(z);
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
Scene *Entity::getScene() const
{
    return scene;
}

void Entity::setScene(Scene *value)
{
    scene = value;
}
Entity::STATE Entity::getState() const
{
    return state;
}

void Entity::setState(const STATE &value)
{
    state = value;
}
int Entity::getRemainTime() const
{
    return remainTime;
}

void Entity::setRemainTime(int value)
{
    remainTime = value;
}







