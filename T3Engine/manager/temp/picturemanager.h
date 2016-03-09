#ifndef PICTUREMANAGER_H
#define PICTUREMANAGER_H


#include"picture.h"


class PictureManager:public Singleton<PictureManager>
{
public:
    PictureManager();
    void init();
    Picture *getPicture(const QString& pictureName);

    //调试用，看看读了那些图,qdebug输出资源标识符以及相应资源指针
    void showPictureBoxMessage();
private:
    void loadImage(const QString& path);
    //图片资源，通过QString类型的资源标识符获得
    QHash<QString,Picture*> pictureBox;
};

#endif // PICTUREMANAGER_H
