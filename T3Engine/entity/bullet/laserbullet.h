#ifndef LASERBULLET_H
#define LASERBULLET_H

#include"bullet.h"

class LaserBullet:public Bullet
{
public:
    LaserBullet(const QString& spriteName);
    void update();
    void boom();
    Bullet* clone();
};

#endif // LASERBULLET_H
