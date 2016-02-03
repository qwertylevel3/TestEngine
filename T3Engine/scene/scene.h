#ifndef SCENE_H
#define SCENE_H

#include"T3Engine/entity/character/character.h"
#include<QList>

class Scene
{
    //Q_OBJECT
public:
    Scene();
    ~Scene();

    void init();
    void draw();
    void drawRect();
    void update();

    void load(const QString& filename);
    void unload();

    void collision();
    bool isCollision(Entity *a, Entity *b);
    bool isCollision(QRectF a,QRectF b);
protected:
    QList<Character*> characterBox;
};

#endif // SCENE_H
