#ifndef GAMECONFIGURATOR_H
#define GAMECONFIGURATOR_H

#include"singleton.h"

class GameConfigurator :public Singleton<GameConfigurator>
{
public:
    GameConfigurator();

    void init();

    float getScale(){return scale;}
    int getWindowWidth(){return windowWidth;}
    int getWindowHeight(){return windowHeight;}
    QSurfaceFormat getQSurfaceFormat(){return format;}
    QString getSpriteConfigFileName() const
    {
        return spriteConfigFileName;
    }
    void setSpriteConfigFileName(const QString &value)
    {
        spriteConfigFileName = value;
    }

    QString getCharacterConfigFileName() const
    {
        return characterConfigFileName;
    }
    void setCharacterConfigFileName(const QString &value)
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

    int getPaintNear() const
    {
        return paintNear;
    }
    void setPaintNear(float value)
    {
        paintNear = value;
    }

    int getPaintFar() const
    {
        return paintFar;
    }
    void setPaintFar(float value)
    {
        paintFar = value;
    }

    bool getDrawRect() const
    {
        return drawRect;
    }
    void setDrawRect(bool value)
    {
        drawRect = value;
    }

    QString getBulletConfigFileName() const
    {
        return bulletConfigFileName;
    }
    void setBulletConfigFileName(const QString &value)
    {
        bulletConfigFileName = value;
    }

    QString getSceneConfigFileName() const;
    void setSceneConfigFileName(const QString &value);

protected:
    float scale;//绘制时缩放比例,值越大越小。。
    bool drawRect;
    int windowWidth;
    int windowHeight;
    int paintNear;
    int paintFar;
    QSurfaceFormat format;
    QString spriteConfigFileName;
    QString characterConfigFileName;
    QString terrainConfigFileName;
    QString decorationConfigFileName;
    QString bulletConfigFileName;
    QString SceneConfigFileName;
};

#endif // GAMECONFIGURATOR_H
