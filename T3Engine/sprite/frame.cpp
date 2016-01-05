#include "frame.h"
#include"T3Engine/render/rendermodule.h"
#include"T3Engine/manager/picturemanager.h"

Frame::Frame(const QString& pictureName, const QRectF &fp)
{
    picture=pictureName;
    framePosition=fp;
}


Frame::~Frame()
{
}

void Frame::addRect(const QRectF &r)
{
//    QRectF temp(r);
//    rects.push_back(temp);

//    QRectF mtemp(pixmap.width()-x-width,
//                 y,
//                 width,
//                 height);
//    mrects.push_back(mtemp);
}

void Frame::addRect(float x, float y, float dx, float dy)
{
//    QRectF temp(x,y,width,height);
//    rects.push_back(temp);

//    QRectF mtemp(pixmap.width()-x-width,
//                 y,
//                 width,
//                 height);
    //    mrects.push_back(mtemp);
}

void Frame::draw(float x, float y, float zoom, bool mir)
{
    Picture* p=PictureManager::instance()->getPicture(picture);
    if(!p)
    {
        qDebug()<<"can not get picture point"<<endl;
        return;
    }
    p->setTexturePosition(framePosition.x(),framePosition.y(),
                          framePosition.width()/p->getImageWidth(),
                          framePosition.height()/p->getImageHeight());
    p->setCoordinate(x,y);
    p->setZoom(zoom);
    p->mirror(mir);
    p->draw();
}
