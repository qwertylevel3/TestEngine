#ifndef ACTION_H
#define ACTION_H

#include"frame.h"

class Action
{
public:
    Action();
    ~Action();

    void setText(const QString& text)
    {
        frameBox[currFrame]->setText(text);
    }

    void setCoordinate(float x,float y,float z)
    {
        frameBox[currFrame]->setCoordinate(x,y,z);
    }
    void setZoomX(float zoomX)
    {
        frameBox[currFrame]->setZoomX(zoomX);
    }
    void setZoomY(float zoomY)
    {
        frameBox[currFrame]->setZoomY(zoomY);
    }
    void mirror(float mir)
    {
        frameBox[currFrame]->mirror(mir);
    }
    void rotate(float angle,float ax,float ay,float az)
    {
        frameBox[currFrame]->rotate(angle,ax,ay,az);
    }
    void setWidth(float width)
    {
        frameBox[currFrame]->setWidth(width);
    }
    void setHeight(float height)
    {
        frameBox[currFrame]->setHeight(height);
    }
    void setRepeatX(int value)
    {
        frameBox[currFrame]->setRepeatX(value);
    }
    void setRepeatY(int value)
    {
        frameBox[currFrame]->setRepeatY(value);
    }
    void draw()
    {
        frameBox[currFrame]->draw();
    }

    Action* clone();

    void addFrame(Frame* frame){frameBox.push_back(frame);}

    void drawRect();

    void start();
    int update();
    void end();

    void setName(const QString& n){name=n;}
    void setFrameTotal(int n){frameTotal=n;}
    void setFrameDelay(int d){frameDelay=d;}
    void setCurrFrame(int index){currFrame=index;}
    void setRepeat(bool r){isRepeat=r;}
    void setRepeatStart(int index){repeatStart=index;}
    void setRepeatOver(int index){repeatOver=index;}

    QString getName(){return name;}
    int getFrameTotal(){return frameTotal;}
    int getFrameDelay(){return frameDelay;}
    int getCurrFrameIndex(){return currFrame;}
    bool getRepeat(){return isRepeat;}
    int getRepeatStart(){return repeatStart;}
    int getRepeatOver() {return repeatOver;}
    Frame* getCurrFrame(){return frameBox[currFrame];}
private:
    QString name;
    QList<Frame*> frameBox;

    int frameDelay;//每帧延迟
    int frameTotal;//总帧数
    bool isRepeat;//重复播放
    int currFrame;//当前帧
    int frameClock;//计时用

    int repeatStart;//重复开始帧
    int repeatOver;//重复终止帧
};

#endif // ACTION_H
