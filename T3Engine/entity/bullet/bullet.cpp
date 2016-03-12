#include "bullet.h"

Bullet::Bullet(const QString &spriteName)
    :Entity(spriteName)
{
    sprite=SpriteManager::instance()->getBulletSprite(spriteName);
}

Bullet *Bullet::clone()
{
    Bullet* newBullet=new Bullet(this->spriteName);
    newBullet->setSpeed(this->speed);
    newBullet->setDamage(this->damage);

    return newBullet;
}

void Bullet::update()
{
    Entity::update();

    this->setX(this->getX()+directionX*speed);
    this->setY(this->getY()+directionY*speed);

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


