#include "picturemanager.h"
#include"stable.h"

PictureManager::PictureManager()
{

}

void PictureManager::init()
{
    QString path=QDir::currentPath();
    path+=QDir::separator()+QString("resource");
    loadImage(path);
}

void PictureManager::destroy()
{
    QHash<QString,Picture* >::iterator i=pictureBox.begin();
    while(i!=pictureBox.end())
    {
        delete i.value();
        i++;
    }
}

Picture *PictureManager::getPicture(const QString &pictureName)
{
    return pictureBox.value(pictureName);
}

void PictureManager::showPictureBoxMessage()
{
    QHash<QString, Picture*>::const_iterator i = pictureBox.constBegin();
    while (i != pictureBox.constEnd()) {
        qDebug() << i.key() << ": " << i.value() << endl;
        ++i;
    }
}

void PictureManager::loadImage(const QString &path)
{
    QDir dir(path);

    QStringList filters;
    foreach(QByteArray format,QImageReader::supportedImageFormats())
        filters+="*."+format;
    foreach(QString file,dir.entryList(filters,QDir::Files))
    {
        QString filePath=path+QDir::separator()
                +QFileInfo(dir,file).fileName();

        Picture* t=new Picture(filePath);
        pictureBox.insert(t->getName(),t);

    }
    foreach(QString subDir,dir.entryList(QDir::Dirs | QDir::NoDotAndDotDot))
    {
        loadImage(path+QDir::separator()+subDir);
    }
}

