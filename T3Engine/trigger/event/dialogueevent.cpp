#include "dialogueevent.h"
#include"dialogmanager.h"

DialogueEvent::DialogueEvent()
{

}

void DialogueEvent::run()
{
    Dialog* dialog=DialogManager::instance()->getDialog(dialogName);
    dialog->setScene(scene);
    scene->switchFocusToDialog(dialog);
    scene->addDialogToScene(dialog);
}

void DialogueEvent::setScene(Scene *value)
{
    scene = value;
}
void DialogueEvent::setDialogName(const QString &value)
{
    dialogName = value;
}



