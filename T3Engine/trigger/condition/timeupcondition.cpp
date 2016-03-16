#include "timeupcondition.h"

TimeUpCondition::TimeUpCondition()
{

}

bool TimeUpCondition::judge()
{
    return QTime::currentTime()>time;
}

void TimeUpCondition::config(QXmlStreamReader *reader)
{
    reader->readNextStartElement();//<config>

    reader->readNextStartElement();//<time>
    this->setTime(reader->readElementText().toInt());

    reader->readNextStartElement();//</config>
}

void TimeUpCondition::setTime(int ms)
{
    time=QTime::currentTime();
    time=time.addMSecs(ms);
    timeMs=ms;
}

void TimeUpCondition::save(QXmlStreamWriter *writer)
{
    writer->writeStartElement("Condition");

    writer->writeStartElement("ConditionType","TimeUp");
    writer->writeStartElement("Config");

    writer->writeTextElement("Time",QString::number(timeMs));

    writer->writeEndElement();

    writer->writeEndElement();
}

