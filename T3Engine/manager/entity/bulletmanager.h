#ifndef BULLETMANAGER_H
#define BULLETMANAGER_H

#include"bullet.h"

class BulletList
{
public:
    BulletList();
    void addBullet(Bullet* bullet);
    Bullet* getBullet();
    QString getBulletName() const;
    void setBulletName(const QString &value);
    ~BulletList();

private:
    QString bulletName;
    int index;
    QList<Bullet* > list;
};

class BulletManager:public Singleton<BulletManager>
{
public:
    BulletManager();
    void init();
    Bullet* getBullet(const QString& bulletName);
protected:
    QMap<QString,BulletList*> bulletBox;
    QXmlStreamReader reader;

    BulletList* makeBulletList();
};

#endif // BULLETMANAGER_H
