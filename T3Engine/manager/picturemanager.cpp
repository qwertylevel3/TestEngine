#include "picturemanager.h"
#include<QDir>
#include<QImageReader>

PictureManager::PictureManager()
{

}

void PictureManager::init()
{
    QString path=QDir::currentPath();
    path+=QDir::separator()+QString("resource");
    loadImage(path);
}

Picture *PictureManager::getPicture(const QString &pictureName)
{
    return pictureBox.value(pictureName);
}

void PictureManager::loadImage(const QString &path)
{
    QDir dir(path);

    QStringList filters;
    foreach(QByteArray format,QImageReader::supportedImageFormats())
        filters+="*."+format;
    foreach(QString file,dir.entryList(filters,QDir::Files))
    {
        QString fileName=QFileInfo(dir,file).fileName();
        Picture* t=new Picture(fileName);
        pictureBox.insert(fileName,t);

    }
    foreach(QString subDir,dir.entryList(QDir::Dirs | QDir::NoDotAndDotDot))
    {
        loadImage(path+QDir::separator()+subDir);
    }
}

