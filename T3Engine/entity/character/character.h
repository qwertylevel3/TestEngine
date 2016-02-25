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
    Character(const QString& spriteName);

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
    void setOrientation(const Orientation::ORIENTATION &value);


protected:
    void initSkill();
    void initParamater();
    void runSkill();

    void startUp(InputModule::Command c);
    void startDown(InputModule::Command c);
    void startLeft(InputModule::Command c);
    void startRight(InputModule::Command c);
    void startA_C(InputModule::Command c);

    void endUp(InputModule::Command c);
    void endDown(InputModule::Command c);
    void endLeft(InputModule::Command c);
    void endRight(InputModule::Command c);
    void endA_C(InputModule::Command c);

    int HP;
    int MP;
    int currentHP;
    int currentMP;
    float speed;

    Orientation::ORIENTATION orientation;
    QList<Skill*> skillList;
};

#endif // CHARACTER_H
