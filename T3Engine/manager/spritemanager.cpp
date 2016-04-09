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
        Animatioin* action=makeAction();
        sprite->addAction(action);
        if(i==0)
        {
            sprite->setCurrentAction(action->getName());
        }
    }

    reader.readNextStartElement();//</sprite>

    return sprite;
}

Animatioin *SpriteManager::makeAction()
{
    reader.readNextStartElement();//Action;

    Animatioin* action=new Animatioin();

    reader.readNextStartElement();//ActionName;
    action->setName(reader.readElementText());

    reader.readNextStartElement();
    int frameDelay=reader.readElementText().toInt();
    action->setFrameDelay(frameDelay);

    reader.readNextStartElement();
    int frameTotal=reader.readElementText().toInt();
    action->setFrameTotal(frameTotal);

    reader.readNextStartElement();
    bool isRepeat=reader.readElementText()=="true"?true:false;
    action->setRepeat(isRepeat);

    reader.readNextStartElement();
    int repeatStart=reader.readElementText().toInt();
    action->setRepeatStart(repeatStart);

    reader.readNextStartElement();
    int repeatOver=reader.readElementText().toInt();
    action->setRepeatOver(repeatOver);

    reader.readNextStartElement();//frameBox

    for(int j=0;j<frameTotal;j++)
    {
        QString temp=reader.name().toString();

        Frame* frame=makeFrame();
        action->addFrame(frame);
    }
    reader.readNextStartElement();//</FrameBox>
    reader.readNextStartElement();//</Action>

    return action;
}

Frame *SpriteManager::makeFrame()
{
    reader.readNextStartElement();//frame

    reader.readNextStartElement();

    QString pictureName=reader.readElementText();

    reader.readNextStartElement();
    float x=reader.readElementText().toFloat();

    reader.readNextStartElement();
    float y=reader.readElementText().toFloat();

    reader.readNextStartElement();
    float dx=reader.readElementText().toFloat();

    reader.readNextStartElement();
    float dy=reader.readElementText().toFloat();

    QRectF rect(x,y,dx,dy);

    Frame* frame=new Frame(pictureName,rect);

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
