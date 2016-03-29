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

    Sprite* getCharacterSprite(const QString& spriteName);

    void addSprite(Sprite* sp)
    {
        spriteBox.insert(sp->getName(),sp);
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
    Animatioin* makeAction();
    Frame* makeFrame();
    QRectF makeRect();

};

#endif // SPRITEMANAGER_H
