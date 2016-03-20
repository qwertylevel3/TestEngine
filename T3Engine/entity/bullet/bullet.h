#ifndef BULLET_H
#define BULLET_H

#include"entity.h"
#include"character.h"
#include"orientation.h"

class Bullet:public Entity
{
public:
    static Bullet* getBullet(const QString& spriteName,const QString& type);
    Bullet(const QString& spriteName);
    Bullet* clone();
    virtual void update();
    virtual void init(Character* shooter);

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

    void boom();

    Character *getTarget() const;
    void setTarget(Character *value);

    void setDirectionToTarget();
    void fly();

protected:
    float speed;
    float damage;

    float directionX;
    float directionY;

    Character* shooter;
    Character* target;
};

#endif // BULLET_H
