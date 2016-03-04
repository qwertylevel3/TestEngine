#ifndef BULLET_H
#define BULLET_H

#include"entity.h"
#include"character.h"
#include"orientation.h"

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

    Character *getShooter() const;
    void setShooter(Character *value);

    float getDirectionX() const;
    void setDirectionX(float value);

    float getDirectionY() const;
    void setDirectionY(float value);

protected:
    float speed;
    float damage;

    float directionX;
    float directionY;

    Character* shooter;
};

#endif // BULLET_H
