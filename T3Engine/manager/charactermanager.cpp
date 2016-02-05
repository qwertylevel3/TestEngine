#include "charactermanager.h"
#include<QFile>
#include<QDir>
#include"T3Engine/gameconfigurator.h"

CharacterManager::CharacterManager()
{

}

void CharacterManager::init()
{
    QString fileName=GameConfigurator::instance()->getCharacterConfiguratorName();
    QString path=QDir::currentPath()+QDir::separator()+fileName;

    QFile file(path);

    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        qDebug()<<"can not open "<<fileName<<endl;
        return ;
    }
    reader.setDevice(&file);

    reader.readNextStartElement();//<CharacterBox>

    reader.readNextStartElement();//<TotalCharacterNumber>
    int totalCharacterNumber=reader.readElementText().toInt();

    for(int i=0;i<totalCharacterNumber;i++)
    {
        Character* character=makeCharacter();

        addCharacter(character->getName(),character);

    }
    file.close();
}

Character *CharacterManager::getCharacter(const QString &characterName)
{
    return characterBox[characterName]->clone();
}


Character *CharacterManager::makeCharacter()
{
    reader.readNextStartElement();//<Character>

    reader.readNextStartElement();//<Name>
    QString name=reader.readElementText();

    reader.readNextStartElement();//<SpriteName>
    QString spriteName=reader.readElementText();

    reader.readNextStartElement();//<HP>
    int HP=reader.readElementText().toInt();

    reader.readNextStartElement();//<MP>
    int MP=reader.readElementText().toInt();

    reader.readNextStartElement();//<CurrentHP>
    int currentHP=reader.readElementText().toInt();

    reader.readNextStartElement();//<CurrentMP>
    int currentMP=reader.readElementText().toInt();

    reader.readNextStartElement();//</Character>

    Character* character=new Character(spriteName);
    character->setName(name);
    character->setHP(HP);
    character->setMP(MP);
    character->setCurrentHP(currentHP);
    character->setCurrentMP(currentMP);
    return character;
}

