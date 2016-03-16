#ifndef WORLD_H
#define WORLD_H

#include"scene.h"
#include"stable.h"

class World
{
public:
    World();
    ~World();
    void update();
    void draw();
    void switchScene(const QString& sceneName);
    QString getName() const;
    void setName(const QString &value);
    void addScene(Scene* scene);

    void addDecoration(const QString& decorationName);
    void addCharacter(const QString& characterName);
    void setBackground(const QString& backgroundName);

    Entity* selectEntity(const QPoint& p);

protected:
    QString name;
    QMap<QString ,Scene*> sceneBox;
    QString currentScene;
};

#endif // WORLD_H
