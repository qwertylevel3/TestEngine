#ifndef SCENEMANAGER_H
#define SCENEMANAGER_H

#include"scene.h"

class SceneManager:public Singleton<SceneManager>
{
public:
    SceneManager();
    void init();

    Scene* getScene(const QString& sceneName);
protected:
    void makeScene();
    void makeBackground(Scene* scene);
    void makeTerrain(Scene* scene);
    void makeDecoration(Scene* scene);
    void makeCharacter(Scene* scene);
    void makePlayer(Scene* scene);

    QMap<QString,Scene*> sceneBox;
    QXmlStreamReader reader;
};

#endif // SCENEMANAGER_H
