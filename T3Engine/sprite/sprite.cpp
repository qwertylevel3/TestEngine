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
    width=1;
    height=1;
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
    newSp->setOriWidth(oriWidth);
    newSp->setOriHeight(oriHeight);
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
    animationBox[currentAnimation]->setOriWidth(oriWidth);
    animationBox[currentAnimation]->setOriHeight(oriHeight);
    animationBox[currentAnimation]->setZoomX(zoomX);
    animationBox[currentAnimation]->setZoomY(zoomY);
//    animationBox[currentAnimation]->setWidth(width);
//    animationBox[currentAnimation]->setHeight(height);
    animationBox[currentAnimation]->mirror(mir);
    animationBox[currentAnimation]->rotate(angle,ax,ay,az);
    animationBox[currentAnimation]->setRepeatX(repeatX);
    animationBox[currentAnimation]->setRepeatY(repeatY);
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
float Sprite::getOriWidth() const
{
    return oriWidth;
}

void Sprite::setOriWidth(float value)
{
    oriWidth = value;
}
float Sprite::getOriHeight() const
{
    return oriHeight;
}

void Sprite::setOriHeight(float value)
{
    oriHeight = value;
}



void Sprite::addAction(Animatioin *value)
{
    animationBox.insert(value->getName(),value);
}

void Sprite::setCurrentAction(const QString &actionName)
{
    currentAnimation=actionName;
}

void Sprite::setZoomX(float z)
{
    zoomX=z;
    width=oriWidth*z;
}

void Sprite::setZoomY(float z)
{
    zoomY=z;
    height=oriHeight*z;
}
