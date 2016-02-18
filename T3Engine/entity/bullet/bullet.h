#ifndef BULLET_H
#define BULLET_H

#include"T3Engine/entity/entity.h"
#include"T3Engine/entity/character/character.h"

class Bullet:public Entity
{
public:
    enum ORIENTATION{empty,up,down,left,right,
                     upLeft,upRight,downLeft,downRight};

    Bullet(const QString& spriteName);
    Bullet* clone();
    void update();
    float getSpeed() const;
    void setSpeed(float value);

    float getDamage() const;
    void setDamage(float value);

    Bullet::ORIENTATION getOrientation() const;
    void setOrientation(const ORIENTATION &value);

    Character *getShooter() const;
    void setShooter(Character *value);

protected:
    float speed;
    float damage;
    ORIENTATION orientation;

    Character* shooter;
};

#endif // BULLET_H
