#ifndef SENTENCE_H
#define SENTENCE_H

#include"face.h"

class Sentence
{
public:
    Sentence();
    QString getWord() const;
    void setWord(const QString &value);

    QString getFace() const;
    void setFace(const QString &value);

protected:
    QString word;
    QString face;
};

#endif // SENTENCE_H
