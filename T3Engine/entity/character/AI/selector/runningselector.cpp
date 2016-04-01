#include "runningselector.h"

RunningSelector::RunningSelector()
{

}

bool RunningSelector::judge(Character *character)
{
    return character->isRunning();
}

