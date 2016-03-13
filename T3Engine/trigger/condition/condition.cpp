#include "condition.h"
#include"timeupcondition.h"
#include"scene.h"

Condition::Condition()
{

}

Condition::~Condition()
{

}

Condition *Condition::getCondition(const QString &type)
{
    if(type=="TimeUp")
    {
        TimeUpCondition* condition=new TimeUpCondition();
        return condition;
    }
    else
    {
        qDebug()<<"unknow condition type:"<<type<<endl;
        return NULL;
    }
}
Scene *Condition::getScene() const
{
    return scene;
}

void Condition::setScene(Scene *value)
{
    scene = value;
}


