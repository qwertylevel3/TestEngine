#ifndef SHOOTLASER_H
#define SHOOTLASER_H

#include"skill.h"
#include"bullet.h"

class ShootLaser:public Skill
{
public:
    ShootLaser(Character * e);
    void start();
    void run();
    void end();
    QString getLaserName() const;
    void setLaserName(const QString &value);

protected:
    QString laserName;
    Bullet* laser;
};

#endif // SHOOTLASER_H
