#include "shootlaser.h"
#include"bulletmanager.h"
#include"scene.h"
#include"character.h"

ShootLaser::ShootLaser(Character* e)
    :Skill(e)
{
    laserName="laser";
    laser=NULL;
}

void ShootLaser::start()
{
    Skill::start();
    if(!laser)
    {
        laser=BulletManager::instance()->getBullet(laserName);
        laser->init(character);
        laser->setRemainTime(99999);
        //TODO change scene , refresh laser
        character->getScene()->addBulletToBox(laser);
    }
    //laser->setState(Entity::ALIVE);

}

void ShootLaser::run()
{
    laser->init(character);

    int focusCharacterIndex=character->getFocusIndex();
    Character* focusCharacter=character->getScene()->getCharacterList()[focusCharacterIndex];

    if(focusCharacter->getState()==Character::DEAD)
    {
        return;
    }

    laser->setState(Entity::ALIVE);


    float x1=character->getX();
    float y1=character->getY();

    float x2=laser->getTarget()->getX();
    float y2=laser->getTarget()->getY();

    float dx=x2-x1;
    float dy=y2-y1;

    laser->setX(x1+dx/2);
    laser->setY(y1+dy/2);

    laser->setWidth(sqrt(dx*dx+dy*dy));
}

void ShootLaser::end()
{
    Skill::end();
    laser->setState(Entity::DEAD);
}

QString ShootLaser::getLaserName() const
{
    return laserName;
}

void ShootLaser::setLaserName(const QString &value)
{
    laserName = value;
}

