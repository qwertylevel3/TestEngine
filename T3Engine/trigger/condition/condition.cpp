#include "condition.h"
#include"timeupcondition.h"
#include"arrivecondition.h"
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
    if(type=="Arrive")
    {
        ArriveCondition* condition=new ArriveCondition();
        return condition;
    }
    else
    {
        qDebug()<<"unknow condition type:"<<type<<endl;
        exit(0);
    }
    exit(0);
}

Scene *Condition::getScene() const
{
    return scene;
}

void Condition::setScene(Scene *value)
{
    scene = value;
}


