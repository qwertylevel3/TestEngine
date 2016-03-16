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
    virtual void config(QXmlStreamReader* reader);
    virtual void run();

    void setDialogName(const QString &value);

    void save(QXmlStreamWriter *writer);
protected:
    QString dialogName;
};

#endif // DIALOGUEEVENT_H
