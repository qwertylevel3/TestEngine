#ifndef SCENE_H
#define SCENE_H

#include"T3Engine/entity/decoration/decoration.h"
#include"T3Engine/entity/character/character.h"
#include"T3Engine/entity/terrain/terrain.h"
#include"T3Engine/entity/bullet/bullet.h"
#include<QList>

class Scene
{
    //Q_OBJECT
public:
    Scene();
    ~Scene();

    void draw();
    void drawBackground();
    void update();

    void load(const QString& filename);
    void unload();

    void collision();
    bool isCollision(Entity *a, Entity *b);
    bool isCollision(QRectF a,QRectF b);
    
    void addCharacterToBox(Character* character);
    void addTerrainToBox(Terrain* terrain);
    void addDecorationToBox(Decoration* decoration);
    void addBulletToBox(Bullet* bullet);
    int getWidth() const;
    void setWidth(int value);

    int getHeight() const;
    void setHeight(int value);

protected:
    void addEntityToLayerBox(Entity* entity);


    QList<Character*> characterBox;
    QList<Terrain*> terrainBox;
    QList<Decoration*> decorationBox;
    QList<Bullet*> bulletBox;

    QList<QList<Entity*> > layerBox;

    int width;
    int height;
};

#endif // SCENE_H
