#ifndef TIMEUPCONDITION_H
#define TIMEUPCONDITION_H

#include"condition.h"
#include"QTime"

class TimeUpCondition:public Condition
{
public:
    TimeUpCondition();
    virtual bool judge();
    void setTime(int ms);
protected:
    QTime time;
};

#endif // TIMEUPCONDITION_H
