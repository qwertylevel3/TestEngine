#include "facemanager.h"

FaceManager::FaceManager()
{

}

void FaceManager::init()
{
    QString fileName=GameConfigurator::instance()->getFaceConfigFileName();
    QString path=QDir::currentPath()+QDir::separator()+fileName;

    QFile file(path);

    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        qDebug()<<"can not open "<<fileName<<endl;
        return ;
    }
    reader.setDevice(&file);

    reader.readNextStartElement();//<DecorationBox>

    reader.readNextStartElement();//<TotalDecorationNumber>
    int totalFaceNumber=reader.readElementText().toInt();

    for(int i=0;i<totalFaceNumber;i++)
    {
        Face* face=makeFace();

        addFace(face->getName(),face);

    }
    file.close();
}

Face *FaceManager::getFace(const QString &faceName)
{
    return faceBox[faceName];
}

void FaceManager::addFace(const QString &faceName, Face *face)
{
    faceBox.insert(faceName,face);
}

Face *FaceManager::makeFace()
{
    reader.readNextStartElement();//<Face>

    reader.readNextStartElement();//<Name>
    QString name=reader.readElementText();

    reader.readNextStartElement();//<SpriteName>
    QString spriteName=reader.readElementText();

    reader.readNextStartElement();//</Face>

    Face* face=new Face(spriteName);
    face->setName(name);
    return face;
}

