#include "shoot.h"
#include"T3Engine/manager/bulletmanager.h"
#include"T3Engine/manager/scenemanager.h"


Shoot::Shoot(Character *e)
    :Skill(e)
{

}

void Shoot::start(InputModule::Command c)
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

void Shoot::end(InputModule::Command c)
{

}

void Shoot::run()
{

}

