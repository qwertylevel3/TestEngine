#ifndef CHARACTERMANAGER_H
#define CHARACTERMANAGER_H

#include"T3Engine/entity/character/character.h"
#include<QMap>
#include<QXmlStreamReader>
#include"T3Engine/singleton.h"

class CharacterManager:public Singleton<CharacterManager>
{
public:
    CharacterManager();
    void init();

    Character* getCharacter(const QString& characterName);
    void addCharacter(const QString& characterName,Character* character){characterBox.insert(characterName,character);}
protected:
    QMap<QString,Character*> characterBox;
    QXmlStreamReader reader;

    Character* makeCharacter();
};

#endif // CHARACTERMANAGER_H
