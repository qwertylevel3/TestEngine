#ifndef SELECTOR_H
#define SELECTOR_H

#include"ainode.h"
#include"character.h"

class Selector:public AINode
{
public:
    Selector();
    ~Selector();
    virtual bool judge(Character* character)=0;

    AINode *getTChild() const;
    void setTChild(AINode *value);

    AINode *getFChild() const;
    void setFChild(AINode *value);

protected:
    AINode* TChild;
    AINode* FChild;
};

#endif // SELECTOR_H
