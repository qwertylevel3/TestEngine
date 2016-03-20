#include "trackbullet.h"

TrackBullet::TrackBullet(const QString& spriteName)
    :Bullet(spriteName)
{

}

void TrackBullet::update()
{
    Bullet::update();

    setDirectionToTarget();
    fly();
}

Bullet *TrackBullet::clone()
{
    TrackBullet* newBullet=new TrackBullet(this->spriteName);

    newBullet->setSpeed(this->speed);
    newBullet->setDamage(this->damage);
    newBullet->setName(this->name);

    return newBullet;
}

