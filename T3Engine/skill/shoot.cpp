#include "shoot.h"
#include"bulletmanager.h"
#include"scenemanager.h"
#include"clockmanager.h"
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
    Bullet* bullet=BulletManager::instance()->getBullet("bullet");
    bullet->setZoomX(0.2);
    bullet->setZoomY(0.2);

    bullet->setX(character->getX());
    bullet->setY(character->getY());
    bullet->setZ(character->getZ());

    bullet->setRemainTime(100);
    float x1=character->getX();
    float y1=character->getY();

    int focusIndex=character->getFocusIndex();

    float x2=character->getScene()->getCharacterBox()[focusIndex]->getX();
    float y2=character->getScene()->getCharacterBox()[focusIndex]->getY();

    float dx=x2-x1;
    float dy=y2-y1;

    float dv=sqrt(dx*dx+dy*dy);

    float directionX=dx/dv;
    float directionY=dy/dv;

    bullet->setDirectionX(directionX);
    bullet->setDirectionY(directionY);

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

