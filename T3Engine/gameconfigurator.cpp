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
    spriteConfigFileName="conf/test.xml";
    characterConfigFileName="conf/character.xml";
    terrainConfigFileName="conf/terrain.xml";
    decorationConfigFileName="conf/decoration.xml";
    bulletConfigFileName="conf/bullet.xml";
    SceneConfigFileName="conf/scene.xml";

    //format.setSamples(16);
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









