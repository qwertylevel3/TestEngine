#include "wander.h"
#include"inputmodule.h"
#include"character.h"

Wander::Wander(Character* c)
    :AI(c)
{

}

void Wander::update()
{
    if(character->isHeartAlarm())
    {
        character->clearHeartAlarm();
        character->endCommand(currentCommand);
        int num=qrand()%4;
        switch(num)
        {
        case 0:
            character->startCommand(InputModule::up);
            currentCommand=InputModule::up;
            break;
        case 1:
            character->startCommand(InputModule::down);
            currentCommand=InputModule::down;
            break;
        case 2:
            character->startCommand(InputModule::left);
            currentCommand=InputModule::left;
            break;
        case 3:
            character->startCommand(InputModule::right);
            currentCommand=InputModule::right;
            break;
        case 5:
            character->startCommand(InputModule::enter);
            currentCommand=InputModule::enter;
            break;
        default:
            break;
        }
    }
}

