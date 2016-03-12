#ifndef WORLD_H
#define WORLD_H

#include"scene.h"
#include"stable.h"

class World
{
public:
    World();
    void update();
    void draw();
    void switchScene(QString sceneName);
protected:
    QMap<QString ,Scene*> sceneBox;
    QString currentScene;
};

#endif // WORLD_H
