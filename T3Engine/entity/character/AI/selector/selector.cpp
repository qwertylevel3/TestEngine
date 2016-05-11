#include "selector.h"

Selector::Selector()
{
    leaf=false;
}

Selector::~Selector()
{
    delete TChild;
    delete FChild;
}
AINode *Selector::getTChild() const
{
    return TChild;
}

void Selector::setTChild(AINode *value)
{
    TChild = value;
}
AINode *Selector::getFChild() const
{
    return FChild;
}

void Selector::setFChild(AINode *value)
{
    FChild = value;
}



