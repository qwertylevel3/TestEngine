#ifndef BACKGROUNDMANAGER_H
#define BACKGROUNDMANAGER_H

#include"background.h"

class BackgroundManager:public Singleton<BackgroundManager>
{
public:
    BackgroundManager();
    void init();
    void destroy();

    Background* getBackground(const QString& bkName);
    void addBackground(Background* bk);
    QMap<QString,Background*>& getBackgroundBox();
protected:
    QMap<QString,Background*> backgroundBox;

    QList<Background*> activeBox;
    QXmlStreamReader reader;

    Background* makeBackground();
};

#endif // BACKGROUNDMANAGER_H
