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

    QString getBulletName() const;
    void setBulletName(const QString &value);

protected:
    void shoot();
    int clockId;
    int interval;
    QString bulletName;
};

#endif // SHOOTBULLET_H
