#ifndef EMPTYEVENT_H
#define EMPTYEVENT_H

#include"event.h"

class EmptyEvent:public Event
{
public:
    EmptyEvent();
    virtual void config(QXmlStreamReader* reader);
    virtual void run();
    void save(QXmlStreamWriter *writer);
};

#endif // EMPTYEVENT_H
