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

    Orientation::ORIENTATION getMoveOrientation() const;
    void setMoveOrientation(const Orientation::ORIENTATION &value);

protected:
    void initSkill();
    void initParamater();
    void runSkill();
    int HP;
    int MP;
    int currentHP;
    int currentMP;
    float speed;

    Orientation::ORIENTATION orientation;
    Orientation::ORIENTATION moveOrientation;
    QList<Skill*> skillList;

};

#endif // CHARACTER_H
