#ifndef CHARACTER_H
#define CHARACTER_H

//#include"T3Engine/sprite/sprite.h"
//#include"T3Engine/manager/spritemanager.h"
#include"T3Engine/skill/skill.h"
#include"T3Engine/entity/entity.h"

class Character:public Entity
{
public:
    enum ORIENTATION{empty,up,down,left,right,
                     upLeft,upRight,downLeft,downRight};

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

    ORIENTATION getOrientation() const;
    void setOrientation(const ORIENTATION &value);

protected:
    int HP;
    int MP;
    int currentHP;
    int currentMP;
    float speed;

    ORIENTATION orientation;
    QList<Skill*> skillList;
};

#endif // CHARACTER_H
