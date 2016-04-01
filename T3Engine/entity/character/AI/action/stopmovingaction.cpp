#include "stopmovingaction.h"

StopMovingAction::StopMovingAction()
{

}

void StopMovingAction::run(Character *character)
{
    character->stopMoving();
}

