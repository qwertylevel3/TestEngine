#include "clockmanager.h"

//clock......

Clock::Clock()
{
    interval=0;
    tick=0;
}

void Clock::update()
{
    tick++;
}

bool Clock::isAlarm()
{
    return tick>=interval?true:false;
}

void Clock::clear()
{
    tick=0;
}
void Clock::setInterval(int value)
{
    interval = value;
    clear();
}

//clockManager......

ClockManager::ClockManager()
{
    totalClockNumber=0;
}

void ClockManager::init()
{

}

void ClockManager::update()
{
    for(int i=0;i<totalClockNumber;i++)
    {
        clockBox[i].update();
    }
}

int ClockManager::genClock()
{
    Clock* c=new Clock;
    clockBox.insert(totalClockNumber++,*c);
    return totalClockNumber-1;
}

bool ClockManager::setClockInterval(int clockId, int interval)
{
    if(clockBox.contains(clockId))
    {
        clockBox[clockId].setInterval(interval);
        return true;
    }
    else
    {
        return false;
    }
}

bool ClockManager::isAlarm(int clockId)
{
    return clockBox[clockId].isAlarm();
}

void ClockManager::clear(int clockId)
{
    clockBox[clockId].clear();
}

void ClockManager::deleteClock(int clockId)
{
    clockBox.remove(clockId);
}
