#ifndef ENTITY_H
#define ENTITY_H

#include"T3Engine/sprite/sprite.h"
#include"T3Engine/manager/spritemanager.h"

class Entity
{
public:
    Entity();
    Entity(const QString& spriteName);
    ~Entity();

    void setName(const QString& n){name=n;}
    void setSprite(const QString& n);
    void draw(){sprite->draw();}
    void drawRect(){sprite->drawRect();}

    virtual void update();

    void setX(float x){sprite->setX(x);}
    void setY(float y){sprite->setY(y);}
    void setZ(float z){sprite->setZ(z);}
    void setCurrentAction(int index){sprite->setCurrentAction(index);}
    void setTotalActionNumber(int t){sprite->setTotalActionNumber(t);}
    void setZoomX(float z){sprite->setZoomX(z);}
    void setZoomY(float z){sprite->setZoomY(z);}
    void mirror(bool m){sprite->mirror(m);}
    void setRotateAngle(float a){sprite->setRotateAngle(a);}
    void setRotateX(float x){sprite->setRotateX(x);}
    void setRotateY(float y){sprite->setRotateY(y);}
    void setRotateZ(float z){sprite->setRotateZ(z);}


    float getX(){return sprite->getX();}
    float getY(){return sprite->getY();}
    float getZ(){return sprite->getZ();}
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
protected:
    QString name;
    QString spriteName;

    Sprite* sprite;
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



#endif // ENTITY_H
