#include "frame.h"

Frame::Frame(Picture *p, const QRectF &fp)
{
    picture=p;
    framePosition=fp;
}


Frame::~Frame()
{
    delete picture;
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

void Frame::draw()
{
    picture->draw();
}
