#include "aimanager.h"
#include"action/emptyaction.h"
#include"action/fleeaction.h"
#include"safeselector.h"

AIManager::AIManager()
{

}

void AIManager::init()
{
    SafeSelector* root=new SafeSelector();
    root->setTChild(new EmptyAction());
    root->setFChild(new FleeAction());

    AIBox.insert("SimpleAI",root);
}

AINode *AIManager::getAI(const QString &AIName)
{
    if(!AIBox.contains(AIName))
    {
        qDebug()<<"error ainame:"<<AIName<<endl;
    }
    return AIBox[AIName];
}

