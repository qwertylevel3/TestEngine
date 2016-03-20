#ifndef TRACKBULLET_H
#define TRACKBULLET_H

#include"bullet.h"

class TrackBullet:public Bullet
{
public:
    TrackBullet(const QString& spriteName);
    void update();
    Bullet* clone();
};

#endif // TRACKBULLET_H
