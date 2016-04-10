#ifndef SHOOTBULLET_H
#define SHOOTBULLET_H

#include"skill.h"

class ShootBullet:public Skill
{
public:
    ShootBullet(Character *e);
    void start();
    void end();
    void run();

    int getInterval() const;
    void setInterval(int value);
protected:
    void shootBullet();
    int clockId;
    int interval;
};

#endif // SHOOTBULLET_H
