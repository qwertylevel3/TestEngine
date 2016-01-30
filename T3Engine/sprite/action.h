#ifndef ACTION_H
#define ACTION_H

#include"frame.h"

class Action
{
public:
    Action();
    ~Action();

    Action* clone();

    void addFrame(Frame* frame){frameBox.push_back(frame);}

    //xyz坐标，zoom放缩，mir是否镜像，绕axayaz转angle度
    void draw(float x, float y, float z,float zoomX=1.0,float zoomY=1.0, bool mir=false
            ,float angle=0,float ax=0,float ay=0,float az=0);
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
