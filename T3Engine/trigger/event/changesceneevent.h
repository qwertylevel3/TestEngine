#ifndef CHANGESCENEEVENT_H
#define CHANGESCENEEVENT_H

#include"event.h"

class ChangeSceneEvent:public Event
{
public:
    ChangeSceneEvent();
    virtual void config(QXmlStreamReader* reader);
    virtual void run();
    void save(QXmlStreamWriter *writer);


protected:
    QString sceneName;
    float x;
    float y;
};

#endif // CHANGESCENEEVENT_H
