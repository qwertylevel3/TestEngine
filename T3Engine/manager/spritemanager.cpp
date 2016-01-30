#include "spritemanager.h"
#include<QFile>

SpriteManager::SpriteManager()
{

}

void SpriteManager::init()
{
    QString fileName="test.xml";
    QFile file(fileName);

    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        qDebug()<<"can not open "<<fileName<<endl;
        return ;
    }
    reader.setDevice(&file);

    reader.readNextStartElement();//spriteBox;

    reader.readNextStartElement();//sprite
    QString tagName=reader.name().toString();

    while(!reader.atEnd() && tagName=="Sprite")
    {
        Sprite* sprite=new Sprite();

        reader.readNextStartElement();
        QString spriteName=reader.readElementText();
        sprite->setName(spriteName);

        reader.readNextStartElement();
        QString pictureName=reader.readElementText();
        sprite->setPictureName(pictureName);

        reader.readNextStartElement();
        int totalActionNumber=reader.readElementText().toInt();
        sprite->setTotalActionNumber(totalActionNumber);

        reader.readNextStartElement();//Action;
        for(int i=0;i<totalActionNumber;i++)
        {
            Action* action=new Action();

            reader.readNextStartElement();//ActionName;
            action->setName(reader.readElementText());

            reader.readNextStartElement();
            int frameDelay=reader.readElementText().toInt();
            action->setFrameDelay(frameDelay);

            reader.readNextStartElement();
            int frameTotal=reader.readNextStartElement();
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
                reader.readNextStartElement();//frame

                reader.readNextStartElement();
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

                action->addFrame(frame);
            }

            sprite->addAction(action);
        }

        this->addSprite(spriteName,sprite);

        reader.readNextStartElement();
    }
    file.close();
}

Sprite *SpriteManager::getSprite(const QString &spriteName)
{
    Sprite* s=spriteBox[spriteName]->clone();
    return s;
}
