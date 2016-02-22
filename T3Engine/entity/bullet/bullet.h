#ifndef BULLET_H
#define BULLET_H

#include"T3Engine/entity/entity.h"
#include"T3Engine/entity/character/character.h"
#include"T3Engine/orientation.h"

class Bullet:public Entity
{
public:
    Bullet(const QString& spriteName);
    Bullet* clone();
    void update();
    float getSpeed() const;
    void setSpeed(float value);

    float getDamage() const;
    void setDamage(float value);

    Orientation::ORIENTATION getOrientation() const;
    void setOrientation(const Orientation::ORIENTATION &value);

    Character *getShooter() const;
    void setShooter(Character *value);

protected:
    float speed;
    float damage;
    Orientation::ORIENTATION orientation;

    Character* shooter;
};

#endif // BULLET_H
