#include "dialogueevent.h"
#include"dialogmanager.h"

DialogueEvent::DialogueEvent()
{

}

void DialogueEvent::run()
{
    DialogManager::instance()->getDialog(dialogName)->setScene(scene);
    scene->switchFocusToDialog(DialogManager::instance()->getDialog(dialogName));
    scene->addDialogToScene(DialogManager::instance()->getDialog(dialogName));

}

void DialogueEvent::setScene(Scene *value)
{
    scene = value;
}
void DialogueEvent::setDialogName(const QString &value)
{
    dialogName = value;
}



