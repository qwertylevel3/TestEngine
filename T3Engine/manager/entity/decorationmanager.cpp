#include "decorationmanager.h"
#include"gameconfigurator.h"

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

void DecorationManager::destroy()
{
    QMap<QString,Decoration*>::iterator i=decorationBox.begin();
    while(i!=decorationBox.end())
    {
        delete i.value();
        i++;
    }
}

Decoration *DecorationManager::getDecoration(const QString &decorationName)
{
    return decorationBox[decorationName]->clone();
}

QMap<QString, Decoration *> &DecorationManager::getDecorationBox()
{
    return decorationBox;
}


Decoration *DecorationManager::makeDecoration()
{
    reader.readNextStartElement();//<Decoration>

    reader.readNextStartElement();//<Name>
    QString name=reader.readElementText();

    reader.readNextStartElement();//<SpriteName>
    QString spriteName=reader.readElementText();

    reader.readNextStartElement();//<collisionAble>
    bool collisionAble=reader.readElementText().toInt()==0?false:true;

    reader.readNextStartElement();//<destractiable>
    bool destractiable=reader.readElementText().toInt()==0?false:true;

    reader.readNextStartElement();//</Decoration>

    Decoration* decoration=new Decoration(spriteName);
    decoration->setName(name);
    decoration->setCollisionAble(collisionAble);
    decoration->setDestructible(destractiable);
    return decoration;
}

