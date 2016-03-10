#include "dialogmanager.h"

DialogManager::DialogManager()
{

}

void DialogManager::init()
{
    QString fileName=GameConfigurator::instance()->getDialogConfigFileName();
    QString path=QDir::currentPath()+QDir::separator()+fileName;

    QFile file(path);

    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        qDebug()<<"can not open "<<fileName<<endl;
        return ;
    }
    reader.setDevice(&file);

    reader.readNextStartElement();//<DialogBox>

    reader.readNextStartElement();//<TotalDialogNumber>
    int totalDialogNumber=reader.readElementText().toInt();

    for(int i=0;i<totalDialogNumber;i++)
    {
        Dialog* dialog=makeDialog();

        addDialog(dialog->getName(),dialog);
    }
    file.close();
}

Dialog *DialogManager::getDialog(const QString &dialogName)
{
    return dialogBox[dialogName]->clone();
}

void DialogManager::addDialog(const QString &dialogName, Dialog *dialog)
{
    dialogBox.insert(dialogName,dialog);
}

Dialog *DialogManager::makeDialog()
{
    reader.readNextStartElement();//<dialog>

    reader.readNextStartElement();//<dialogName>
    QString dialogName=reader.readElementText();

    reader.readNextStartElement();//<spriteName>
    QString spriteName=reader.readElementText();

    Dialog* dialog=new Dialog(spriteName);

    reader.readNextStartElement();//<sentenceNumber>
    int sentenceNumber=reader.readElementText().toInt();

    dialog->setName(dialogName);
    for(int i=0;i<sentenceNumber;i++)
    {
        Sentence* sentence=makeSentence();

        dialog->addSentence(sentence);
    }

    reader.readNextStartElement();//</dialog>
    return dialog;
}

Sentence *DialogManager::makeSentence()
{
    reader.readNextStartElement();//<Sentence>

    reader.readNextStartElement();//<face>
    QString face=reader.readElementText();

    reader.readNextStartElement();//<word>
    QString word=reader.readElementText();


    Sentence* sentence=new Sentence();
    sentence->setFace(face);
    sentence->setWord(word);

    reader.readNextStartElement();//</Sentence>

    return sentence;
}

