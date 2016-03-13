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
}

