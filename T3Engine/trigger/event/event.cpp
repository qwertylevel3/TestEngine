#include "event.h"
#include"dialogueevent.h"
#include"emptyevent.h"

Event::Event()
{

}

Event::~Event()
{

}

Event *Event::getEvent(const QString &eventType)
{
    if(eventType=="Dialog")
    {
        DialogueEvent* event=new DialogueEvent();
        return event;
    }
    if(eventType=="Empty")
    {
        EmptyEvent* event=new EmptyEvent();
        return event;
    }
    else
    {
        qDebug()<<"unknow event type"<<eventType<<endl;
        exit(0);
    }
    exit(0);
}
Scene *Event::getScene() const
{
    return scene;
}

void Event::setScene(Scene *value)
{
    scene = value;
}


