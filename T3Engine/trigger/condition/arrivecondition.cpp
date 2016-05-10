#include "arrivecondition.h"
#include"collisiondetector.h"
#include"scene.h"
#include"charactermanager.h"
#include"decorationmanager.h"
#include"player.h"

ArriveCondition::ArriveCondition()
{

}

bool ArriveCondition::judge()
{
    //Character* character=CharacterManager::instance()->getCharacter(characterName);
    //if(character->getCurrentScene()==scene->getName())
    //{
    //    return CollisionDetector::isCollision(position,character);
    //}
    if(Player::instance()->getCurrentScene()==scene->getName())
    {
        return CollisionDetector::isCollision(Player::instance(),position);
    }
    return false;
}

void ArriveCondition::config(QXmlStreamReader *reader)
{
    reader->readNextStartElement();//<config>

    reader->readNextStartElement();//<characterName>;
    characterName=reader->readElementText();

    reader->readNextStartElement();//<x>
    float x=reader->readElementText().toFloat();

    reader->readNextStartElement();//<y>
    float y=reader->readElementText().toFloat();

    reader->readNextStartElement();//<width>
    float width=reader->readElementText().toFloat();

    reader->readNextStartElement();//<height>
    float height=reader->readElementText().toFloat();

    position=DecorationManager::instance()->getDecoration("empty");
    position->setX(x);
    position->setY(y);
    position->setWidth(width);
    position->setHeight(height);

    reader->readNextStartElement();//</config>
}

void ArriveCondition::save(QXmlStreamWriter *writer)
{
    writer->writeStartElement("Condition");

    writer->writeStartElement("ConditionType","Arrive");
    writer->writeStartElement("Config");

    writer->writeTextElement("characterName",characterName);
    writer->writeTextElement("x",QString::number(position->getX()));
    writer->writeTextElement("y",QString::number(position->getY()));
    writer->writeTextElement("width",QString::number(position->getWidth()));
    writer->writeTextElement("height",QString::number(position->getHeight()));

    writer->writeEndElement();

    writer->writeEndElement();
}

