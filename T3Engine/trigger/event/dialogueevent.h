#ifndef DIALOGUEEVENT_H
#define DIALOGUEEVENT_H

#include"event.h"
#include"scene.h"
#include"decoration.h"
#include"dialog.h"

class DialogueEvent:public Event
{
public:
    DialogueEvent();
    virtual void run();
    void setScene(Scene *value);

    void setDialogName(const QString &value);

protected:
    Scene* scene;
    QString dialogName;
};

#endif // DIALOGUEEVENT_H
