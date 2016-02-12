#ifndef ENTITY_H
#define ENTITY_H

#include"T3Engine/sprite/sprite.h"
#include"T3Engine/manager/spritemanager.h"
#include<QList>

class Entity
{
public:
    Entity();
    Entity(const QString& spriteName);
    ~Entity();

    void setName(const QString& n){name=n;}
    void setSprite(const QString& n);
    virtual void draw();
    void drawRect();

    virtual void update();
    virtual Entity* clone()=0;

    void addChild(Entity* childEntity)
    {
        child.append(childEntity);
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
    void setX(float x);
    void setY(float y);
    void setZ(float z);

    void setRepeatX(int value)
    {
        sprite->setRepeatX(value);
    }
    void setRepeatY(int value)
    {
        sprite->setRepeatY(value);
    }
    int getRepeatX() const
    {
        return sprite->getRepeatX();
    }
    int getRepeatY() const
    {
        return sprite->getRepeatY();
    }


    void setWidth(float width)
    {
        sprite->setWidth(width);
    }
    void setHeight(float height)
    {
        sprite->setHeight(height);
    }
    float getWidth() const
    {
        return sprite->getWidth();
    }
    float getHeight() const
    {
        return sprite->getHeight();
    }

    void setLocalX(float x);
    void setLocalY(float y);
    void setLocalZ(float z);

    void setCurrentAction(int index){sprite->setCurrentAction(index);}
    void setChildCurrentAction(int childIndex,int index)
    {
        child[childIndex]->setCurrentAction(index);
    }
    void setTotalActionNumber(int t){sprite->setTotalActionNumber(t);}
    void setZoomX(float z);
    void setZoomY(float z);

    //TODO: handle child......
    void mirror(bool m){sprite->mirror(m);}
    void setRotateAngle(float a){sprite->setRotateAngle(a);}
    void setRotateX(float x){sprite->setRotateX(x);}
    void setRotateY(float y){sprite->setRotateY(y);}
    void setRotateZ(float z){sprite->setRotateZ(z);}

    QList<Entity*>& getChild(){return child;}
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

protected:
    QString name;
    QString spriteName;

    Sprite* sprite;
    Entity* parent;
    QList<Entity*> child;
    float localX;
    float localY;
    float localZ;
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
