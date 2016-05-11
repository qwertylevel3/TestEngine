#ifndef DECORATIONMANAGER_H
#define DECORATIONMANAGER_H


#include"decoration.h"

class DecorationManager:public Singleton<DecorationManager>
{
public:
    DecorationManager();
    void init();
    void destroy();

    Decoration* getDecoration(const QString& decorationName);
    void addDecoration(const QString& decorationName,Decoration* decoration){decorationBox.insert(decorationName,decoration);}
    QMap<QString,Decoration*>& getDecorationBox();
protected:
    QMap<QString,Decoration*> decorationBox;
    QXmlStreamReader reader;

    Decoration* makeDecoration();
};

#endif // DECORATIONMANAGER_H
