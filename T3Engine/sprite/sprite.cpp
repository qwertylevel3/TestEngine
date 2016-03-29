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

    currentAction="";
    totalActionNumber=0;

    text="";
}

Sprite *Sprite::clone()
{
    Sprite* newSp=new Sprite();
    newSp->setName(this->name);
    newSp->setCurrentAction(this->getCurrentActionName());
    newSp->setTotalActionNumber(this->totalActionNumber);
    newSp->setWidth(width);
    newSp->setHeight(height);


    QMap<QString,Animatioin*>::const_iterator i=actionBox.constBegin();
    while(i!=actionBox.constEnd())
    {
        Animatioin* a=i.value()->clone();
        newSp->addAction(a);
        i++;
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




void Sprite::addAction(Animatioin *value)
{
    actionBox.insert(value->getName(),value);
}

void Sprite::setCurrentAction(const QString &actionName)
{
    currentAction=actionName;
}
