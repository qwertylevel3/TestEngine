#ifndef FRAME_H
#define FRAME_H

#include"T3Engine/render/picture.h"
#include<QList>
#include<QTextStream>
#include<QPixmap>

struct Frame
{
    Frame(const QString& pictureName,const QRectF& fp);
    ~Frame();

    void setPicture(const QString& pictureName);
    void setFramePosition(const QRectF& p){framePosition=p;}
    void addRect(const QRectF& r);
    void addRect(float x,float y,float dx,float dy);
    void draw(float x, float y, float z,float zoomX=1.0,float zoomY=1.0,
              bool mir=false,float angle=0,float ax=0,float ay=0,float az=0);
    void drawRect();

    QString getPicture(){return picture;}
    QRectF& getFramePosition(){return framePosition;}
    QList<QRectF>& getRects(){return rects;}
    QList<QRectF>& getmRects(){return mrects;}

    QString picture;
    QRectF framePosition;//当前帧在全图中的坐标
    //QVector<QRectF> redRect;
    QList<QRectF> rects;
    QList<QRectF> mrects;//镜像矩形

};

#endif // FRAME_H
