#ifndef FRAME_H
#define FRAME_H

#include"picture.h"
#include<QList>
#include<QTextStream>
#include<QPixmap>

struct Frame
{
    Frame();
    ~Frame();
    Frame(Frame *f);
    void setPicture(const QString& p);

    Picture* picture;
    //QVector<QRectF> redRect;
    QList<QRectF> rects;
    QList<QRectF> mrects;//镜像矩形

};

#endif // FRAME_H
