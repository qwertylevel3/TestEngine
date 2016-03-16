#ifndef CONDITION_H
#define CONDITION_H

#include"stable.h"

class Scene;

class Condition
{
public:
    Condition();
    virtual ~Condition();
    static Condition* getCondition(const QString& type);
    virtual void config(QXmlStreamReader * reader)=0;
    virtual bool judge()=0;
    Scene *getScene() const;
    void setScene(Scene *value);

    virtual void save(QXmlStreamWriter* writer)=0;
protected:
    Scene* scene;
};

#endif // CONDITION_H
