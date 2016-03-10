#include"inputmodule.h"
#include"entity.h"

InputModule::InputModule()
{
    keyMap[Qt::Key_W]=up;
    keyMap[Qt::Key_S]=down;
    keyMap[Qt::Key_A]=left;
    keyMap[Qt::Key_D]=right;
    keyMap[Qt::Key_T]=A_C;
    keyMap[Qt::Key_F]=B_C;
    keyMap[Qt::Key_H]=C_C;
    keyMap[Qt::Key_G]=D_C;
    keyMap[Qt::Key_R]=E_C;
    keyMap[Qt::Key_Y]=F_C;
    keyMap[Qt::Key_Enter]=enter;
    getInput=true;
    entity=0;
}

InputModule::~InputModule()
{

}

void InputModule::input(int key)
{
    if(getInput && keyMap.contains(key))
    {
        commandStack.push(keyMap[key]);
    }
}

InputModule::Command InputModule::getCommand()
{
    if(!commandStack.isEmpty())
    {
        return commandStack.top();
    }
    return enter;
}

InputModule::Command InputModule::popCommand()
{
    if(!commandStack.isEmpty())
    {
        return commandStack.pop();
    }
    return enter;
}

void InputModule::setEntity(Entity *e)
{
    entity=e;
}

void InputModule::keyPressEvent(QKeyEvent *e)
{
    if(e->isAutoRepeat())
    {
        //qDebug()<<"press repeat"<<endl;
        return ;
    }
    //this->input(e->key());
    if(entity)
    {
        entity->startCommand(keyMap[e->key()]);
    }
}

void InputModule::keyReleaseEvent(QKeyEvent *e)
{
    if(e->isAutoRepeat())
    {
        //qDebug()<<"release repeat"<<endl;
        return ;
    }
    if(entity)
    {
        entity->endCommand(keyMap[e->key()]);
    }
}
