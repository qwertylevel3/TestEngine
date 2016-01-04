#ifndef ACTION_H
#define ACTION_H

#include"frame.h"

class Action
{
public:
    Action();
    ~Action();

    void addFrame(Frame* frame){frameBox.push_back(frame);}

    void draw(bool showRect);

    void start();
    int update();
    void end();

    void setFrameTotal(int n){frameTotal=n;}
    void setFrameDelay(int d){frameDelay=d;}
    void setCurrFrame(int index){currFrame=index;}
    void setRepeat(bool r){isRepeat=r;}
    void setRepeatStart(int index){repeatStart=index;}
    void setRepeatOver(int index){repeatOver=index;}
    void mirror(bool m);


    int getFrameTotal(){return frameTotal;}
    int getFrameDelay(){return frameDelay;}
    int getCurrFrame(){return currFrame;}
    bool getRepeat(){return isRepeat;}
    int getRepeatStart(){return repeatStart;}
    int getRepeatOver() {return repeatOver;}
    bool isMirror(){return mir;}


private:
    QList<Frame*> frameBox;

    int frameDelay;//每帧延迟
    int frameTotal;//总帧数
    bool isRepeat;//重复播放
    int currFrame;//当前帧
    int frameClock;//计时用

    int repeatStart;//重复开始帧
    int repeatOver;//重复终止帧
    bool mir;//是否反向(向左为true)

};

#endif // ACTION_H
