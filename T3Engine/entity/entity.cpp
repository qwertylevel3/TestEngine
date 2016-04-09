#include "entity.h"
#include"inputmodule.h"
#include"scene.h"


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

    collisionAble=false;
    destructible=false;
    moveAble=true;
    dx=0;
    dy=0;
}

Entity::~Entity()
{
    if(sprite)
    {
        delete sprite;
    }
    QMap<QString, Entity*>::const_iterator i = childBox.constBegin();
    while (i != childBox.constEnd()) {
        //cout << i.key() << ": " << i.value() << endl;
        delete (i.value());
        ++i;
    }
    childBox.clear();
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

    //TODO............
    if(getMoveAble())
    {
        this->setX(this->getX()+dx);
        this->setY(this->getY()+dy);
    }
    dx=0;
    dy=0;
}

Entity *Entity::clone()
{
    return new Entity(this->spriteName);
}

void Entity::moveX(float dx)
{
//    setX(getX()+dx);
    this->dx=dx;
}

void Entity::moveY(float dy)
{
//    setY(getY()+dy);
    this->dy=dy;
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

void Entity::setCurrentAction(const QString &actionName)
{
    sprite->setCurrentAction(actionName);
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
bool Entity::getCollisionAble() const
{
    return collisionAble;
}

void Entity::setCollisionAble(bool value)
{
    collisionAble = value;
}
bool Entity::getDestructible() const
{
    return destructible;
}

void Entity::setDestructible(bool value)
{
    destructible = value;
}
bool Entity::getMoveAble() const
{
    return moveAble;
}

void Entity::setMoveAble(bool value)
{
    moveAble = value;
}
float Entity::getDx() const
{
    return dx;
}

void Entity::setDx(float value)
{
    dx = value;
}
float Entity::getDy() const
{
    return dy;
}

void Entity::setDy(float value)
{
    dy = value;
}

