#include "entity.h"
#include"inputmodule.h"
#include"scene.h"
#include"module.h"


bool Entity::compareY(Entity *a, Entity *b)
{

    float ya=a->getY()-a->getHeight()/GameConfigurator::instance()->getScale();
    float yb=b->getY()-b->getHeight()/GameConfigurator::instance()->getScale();
    return ya>yb;

}

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

        QMap<QString, Entity*>::const_iterator i = childBox.constBegin();
        while (i != childBox.constEnd()) {
            //cout << i.key() << ": " << i.value() << endl;
            i.value()->setState(DEAD);
            ++i;
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
        QMap<QString,Entity*>::const_iterator i=childBox.constBegin();
        while(i!=childBox.constEnd())
        {
            i.value()->draw();
            i++;
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
    QMap<QString,Entity*>::const_iterator i=childBox.constBegin();
    while(i!=childBox.constEnd())
    {
        i.value()->update();
        i++;
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

void Entity::removeChild(QString name)
{
//    delete childBox[name];
    childBox.remove(name);
}

void Entity::setX(float x)
{
    sprite->setX(x);
    QMap<QString,Entity*>::const_iterator i=childBox.constBegin();
    while(i!=childBox.constEnd())
    {
        i.value()->setX(x+i.value()->getLocalX());
        i++;
    }
}

void Entity::setY(float y)
{
    sprite->setY(y);
    QMap<QString,Entity*>::const_iterator i=childBox.constBegin();
    while(i!=childBox.constEnd())
    {
        i.value()->setY(y+i.value()->getLocalY());
        i++;
    }
}

void Entity::setZ(float z)
{
    sprite->setZ(z);
    QMap<QString,Entity*>::const_iterator i=childBox.constBegin();
    while(i!=childBox.constEnd())
    {
        i.value()->setZ(z+i.value()->getLocalZ());
        i++;
    }
}

void Entity::setZoomX(float z)
{
    sprite->setZoomX(z);
    QMap<QString,Entity*>::const_iterator i=childBox.constBegin();
    while(i!=childBox.constEnd())
    {
        i.value()->setZoomX(z);
        i++;
    }
}

void Entity::setZoomY(float z)
{
    sprite->setZoomY(z);
    QMap<QString,Entity*>::const_iterator i=childBox.constBegin();
    while(i!=childBox.constEnd())
    {
        i.value()->setZoomY(z);
        i++;
    }
}

Entity *Entity::getChild(QString name)
{
    return childBox[name];
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







