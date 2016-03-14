#include "background.h"

Background::Background(const QString &spriteName)
    :Entity(spriteName)
{
    sprite=SpriteManager::instance()->getBackgroundSprite(spriteName);
}

Background *Background::clone()
{
    Background* newBK=new Background(this->getSpriteName());
    newBK->setName(this->name);
    return newBK;
}

