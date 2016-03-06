#ifndef TRIGGER_H
#define TRIGGER_H

#include"condition.h"
#include"event.h"

class Trigger
{
public:
    Trigger();
    ~Trigger();
    bool judge();
    void run();
    void setCondition(Condition *value);
    void setEvent(Event *value);
protected:
    Condition* condition;
    Event* event;
};

#endif // TRIGGER_H
