#include "sentence.h"

Sentence::Sentence()
{

}
QString Sentence::getWord() const
{
    return word;
}

void Sentence::setWord(const QString &value)
{
    word = value;
}
QString Sentence::getFace() const
{
    return face;
}

void Sentence::setFace(const QString &value)
{
    face = value;
}




