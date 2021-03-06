#include "trigger.h"

Trigger::Trigger()
{

}

Trigger::~Trigger()
{
    delete condition;
    delete event;
}

bool Trigger::judge()
{
    return condition->judge();
}

void Trigger::run()
{
    event->run();
}
void Trigger::setCondition(Condition *value)
{
    condition = value;
}
void Trigger::setEvent(Event *value)
{
    event = value;
}

void Trigger::save(QXmlStreamWriter *writer)
{
    writer->writeStartElement("Trigger");

    condition->save(writer);
    event->save(writer);

    writer->writeEndElement();
}
