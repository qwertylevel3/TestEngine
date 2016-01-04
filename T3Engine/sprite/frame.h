#ifndef FRAME_H
#define FRAME_H

#include"picture.h"
#include<QList>
#include<QTextStream>
#include<QPixmap>

struct Frame
{
    Frame(Picture* p,const QRectF& fp);
    ~Frame();

    void setPicture(Picture* p);
    void setFramePosition(const QRectF& p){framePosition=p;}
    void addRect(const QRectF& r);
    void addRect(float x,float y,float dx,float dy);
    void draw();

    Picture* getPicture(){return picture;}
    QRectF& getFramePosition(){return framePosition;}
    QList<QRectF>& getRects(){return rects;}
    QList<QRectF>& getmRects(){return mrects;}

    Picture* picture;
    //the position of this frame in the picture
    QRectF framePosition;
    //QVector<QRectF> redRect;
    QList<QRectF> rects;
    QList<QRectF> mrects;//镜像矩形

};

#endif // FRAME_H
