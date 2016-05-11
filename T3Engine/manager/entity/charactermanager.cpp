#include "charactermanager.h"
#include"stable.h"
#include"gameconfigurator.h"

CharacterManager::CharacterManager()
{

}

void CharacterManager::init()
{
    QString fileName=GameConfigurator::instance()->getCharacterConfigFileName();
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

void CharacterManager::destroy()
{
    QMap<QString,Character*>::iterator i=characterBox.begin();
    while(i!=characterBox.end())
    {
        delete i.value();
        i++;
    }
}

Character *CharacterManager::getCharacter(const QString &characterName)
{
    return characterBox[characterName];
}

QMap<QString, Character *> &CharacterManager::getCharacterBox()
{
    return characterBox;
}


Character *CharacterManager::makeCharacter()
{
    reader.readNextStartElement();//<Character>

    reader.readNextStartElement();//<Name>
    QString name=reader.readElementText();

    reader.readNextStartElement();//<SpriteName>
    QString spriteName=reader.readElementText();

    reader.readNextStartElement();//<currentScene>
    QString currentScene=reader.readElementText();

    reader.readNextStartElement();//<x>
    int x=reader.readElementText().toInt();

    reader.readNextStartElement();//<y>
    int y=reader.readElementText().toInt();

    reader.readNextStartElement();//<HP>
    int HP=reader.readElementText().toInt();

    reader.readNextStartElement();//<MP>
    int MP=reader.readElementText().toInt();

    reader.readNextStartElement();//<CurrentHP>
    int currentHP=reader.readElementText().toInt();

    reader.readNextStartElement();//<CurrentMP>
    int currentMP=reader.readElementText().toInt();

    reader.readNextStartElement();//<speed>
    float speed=reader.readElementText().toFloat();

    reader.readNextStartElement();//<heartRate>
    int heartRate=reader.readElementText().toInt();

    reader.readNextStartElement();//</Character>

    Character* character=new Character(spriteName);
    character->setName(name);
    character->setCurrentScene(currentScene);
    character->setX(x);
    character->setY(y);
    character->setHP(HP);
    character->setMP(MP);
    character->setCurrentHP(currentHP);
    character->setCurrentMP(currentMP);
    character->setSpeed(speed);
    character->setHeartRate(heartRate);
    return character;
}

