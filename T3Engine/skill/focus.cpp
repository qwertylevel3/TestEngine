#include "focus.h"
#include"decorationmanager.h"
#include"scenemanager.h"

Focus::Focus(Character* c)
    :Skill(c)
{

}



void Focus::start(InputModule::Command c)
{
    Decoration* focus=DecorationManager::instance()->getDecoration("targetCircle");
}

void Focus::end(InputModule::Command c)
{

}

void Focus::run()
{

}
