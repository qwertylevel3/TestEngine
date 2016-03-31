#include "character.h"
#include"inputmodule.h"
#include"move.h"
#include"shoot.h"
#include"focus.h"
#include"clockmanager.h"
#include"picturemanager.h"
#include"wander.h"
#include"aiengine.h"
#include"aimanager.h"


Character::Character(const QString &spriteName)
    :Entity(spriteName)
{

}

Character::~Character()
{
    ClockManager::instance()->deleteClock(heartId);
}

void Character::draw()
{
    Entity::draw();
    drawField(alarmField);
    //TODO...draw 2 rect
}

void Character::update()
{

    Entity::update();

    runSkill();
    if(this->type!=PLAYER)
    {
        runAI();
    }
    //qDebug()<<ClockManager::instance()->getTick(heartId)<<endl;
}

Character *Character::clone()
{
    Character* newCharacter=new Character(this->spriteName);

    newCharacter->init();

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
    currentCommand=c;
    if(c==InputModule::up)
    {
        startUp();
    }
    if(c==InputModule::down)
    {
        startDown();
    }
    if(c==InputModule::left)
    {
        startLeft();
    }
    if(c==InputModule::right)
    {
        startRight();
    }
    if(c==InputModule::A_C)
    {
        startA_C();
    }
    if(c==InputModule::B_C)
    {
        startB_C();
    }
}


void Character::endCommand(InputModule::Command c)
{
    currentCommand=c;
    if(c==InputModule::up)
    {
        endUp();
    }
    if(c==InputModule::down)
    {
        endDown();
    }
    if(c==InputModule::left)
    {
        endLeft();
    }
    if(c==InputModule::right)
    {
        endRight();
    }
    if(c==InputModule::A_C)
    {
        endA_C();
    }
    if(c==InputModule::B_C)
    {
        endB_C();
    }
}

int Character::getHP() const
{
    return HP;
}

void Character::setHP(int value)
{
    HP = value;
}

int Character::getMP() const
{
    return MP;
}

void Character::setMP(int value)
{
    MP = value;
}

int Character::getCurrentHP() const
{
    return currentHP;
}

void Character::setCurrentHP(int value)
{
    currentHP = value;
}

int Character::getCurrentMP() const
{
    return currentMP;
}

