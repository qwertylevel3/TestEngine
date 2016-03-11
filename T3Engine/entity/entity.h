#ifndef ENTITY_H
#define ENTITY_H

#include"sprite.h"
#include"spritemanager.h"
#include"inputmodule.h"

class Scene;

class Entity
{
public:
    static bool compareY(Entity* a,Entity* b);
    enum STATE{ALIVE,DEAD};
    Entity();
    Entity(const QString& spriteName);
    virtual ~Entity();


    virtual void startCommand(InputModule::Command c);
    virtual void endCommand(InputModule::Command c);

    void updateRemainTime();
    bool isAlive();

    void setName(const QString& n){name=n;}
    void setSprite(const QString& n);
    void drawRect();

    virtual void draw();
    virtual void update();
    virtual Entity* clone();

    void setText(const QString& text);


    void moveX(float dx);
    void moveY(float dy);

    void setAlpha(float alpha)
    {
        sprite->setAlpha(alpha);
    }
    float getAlpha()
    {
        return sprite->getAlpha();
    }

    void addChild(QString name,Entity* childEntity);
    void removeChild(QString name);
    void setX(float x);
    void setY(float y);
    void setZ(float z);

    void setRepeatX(int value);
    void setRepeatY(int value);
    int getRepeatX() const;
    int getRepeatY() const;

    void setWidth(float width);
    void setHeight(float height);
    float getWidth() const;
    float getHeight() const;

    void setLocalX(float x);
    void setLocalY(float y);
    void setLocalZ(float z);

    void setCurrentAction(int index);
    void setChildCurrentAction(QString name,int index);
    void setTotalActionNumber(int t){sprite->setTotalActionNumber(t);}
    void setZoomX(float z);
    void setZoomY(float z);

    //TODO: handle child......
    void mirror(bool m){sprite->mirror(m);}
    void setRotateAngle(float a){sprite->setRotateAngle(a);}
    void setRotateX(float x){sprite->setRotateX(x);}
    void setRotateY(float y){sprite->setRotateY(y);}
    void setRotateZ(float z){sprite->setRotateZ(z);}

    Entity* getChild(QString name);
    float getX(){return sprite->getX();}
    float getY(){return sprite->getY();}
    float getZ(){return sprite->getZ();}

    float getLocalX();
    float getLocalY();
    float getLocalZ();

    int getCurrentActionIndex(){return sprite->getCurrentActionIndex();}
    QList<QRectF>& getCurrentRects(){return sprite->getCurrentRects();}
    int getTotalActionNumber(){return sprite->getTotalActionNumber();}
    float getZoomX(){return sprite->getZoomX();}
    float getZoomY(){return sprite->getZoomY();}
    bool isMirror(){return sprite->isMirror();}
    float getRotateAngle(){return sprite->getRotateAngle();}

    float getRotateX(){return sprite->getRotateX();}
    float getRotateY(){return sprite->getRotateY();}
    float getRotateZ(){return sprite->getRotateZ();}

    QString getName(){return name;}
    QString getSpriteName(){return spriteName;}
    Sprite* getSprite(){return sprite;}
    Entity *getParent() const;
    void setParent(Entity *value);

    Scene *getScene() const;
    void setScene(Scene *value);

    STATE getState() const;
    void setState(const STATE &value);

    int getRemainTime() const;
    void setRemainTime(int value);

    bool getCollisionAble() const;
    void setCollisionAble(bool value);

    bool getDestructible() const;
    void setDestructible(bool value);

    bool getMoveAble() const;
    void setMoveAble(bool value);

    float getDx() const;
    void setDx(float value);

    float getDy() const;
    void setDy(float value);

protected:
    QString name;
    QString spriteName;

    Sprite* sprite;
    Entity* parent;
 //   QList<Entity*> childList;
    QMap<QString , Entity* > childBox;
    float localX;
    float localY;
    float localZ;

    Scene* scene;
    STATE state;

    int remainTime;

    bool collisionAble;//可碰撞
    bool destructible;//可破坏
    bool moveAble;

    float dx;
    float dy;
};

inline
void Entity::setSprite(const QString &n)
{
    if(sprite)
    {
        delete sprite;
    }
    spriteName=n;
    sprite=SpriteManager::instance()->getSprite(spriteName);
}

inline
void Entity::setText(const QString &text)
{
    sprite->setText(text);
}

inline
void Entity::addChild(QString name, Entity *childEntity)
{
    childBox.insert(name,childEntity);
    childEntity->setParent(this);

    childEntity->setX(this->getX());
    childEntity->setY(this->getY());
    childEntity->setZ(this->getZ());

    childEntity->setLocalX(0);
    childEntity->setLocalY(0);
    childEntity->setLocalZ(0);

    childEntity->setZoomX(this->getZoomX());
    childEntity->setZoomY(this->getZoomY());
}


inline
void Entity::setRepeatX(int value)
{
    sprite->setRepeatX(value);
}

inline
void Entity::setRepeatY(int value)
{
    sprite->setRepeatY(value);
}

inline
int Entity::getRepeatX() const
{
    return sprite->getRepeatX();
}

inline
int Entity::getRepeatY() const
{
    return sprite->getRepeatY();
}

inline
void Entity::setWidth(float width)
{
    sprite->setWidth(width);
}

inline
void Entity::setHeight(float height)
{
    sprite->setHeight(height);
}

inline
float Entity::getWidth() const
{
    return sprite->getWidth();
}

inline
float Entity::getHeight() const
{
    return sprite->getHeight();
}

inline
void Entity::setLocalX(float x)
{
    if(parent)
    {
        float px=parent->getX();
        localX=x;
        this->setX(px+x);
    }
    else
    {
        this->setX(x);
    }
}
inline
void Entity::setLocalY(float y)
{
    if(parent)
    {
        float py=parent->getY();
        localY=y;
        this->setY(py+y);
    }
    else
    {
        this->setY(y);
    }
}
inline
void Entity::setLocalZ(float z)
{
    if(parent)
    {
        float pz=parent->getZ();
        localZ=z;
        this->setZ(pz+z);
    }
    else
    {
        this->setZ(z);
    }
}

inline
void Entity::setCurrentAction(int index)
{
    sprite->setCurrentAction(index);
}

inline
void Entity::setChildCurrentAction(QString name, int index)
{
    childBox[name]->setCurrentAction(index);
}


inline
float Entity::getLocalX()
{
    if(parent)
    {
        return localX;
    }
    return getX();
}
inline
float Entity::getLocalY()
{
    if(parent)
    {
        return localY;
    }
    return getY();
}
inline
float Entity::getLocalZ()
{
    if(parent)
    {
        return localZ;
    }
    return getZ();
}



#endif // ENTITY_H
