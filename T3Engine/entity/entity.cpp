#include "entity.h"


Entity::Entity(const QString &spriteName)
{
    this->spriteName=spriteName;
    sprite=SpriteManager::instance()->getSprite(spriteName);
}

Entity::~Entity()
{
    if(sprite)
    {
        delete sprite;
    }
}

void Entity::update()
{
    sprite->update();
}


