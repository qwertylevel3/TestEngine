#ifndef SHOOT_H
#define SHOOT_H

#include"skill.h"

class Shoot:public Skill
{
public:
    Shoot(Character *e);
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

#endif // SHOOT_H
