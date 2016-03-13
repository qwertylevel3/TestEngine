#include "event.h"
#include"dialogueevent.h"

Event::Event()
{

}

Event::~Event()
{

}

Event *Event::getEvent(const QString &eventType)
{
    if(eventType=="dialog")
    {
        DialogueEvent* event=new DialogueEvent();
        return event;
    }
    else
    {
        qDebug()<<"unknow event type"<<eventType<<endl;
    }
}
Scene *Event::getScene() const
{
    return scene;
}

void Event::setScene(Scene *value)
{
    scene = value;
}


