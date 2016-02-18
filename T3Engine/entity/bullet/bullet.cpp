#include "bullet.h"

Bullet::Bullet(const QString &spriteName)
    :Entity(spriteName)
{
    orientation=empty;

}

Bullet *Bullet::clone()
{
    Bullet* newBullet=new Bullet(this->spriteName);

    return newBullet;
}

void Bullet::update()
{
    Entity::update();

    switch(orientation)
    {
    case up:this->setY(this->getY()+speed);break;
    case down:this->setY(this->getY()-speed);break;
    case left:this->setX(this->getX()-speed);break;
    case right:this->setX(this->getX()+speed);break;
    case upLeft:
        this->setX(this->getX()-speed);
        this->setY(this->getY()+speed);
        break;
    case downLeft:
        this->setX(this->getX()-speed);
        this->setY(this->getY()+speed);
        break;
    case upRight:
        this->setX(this->getX()+speed);
        this->setY(this->getY()+speed);
        break;
    case downRight:
        this->setX(this->getX()+speed);
        this->setY(this->getY()-speed);
        break;
    default:
        break;

    }
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
Bullet::ORIENTATION Bullet::getOrientation() const
{
    return orientation;
}

void Bullet::setOrientation(const ORIENTATION &value)
{
    orientation = value;
}
Character *Bullet::getShooter() const
{
    return shooter;
}

void Bullet::setShooter(Character *value)
{
    shooter = value;
    switch(shooter->getOrientation())
    {
    case Character::up:
        orientation=up;
        break;
    case Character::down:
        orientation=down;
        break;
    case Character::left:
        orientation=left;
        break;
    case Character::right:
        orientation=right;
        break;
    case Character::upLeft:
        orientation=upLeft;
        break;
    case Character::downLeft:
        orientation=downLeft;
        break;
    case Character::upRight:
        orientation=upRight;
        break;
    case Character::downRight:
        orientation=downRight;
        break;
    default:
        break;

    }
}
