#include "shoot.h"
#include"bulletmanager.h"
#include"scenemanager.h"
#include"clockmanager.h"


Shoot::Shoot(Character *e)
    :Skill(e)
{
    clockId=ClockManager::instance()->genClock();
}

void Shoot::start(InputModule::Command c)
{
    Skill::start(c);

}

void Shoot::end(InputModule::Command c)
{
    Skill::end(c);
}

void Shoot::run()
{
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

    bullet->setOrientation(character->getOrientation());
    Scene* scene=SceneManager::instance()->getScene("init");

    scene->addBulletToBox(bullet);
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

