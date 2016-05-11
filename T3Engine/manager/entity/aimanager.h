#ifndef AIMANAGER_H
#define AIMANAGER_H

#include"ainode.h"
#include"stable.h"

class AIManager:public Singleton<AIManager>
{
public:
    AIManager();
    void init();
    void destory();
    AINode *getAI(const QString& AIName);
protected:
    QMap<QString,AINode*> AIBox;
};

#endif // AIMANAGER_H
