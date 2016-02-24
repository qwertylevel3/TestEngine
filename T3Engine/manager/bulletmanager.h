#ifndef BULLETMANAGER_H
#define BULLETMANAGER_H

#include"bullet.h"


class BulletManager:public Singleton<BulletManager>
{
public:
    BulletManager();
    void init();
    Bullet* getBullet(const QString& bulletName);
    void addBullet(const QString& bulletName,Bullet* bullet){bulletBox.insert(bulletName,bullet);}
protected:
    QMap<QString,Bullet*> bulletBox;
    QXmlStreamReader reader;

    Bullet* makeBullet();
};

#endif // BULLETMANAGER_H
