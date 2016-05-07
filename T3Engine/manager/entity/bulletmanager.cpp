#include "bulletmanager.h"
#include"stable.h"
#include"gameconfigurator.h"


BulletList::BulletList()
{
    index=0;
}

void BulletList::addBullet(Bullet *bullet)
{
    list.push_back(bullet);
}

Bullet *BulletList::getBullet()
{
    if(list.empty())
    {
        qDebug()<<bulletName<<" is empty"<<endl;
    }
    int start=index;
    while(list[index]->isAlive())
    {
        index=(++index)%list.size();
        qDebug()<<index<<endl;
        if(index==start)
        {
            qDebug()<<bulletName<<" is full"<<endl;
            return NULL;
        }
    }
    list[index]->setState(Bullet::ALIVE);
    return list[index];
}
QString BulletList::getBulletName() const
{
    return bulletName;
}

void BulletList::setBulletName(const QString &value)
{
    bulletName = value;
}

BulletList::~BulletList()
{
    for(int i=0;i<list.size();i++)
    {
        delete list[i];
    }
}









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
        BulletList* bulletList=makeBulletList();
        bulletBox.insert(bulletList->getBulletName(),bulletList);
    }

    file.close();
}

Bullet* BulletManager::getBullet(const QString &bulletName)
{
    return bulletBox[bulletName]->getBullet();
}

BulletList *BulletManager::makeBulletList()
{
    BulletList* bulletList=new BulletList();

    reader.readNextStartElement();//<Bullet>

    reader.readNextStartElement();//<Type>
    QString type=reader.readElementText();

    reader.readNextStartElement();//<Name>
    QString name=reader.readElementText();

    reader.readNextStartElement();//<SpriteName>
    QString spriteName=reader.readElementText();

    reader.readNextStartElement();//<total>
    int total= reader.readElementText().toInt();

    reader.readNextStartElement();//<speed>
    float speed=reader.readElementText().toFloat();

    reader.readNextStartElement();//<damage>
    float damage=reader.readElementText().toFloat();

    reader.readNextStartElement();//</Bullet>

    for(int i=0;i<total;i++)
    {
        Bullet* bullet=Bullet::getBullet(spriteName,type);
        bullet->setName(name);
        bullet->setSpeed(speed);
        bullet->setDamage(damage);
        bullet->setState(Bullet::DEAD);

        bulletList->addBullet(bullet);
    }
    bulletList->setBulletName(name);
    return bulletList;
}


