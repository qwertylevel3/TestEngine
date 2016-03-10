#ifndef SPRITEMANAGER_H
#define SPRITEMANAGER_H

#include"stable.h"
#include"sprite.h"

class SpriteManager:public Singleton<SpriteManager>
{
public:
    SpriteManager();
    void init();

    Sprite* getSprite(const QString& spriteName);
    void addSprite(const QString& spriteName,Sprite* sp)
    {
        spriteBox.insert(spriteName,sp);
    }

    QMap<QString ,Sprite*>& getSpriteBox()
    {
        return spriteBox;
    }

    void write();
    void writeSprite();
    int getTotalSpriteNumber()
    {
        return spriteBox.size();
    }

protected:
    void makeDifSprite();

    QMap<QString,Sprite*> spriteBox;

    QXmlStreamReader reader;
    QXmlStreamWriter writer;

    Sprite* makeSprite();
    Action* makeAction();
    Frame* makeFrame();
    QRectF makeRect();

};

#endif // SPRITEMANAGER_H
