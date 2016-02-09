#ifndef CHARACTER_H
#define CHARACTER_H

//#include"T3Engine/sprite/sprite.h"
//#include"T3Engine/manager/spritemanager.h"
#include"T3Engine/entity/entity.h"

class Character:public Entity
{
public:
    Character(const QString& spriteName);
    Character* clone();

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
protected:
    int HP;
    int MP;
    int currentHP;
    int currentMP;
};

#endif // CHARACTER_H
