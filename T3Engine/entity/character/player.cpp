#include "player.h"

Player::Player()
    :Character("test")
{

}

void Player::init()
{
    initParamater();
    initSkill();
    initClock();
    this->type=PLAYER;
}

void Player::initParamater()
{
    HP=100;
    MP=100;
    currentHP=100;
    currentMP=100;
    speed=3;
    orientation=Orientation::down;
    lastOrientation=Orientation::down;
    invincible=false;

    viewField.setX(500);
    viewField.setY(500);

    alarmField.setX(100);
    alarmField.setY(100);

    focusIndex=-1;
    setCollisionAble(true);
    setDestructible(true);
}

