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
    Sprite* getTerrainSprite(const QString& spriteName);
    Sprite* getDecorationSprite(const QString& spriteName);
    Sprite* getDialogSprite(const QString& spriteName);
    Sprite* getFaceSprite(const QString& spriteName);
    Sprite* getBulletSprite(const QString& spriteName);

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
    void makeCharacterSprite();
    void makeBulletSprite();
    void makeDecorationSprite();
    void makeDialogSprite();
    void makeFaceSprite();
    void makeTerrainSprite();

    QMap<QString,Sprite*> spriteBox;

    QMap<QString,Sprite*> characterSpriteBox;
    QMap<QString,Sprite*> bulletSpriteBox;
    QMap<QString,Sprite*> decorationSpriteBox;
    QMap<QString,Sprite*> dialogSpriteBox;
    QMap<QString,Sprite*> faceSpriteBox;
    QMap<QString,Sprite*> terrainSpriteBox;

    QXmlStreamReader reader;
    QXmlStreamWriter writer;

    Sprite* makeSprite();
    Action* makeAction();
    Frame* makeFrame();
    QRectF makeRect();

};

#endif // SPRITEMANAGER_H
