#ifndef DIALOGUEEVENT_H
#define DIALOGUEEVENT_H

#include"event.h"
#include"scene.h"
#include"decoration.h"

class DialogueEvent:public Event
{
public:
    DialogueEvent();
    virtual void run();
    void setScene(Scene *value);
    void addContent(QString content);
protected:
    Scene* scene;
    QList<QString> dialogueContent;
};

#endif // DIALOGUEEVENT_H
