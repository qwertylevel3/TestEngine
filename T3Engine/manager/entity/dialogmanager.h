#ifndef DIALOGMANAGER_H
#define DIALOGMANAGER_H

#include"dialog.h"

class DialogManager:public Singleton<DialogManager>
{
public:
    DialogManager();
    void init();
    void destroy();

    Dialog* getDialog(const QString& dialogName);
    void addDialog(const QString& dialogName,Dialog* dialog);
protected:
    QMap<QString,Dialog*> dialogBox;
    QXmlStreamReader reader;

    Dialog* makeDialog();
    Sentence* makeSentence();
};

#endif // DIALOGMANAGER_H
