#include "sprite.h"

Sprite::Sprite()
{
    zoomX=1;
    zoomY=1;
    zoomUp=1;
    zoomDown=1;
    zoomLeft=1;
    zoomRight=1;
    x=y=z=0;

    mir=false;

    angle=0;
    ax=ay=az=0;
    repeatX=0;
    repeatY=0;
    width=0.1;
    height=0.1;
    alpha=1.0;

    currentAnimation="";
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


    QMap<QString,Animatioin*>::const_iterator i=animationBox.constBegin();
    while(i!=animationBox.constEnd())
    {
        Animatioin* a=i.value()->clone();
        newSp->addAction(a);
        i++;
    }

    return newSp;
}

void Sprite::update()
{
    animationBox[currentAnimation]->update();
}

void Sprite::draw()
{
    if(!text.isEmpty())
    {
        animationBox[currentAnimation]->setText(text);
    }
    animationBox[currentAnimation]->setCoordinate(x,y,z);
    //animationBox[currentAnimation]->setZoomX(zoomX);
    //animationBox[currentAnimation]->setZoomY(zoomY);
    animationBox[currentAnimation]->setZoomUp(zoomUp);
    animationBox[currentAnimation]->setZoomDown(zoomDown);
    animationBox[currentAnimation]->setZoomLeft(zoomLeft);
    animationBox[currentAnimation]->setZoomRight(zoomRight);
    animationBox[currentAnimation]->mirror(mir);
    animationBox[currentAnimation]->rotate(angle,ax,ay,az);
    animationBox[currentAnimation]->setRepeatX(repeatX);
    animationBox[currentAnimation]->setRepeatY(repeatY);
    animationBox[currentAnimation]->setWidth(width);
    animationBox[currentAnimation]->setHeight(height);
    animationBox[currentAnimation]->setAlpha(alpha);
    animationBox[currentAnimation]->draw();
}

void Sprite::drawRect()
{
    animationBox[currentAnimation]->drawRect();
}
float Sprite::getAlpha() const
{
    return alpha;
}

void Sprite::setAlpha(float value)
{
    alpha = value;
}
float Sprite::getZoomUp() const
{
    return zoomUp;
}

void Sprite::setZoomUp(float value)
{
    zoomUp = value;
}
float Sprite::getZoomDown() const
{
    return zoomDown;
}

void Sprite::setZoomDown(float value)
{
    zoomDown = value;
}
float Sprite::getZoomLeft() const
{
    return zoomLeft;
}

void Sprite::setZoomLeft(float value)
{
    zoomLeft = value;
}
float Sprite::getZoomRight() const
{
    return zoomRight;
}

void Sprite::setZoomRight(float value)
{
    zoomRight = value;
}








void Sprite::addAction(Animatioin *value)
{
    animationBox.insert(value->getName(),value);
}

void Sprite::setCurrentAction(const QString &actionName)
{
    currentAnimation=actionName;
}
