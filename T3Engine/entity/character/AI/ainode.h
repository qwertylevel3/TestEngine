#ifndef AINODE_H
#define AINODE_H

//TODO:behavior tree

class AINode
{
public:
    AINode();
    virtual void update()=0;
    virtual void judge()=0;
protected:
};

#endif // AINODE_H
