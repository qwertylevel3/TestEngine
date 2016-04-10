#include "laserbullet.h"
#include"clockmanager.h"

LaserBullet::LaserBullet(const QString &spriteName)
    :Bullet(spriteName)
{
}

void LaserBullet::update()
{
    Bullet::update();
}

Bullet *LaserBullet::clone()
{
    LaserBullet* newBullet=new LaserBullet(this->spriteName);

    newBullet->setSpeed(this->speed);
    newBullet->setDamage(this->damage);
    newBullet->setName(this->name);

    return newBullet;
}

