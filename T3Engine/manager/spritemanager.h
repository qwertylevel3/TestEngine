#ifndef SPRITEMANAGER_H
#define SPRITEMANAGER_H


#include"sprite.h"

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

    Sprite* makeSprite();
    Action* makeAction();
    Frame* makeFrame();
    QRectF makeRect();

};

#endif // SPRITEMANAGER_H
