#ifndef SPRITEMANAGER_H
#define SPRITEMANAGER_H

#include<QXmlStreamReader>
#include<QMap>
#include"T3Engine/sprite/sprite.h"
#include"T3Engine/singleton.h"

class SpriteManager:public Singleton<SpriteManager>
{
public:
    SpriteManager();
    void init();

    Sprite* getSprite(const QString& spriteName);
    void addSprite(const QString& spriteName,Sprite* sp){spriteBox.insert(spriteName,sp);}
protected:
    QMap<QString,Sprite*> spriteBox;
    QXmlStreamReader reader;

};

#endif // SPRITEMANAGER_H
