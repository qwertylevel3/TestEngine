#include "directbullet.h"

DirectBullet::DirectBullet(const QString& spriteName)
    :Bullet(spriteName)
{

}

void DirectBullet::update()
{
    Bullet::update();
    fly();
}

Bullet *DirectBullet::clone()
{
    DirectBullet* newBullet=new DirectBullet(this->spriteName);
    newBullet->setSpeed(this->speed);
    newBullet->setDamage(this->damage);
    newBullet->setName(this->name);

    return newBullet;
}
