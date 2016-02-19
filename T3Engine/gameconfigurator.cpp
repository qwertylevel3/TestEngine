#include "gameconfigurator.h"

GameConfigurator::GameConfigurator()
{

}

void GameConfigurator::init()
{
    scale=200;
    drawRect=true;
    paintNear=3;
    paintFar=20;
    windowWidth=800;
    windowHeight=600;
    spriteConfigFileName="test.xml";
    characterConfigFileName="character.xml";
    terrainConfigFileName="terrain.xml";
    decorationConfigFileName="decoration.xml";
    bulletConfigFileName="bullet.xml";
    SceneConfigFileName="scene.xml";

    format.setSamples(16);
    format.setDepthBufferSize(24);
    QSurfaceFormat::setDefaultFormat(format);
}
QString GameConfigurator::getSceneConfigFileName() const
{
    return SceneConfigFileName;
}

void GameConfigurator::setSceneConfigFileName(const QString &value)
{
    SceneConfigFileName = value;
}









