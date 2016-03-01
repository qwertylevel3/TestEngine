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

    skillList.push_back(moveUp);
    skillList.push_back(moveDown);
    skillList.push_back(moveLeft);
    skillList.push_back(moveRight);

    Shoot* shoot=new Shoot(this);
    shoot->setInterval(15);
    skillList.push_back(shoot);
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
    for(int i=0;i<skillList.size();i++)
    {
        if(skillList[i]->isRunning())
        {
            skillList[i]->run();
        }
    }
}

//start command.......

void Character::startUp(InputModule::Command c)
{
    skillList[0]->start(c);
    setOrientation(Orientation::up);
    if(skillList[2]->isRunning())
    {
        setOrientation(Orientation::upLeft);
    }
    else if(skillList[3]->isRunning())
    {
        setOrientation(Orientation::upRight);
    }
}

void Character::startDown(InputModule::Command c)
{
    skillList[1]->start(c);
    setOrientation(Orientation::down);
    if(skillList[2]->isRunning())
    {
        setOrientation(Orientation::downLeft);
    }
    if(skillList[3]->isRunning())
    {
        setOrientation(Orientation::downRight);
    }
}

void Character::startLeft(InputModule::Command c)
{
    skillList[2]->start(c);
    setOrientation(Orientation::left);
    if(skillList[0]->isRunning())
    {
        setOrientation(Orientation::upLeft);
    }
    else if(skillList[1]->isRunning())
    {
        setOrientation(Orientation::downLeft);
    }
}

void Character::startRight(InputModule::Command c)
{
    skillList[3]->start(c);
    setOrientation(Orientation::right);
    if(skillList[0]->isRunning())
    {
        setOrientation(Orientation::upRight);
    }
    if(skillList[1]->isRunning())
    {
        setOrientation(Orientation::downRight);
    }
}

void Character::startA_C(InputModule::Command c)
{
    skillList[4]->start(c);
}

//end command.......
void Character::endUp(InputModule::Command c)
{
    skillList[0]->end(c);
    if(skillList[2]->isRunning())
    {
        setOrientation(Orientation::left);
    }
    else if(skillList[3]->isRunning())
    {
        setOrientation(Orientation::right);
    }
}

void Character::endDown(InputModule::Command c)
{
    skillList[1]->end(c);
    if(skillList[2]->isRunning())
    {
        setOrientation(Orientation::left);
    }
    else if(skillList[3]->isRunning())
    {
        setOrientation(Orientation::right);
    }
}

void Character::endLeft(InputModule::Command c)
{
    skillList[2]->end(c);
    if(skillList[0]->isRunning())
    {
        setOrientation(Orientation::up);

    }
    else if(skillList[1]->isRunning())
    {
        setOrientation(Orientation::down);
    }
}

void Character::endRight(InputModule::Command c)
{
    skillList[3]->end(c);
    if(skillList[0]->isRunning())
    {
        setOrientation(Orientation::up);
    }
    else if(skillList[1]->isRunning())
    {
        setOrientation(Orientation::down);
    }
}

void Character::endA_C(InputModule::Command c)
{
    skillList[4]->end(c);
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

