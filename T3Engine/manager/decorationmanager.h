#ifndef DECORATIONMANAGER_H
#define DECORATIONMANAGER_H

#include"T3Engine/singleton.h"
#include<QMap>
#include<QXmlStreamReader>
#include<T3Engine/entity/decoration/decoration.h>

class DecorationManager:public Singleton<DecorationManager>
{
public:
    DecorationManager();
    void init();

    Decoration* getDecoration(const QString& decorationName);
    void addDecoration(const QString& decorationName,Decoration* decoration){decorationBox.insert(decorationName,decoration);}
protected:
    QMap<QString,Decoration*> decorationBox;
    QXmlStreamReader reader;

    Decoration* makeDecoration();
};

#endif // DECORATIONMANAGER_H
