#include "bullet.h"
#include"directbullet.h"
#include"trackbullet.h"
#include"scene.h"
#include<math.h>
#include"collisiondetector.h"

Bullet::Bullet(const QString &spriteName)
    :Entity(spriteName)
{
    shooter=0;
    target=0;
}

Bullet *Bullet::clone()
{
    Bullet* newBullet=new Bullet(this->spriteName);
    newBullet->setSpeed(this->speed);
    newBullet->setDamage(this->damage);
    newBullet->setName(this->name);

    return newBullet;
}

Bullet *Bullet::getBullet(const QString& spriteName,const QString& type)
{
    if(type=="Direct")
    {
        DirectBullet* bullet=new DirectBullet(spriteName);
        return bullet;
    }
    else if(type=="Track")
    {
        TrackBullet* bullet=new TrackBullet(spriteName);
        return bullet;
    }
    else
    {
        qDebug()<<"unknow bullet type:"<<type<<endl;
        return NULL;
    }
}

void Bullet::update()
{
    Entity::update();
}

float Bullet::getSpeed() const
{
    return speed;
}

void Bullet::setSpeed(float value)
{
    speed = value;
}
float Bullet::getDamage() const
{
    return damage;
}

void Bullet::setDamage(float value)
{
    damage = value;
}
Character *Bullet::getShooter() const
{
    return shooter;
}

void Bullet::setShooter(Character *value)
{
    shooter = value;
    int focusIndex=shooter->getFocusIndex();

    target=shooter->getScene()->getCharacterList()[focusIndex];
}

float Bullet::getDirectionX() const
{
    return directionX;
}

void Bullet::setDirectionX(float value)
{
    directionX = value;
}
float Bullet::getDirectionY() const
{
    return directionY;
}

void Bullet::setDirectionY(float value)
{
    directionY = value;
}

void Bullet::boom()
{
    this->setState(Entity::DEAD);
}
Character *Bullet::getTarget() const
{
    return target;
}

void Bullet::setTarget(Character *value)
{
    target = value;
}

void Bullet::setDirectionToTarget()
{
    if(target && target->isAlive() && shooter)
    {
        float x1=this->getX();
        float y1=this->getY();

        float x2=target->getX();
        float y2=target->getY();

    //    float dx=x2-x1;
    //    float dy=y2-y1;

        float tempAngle;
        if(x2>x1)
        {
            tempAngle=-CollisionDetector::radian2angle(atan((y2-y1)/(x2-x1)));
        }
        else if(x2<x1)
        {
            tempAngle=-CollisionDetector::radian2angle(atan((y2-y1)/(x2-x1)));
            tempAngle+=180;
        }
        else
        {
            tempAngle=180;
        }

        this->setRotateZ(1);
        this->setRotateAngle(tempAngle);
    }
}

void Bullet::fly()
{
    this->setX(this->getX()+directionX*speed);
    this->setY(this->getY()+directionY*speed);
}

void Bullet::init(Character* shooter)
{
    setShooter(shooter);

    setZoomX(0.2);
    setZoomY(0.2);

    setX(shooter->getX());
    setY(shooter->getY());
    setZ(shooter->getZ());

    setRemainTime(100);

    setDirectionToTarget();

}
