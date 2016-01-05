#ifndef T3ENGINE_H
#define T3ENGINE_H

#include<QSurfaceFormat>
#include"T3Engine/scene/scene.h"
#include"T3Engine/manager/shadermanager.h"
#include"T3Engine/render/rendermodule.h"

class T3Engine
{
public:
    T3Engine();
    ~T3Engine();
    void init();
    void run();
private:
    QSurfaceFormat format;
};

#endif // T3ENGINE_H
