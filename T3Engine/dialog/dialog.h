#ifndef DIALOG_H
#define DIALOG_H

#include<entity.h>
#include"sentence.h"

class Dialog:public Entity
{
public:
    Dialog(const QString& spriteName);

    virtual void startCommand(InputModule::Command c);
    virtual void draw();

    void addSentence(Sentence *sentence);

    Scene *getScene() const;
    void setScene(Scene *value);

protected:
    Scene* scene;
    QList<Sentence*> sentenceList;
    int currentSentence;
};

#endif // DIALOG_H
