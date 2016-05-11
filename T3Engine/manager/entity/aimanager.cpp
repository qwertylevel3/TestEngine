#include "aimanager.h"
#include"emptyaction.h"
#include"fleeaction.h"
#include"safeselector.h"
#include"runningselector.h"
#include"stopmovingaction.h"

AIManager::AIManager()
{

}

void AIManager::init()
{
    SafeSelector* root=new SafeSelector();

    RunningSelector* runningSelector_1=new RunningSelector();
    RunningSelector* runningSelector_2=new RunningSelector();

    root->setTChild(runningSelector_1);
    root->setFChild(runningSelector_2);

    runningSelector_1->setTChild(new StopMovingAction);
    runningSelector_1->setFChild(new EmptyAction);

    runningSelector_2->setTChild(new EmptyAction);
    runningSelector_2->setFChild(new FleeAction);


    AIBox.insert("SimpleAI",root);
}

void AIManager::destory()
{
    QMap<QString,AINode*>::iterator i=AIBox.begin();
    while(i!=AIBox.end())
    {
        delete i.value();
        i++;
    }
}

AINode *AIManager::getAI(const QString &AIName)
{
    if(!AIBox.contains(AIName))
    {
        qDebug()<<"error ainame:"<<AIName<<endl;
    }
    return AIBox[AIName];
}

