#include "timeupcondition.h"

TimeUpCondition::TimeUpCondition()
{

}

bool TimeUpCondition::judge()
{
    return QTime::currentTime()>time;
}

void TimeUpCondition::setTime(int ms)
{
    time=QTime::currentTime();
    time=time.addMSecs(ms);
}