void Character::setCurrentMP(int value)
{
    currentMP = value;
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

void Character::setMoveOrientation(const Orientation::ORIENTATION &value)
{
    orientation = value;
    switch(orientation)
    {
    case Orientation::up:
    case Orientation::upLeft:
    case Orientation::upRight:
        setCurrentAction("moveUp");
        break;
    case Orientation::down:
    case Orientation::downLeft:
    case Orientation::downRight:
        setCurrentAction("moveDown");
        break;
    case Orientation::left:
        setCurrentAction("moveLeft");
        break;
    case Orientation::right:
        setCurrentAction("moveRight");
        break;
    default:
        break;
    }
}

void Character::setReadyOrientation(const Orientation::ORIENTATION &value)
{
    orientation = value;
    switch(orientation)
    {
    case Orientation::up:
    case Orientation::upLeft:
    case Orientation::upRight:
        setCurrentAction("readyUp");
        break;
    case Orientation::down:
    case Orientation::downLeft:
    case Orientation::downRight:
        setCurrentAction("readyDown");
        break;
    case Orientation::left:
        setCurrentAction("readyLeft");
        break;
    case Orientation::right:
        setCurrentAction("readyRight");
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

    Focus* focus=new Focus(this);
    skillBox.insert("focus",focus);
}

void Character::initAI()
{
    if(this->type!=PLAYER)
    {
        ai=AIManager::instance()->getAI("SimpleAI");
    }

}

void Character::initClock()
{
    heartId=ClockManager::instance()->genClock();
    ClockManager::instance()->setClockInterval(heartId,heartRate);
}

void Character::init()
{
    initParamater();
    initSkill();
    initClock();
    initAI();
}

void Character::initParamater()
{
    HP=0;
    MP=0;
    currentHP=0;
    currentMP=0;
    speed=10;
    orientation=Orientation::down;
    lastOrientation=Orientation::down;
    invincible=false;
    type=FRIEND;

    viewField.setX(500);
    viewField.setY(500);

    alarmField.setX(100);
    alarmField.setY(100);

    focusIndex=-1;
    setCollisionAble(true);
    setDestructible(true);
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

void Character::runAI()
{
    AIEngine::instance()->run(this);
}

//start command.......
void Character::startUp()
{
    skillBox["moveUp"]->start();
    setMoveOrientation(Orientation::up);
    if(skillBox["moveLeft"]->isRunning())
    {
        setMoveOrientation(Orientation::upLeft);
    }
    else if(skillBox["moveRight"]->isRunning())
    {
        setMoveOrientation(Orientation::upRight);
    }
}

void Character::startDown()
{
    skillBox["moveDown"]->start();
    setMoveOrientation(Orientation::down);
    if(skillBox["moveLeft"]->isRunning())
    {
        setMoveOrientation(Orientation::downLeft);
    }
    if(skillBox["moveRight"]->isRunning())
    {
        setMoveOrientation(Orientation::downRight);
    }
}

void Character::startLeft()
{
    skillBox["moveLeft"]->start();
    setMoveOrientation(Orientation::left);
    if(skillBox["moveUp"]->isRunning())
    {
        setMoveOrientation(Orientation::upLeft);
    }
    else if(skillBox["moveDown"]->isRunning())
    {
        setMoveOrientation(Orientation::downLeft);
    }
}

void Character::startRight()
{
    skillBox["moveRight"]->start();
    setMoveOrientation(Orientation::right);
    if(skillBox["moveUp"]->isRunning())
    {
        setMoveOrientation(Orientation::upRight);
    }
    if(skillBox["moveDown"]->isRunning())
    {
        setMoveOrientation(Orientation::downRight);
    }
}

void Character::startA_C()
{
    skillBox["shoot"]->start();
}

void Character::startB_C()
{
    skillBox["focus"]->start();
}

//end command.......
void Character::endUp()
{
    skillBox["moveUp"]->end();
    if(skillBox["moveLeft"]->isRunning())
    {
        setMoveOrientation(Orientation::left);
    }
    else if(skillBox["moveRight"]->isRunning())
    {
        setMoveOrientation(Orientation::right);
    }
    else
    {
        setReadyOrientation(Orientation::up);
    }
}

void Character::endDown()
{
    skillBox["moveDown"]->end();
    if(skillBox["moveLeft"]->isRunning())
    {
        setMoveOrientation(Orientation::left);
    }
    else if(skillBox["moveDown"]->isRunning())
    {
        setMoveOrientation(Orientation::right);
    }
    else
    {
        setReadyOrientation(Orientation::down);
    }
}

void Character::endLeft()
{
    skillBox["moveLeft"]->end();
    if(skillBox["moveUp"]->isRunning())
    {
        setMoveOrientation(Orientation::up);

    }
    else if(skillBox["moveDown"]->isRunning())
    {
        setMoveOrientation(Orientation::down);
    }
    else
    {
        setReadyOrientation(Orientation::left);
    }
}

void Character::endRight()
{
    skillBox["moveRight"]->end();
    if(skillBox["moveUp"]->isRunning())
    {
        setMoveOrientation(Orientation::up);
    }
    else if(skillBox["moveDown"]->isRunning())
    {
        setMoveOrientation(Orientation::down);
    }
    else
    {
        setReadyOrientation(Orientation::right);
    }
}

void Character::endA_C()
{
    skillBox["shoot"]->end();
}

void Character::endB_C()
{
    skillBox["focus"]->end();
}

void Character::drawField(QVector2D r)
{

    Picture* rectPoint=PictureManager::instance()->getPicture("\\resource\\rect.png");

    rectPoint->setAlpha(0.5);

    rectPoint->setWidth(float(r.x()));
    rectPoint->setHeight(float(r.y()));


    rectPoint->setCoordinate(this->getX(),
                             this->getY(),
                             -1);

    //rotate...

    rectPoint->rotate(this->getRotateAngle(),
                      this->getRotateX(),
                      this->getRotateY(),
                      this->getRotateZ());
    rectPoint->draw();
}
InputModule::Command Character::getCurrentCommand() const
{
    return currentCommand;
}

void Character::setCurrentCommand(const InputModule::Command &value)
{
    currentCommand = value;
}

QVector2D Character::getAlarmField() const
{
    return alarmField;
}

void Character::setAlarmField(const QVector2D &value)
{
    alarmField = value;
}

QVector2D Character::getViewField() const
{
    return viewField;
}

void Character::setViewField(const QVector2D &value)
{
    viewField = value;
}

AINode *Character::getAi() const
{
    return ai;
}

void Character::setAi(AINode *value)
{
    ai = value;
}



bool Character::getInvincible() const
{
    return invincible;
}

void Character::setInvincible(bool value)
{
    invincible = value;
}

void Character::clearHeartAlarm()
{
    ClockManager::instance()->clear(heartId);
}

bool Character::isHeartAlarm()
{
    return ClockManager::instance()->isAlarm(this->heartId);
}

int Character::getFocusIndex() const
{
    return focusIndex;
}

void Character::setFocusIndex(int value)
{
    focusIndex = value;
}

void Character::getDamage(float damage)
{
    if(!invincible)
    {
        if(currentHP-damage<=0)
        {
            dead();
        }
        else
        {
            currentHP-=damage;
        }
    }
}

void Character::dead()
{
    this->setState(DEAD);
}

Character::TYPE Character::getType() const
{
    return type;
}

QString Character::typeToString(const Character::TYPE &value)
{
    QString type;
    switch(value)
    {
    case FRIEND:type="FRIEND";break;
    case ENEMY:type="ENEMY";break;
    case PLAYER:type="PLAYER";break;
    }
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

