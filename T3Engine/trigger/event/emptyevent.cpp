#include "emptyevent.h"

EmptyEvent::EmptyEvent()
{

}

void EmptyEvent::config(QXmlStreamReader *reader)
{
    reader->readNextStartElement();//<config>

    //reader->readNextStartElement();//<dialogName>
    //this->setDialogName(reader->readElementText());

    reader->readNextStartElement();//</config>
}

void EmptyEvent::run()
{
    qDebug()<<"empty event!!"<<endl;
}

void EmptyEvent::save(QXmlStreamWriter *writer)
{
    writer->writeStartElement("Event");

    writer->writeTextElement("EventType","Empty");
    writer->writeStartElement("Config");

    writer->writeEndElement();

    writer->writeEndElement();
}


