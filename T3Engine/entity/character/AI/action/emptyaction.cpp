#include "emptyaction.h"

EmptyAction::EmptyAction()
{

}

void EmptyAction::run(Character *character)
{
    character->endCommand(character->getCurrentCommand());
}

