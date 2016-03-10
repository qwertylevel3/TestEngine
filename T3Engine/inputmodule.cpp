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

    runningList[up]=false;
    runningList[down]=false;
    runningList[left]=false;
    runningList[right]=false;
    runningList[A_C]=false;
    runningList[B_C]=false;
    runningList[C_C]=false;
    runningList[D_C]=false;
    runningList[E_C]=false;
    runningList[F_C]=false;
    runningList[enter]=false;

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
    if(entity)
    {
        shutdownAllCommand();
    }
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
        runningList[keyMap[e->key()]]=true;
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
        runningList[keyMap[e->key()]]=false;
        entity->endCommand(keyMap[e->key()]);
    }
}

void InputModule::shutdownAllCommand()
{
    QMap<Command,bool>::const_iterator i=runningList.constBegin();
    while(i!=runningList.constEnd())
    {
        if(i.value())
        {
            entity->endCommand(i.key());
        }
        i++;
    }
}
