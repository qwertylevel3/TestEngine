#include "focus.h"
#include"decorationmanager.h"
#include"scenemanager.h"
#include"decoration.h"

Focus::Focus(Character* c)
    :Skill(c)
{

}



void Focus::start(InputModule::Command c)
{
    focus=DecorationManager::instance()->getDecoration("targetCircle");


}

void Focus::end(InputModule::Command c)
{

}

void Focus::run()
{

}
