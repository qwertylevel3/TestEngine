#include "dialogueevent.h"

DialogueEvent::DialogueEvent()
{

}

void DialogueEvent::run()
{
    qDebug()<<"run"<<endl;
}
void DialogueEvent::setScene(Scene *value)
{
    scene = value;
}

void DialogueEvent::addContent(QString content)
{
    dialogueContent.push_back(content);
}


