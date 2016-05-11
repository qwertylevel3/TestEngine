#ifndef FACEMANAGER_H
#define FACEMANAGER_H

#include"face.h"

class FaceManager:public Singleton<FaceManager>
{
public:
    FaceManager();
    void init();
    void destroy();

    Face* getFace(const QString& faceName);
    void addFace(const QString& faceName,Face* face);

protected:
    QMap<QString,Face*> faceBox;
    QXmlStreamReader reader;

    Face* makeFace();
};

#endif // FACEMANAGER_H
