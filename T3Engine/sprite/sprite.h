#ifndef SPRITE_H
#define SPRITE_H

#include"action.h"
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

    void setText(const QString& text)
    {
        this->text=text;
        actionBox[currentAction]->setText(text);
    }

    void addAction(Action* value);
    void setX(float x){this->x=x;}
    void setY(float y){this->y=y;}
    void setZ(float z){this->z=z;}
    void setCurrentAction(const QString& actionName);
    void setName(const QString& n){name=n;}
    void setTotalActionNumber(int n){totalActionNumber=n;}
    void setZoomX(float z){zoomX=z;}
    void setZoomY(float z){zoomY=z;}
    void mirror(bool m){mir=m;}
    void setRotateAngle(float a){angle=a;}
    void setRotateX(float x){ax=x;}
    void setRotateY(float y){ay=y;}
    void setRotateZ(float z){az=z;}

    float getX(){return x;}
    float getY(){return y;}
    float getZ(){return z;}
    QString getCurrentActionName(){return currentAction;}
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
    Action* getAction(const QString& actionName){return actionBox[actionName];}

    float getWidth() const
    {
        return width;
    }
    void setWidth(float value)
    {
        width=value;
    }

    float getHeight() const
    {
        return height;
    }
    void setHeight(float value)
    {
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

protected:
    QString name;

    QString currentAction;
    int totalActionNumber;

    float zoomX;//放缩
    float zoomY;

    float x,y,z;//位置坐标

    bool mir;//镜像

    float angle;//旋转角度
    float ax,ay,az;//旋转轴
    float width;
    float height;
    int repeatX;//重复绘制
    int repeatY;
    float alpha;
    QString text;

//    QList<Action*> actionBox;
    QMap<QString,Action*> actionBox;
};


inline
QList<QRectF> &Sprite::getCurrentRects()
{
    return actionBox[currentAction]->getCurrFrame()->getRects();
}

#endif // SPRITE_H
