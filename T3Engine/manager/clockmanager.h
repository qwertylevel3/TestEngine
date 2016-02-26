#ifndef CLOCKMANAGER_H
#define CLOCKMANAGER_H

#include"stable.h"

class Clock
{
public:
    Clock();

    void update();
    bool isAlarm();
    void clear();

    void setInterval(int value);
    int getTick() const;
    void setTick(int value);

protected:
    int interval;
    int tick;
};

class ClockManager:public Singleton<ClockManager>
{
public:
    ClockManager();

    void init();

    void update();
    int genClock();
    bool setClockInterval(int clockId,int interval);
    bool isAlarm(int clockId);
    void clear(int clockId);
    void deleteClock(int clockId);

    int getTick(int clockId);
protected:
    QMap<int,Clock> clockBox;
    int totalClockNumber;
    int MAXClock;
};

#endif // CLOCKMANAGER_H
