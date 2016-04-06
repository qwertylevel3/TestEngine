#ifndef FRAME_H
#define FRAME_H

#include<picture.h>

struct Frame
{
    Frame(const QString& pictureName, const QRectF& fp);
    ~Frame();

    void setCoordinate(float x,float y,float z)
    {
        picturePoint->setCoordinate(x,y,z);
    }
    void setZoomX(float zoomX)
    {
        picturePoint->setZoomX(zoomX);
    }
    void setZoomY(float zoomY)
    {
        picturePoint->setZoomY(zoomY);
    }
    void setZoomUp(float zoomUp)
    {
        picturePoint->setZoomUp(zoomUp);
    }
    void setZoomDown(float zoomDown)
    {
        picturePoint->setZoomDown(zoomDown);
    }
    void setZoomLeft(float zoomLeft)
    {
        picturePoint->setZoomLeft(zoomLeft);
    }
    void setZoomRight(float zoomRight)
    {
        picturePoint->setZoomRight(zoomRight);
    }

    void mirror(bool mir)
    {
        picturePoint->setMirror(mir);
    }
    void rotate(float angle,float ax,float ay,float az)
    {
        picturePoint->rotate(angle,ax,ay,az);
    }
    void setWidth(float width)
    {
        picturePoint->setWidth(width);
    }
    void setHeight(float height)
    {
        picturePoint->setHeight(height);
    }
    void setRepeatX(int value)
    {
        picturePoint->setRepeatX(value);
    }
    void setRepeatY(int value)
    {
        picturePoint->setRepeatY(value);
    }

    void setText(const QString& text)
    {
        picturePoint->setText(text);
    }
    void setAlpha(float alpha)
    {
        picturePoint->setAlpha(alpha);
    }

    void draw();

    Frame* clone();
    void setPicture(const QString& pictureName);
    void setFramePosition(const QRectF& p){framePosition=p;}
    void addRect(const QRectF& r);
    void addRect(float x,float y,float dx,float dy);
    void drawRect();

    QString getPicture(){return pictureName;}
    QRectF& getFramePosition(){return framePosition;}
    QList<QRectF>& getRects(){return rects;}

    QString pictureName;
    Picture* picturePoint;
    QRectF framePosition;//当前帧在全图中的位置
    //QVector<QRectF> redRect;
    QList<QRectF> rects;

    float scale;
};

#endif // FRAME_H
