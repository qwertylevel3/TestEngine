#include "spritemanager.h"
#include<QFile>
#include<QDir>
#include"T3Engine/gameconfigurator.h"

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

    reader.readNextStartElement();//spriteBox;

    reader.readNextStartElement();//<totalSpriteNumber>
    int totalSpriteNumber=reader.readElementText().toInt();

    for(int i=0;i<totalSpriteNumber;i++)
    {

        Sprite* sprite=makeSprite();

        this->addSprite(sprite->getName(),sprite);

        reader.readNextStartElement();
    }
    file.close();
}

Sprite *SpriteManager::getSprite(const QString &spriteName)
{
    Sprite* t=spriteBox[spriteName];
    Sprite* s=t->clone();
    return s;
}

Sprite *SpriteManager::makeSprite()
{
    reader.readNextStartElement();//sprite

    QString s=reader.name().toString();

    Sprite* sprite=new Sprite();

    reader.readNextStartElement();
    QString spriteName=reader.readElementText();
    sprite->setName(spriteName);

    reader.readNextStartElement();
    int totalActionNumber=reader.readElementText().toInt();
    sprite->setTotalActionNumber(totalActionNumber);

    for(int i=0;i<totalActionNumber;i++)
    {
        Action* action=makeAction();
        sprite->addAction(action);
    }

    return sprite;
}

Action *SpriteManager::makeAction()
{
    reader.readNextStartElement();//Action;

    Action* action=new Action();

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
    QString t=reader.name().toString();

    return action;
}

Frame *SpriteManager::makeFrame()
{
    reader.readNextStartElement();//frame

    reader.readNextStartElement();

    QString temp=reader.name().toString();

    QString pictureName=reader.readElementText();

    reader.readNextStartElement();
    QString temp1=reader.name().toString();
    float x=reader.readElementText().toFloat();

    reader.readNextStartElement();
    float y=reader.readElementText().toFloat();

    reader.readNextStartElement();
    float dx=reader.readElementText().toFloat();

    reader.readNextStartElement();
    float dy=reader.readElementText().toFloat();

    reader.readNextStartElement();
    float width=reader.readElementText().toFloat();

    reader.readNextStartElement();
    float height=reader.readElementText().toFloat();

    QRectF rect(x,y,dx,dy);

    Frame* frame=new Frame(pictureName,rect,width,height);


    reader.readNextStartElement();//<rectBox>
    QString rectBox=reader.name().toString();

    reader.readNextStartElement();//<rectNumber>
    QString rectNumberStr=reader.name().toString();
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