#include "dialog.h"
#include"facemanager.h"
#include"scene.h"

Dialog::Dialog(const QString &spriteName)
    :Entity(spriteName)
{
    sprite=SpriteManager::instance()->getDialogSprite(spriteName);
    currentSentence=0;
    this->setZ(-5);
    this->setY(-200);
}

Dialog::~Dialog()
{
    for(int i=0;i<sentenceList.size();i++)
    {
        delete sentenceList[i];
    }
    sentenceList.clear();
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
            scene->setPause(false);
            return;
        }
    }
}

void Dialog::draw()
{
    QString currentFace=sentenceList[currentSentence]->getFace();
    Face* face=FaceManager::instance()->getFace(currentFace);
    face->setZ(-6);
    face->setY(100);
    face->draw();

    this->setText(sentenceList[currentSentence]->getWord());
    Entity::draw();

}

Dialog* Dialog::clone()
{
    Dialog* newDialog=new Dialog(this->spriteName);

    for(int i=0;i<sentenceList.size();i++)
    {
        Sentence * sentence=new Sentence();
        sentence->setFace(sentenceList[i]->getFace());
        sentence->setWord(sentenceList[i]->getWord());
        newDialog->addSentence(sentence);
    }

    return newDialog;
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
