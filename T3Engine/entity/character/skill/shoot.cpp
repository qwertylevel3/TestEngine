#include "shoot.h"
#include"bulletmanager.h"
#include"clockmanager.h"
#include"scene.h"
#include"math.h"


Shoot::Shoot(Character *e)
    :Skill(e)
{
    clockId=ClockManager::instance()->genClock();
}

void Shoot::start()
{
    Skill::start();
}

void Shoot::end()
{
    Skill::end();
}

void Shoot::run()
{
    if(character->getFocusIndex()==-1)
    {
        return;
    }
    if(ClockManager::instance()->isAlarm(clockId))
    {
        ClockManager::instance()->clear(clockId);
        shootBullet();
    }
}

void Shoot::shootBullet()
{
    int focusIndex=character->getFocusIndex();

    Character* focusCharacter=character->getScene()->getCharacterList()[focusIndex];
    if(focusCharacter->getState()==Character::DEAD)
    {
        return;
    }

//    Bullet* bullet=BulletManager::instance()->getBullet("trackBullet");
    Bullet* bullet=BulletManager::instance()->getBullet("laser");
    bullet->init(character);
    bullet->setZoomX(10);
//    bullet->setRemainTime(10);


    character->getScene()->addBulletToBox(bullet);
}
int Shoot::getInterval() const
{
    return interval;
}

void Shoot::setInterval(int value)
{
    interval = value;
    ClockManager::instance()->setClockInterval(clockId,value);
}

