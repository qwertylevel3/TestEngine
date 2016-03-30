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
#include"background.h"
#include"stable.h"

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
    void detectCharacterDecorationCollision();
    void detectPlayerDecorationCollision();
    
    void addCharacterToBox(Character* character);
    void addTerrainToBox(Terrain* terrain);
    void addDecorationToBox(Decoration* decoration);
    void addBulletToBox(Bullet* bullet);
    void addTrigger(Trigger* trigger);
    void setBackground(Background* BK);

    int getWidth() const;
    void setWidth(int value);

    int getHeight() const;
    void setHeight(int value);

    Character *getPlayer() const;
    void setPlayer(Character *value);

    QList<Character *>& getCharacterList();

    void switchFocusToPlayer();
    void switchFocusToDialog(Dialog* dialog);

    void addDialogToScene(Dialog* dialog);

    bool getPause() const;
    void setPause(bool value);

    QString getName() const;
    void setName(const QString &value);

    Entity* selectEntity(const QPoint& p);


    Background *getBk() const;

    QList<Trigger *> getTriggerList() const;


    void save(QXmlStreamWriter* writer);
    void writeBackground(QXmlStreamWriter* writer);
    void writeTerrainBox(QXmlStreamWriter* writer);
    void writeDecorationBox(QXmlStreamWriter* writer);
    void writeCharacterBox(QXmlStreamWriter* writer);
    void writePlayer(QXmlStreamWriter* writer);
    void writeTriggerBox(QXmlStreamWriter* writer);
protected:
    QString name;
    bool addEntityToLayerBox(Entity* entity);

    QList<Character*> characterList;
    QList<Terrain*> terrainList;
    QList<Decoration*> decorationList;
    QList<Bullet*> bulletList;
    QList<Dialog*> dialogList;
    Background* bk;

    Character* player;

    QList<QList<Entity*> > layerBox;

    int width;
    int height;

    CollisionDetector detector;

    QList<Trigger*> triggerList;

    bool pause;

};

#endif // SCENE_H
