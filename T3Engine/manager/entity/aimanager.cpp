#include "aimanager.h"

AIManager::AIManager()
{

}

void AIManager::init()
{

}

AINode *AIManager::getAI(const QString &AIName)
{
    return AIBox[AIName];
}

