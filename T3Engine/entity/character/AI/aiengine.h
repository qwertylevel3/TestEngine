#ifndef AIENGINE_H
#define AIENGINE_H

#include"stable.h"
#include"character.h"

class AIEngine:public Singleton<AIEngine>
{
public:
    AIEngine();
    void run(Character* character);
protected:
};

#endif // AIENGINE_H
