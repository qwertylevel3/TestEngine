#include "ainode.h"

AINode::AINode()
{
}

AINode::~AINode()
{

}

bool AINode::isLeaf()
{
    return leaf;
}
bool AINode::getLeaf() const
{
    return leaf;
}

void AINode::setLeaf(bool value)
{
    leaf = value;
}


