#include "dialogueevent.h"
#include"dialogmanager.h"

DialogueEvent::DialogueEvent()
{

}

void DialogueEvent::config(QXmlStreamReader *reader)
{
    reader->readNextStartElement();//<config>

    reader->readNextStartElement();//<dialogName>
    this->setDialogName(reader->readElementText());

    reader->readNextStartElement();//</config>
}

void DialogueEvent::run()
{
    Dialog* dialog=DialogManager::instance()->getDialog(dialogName);
    dialog->setScene(scene);
    scene->switchFocusToDialog(dialog);
    scene->addDialogToScene(dialog);
    scene->setPause(true);
}

void DialogueEvent::setDialogName(const QString &value)
{
    dialogName = value;
}

void DialogueEvent::save(QXmlStreamWriter *writer)
{
    writer->writeStartElement("Event");

    writer->writeTextElement("EventType","Dialog");
    writer->writeStartElement("Config");

    writer->writeTextElement("DialogName",dialogName);

    writer->writeEndElement();

    writer->writeEndElement();
}



