#include "changesceneevent.h"

ChangeSceneEvent::ChangeSceneEvent()
{

}

void ChangeSceneEvent::config(QXmlStreamReader *reader)
{
    reader->readNextStartElement();//<config>

    reader->readNextStartElement();//<sceneName>
    sceneName=reader->readElementText();

    reader->readNextStartElement();//<x>
    x=reader->readElementText().toFloat();

    reader->readNextStartElement();//<y>
    y=reader->readElementText().toFloat();


    reader->readNextStartElement();//</config>
}

void ChangeSceneEvent::run()
{

}

void ChangeSceneEvent::save(QXmlStreamWriter *writer)
{
    writer->writeStartElement("Event");

    writer->writeTextElement("EventType","ChangeScene");
    writer->writeStartElement("Config");

    writer->writeTextElement("sceneName",sceneName);

    writer->writeTextElement("x",QString::number(x));

    writer->writeTextElement("y",QString::number(y));

    writer->writeEndElement();

    writer->writeEndElement();
}
