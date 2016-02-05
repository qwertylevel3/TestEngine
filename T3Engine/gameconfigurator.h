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
        return characterConfigFileName;
    }
    void setCharacterConfiguratorName(const QString &value)
    {
        characterConfigFileName = value;
    }

    QString getTerrainConfigFileName() const
    {
        return terrainConfigFileName;
    }
    void setTerrainConfigFileName(const QString &value)
    {
        terrainConfigFileName = value;
    }

    QString getDecorationConfigFileName() const
    {
        return decorationConfigFileName;
    }
    void setDecorationConfigFileName(const QString &value)
    {
        decorationConfigFileName = value;
    }

protected:
    float scale;//绘制时缩放比例,值越大越小。。
    int windowWidth;
    int windowHeight;
    QSurfaceFormat format;
    QString spriteConfiguratorName;
    QString characterConfigFileName;
    QString terrainConfigFileName;
    QString decorationConfigFileName;
};

#endif // GAMECONFIGURATOR_H
