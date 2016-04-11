#include "shootbullet.h"
#include"bulletmanager.h"
#include"clockmanager.h"
#include"scene.h"
#include"math.h"


ShootBullet::ShootBullet(Character *e)
    :Skill(e)
{
    clockId=ClockManager::instance()->genClock();
    bulletName="trackBullet";
    interval=15;
}

void ShootBullet::start()
{
    Skill::start();
}

void ShootBullet::end()
{
    Skill::end();
}

void ShootBullet::run()
{
    if(character->getFocusIndex()==-1)
    {
        return;
    }
    if(ClockManager::instance()->isAlarm(clockId))
    {
        ClockManager::instance()->clear(clockId);
        shoot();
    }
}

void ShootBullet::shoot()
{
    int focusIndex=character->getFocusIndex();

    Character* focusCharacter=character->getScene()->getCharacterList()[focusIndex];

    if(focusCharacter->getState()==Character::DEAD)
    {
        return;
    }

    Bullet* bullet=BulletManager::instance()->getBullet(bulletName);
//    Bullet* bullet=BulletManager::instance()->getBullet("directBullet");
    bullet->init(character);
//    bullet->setRemainTime(10);

    character->getScene()->addBulletToBox(bullet);
}

QString ShootBullet::getBulletName() const
{
    return bulletName;
}

void ShootBullet::setBulletName(const QString &value)
{
    bulletName = value;
}

int ShootBullet::getInterval() const
{
    return interval;
}

void ShootBullet::setInterval(int value)
{
    interval = value;
    ClockManager::instance()->setClockInterval(clockId,value);
}

