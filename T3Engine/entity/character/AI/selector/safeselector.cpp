#include "safeselector.h"
#include"scene.h"
#include"collisiondetector.h"

SafeSelector::SafeSelector()
{

}

bool SafeSelector::judge(Character *character)
{
    Scene* curScene=character->getScene();
    Character* player=curScene->getPlayer();

    return !CollisionDetector::inField(character->getAlarmField(),
                                      character->getX(),
                                      character->getY(),
                                      player->getX(),
                                      player->getY());
}

