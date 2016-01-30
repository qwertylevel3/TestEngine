#include "sprite.h"

Sprite::Sprite()
{
    zoomX=1;
    zoomY=1;
    x=y=z=0;

    mir=false;

    angle=0;
    ax=ay=az=0;
}

Sprite *Sprite::clone()
{
    Sprite* newSp=new Sprite();
    newSp->setName(this->name);
    newSp->setPictureName(this->pictureName);
    newSp->setCurrentAction(0);
    newSp->setTotalActionNumber(this->totalActionNumber);

    for(int i=0;i<this->actionBox.size();i++)
    {
        Action* a=actionBox[i]->clone();
        actionBox.append(a);
    }

    return newSp;
}

void Sprite::update()
{
    actionBox[currentAction]->update();
}

void Sprite::draw()
{
    actionBox[currentAction]->draw(x,y,z,zoomX,zoomY,mir,angle,ax,ay,az);
}


