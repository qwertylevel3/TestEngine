#include "spritemanager.h"
#include"stable.h"
#include"gameconfigurator.h"

SpriteManager::SpriteManager()
{

}

void SpriteManager::init()
{
    QString fileName=GameConfigurator::instance()->getSpriteConfigFileName();

    QString path=QDir::currentPath()+QDir::separator()+fileName;

    QFile file(path);

    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        qDebug()<<"can not open "<<fileName<<endl;
        return ;
    }
    reader.setDevice(&file);

    reader.readNextStartElement();//<spriteBox>;


    for(int i=0;i<6;i++)
    {
        makeDifSprite();
    }

    reader.readNextStartElement();//</spriteBox>
    file.close();
}

void SpriteManager::destroy()
{
    QMap<QString,Sprite*>::iterator i=spriteBox.begin();
    while(i!=spriteBox.end())
    {
        delete i.value();
        i++;
    }
}

Sprite *SpriteManager::getSprite(const QString &spriteName)
{
    return spriteBox[spriteName]->clone();

}


void SpriteManager::write()
{
//    QString fileName=GameConfigurator::instance()->getSpriteConfigFileName();
//    QString path=QDir::currentPath()+QDir::separator()+fileName;
//    QFile file(path);
//
//    //todo...
//
//    if (!file.open(QFile::WriteOnly | QFile::Text))
//    {
//        qDebug()<<"can not open "<<fileName<<" to write."<<endl;
//        return ;
//    }
//    writer.setDevice(&file);
//    writer.setAutoFormatting(true);
//    writer.writeStartDocument();
//    writer.writeStartElement("SpriteBox");
//
//    for(int i=0;i<spriteBox.size();i++)
//    {
//
//    }
//
    //    file.close();
}

void SpriteManager::makeDifSprite()
{
    reader.readNextStartElement();//<....Sprite>

    reader.readNextStartElement();//<TotalSpriteNumber>
    int number=reader.readElementText().toInt();

    for(int i=0;i<number;i++)
    {
        Sprite* sprite=makeSprite();
        addSprite(sprite);
    }

    reader.readNextStartElement();//</....Sprite>
}


Sprite *SpriteManager::makeSprite()
{
    reader.readNextStartElement();//sprite

    Sprite* sprite=new Sprite();

    reader.readNextStartElement();
    QString spriteName=reader.readElementText();//<spriteName>
    sprite->setName(spriteName);

    reader.readNextStartElement();
    QString pictureName=reader.readElementText();//<pictureName>
    sprite->setPictureName(pictureName);

    reader.readNextStartElement();
    int totalActionNumber=reader.readElementText().toInt();//<totalActionNumber>
    sprite->setTotalActionNumber(totalActionNumber);

    reader.readNextStartElement();//<width>
    float width=reader.readElementText().toFloat();
    sprite->setOriWidth(width);
    sprite->setWidth(width);

    reader.readNextStartElement();//<height>
    float height=reader.readElementText().toFloat();
    sprite->setOriHeight(height);
    sprite->setHeight(height);

    for(int i=0;i<totalActionNumber;i++)
    {
        makeAnimation(sprite);
    }

    reader.readNextStartElement();//</sprite>

    return sprite;
}

void SpriteManager::makeAnimation(Sprite *sprite)
{
    reader.readNextStartElement();//Action;

    Animatioin* animation=new Animatioin();

    reader.readNextStartElement();//ActionName;
    animation->setName(reader.readElementText());

    reader.readNextStartElement();
    int frameDelay=reader.readElementText().toInt();
    animation->setFrameDelay(frameDelay);

    reader.readNextStartElement();
    int frameTotal=reader.readElementText().toInt();
    animation->setFrameTotal(frameTotal);

    reader.readNextStartElement();
    bool isRepeat=reader.readElementText()=="true"?true:false;
    animation->setRepeat(isRepeat);

    reader.readNextStartElement();
    int repeatStart=reader.readElementText().toInt();
    animation->setRepeatStart(repeatStart);

    reader.readNextStartElement();
    int repeatOver=reader.readElementText().toInt();
    animation->setRepeatOver(repeatOver);

    reader.readNextStartElement();//frameBox

    for(int j=0;j<frameTotal;j++)
    {
        QString temp=reader.name().toString();

        Frame* frame=makeFrame(sprite);
        animation->addFrame(frame);
    }
    reader.readNextStartElement();//</FrameBox>
    reader.readNextStartElement();//</Action>

    sprite->addAction(animation);

    //todo...
    sprite->setCurrentAction(animation->getName());
}

Frame *SpriteManager::makeFrame(Sprite *sprite)
{
    reader.readNextStartElement();//frame

    reader.readNextStartElement();
    float x=reader.readElementText().toFloat();

    reader.readNextStartElement();
    float y=reader.readElementText().toFloat();


    QRectF rect(x,y,sprite->getWidth(),sprite->getHeight());

    Frame* frame=new Frame(sprite->getPictureName(),rect);

    reader.readNextStartElement();//<rectBox>

    reader.readNextStartElement();//<rectNumber>
    int rectNumber=reader.readElementText().toInt();

    for(int i=0;i<rectNumber;i++)
    {
        QRectF rect=makeRect();
        frame->addRect(rect);
    }
    reader.readNextStartElement();//</rectBox>

    reader.readNextStartElement();//</Frame>

    return frame;
}

QRectF SpriteManager::makeRect()
{
    reader.readNextStartElement();//<rect>

    reader.readNextStartElement();
    int x=reader.readElementText().toInt();

    reader.readNextStartElement();
    int y=reader.readElementText().toInt();

    reader.readNextStartElement();
    int w=reader.readElementText().toInt();

    reader.readNextStartElement();
    int h=reader.readElementText().toInt();

    QRectF rect(x,y,w,h);

    reader.readNextStartElement();//</rect>

    return rect;
}
