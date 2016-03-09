#ifndef SCENE_H
#define SCENE_H

#include"decoration.h"
#include"character.h"
#include"terrain.h"
#include"bullet.h"
#include"collisiondetector.h"
#include"trigger.h"
#include"timeupcondition.h"
#include"dialogueevent.h"
#include"dialog.h"

class Scene
{
    //Q_OBJECT
public:
    Scene();
    ~Scene();

    void draw();
    void drawBackground();
    void update();

    void collision();
    void detectPlayerBulletCollision();
    void detectCharacterBulletCollision();
    void detectPlayerCharacterCollision();
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

    QString getName() const;
    void setName(const QString &value);

    Character *getPlayer() const;
    void setPlayer(Character *value);

    QList<Character *>& getCharacterBox();

    void switchFocusToPlayer();
    void switchFocusToDialog(Dialog* dialog);

    void addDialogToScene(Dialog* dialog);

protected:
    bool addEntityToLayerBox(Entity* entity);

    QList<Character*> characterBox;
    QList<Terrain*> terrainBox;
    QList<Decoration*> decorationBox;
    QList<Bullet*> bulletBox;

    Character* player;

    QList<QList<Entity*> > layerBox;

    int width;
    int height;

    CollisionDetector detector;

    QList<Trigger*> triggerList;

};

#endif // SCENE_H
