#include "decorationmanager.h"
#include"T3Engine/gameconfigurator.h"
#include<QDir>
#include<QFile>

DecorationManager::DecorationManager()
{

}

void DecorationManager::init()
{
    QString fileName=GameConfigurator::instance()->getDecorationConfigFileName();
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
    int totalDecorationNumber=reader.readElementText().toInt();

    for(int i=0;i<totalDecorationNumber;i++)
    {
        Decoration* decoration=makeDecoration();

        addDecoration(decoration->getName(),decoration);

    }
    file.close();

}

Decoration *DecorationManager::getDecoration(const QString &decorationName)
{
    return decorationBox[decorationName]->clone();
}


Decoration *DecorationManager::makeDecoration()
{
    reader.readNextStartElement();//<Decoration>

    reader.readNextStartElement();//<Name>
    QString name=reader.readElementText();

    reader.readNextStartElement();//<SpriteName>
    QString spriteName=reader.readElementText();

    reader.readNextStartElement();//</Decoration>

    Decoration* decoration=new Decoration(spriteName);
    decoration->setName(name);
    return decoration;
}

