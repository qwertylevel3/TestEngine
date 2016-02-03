#ifndef GAMECONFIGURATOR_H
#define GAMECONFIGURATOR_H

#include"T3Engine/singleton.h"
#include<QSurfaceFormat>

class GameConfigurator :public Singleton<GameConfigurator>
{
public:
    GameConfigurator();

    void init();

    float getScale(){return scale;}
    int getWindowWidth(){return windowWidth;}
    int getWindowHeight(){return windowHeight;}
    QSurfaceFormat getQSurfaceFormat(){return format;}
protected:
    float scale;//绘制时缩放比例
    int windowWidth;
    int windowHeight;
    QSurfaceFormat format;
};

#endif // GAMECONFIGURATOR_H
