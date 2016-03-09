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
int Clock::getTick() const
{
    return tick;
}

void Clock::setTick(int value)
{
    tick = value;
}


//clockManager......

ClockManager::ClockManager()
{
    totalClockNumber=0;
    MAXClock=999;
}

void ClockManager::init()
{

}

void ClockManager::update()
{
    int count=0;
    for(int i=0;i<MAXClock;i++)
    {
        if(clockBox.contains(i))
        {
            clockBox[i].update();
            if(++count==totalClockNumber)
            {
                return;
            }
        }
    }
}

int ClockManager::genClock()
{
    Clock* c=new Clock;
    int index=0;
    for(;index<MAXClock;index++)
    {
        if(!clockBox.contains(index))
        {
            clockBox.insert(index,*c);
            totalClockNumber++;
            break;
        }
    }
    if(index>=MAXClock)
    {
        qDebug()<<"clock out of range"<<endl;
        delete c;
        return -1;
    }
    return index;
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
    totalClockNumber--;
}

int ClockManager::getTick(int clockId)
{
    return clockBox[clockId].getTick();
}
