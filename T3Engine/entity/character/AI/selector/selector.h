#ifndef SELECTOR_H
#define SELECTOR_H

#include"ainode.h"

class Selector:public AINode
{
public:
    Selector();
    virtual bool judge()=0;

    AINode *getLeftChild() const;
    void setLeftChild(AINode *value);

    AINode *getRightChild() const;
    void setRightChild(AINode *value);

protected:
    AINode* leftChild;
    AINode* rightChild;
};

#endif // SELECTOR_H
