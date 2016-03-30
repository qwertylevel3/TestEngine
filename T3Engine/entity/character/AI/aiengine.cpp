#include "aiengine.h"
#include"ainode.h"
#include"action.h"
#include"selector.h"

AIEngine::AIEngine()
{

}

void AIEngine::run(Character *character)
{
    AINode* curNode=character->getAi();

    while(!curNode->isLeaf())
    {
        Selector* curSelector=static_cast<Selector*>(curNode);
        if(curSelector->judge(character))
        {
            curNode=curSelector->getTChild();
        }
        else
        {
            curNode=curSelector->getFChild();
        }
    }
    static_cast<Action*>(curNode)->run(character);
}

