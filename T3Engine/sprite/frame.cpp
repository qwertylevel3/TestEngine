#include "frame.h"
#include"T3Engine/render/rendermodule.h"
#include"T3Engine/manager/picturemanager.h"

Frame::Frame(const QString& pictureName, const QRectF &fp,
             const float w,const float h)
{
    this->pictureName=pictureName;
    picturePoint=PictureManager::instance()->getPicture(pictureName);
    if(!picturePoint)
    {
        qDebug()<<"picturePoint"<<pictureName<<" is empty"<<endl;
    }
    framePosition=fp;
    width=w/100;
    height=h/100;
    qDebug()<<width<<" "<<height<<endl;

    x=y=z=0;
}


Frame::~Frame()
{
}

Frame *Frame::clone()
{
    Frame* newFrame=new Frame(this->pictureName,this->framePosition,
                             (this->width)*100,(this->height)*100);
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

void Frame::draw(float x, float y,float z,float zoomX,float zoomY,
                 bool mir, float angle, float ax, float ay, float az)
{

    picturePoint->setTexturePosition(framePosition.x()/picturePoint->getImageWidth(),
                          framePosition.y()/picturePoint->getImageHeight(),
                          framePosition.width()/picturePoint->getImageWidth(),
                          framePosition.height()/picturePoint->getImageHeight());

    //qDebug()<<framePosition.x()<<endl;
    //qDebug()<<framePosition.y()<<endl;
    //qDebug()<<framePosition.width()/p->getImageWidth()<<endl;
    //qDebug()<<framePosition.height()/p->getImageHeight()<<endl;

    this->x=x;
    this->y=y;
    this->z=z;

    picturePoint->setCoordinate(x,y,z);

    picturePoint->setZoomX(zoomX);
    picturePoint->setZoomY(zoomY);
    picturePoint->mirror(mir);
    picturePoint->rotate(angle,ax,ay,az);
    picturePoint->setWidth(width);
    picturePoint->setHeight(height);
    picturePoint->draw();
}

void Frame::drawRect()
{
    Picture* rectPoint=PictureManager::instance()->getPicture("\\resource\\rect.png");

    for(int i=0;i<rects.size();i++)
    {
        rectPoint->setWidth(float(rects[i].width())/100);
        rectPoint->setHeight(float(rects[i].height())/100);

        rectPoint->setCoordinate(x+float(rects[i].x()*width)/100,
                         y+float(rects[i].y()*height)/100,z);

        rectPoint->draw();
    }
}

