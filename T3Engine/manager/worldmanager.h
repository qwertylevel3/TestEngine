#ifndef WORLDMANAGER_H
#define WORLDMANAGER_H

#include"world.h"

class WorldManager:public Singleton<WorldManager>
{
public:
    WorldManager();
    void init();

    World* getWorld();
protected:
    Scene* makeScene();
    void makeBackground(Scene* scene);
    void makeTerrain(Scene* scene);
    void makeDecoration(Scene* scene);
    void makeCharacter(Scene* scene);
    void makePlayer(Scene* scene);
    void makeTriggerBox(Scene* scene);
    void makeTrigger(Scene* scene);


    World* world;
    QXmlStreamReader reader;
};

#endif // WORLDMANAGER_H
