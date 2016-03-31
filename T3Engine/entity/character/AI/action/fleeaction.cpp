#include "fleeaction.h"
#include"scene.h"

FleeAction::FleeAction()
{

}

void FleeAction::run(Character *character)
{
        Scene* curScene=character->getScene();

        Character* player=curScene->getPlayer();

        if(player->getX()>character->getX())
        {
            character->startCommand(InputModule::left);
        }
        else
        {
            character->startCommand(InputModule::right);
        }


    //    if(player->getY()>character->getY())
    //    {
    //        character->startCommand(InputModule::down);
    //    }
    //    else
    //    {
    //        character->startCommand(InputModule::up);
    //    }
}

