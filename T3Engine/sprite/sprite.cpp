#include "sprite.h"

Sprite::Sprite()
{
    zoomX=1;
    zoomY=1;
    x=y=z=0;

    mir=false;

    angle=0;
    ax=ay=az=0;
    repeatX=0;
    repeatY=0;
    width=0.1;
    height=0.1;

    currentAction=0;
    totalActionNumber=0;
}

Sprite *Sprite::clone()
{
    Sprite* newSp=new Sprite();
    newSp->setName(this->name);
    newSp->setCurrentAction(0);
    newSp->setTotalActionNumber(this->totalActionNumber);

    for(int i=0;i<this->actionBox.size();i++)
    {
        Action* a=actionBox[i]->clone();
        newSp->addAction(a);
    }

    return newSp;
}

void Sprite::update()
{
    actionBox[currentAction]->update();
}

void Sprite::draw()
{
    actionBox[currentAction]->setCoordinate(x,y,z);
    actionBox[currentAction]->setZoomX(zoomX);
    actionBox[currentAction]->setZoomY(zoomY);
    actionBox[currentAction]->mirror(mir);
    actionBox[currentAction]->rotate(angle,ax,ay,az);
    actionBox[currentAction]->setRepeatX(repeatX);
    actionBox[currentAction]->setRepeatY(repeatY);
    actionBox[currentAction]->setWidth(width);
    actionBox[currentAction]->setHeight(height);
    actionBox[currentAction]->draw();
}

void Sprite::drawRect()
{
    actionBox[currentAction]->drawRect();
}

