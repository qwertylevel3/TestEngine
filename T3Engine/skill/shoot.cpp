#include "shoot.h"
#include"bulletmanager.h"
#include"scenemanager.h"


Shoot::Shoot(Character *e)
    :Skill(e)
{

}

void Shoot::start(InputModule::Command c)
{
    Skill::start(c);

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
    Skill::end(c);
}

void Shoot::run()
{

}

