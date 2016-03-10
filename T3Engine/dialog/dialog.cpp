#include "dialog.h"
#include"facemanager.h"
#include"scene.h"

Dialog::Dialog(const QString &spriteName)
    :Entity(spriteName)
{
    currentSentence=0;
    this->setZ(-5);
    this->setY(-1.4);
}

void Dialog::startCommand(InputModule::Command c)
{
    if(c==InputModule::enter)
    {
        currentSentence++;
        if(currentSentence>=sentenceList.size())
        {
            this->setState(DEAD);

            scene->switchFocusToPlayer();
            return;
        }
    }
}

void Dialog::draw()
{

    QString currentFace=sentenceList[currentSentence]->getFace();
    Face* face=FaceManager::instance()->getFace(currentFace);
    face->setZ(-6);
    face->draw();

    this->setText(sentenceList[currentSentence]->getWord());
    Entity::draw();

}

void Dialog::addSentence(Sentence *sentence)
{
    sentenceList.push_back(sentence);
}
Scene *Dialog::getScene() const
{
    return scene;
}

void Dialog::setScene(Scene *value)
{
    scene = value;
}
