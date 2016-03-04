#include "focus.h"
#include"decorationmanager.h"
#include"scenemanager.h"
#include"decoration.h"

Focus::Focus(Character* c)
    :Skill(c)
{
    focus=NULL;
    focusIndex=-1;
}



void Focus::start(InputModule::Command c)
{
    Q_UNUSED(c)

    Scene* currentScene=character->getScene();
    QList<Character*>& characterBox=currentScene->getCharacterBox();

    if(focusIndex!=-1)
    {
        characterBox[focusIndex]->removeChild("focus");
    }
    if(focus)
    {
        delete focus;
    }

    focusIndex=chooseFocusCharacter();

    if(focusIndex!=-1)
    {
        focus=DecorationManager::instance()->getDecoration("targetCircle");
        characterBox[focusIndex]->addChild("focus",focus);
        focus->setWidth(characterBox[focusIndex]->getWidth());
    }
}

void Focus::end(InputModule::Command c)
{
    Q_UNUSED(c)
}

void Focus::run()
{

}

int Focus::chooseFocusCharacter()
{
    Scene* currentScene=character->getScene();
    QList<Character*>& characterBox=currentScene->getCharacterBox();

    if(characterBox.isEmpty())
    {
        return -1;
    }
    if(!focus)
    {
        return 0;
    }
    focusIndex++;
    if(focusIndex>=characterBox.size())
    {
        focusIndex=0;
    }

    int count=0;
    while(count<characterBox.size() &&
          !characterBox[(focusIndex+count)%characterBox.size()]->isAlive())
    {
        count++;
    }
    if(count==characterBox.size())
    {
        return -1;
    }
    return focusIndex+count;
}
