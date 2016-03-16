#ifndef EVENT_H
#define EVENT_H

#include"stable.h"

class Scene;

class Event
{
public:
    Event();
    virtual ~Event();
    static Event* getEvent(const QString& eventType);
    virtual void run()=0;
    virtual void config(QXmlStreamReader* reader)=0;
    Scene *getScene() const;
    void setScene(Scene *value);

    virtual void save(QXmlStreamWriter* writer)=0;
protected:
    Scene* scene;
};

#endif // EVENT_H
