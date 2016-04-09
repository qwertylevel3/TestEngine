#ifndef SPRITE_H
#define SPRITE_H

#include"animation.h"
#include"gameconfigurator.h"
#include"stable.h"

class Sprite
{
public:
    Sprite();
    Sprite* clone();
    void update();
    void draw();
    void drawRect();

    void setText(QString text)
    {
        this->text=text;
        animationBox[currentAnimation]->setText(text);
    }

    void addAction(Animatioin* value);
    void setX(float x){this->x=x;}
    void setY(float y){this->y=y;}
    void setZ(float z){this->z=z;}
    void setCurrentAction(const QString& actionName);
    void setName(const QString& n){name=n;}
    void setTotalActionNumber(int n){totalActionNumber=n;}
    void setZoomX(float z);
    void setZoomY(float z);
    void mirror(bool m){mir=m;}
    void setRotateAngle(float a){angle=a;}
    void setRotateX(float x){ax=x;}
    void setRotateY(float y){ay=y;}
    void setRotateZ(float z){az=z;}

    float getX(){return x;}
    float getY(){return y;}
    float getZ(){return z;}
    QString getCurrentActionName(){return currentAnimation;}
    QList<QRectF>& getCurrentRects();
    QString getName(){return name;}
    int getTotalActionNumber(){return totalActionNumber;}
    float getZoomX(){return zoomX;}
    float getZoomY(){return zoomY;}
    bool isMirror(){return mir;}
    float getRotateAngle(){return angle;}
    float getRotateX(){return ax;}
    float getRotateY(){return ay;}
    float getRotateZ(){return az;}
    Animatioin* getAction(const QString& actionName){return animationBox[actionName];}


    float getWidth() const
    {
        return width;
    }
    void setWidth(float value)
    {
        zoomX=value/oriWidth;
        width=value;
    }

    float getHeight() const
    {
        return height;
    }
    void setHeight(float value)
    {
        zoomY=value/oriHeight;
        height=value;
    }

    int getRepeatX() const
    {
        return repeatX;
    }
    void setRepeatX(int value)
    {
        repeatX = value;
    }

    int getRepeatY() const
    {
        return repeatY;
    }
    void setRepeatY(int value)
    {
        repeatY = value;
    }

    float getAlpha() const;
    void setAlpha(float value);

    float getZoomUp() const;
    void setZoomUp(float value);

    float getZoomDown() const;
    void setZoomDown(float value);

    float getZoomLeft() const;
    void setZoomLeft(float value);

    float getZoomRight() const;
    void setZoomRight(float value);

    float getOriWidth() const;
    void setOriWidth(float value);

    float getOriHeight() const;
    void setOriHeight(float value);

protected:
    QString name;

    QString currentAnimation;
    int totalActionNumber;

    float zoomX;//放缩
    float zoomY;

    float x,y,z;//位置坐标

    bool mir;//镜像

    float angle;//旋转角度
    float ax,ay,az;//旋转轴
    float oriWidth;
    float oriHeight;
    float width;
    float height;
    int repeatX;//重复绘制
    int repeatY;
    float alpha;
    QString text;

//    QList<Action*> actionBox;
    QMap<QString,Animatioin*> animationBox;
};


inline
QList<QRectF> &Sprite::getCurrentRects()
{
    return animationBox[currentAnimation]->getCurrFrame()->getRects();
}

#endif // SPRITE_H
