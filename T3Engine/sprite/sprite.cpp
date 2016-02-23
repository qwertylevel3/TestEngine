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
    alpha=1.0;

    currentAction=0;
    totalActionNumber=0;
}

Sprite *Sprite::clone()
{
    Sprite* newSp=new Sprite();
    newSp->setName(this->name);
    newSp->setCurrentAction(0);
    newSp->setTotalActionNumber(this->totalActionNumber);
    newSp->setWidth(width);
    newSp->setHeight(height);

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
    if(!text.isEmpty())
    {
        actionBox[currentAction]->setText(text);
    }
    actionBox[currentAction]->setCoordinate(x,y,z);
    actionBox[currentAction]->setZoomX(zoomX);
    actionBox[currentAction]->setZoomY(zoomY);
    actionBox[currentAction]->mirror(mir);
    actionBox[currentAction]->rotate(angle,ax,ay,az);
    actionBox[currentAction]->setRepeatX(repeatX);
    actionBox[currentAction]->setRepeatY(repeatY);
    actionBox[currentAction]->setWidth(width);
    actionBox[currentAction]->setHeight(height);
    actionBox[currentAction]->setAlpha(alpha);
    actionBox[currentAction]->draw();
}

void Sprite::drawRect()
{
    actionBox[currentAction]->drawRect();
}
float Sprite::getAlpha() const
{
    return alpha;
}

void Sprite::setAlpha(float value)
{
    alpha = value;
}


