#ifndef DIRECTBULLET_H
#define DIRECTBULLET_H

#include"bullet.h"

class DirectBullet:public Bullet
{
public:
    DirectBullet(const QString& spriteName);
    void update();
    Bullet *clone();
};

#endif // DIRECTBULLET_H
