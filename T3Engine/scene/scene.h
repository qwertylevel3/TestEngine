#ifndef SCENE_H
#define SCENE_H

#include"T3Engine/entity/decoration/decoration.h"
#include"T3Engine/entity/character/character.h"
#include"T3Engine/entity/terrain/terrain.h"
#include<QList>

class Scene
{
    //Q_OBJECT
public:
    Scene();
    ~Scene();

    void init();
    void draw();
    void drawBackground();
    void update();

    void load(const QString& filename);
    void unload();

    void collision();
    bool isCollision(Entity *a, Entity *b);
    bool isCollision(QRectF a,QRectF b);
protected:
    void addEntityToLayerBox(Entity* entity);
    void addCharacterToBox(Character* character);
    void addTerrainToBox(Terrain* terrain);
    void addDecorationToBox(Decoration* decoration);

    QList<Character*> characterBox;
    QList<Terrain*> terrainBox;
    QList<Decoration*> decorationBox;

    QList<QList<Entity*> > layerBox;

    int width;
    int height;
};

#endif // SCENE_H
