#include "bullet.h"

Bullet::Bullet(const QString &spriteName)
    :Entity(spriteName)
{

}

Bullet *Bullet::clone()
{
    Bullet* newBullet=new Bullet(this->spriteName);

    return newBullet;
}

