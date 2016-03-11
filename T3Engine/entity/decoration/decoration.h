#ifndef DECORATION_H
#define DECORATION_H

#include"entity.h"

class Decoration:public Entity
{
public:
    Decoration(const QString& spriteName);
    Decoration* clone();

    int getHP() const;
    void setHP(int value);
protected:
    int HP;
};

#endif // DECORATION_H
