#ifndef GAMECONFIGURATOR_H
#define GAMECONFIGURATOR_H

#include"T3Engine/singleton.h"
#include<QSurfaceFormat>
#include<QString>

class GameConfigurator :public Singleton<GameConfigurator>
{
public:
    GameConfigurator();

    void init();

    float getScale(){return scale;}
    int getWindowWidth(){return windowWidth;}
    int getWindowHeight(){return windowHeight;}
    QSurfaceFormat getQSurfaceFormat(){return format;}
    QString getSpriteConfiguratorName() const
    {
        return spriteConfiguratorName;
    }
    void setSpriteConfiguratorName(const QString &value)
    {
        spriteConfiguratorName = value;
    }

    QString getCharacterConfiguratorName() const
    {
        return characterConfiguratorName;
    }
    void setCharacterConfiguratorName(const QString &value)
    {
        characterConfiguratorName = value;
    }

protected:
    float scale;//绘制时缩放比例,值越大越小。。
    int windowWidth;
    int windowHeight;
    QSurfaceFormat format;
    QString spriteConfiguratorName;
    QString characterConfiguratorName;
};

#endif // GAMECONFIGURATOR_H
