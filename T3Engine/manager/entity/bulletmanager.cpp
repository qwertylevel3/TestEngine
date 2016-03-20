#include "bulletmanager.h"
#include"stable.h"
#include"gameconfigurator.h"

BulletManager::BulletManager()
{

}

void BulletManager::init()
{
    QString fileName=GameConfigurator::instance()->getBulletConfigFileName();
    QString path=QDir::currentPath()+QDir::separator()+fileName;


    QFile file(path);

    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        qDebug()<<"can not open "<<fileName<<endl;
        return ;
    }
    reader.setDevice(&file);

    reader.readNextStartElement();//<BulletBox>
    reader.readNextStartElement();//<TotalBulletNumber>
    int totalBulletNumber=reader.readElementText().toInt();

    for(int i=0;i<totalBulletNumber;i++)
    {
        Bullet* bullet=makeBullet();
        addBullet(bullet->getName(),bullet);
    }

    file.close();
}

Bullet* BulletManager::getBullet(const QString &bulletName)
{
    return bulletBox[bulletName]->clone();
}

Bullet* BulletManager::makeBullet()
{
    reader.readNextStartElement();//<Bullet>

    reader.readNextStartElement();//<Type>
    QString type=reader.readElementText();

    reader.readNextStartElement();//<Name>
    QString name=reader.readElementText();

    reader.readNextStartElement();//<SpriteName>
    QString spriteName=reader.readElementText();

    reader.readNextStartElement();//<speed>
    float speed=reader.readElementText().toFloat();

    reader.readNextStartElement();//<damage>
    float damage=reader.readElementText().toFloat();

    reader.readNextStartElement();//</Bullet>

    Bullet* bullet=Bullet::getBullet(spriteName,type);
    bullet->setName(name);
    bullet->setSpeed(speed);
    bullet->setDamage(damage);
    return bullet;
}
