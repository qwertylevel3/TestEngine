#include "bullet.h"

Bullet::Bullet(const QString &spriteName)
    :Entity(spriteName)
{
    orientation=Orientation::empty;

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

    switch(orientation)
    {
    case Orientation::up:this->setY(this->getY()+speed);break;
    case Orientation::down:this->setY(this->getY()-speed);break;
    case Orientation::left:this->setX(this->getX()-speed);break;
    case Orientation::right:this->setX(this->getX()+speed);break;
    case Orientation::upLeft:
        this->setX(this->getX()-speed);
        this->setY(this->getY()+speed);
        break;
    case Orientation::downLeft:
        this->setX(this->getX()-speed);
        this->setY(this->getY()-speed);
        break;
    case Orientation::upRight:
        this->setX(this->getX()+speed);
        this->setY(this->getY()+speed);
        break;
    case Orientation::downRight:
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
Orientation::ORIENTATION Bullet::getOrientation() const
{
    return orientation;
}

void Bullet::setOrientation(const Orientation::ORIENTATION &value)
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
    case Orientation::up:
        orientation=Orientation::up;
        break;
    case Orientation::down:
        orientation=Orientation::down;
        break;
    case Orientation::left:
        orientation=Orientation::left;
        break;
    case Orientation::right:
        orientation=Orientation::right;
        break;
    case Orientation::upLeft:
        orientation=Orientation::upLeft;
        break;
    case Orientation::downLeft:
        orientation=Orientation::downLeft;
        break;
    case Orientation::upRight:
        orientation=Orientation::upRight;
        break;
    case Orientation::downRight:
        orientation=Orientation::downRight;
        break;
    default:
        break;

    }
}
