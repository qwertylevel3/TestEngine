#ifndef SAFESELECTOR_H
#define SAFESELECTOR_H


#include"selector.h"

class SafeSelector:public Selector
{
public:
    SafeSelector();
    bool judge(Character *character);
};

#endif // SAFESELECTOR_H
