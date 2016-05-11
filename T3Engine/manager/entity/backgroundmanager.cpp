#include "backgroundmanager.h"

BackgroundManager::BackgroundManager()
{

}


void BackgroundManager::init()
{
    QString fileName=GameConfigurator::instance()->getBackgroundConfigFileName();
    QString path=QDir::currentPath()+QDir::separator()+fileName;


    QFile file(path);

    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        qDebug()<<"can not open "<<fileName<<endl;
        return ;
    }
    reader.setDevice(&file);

    reader.readNextStartElement();//<BackgroundBox>
    reader.readNextStartElement();//<TotalBackgroundNumber>
    int totalBKNumber=reader.readElementText().toInt();

    for(int i=0;i<totalBKNumber;i++)
    {
        Background* BK=makeBackground();
        addBackground(BK);
    }

    file.close();
}

void BackgroundManager::destroy()
{
    for(int i=0;i<activeBox.size();i++)
    {
        delete activeBox[i];
    }
    QMap<QString, Background*>::iterator i = backgroundBox.begin();
    while (i != backgroundBox.end()) {
        delete i.value();
        ++i;
    }
}

Background *BackgroundManager::getBackground(const QString &bkName)
{
    Background* bk=backgroundBox[bkName]->clone();
    activeBox.append(bk);
    return bk;
}

void BackgroundManager::addBackground(Background *bk)
{
    backgroundBox.insert(bk->getName(),bk);
}

QMap<QString, Background *> &BackgroundManager::getBackgroundBox()
{
    return backgroundBox;
}

Background *BackgroundManager::makeBackground()
{
    reader.readNextStartElement();//<Background>

    reader.readNextStartElement();//<Name>
    QString name=reader.readElementText();

    reader.readNextStartElement();//<SpriteName>
    QString spriteName=reader.readElementText();

    reader.readNextStartElement();//</Background>

    Background* BK=new Background(spriteName);
    BK->setName(name);
    return BK;
}

