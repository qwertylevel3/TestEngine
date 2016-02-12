#include "frame.h"
#include"T3Engine/manager/picturemanager.h"
#include"T3Engine/gameconfigurator.h"

Frame::Frame(const QString& pictureName, const QRectF &fp)
{
    scale=GameConfigurator::instance()->getScale();
    this->pictureName=pictureName;
    picturePoint=PictureManager::instance()->getPicture(pictureName);
    if(!picturePoint)
    {
        qDebug()<<"picturePoint"<<pictureName<<" is empty"<<endl;
    }
    framePosition=fp;
}


Frame::~Frame()
{
}

void Frame::draw()
{
    picturePoint->setTexturePosition(framePosition.x()/picturePoint->getImageWidth(),
                                     framePosition.y()/picturePoint->getImageHeight(),
                                     framePosition.width()/picturePoint->getImageWidth(),
                                     framePosition.height()/picturePoint->getImageHeight());
    picturePoint->draw();
    if(GameConfigurator::instance()->getDrawRect())
    {
        drawRect();
    }
}

Frame *Frame::clone()
{
    Frame* newFrame=new Frame(this->pictureName,this->framePosition);
    for(int i=0;i<rects.size();i++)
    {
        QRectF r(rects[i]);
        newFrame->addRect(r);
    }

    return newFrame;
}

void Frame::addRect(const QRectF &r)
{
    QRectF temp(r);
    rects.push_back(temp);
}

void Frame::addRect(float x, float y, float dx, float dy)
{
    QRectF temp(x,y,dx,dy);
    rects.push_back(temp);
}

void Frame::drawRect()
{
    Picture* rectPoint=PictureManager::instance()->getPicture("\\resource\\rect.png");

    for(int i=0;i<rects.size();i++)
    {
        rectPoint->setWidth(float(rects[i].width())/scale);
        rectPoint->setHeight(float(rects[i].height())/scale);

        rectPoint->setCoordinate(picturePoint->getX()+float(rects[i].x()*picturePoint->getWidth())/scale,
                                 picturePoint->getY()+float(rects[i].y()*picturePoint->getHeight())/scale,
                                 -1);

        rectPoint->draw();
    }
}
