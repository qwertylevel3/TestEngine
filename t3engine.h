#ifndef T3ENGINE_H
#define T3ENGINE_H

#include<QSurfaceFormat>
#include"T3Engine/scene/scene.h"
#include"T3Engine/manager/shadermanager.h"

class T3Engine
{
public:
    T3Engine();
    ~T3Engine();
    void init();
    void run();
private:
    Scene* scene;
    QSurfaceFormat format;
};

#endif // T3ENGINE_H
