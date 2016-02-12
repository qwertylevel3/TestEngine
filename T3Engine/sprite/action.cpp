#include "action.h"

Action::Action()
{
    frameDelay=1;
    frameTotal=0;
    isRepeat=false;
    currFrame=0;
    frameClock=0;

    repeatStart=0;
    repeatOver=0;

}

Action::~Action()
{

}

Action *Action::clone()
{
    Action* newAction=new Action();
    newAction->setName(this->name);
    newAction->setCurrFrame(0);
    newAction->setFrameDelay(this->frameDelay);
    newAction->setFrameTotal(this->frameTotal);
    newAction->setRepeat(this->isRepeat);
    newAction->setRepeatStart(this->repeatStart);
    newAction->setRepeatOver(this->repeatOver);


    for(int i=0;i<frameBox.size();i++)
    {
        Frame* f=frameBox[i]->clone();
        newAction->addFrame(f);
    }

    return newAction;
}

void Action::start()
{
    currFrame=repeatStart;
}
//update,return the state:0,over;1,busy
int Action::update()
{
    if(frameClock++==frameDelay)
    {
        frameClock=0;
        if(isRepeat)
        {
            currFrame=(++currFrame>repeatOver?0:currFrame);
            return 1;
        }
        else
        {
            if(++currFrame>repeatOver)
            {
                currFrame=repeatStart;
                return 0;
            }
        }
    }
    return 1;
}

void Action::end()
{

}


void Action::drawRect()
{
    frameBox[currFrame]->drawRect();
}

