#ifndef ARRIVECONDITION_H
#define ARRIVECONDITION_H

#include"condition.h"
#include"character.h"
#include"decoration.h"

class ArriveCondition:public Condition
{
public:
    ArriveCondition();
    virtual bool judge();
    virtual void config(QXmlStreamReader *reader);
    void save(QXmlStreamWriter *writer);
protected:
    Decoration* position;
    QString characterName;
};

#endif // ARRIVECONDITION_H
