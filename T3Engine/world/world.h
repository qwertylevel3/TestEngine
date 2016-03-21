#ifndef WORLD_H
#define WORLD_H

#include"scene.h"
#include"stable.h"
#include"singleton.h"

class World:public Singleton<World>
{
public:
    World();
    ~World();
    bool init();
    bool open(const QString& path);

    void clear();

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

    int getTotalSceneNumber();

    QMap<QString, Scene *> getSceneBox() const;

    bool save(const QString& fileName);
protected:
    bool load(const QString& path);
    QString setInitPath();
    QString setSavePath(const QString& fileName);

    QString name;
    QMap<QString ,Scene*> sceneBox;
    QString currentScene;

    QXmlStreamWriter writer;


    Scene* makeScene();
    void makeBackground(Scene* scene);
    void makeTerrain(Scene* scene);
    void makeDecoration(Scene* scene);
    void makeCharacter(Scene* scene);
    void makePlayer(Scene* scene);
    void makeTriggerBox(Scene* scene);
    void makeTrigger(Scene* scene);
    void makeSceneBorder(Scene* scene);

    void saveWorld(const QString& fileName);

    QXmlStreamReader reader;
};

#endif // WORLD_H
