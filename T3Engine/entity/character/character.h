#ifndef CHARACTER_H
#define CHARACTER_H

//#include"T3Engine/sprite/sprite.h"
//#include"T3Engine/manager/spritemanager.h"
#include"skill.h"
#include"entity.h"
#include"orientation.h"

class Character:public Entity
{
public:
    enum TYPE{PLAYER,ENEMY,FRIEND};

    Character(const QString& spriteName);
    virtual ~Character();

    void draw();
    void update();
    Character* clone();

    void startCommand(InputModule::Command c);
    void endCommand(InputModule::Command c);

    int getHP() const
    {
        return HP;
    }
    void setHP(int value)
    {
        HP = value;
    }

    int getMP() const
    {
        return MP;
    }
    void setMP(int value)
    {
        MP = value;
    }

    int getCurrentHP() const
    {
        return currentHP;
    }
    void setCurrentHP(int value)
    {
        currentHP = value;
    }

    int getCurrentMP() const
    {
        return currentMP;
    }
    void setCurrentMP(int value)
    {
        currentMP = value;
    }

    float getSpeed() const;
    void setSpeed(float value);

    Orientation::ORIENTATION getOrientation() const;
    void setMoveOrientation(const Orientation::ORIENTATION &value);
    void setReadyOrientation(const Orientation::ORIENTATION &value);

    int getHeartRate() const;
    void setHeartRate(int value);

    TYPE getType() const;
    QString typeToString(const TYPE &value);
    void setType(const TYPE &value);
    void setType(const QString& value);

    int getFocusIndex() const;
    void setFocusIndex(int value);

    void getDamage(float damage);
    void dead();
    bool getInvincible() const;
    void setInvincible(bool value);

protected:
    void initSkill();
    void initParamater();
    void runSkill();

    void startUp();
    void startDown();
    void startLeft();
    void startRight();
    void startA_C();
    void startB_C();

    void endUp();
    void endDown();
    void endLeft();
    void endRight();
    void endA_C();
    void endB_C();

    int HP;
    int MP;
    int currentHP;
    int currentMP;
    float speed;
    bool invincible;

    Orientation::ORIENTATION orientation;
    Orientation::ORIENTATION lastOrientation;
    QMap<QString,Skill*> skillBox;
    int heartId;
    int heartRate;

    TYPE type;

    int focusIndex;

    void drawField(QVector2D r);
    QVector2D viewField;
    QVector2D alarmField;
};

#endif // CHARACTER_H
