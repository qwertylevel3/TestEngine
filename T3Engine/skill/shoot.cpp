#include "shoot.h"
#include"T3Engine/manager/bulletmanager.h"


Shoot::Shoot(Character *e)
    :Skill(e)
{

}

void Shoot::start(InputModule::Command c)
{
    Bullet* bullet=BulletManager::instance()->getBullet("bullet");
    bullet->setZoomX(0.2);
    bullet->setZoomY(0.2);
}

void Shoot::end(InputModule::Command c)
{

}

void Shoot::run()
{

}

