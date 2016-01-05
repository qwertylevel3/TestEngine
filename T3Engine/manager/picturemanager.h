#ifndef PICTUREMANAGER_H
#define PICTUREMANAGER_H

#include<T3Engine/singleton.h>
#include<QHash>
#include"T3Engine/render/picture.h"


class PictureManager:public Singleton<PictureManager>
{
public:
    PictureManager();
    void init();
    Picture *getPicture(const QString& pictureName);

    //debug...
    void showPictureBoxMessage();
private:
    void loadImage(const QString& path);
    QHash<QString,Picture*> pictureBox;
};

#endif // PICTUREMANAGER_H
