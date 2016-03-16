#ifndef TIMEUPCONDITION_H
#define TIMEUPCONDITION_H

#include"condition.h"
#include"QTime"

class TimeUpCondition:public Condition
{
public:
    TimeUpCondition();
    virtual bool judge();
    virtual void config(QXmlStreamReader *reader);
    void setTime(int ms);
    void save(QXmlStreamWriter *writer);
protected:
    QTime time;
    int timeMs;
};

#endif // TIMEUPCONDITION_H
