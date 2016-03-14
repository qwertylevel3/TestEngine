#ifndef CHARACTERMANAGER_H
#define CHARACTERMANAGER_H

#include"character.h"

class CharacterManager:public Singleton<CharacterManager>
{
public:
    CharacterManager();
    void init();

    Character* getCharacter(const QString& characterName);
    void addCharacter(const QString& characterName,Character* character){characterBox.insert(characterName,character);}
    QMap<QString,Character*>& getCharacterBox();
protected:
    QMap<QString,Character*> characterBox;
    QXmlStreamReader reader;

    Character* makeCharacter();
};

#endif // CHARACTERMANAGER_H
