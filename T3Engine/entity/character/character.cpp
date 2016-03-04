#include "character.h"
#include"inputmodule.h"
#include"move.h"
#include"shoot.h"
#include"clockmanager.h"


Character::Character(const QString &spriteName)
    :Entity(spriteName)
{
    initParamater();
    initSkill();
    heartId=ClockManager::instance()->genClock();
    ClockManager::instance()->setClockInterval(heartId,heartRate);
}

Character::~Character()
{
    ClockManager::instance()->deleteClock(heartId);
}

void Character::update()
{
    Entity::update();
    runSkill();
    //qDebug()<<ClockManager::instance()->getTick(heartId)<<endl;
}

Character *Character::clone()
{
    Character* newCharacter=new Character(this->spriteName);
    newCharacter->setName(this->name);
    newCharacter->setHP(this->HP);
    newCharacter->setMP(this->MP);
    newCharacter->setCurrentHP(this->HP);
    newCharacter->setCurrentMP(this->MP);
    newCharacter->setSpeed(this->speed);
    newCharacter->setHeartRate(this->heartRate);

    return newCharacter;
}

void Character::startCommand(InputModule::Command c)
{
    if(c==InputModule::up)
    {
        startUp(c);
    }
    if(c==InputModule::down)
    {
        startDown(c);
    }
    if(c==InputModule::left)
    {
        startLeft(c);
    }
    if(c==InputModule::right)
    {
        startRight(c);
    }
    if(c==InputModule::A_C)
    {
        startA_C(c);
    }
}

void Character::endCommand(InputModule::Command c)
{
    if(c==InputModule::up)
    {
        endUp(c);
    }
    if(c==InputModule::down)
    {
        endDown(c);
    }
    if(c==InputModule::left)
    {
        endLeft(c);
    }
    if(c==InputModule::right)
    {
        endRight(c);
    }
    if(c==InputModule::A_C)
    {
        endA_C(c);
    }
}
float Character::getSpeed() const
{
    return speed;
}

void Character::setSpeed(float value)
{
    speed = value;
}
Orientation::ORIENTATION Character::getOrientation() const
{
    return orientation;
}

void Character::setOrientation(const Orientation::ORIENTATION &value)
{
    orientation = value;
    switch(orientation)
    {
    case Orientation::up:
    case Orientation::upLeft:
    case Orientation::upRight:
        setCurrentAction(3);
        break;
    case Orientation::down:
    case Orientation::downLeft:
    case Orientation::downRight:
        setCurrentAction(0);
        break;
    case Orientation::left:
        setCurrentAction(1);
        break;
    case Orientation::right:
        setCurrentAction(2);
        break;
    default:
        break;
    }
}

void Character::initSkill()
{
    Move* moveUp=new Move(this);
    moveUp->setOrientation(Orientation::up);
    Move* moveDown=new Move(this);
    moveDown->setOrientation(Orientation::down);
    Move* moveLeft=new Move(this);
    moveLeft->setOrientation(Orientation::left);
    Move* moveRight=new Move(this);
    moveRight->setOrientation(Orientation::right);

    skillBox.insert("moveUp",moveUp);
    skillBox.insert("moveDown",moveDown);
    skillBox.insert("moveLeft",moveLeft);
    skillBox.insert("moveRight",moveRight);

    Shoot* shoot=new Shoot(this);
    shoot->setInterval(15);
    skillBox.insert("shoot",shoot);
}

void Character::initParamater()
{
    HP=0;
    MP=0;
    currentHP=0;
    currentMP=0;
    speed=0.01;
    orientation=Orientation::down;
    lastOrientation=Orientation::down;
}

void Character::runSkill()
{
    QMap<QString, Skill*>::const_iterator i = skillBox.constBegin();
    while (i != skillBox.constEnd()) {
        if(i.value()->isRunning())
        {
            i.value()->run();
        }
        ++i;
    }
}

//start command.......

void Character::startUp(InputModule::Command c)
{
    skillBox["moveUp"]->start(c);
    setOrientation(Orientation::up);
    if(skillBox["moveLeft"]->isRunning())
    {
        setOrientation(Orientation::upLeft);
    }
    else if(skillBox["moveRight"]->isRunning())
    {
        setOrientation(Orientation::upRight);
    }
}

void Character::startDown(InputModule::Command c)
{
    skillBox["moveDown"]->start(c);
    setOrientation(Orientation::down);
    if(skillBox["moveLeft"]->isRunning())
    {
        setOrientation(Orientation::downLeft);
    }
    if(skillBox["moveRight"]->isRunning())
    {
        setOrientation(Orientation::downRight);
    }
}

void Character::startLeft(InputModule::Command c)
{
    skillBox["moveLeft"]->start(c);
    setOrientation(Orientation::left);
    if(skillBox["moveUp"]->isRunning())
    {
        setOrientation(Orientation::upLeft);
    }
    else if(skillBox["moveDown"]->isRunning())
    {
        setOrientation(Orientation::downLeft);
    }
}

void Character::startRight(InputModule::Command c)
{
    skillBox["moveRight"]->start(c);
    setOrientation(Orientation::right);
    if(skillBox["moveUp"]->isRunning())
    {
        setOrientation(Orientation::upRight);
    }
    if(skillBox["moveDown"]->isRunning())
    {
        setOrientation(Orientation::downRight);
    }
}

void Character::startA_C(InputModule::Command c)
{
    skillBox["shoot"]->start(c);
}

//end command.......
void Character::endUp(InputModule::Command c)
{
    skillBox["moveUp"]->end(c);
    if(skillBox["moveLeft"]->isRunning())
    {
        setOrientation(Orientation::left);
    }
    else if(skillBox["moveRight"]->isRunning())
    {
        setOrientation(Orientation::right);
    }
}

void Character::endDown(InputModule::Command c)
{
    skillBox["moveDown"]->end(c);
    if(skillBox["moveLeft"]->isRunning())
    {
        setOrientation(Orientation::left);
    }
    else if(skillBox["moveDown"]->isRunning())
    {
        setOrientation(Orientation::right);
    }
}

void Character::endLeft(InputModule::Command c)
{
    skillBox["moveLeft"]->end(c);
    if(skillBox["moveUp"]->isRunning())
    {
        setOrientation(Orientation::up);

    }
    if(skillBox["moveDown"]->isRunning())
    {
        setOrientation(Orientation::down);
    }
}

void Character::endRight(InputModule::Command c)
{
    skillBox["moveRight"]->end(c);
    if(skillBox["moveUp"]->isRunning())
    {
        setOrientation(Orientation::up);
    }
    if(skillBox["moveDown"]->isRunning())
    {
        setOrientation(Orientation::down);
    }
}

void Character::endA_C(InputModule::Command c)
{
    skillBox["shoot"]->end(c);
}
Character::TYPE Character::getType() const
{
    return type;
}

void Character::setType(const TYPE &value)
{
    type = value;
}

void Character::setType(const QString &value)
{
    if(value=="PLAYER")
    {
        type=PLAYER;
    }
    else if(value=="ENEMY")
    {
        type=ENEMY;
    }
    else if(value=="FRIEND")
    {
        type=FRIEND;
    }
    else
    {
        qDebug()<<value<<" unknow character type"<<endl;
    }
}

int Character::getHeartRate() const
{
    return heartRate;
}

void Character::setHeartRate(int value)
{
    heartRate = value;
}

