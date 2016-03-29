#include "animation.h"

Animatioin::Animatioin()
{
    frameDelay=1;
    frameTotal=0;
    isRepeat=false;
    currFrame=0;
    frameClock=0;

    repeatStart=0;
    repeatOver=0;

}

Animatioin::~Animatioin()
{

}

Animatioin *Animatioin::clone()
{
    Animatioin* newAction=new Animatioin();
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

void Animatioin::start()
{
    currFrame=repeatStart;
}
//update,return the state:0,over;1,busy
int Animatioin::update()
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

void Animatioin::end()
{

}


void Animatioin::drawRect()
{
    frameBox[currFrame]->drawRect();
}

