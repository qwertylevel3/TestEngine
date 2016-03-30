#ifndef AINODE_H
#define AINODE_H

//TODO:behavior tree

class AINode
{
public:
    AINode();
    virtual ~AINode();
    bool isLeaf();
    bool getLeaf() const;
    void setLeaf(bool value);

protected:
    bool leaf;
};

#endif // AINODE_H
