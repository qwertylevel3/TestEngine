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
    void switchScene(const QString& sceneName);
    QString getName() const;
    void setName(const QString &value);
    void addScene(Scene* scene);

protected:
    QString name;
    QMap<QString ,Scene*> sceneBox;
    QString currentScene;
};

#endif // WORLD_H
